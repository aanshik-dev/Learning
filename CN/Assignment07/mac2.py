TYPE_NAMES = {
    0: "Management",
    1: "Control",
    2: "Data"
}

CONTROL_SUBTYPES = {
    11: "RTS",
    12: "CTS",
    13: "ACK"
}


def mac_address(data):
    return ":".join(f"{x:02X}" for x in data)


def decode(hexstr):
    # 08 01 2c 00
    # 00 1a 2b 3c 4d 5e
    # a4 83 e7 11 22 33
    # 00 50 56 aa bb cc
    # 30 1d
    # aa aa 03 00 00 00 08 00
    try:
        data = bytes.fromhex(hexstr)
    except ValueError:
        raise ValueError("Invalid hexadecimal input")

    if len(data) < 4:
        raise ValueError("Input is too short for Frame Control and Duration")

    # 08 01  =  00001000 00000001
    fc0 = data[0]
    fc1 = data[1]

    protocol_version = fc0 & 0x03
    frame_type = (fc0 >> 2) & 0x03
    subtype = (fc0 >> 4) & 0x0F


    type_name = TYPE_NAMES.get(frame_type, "Reserved")

    if frame_type == 1:
        subtype_name = CONTROL_SUBTYPES.get(
            subtype, f"Control subtype {subtype:04b}"
        )
    elif frame_type == 2:
        subtype_name = "Data" if subtype == 0 else f"Data subtype {subtype:04b}"
    else:
        subtype_name = f"Subtype {subtype:04b}"

    # 00000001
    flags = {
        "ToDS": bool(fc1 & (1 << 0)),
        "FromDS": bool(fc1 & (1 << 1)),
        "More Frag": bool(fc1 & (1 << 2)),
        "Retry": bool(fc1 & (1 << 3)),
        "Power Mgmt": bool(fc1 & (1 << 4)),
        "More Data": bool(fc1 & (1 << 5)),
        "Protected": bool(fc1 & (1 << 6)),
        "Order": bool(fc1 & (1 << 7))
    }

    duration = int.from_bytes(data[2:4], byteorder="little")

    result = {
        "type": type_name,
        "subtype": subtype_name,
        "protocol_version": protocol_version,
        "flags": flags,
        "duration_us": duration,
        "addresses": [],
        "sequence": None,
        "fragment": None,
        "ethertype": None
    }

    # Determine number of addresses
    if frame_type == 1:
        if subtype == 11:       # RTS
            address_count = 2
        elif subtype in (12, 13):   # CTS / ACK
            address_count = 1
        else:
            address_count = 0
    elif frame_type == 2:
        if flags["ToDS"] and flags["FromDS"]:
            address_count = 4
        else:
            address_count = 3
    else:
        address_count = 3

    header_length = 4 + (6 * address_count)

    # Data and management frames have Sequence Control.
    # CTS/ACK/RTS do not
    has_sequence = not (frame_type == 1)

    if has_sequence:
        header_length += 2

    if len(data) < header_length:
        raise ValueError(
            f"Input is too short for this {type_name} frame header"
        )

    # Read addresses
    addresses = []
    offset = 4
    for i in range(address_count):
        address = mac_address(data[offset:offset + 6])
        addresses.append(address)
        offset += 6

    # Assign address roles
    if frame_type == 2:
        to_ds = flags["ToDS"]
        from_ds = flags["FromDS"]

        if not to_ds and not from_ds:
            roles = ["RA/DA", "TA/SA", "BSSID"]
        elif to_ds and not from_ds:
            roles = ["RA", "TA/SA", "DA"]
        elif not to_ds and from_ds:
            roles = ["RA/DA", "TA/BSSID", "SA"]
        else:
            roles = ["RA", "TA", "DA", "SA"]

    elif frame_type == 1:
        if subtype == 11:
            roles = ["RA", "TA"]
        elif subtype in (12, 13):
            roles = ["RA"]
        else:
            roles = [f"Address {i + 1}" for i in range(address_count)]

    else:
        roles = ["RA/DA", "TA/SA", "BSSID"]

    for address, role in zip(addresses, roles):
        result["addresses"].append({
            "address": address,
            "role": role
        })

    # Sequence Control
    if has_sequence:
        sequence_control = int.from_bytes(
            data[offset:offset + 2],
            byteorder="little"
        )

        result["sequence"] = sequence_control >> 4
        result["fragment"] = sequence_control & 0x0F

        offset += 2

    # LLC/SNAP and EtherType
    if frame_type == 2:
        if len(data) >= offset + 8:
            llc = data[offset:offset + 8]
            # SNAP header:
            # AA AA 03 00 00 00
            if llc[0:6] == bytes.fromhex("AA AA 03 00 00 00"):
                ether_type = int.from_bytes(
                    llc[6:8],
                    byteorder="big"
                )
                result["ethertype"] = f"0x{ether_type:04X}"

    return result


def print_summary(name, result):
    print("-" * 60)
    print(name)
    print("-" * 60)

    print(f"Protocol Version: {result['protocol_version']}")
    print(f"Type            : {result['type']}")
    print(f"Subtype         : {result['subtype']}")

    print("\nFlags:")
    for flag, value in result["flags"].items():
        if value:
            print(f"  {flag}: 1")
    if not any(result["flags"].values()):
        print("  None")

    print(f"\nDuration        : {result['duration_us']} µs")

    print("\nAddresses:")
    for item in result["addresses"]:
        print(f"  {item['role']:<8}: {item['address']}")

    if result["sequence"] is not None:
        print(f"\nSequence Number : {result['sequence']}")
        print(f"Fragment Number : {result['fragment']}")

    if result["ethertype"] is not None:
        print(f"EtherType       : {result['ethertype']}")
    print()


frames = {
    "F1": """
    08 01 2c 00
    00 1a 2b 3c 4d 5e
    a4 83 e7 11 22 33
    00 50 56 aa bb cc
    30 1d
    aa aa 03 00 00 00 08 00
    """,

    "F2": """
    08 0a 2c 00
    a4 83 e7 11 22 33
    00 1a 2b 3c 4d 5e
    00 50 56 aa bb cc
    40 1d
    aa aa 03 00 00 00 08 00
    """,

    "F3": """
    b4 00 5e 01
    00 1a 2b 3c 4d 5e
    a4 83 e7 11 22 33
    """,

    "F4": """
    c4 00 44 01
    a4 83 e7 11 22 33
    """,

    "F5": """
    d4 00 00 00
    a4 83 e7 11 22 33
    """,

    "F6": """
    08 07 2c 00
    02 11 22 33 44 55
    02 66 77 88 99 aa
    00 50 56 aa bb cc
    51 1d
    a4 83 e7 11 22 33
    aa aa 03 00 00 00 08 00
    """
}


for name, hexstr in frames.items():
    result = decode(hexstr)
    print_summary(name, result)




# F1: 08 01 2c 00 --> 00001000 00000001 00101100 00000000 -> Data / Data

# F2: 08 0a 2c 00 --> 00001000 00001010 00101100 00000000 -> Data / Data

# F3: b4 00 5e 01 --> 10110100 00000000 01011110 00000001 -> Control / RTS

# F4: c4 00 44 01 --> 11000100 00000000 01000100 00000001

# F5: d4 00 00 00 --> 11010100 00000000 00000000 00000000

# F6: 08 07 2c 00 --> 00001000 00000111 00101100 00000000