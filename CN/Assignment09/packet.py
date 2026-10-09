# Part B: IPv4 Header Checksum Verification
def verify_ip_checksum(header):
    stored = (header[10] << 8) | header[11]

    # sum all 16 bit word
    total = 0
    for i in range(0, len(header), 2):
        word = (header[i] << 8) | header[i + 1]
        total += word

    # carries
    while total >> 16:
        total = (total & 0xFFFF) + (total >> 16)

    # if header is valid then all 1s
    valid = (total == 0xFFFF)

    # subtract stored checksum contribution and recompute
    total_without = 0
    for i in range(0, len(header), 2):
        if i == 10:
            continue  # skip checksum field
        word = (header[i] << 8) | header[i + 1]
        total_without += word

    while total_without >> 16:
        total_without = (total_without & 0xFFFF) + (total_without >> 16)

    computed = (~total_without) & 0xFFFF

    return stored, computed, valid


# Part C: Fragment Reassembly
def reassemble(fragments):
    # fragments: list of (offset_units, more_fragments_flag, payload_length)
    ranges = []
    for offset_units, mf, payload_len in fragments:
        start = offset_units * 8
        end = start + payload_len - 1
        ranges.append((start, end))

    # total length = end of last byte + 1
    total_length = max(end for _, end in ranges) + 1

    # complete if ranges cover 0..total_length-1 with no gaps and last fragment has MF=0
    sorted_frags = sorted(zip(fragments, ranges), key=lambda x: x[1][0])
    expected = 0
    complete = True
    for (offset_units, mf, payload_len), (start, end) in sorted_frags:
        if start != expected:
            complete = False
            break
        expected = end + 1

    # last fragment must have MF=0
    last_frag = sorted_frags[-1][0]
    if last_frag[1] != 0:
        complete = False

    return ranges, total_length, complete


# Part B
print("\nPart B: Header Checksum Verification")
print("-" * 50)
# 8 -> TTL and 10 - 11 -> Checksum
clean_header = [
    0x45, 0x00, 0x00, 0x28, 0x1C, 0x46, 0x00, 0x00, 0x40, 0x11, 0xDB, 0x10, 0xC0, 0xA8, 0x01, 0x0A, 0xC0, 0xA8, 0x01, 0x14
]
corrupted_header = [
    0x45, 0x00, 0x00, 0x28, 0x1C, 0x46, 0x00, 0x00, 0x3F, 0x11, 0xDB, 0x10, 0xC0, 0xA8, 0x01, 0x0A, 0xC0, 0xA8, 0x01, 0x14
]

stored, computed, valid = verify_ip_checksum(clean_header)
print(f"\nClean header:")
print(f"  Stored checksum:   0x{stored:04X}")
print(f"  Computed checksum: 0x{computed:04X}")
print(f"  Valid: {valid}")

stored, computed, valid = verify_ip_checksum(corrupted_header)
print(f"\nCorrupted header (TTL 0x40 -> 0x3F):")
print(f"  Stored checksum:   0x{stored:04X}")
print(f"  Computed checksum: 0x{computed:04X}")
print(f"  Valid: {valid}")

# Part C
print("\n" + "=" * 50)
print("Part C: Fragment Reassembly")
print("=" * 50)

# (offset_units, more_fragments_flag, payload_length)
fragments = [
    (0, 1, 1480),
    (185, 1, 1480),
    (370, 0, 40)
]

ranges, total_length, complete = reassemble(fragments)

print(f"\nFragment details (ID = 0x4A3F):")
for i, ((off, mf, plen), (start, end)) in enumerate(zip(fragments, ranges)):
    print(f"  Fragment {i + 1}: offset={off} units, MF={mf}, payload={plen} bytes -> bytes {start} to {end}")

print(f"\nTotal reassembled length: {total_length} bytes")
print(f"Datagram complete: {complete}")
