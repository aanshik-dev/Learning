import random

FLAG = 0x7E
ESC = 0x7D

def show(data):
    return " ".join(f"{x:02X}" for x in data)

def transmit(frame_bytes, corruptions):
    data = frame_bytes[:]
    for index, value in corruptions:
        if 0 <= index < len(data):
            data[index] = value
    return data

def byteCount(payload):
    return [len(payload)] + payload

def recoverByteCount(stream):
    result = []
    i = 0
    while i < len(stream):
        length = stream[i]
        i += 1

        if i + length > len(stream):
            result.append(stream[i:])
            break
        result.append(stream[i:i + length])
        i += length
    return result

pLoad1 = [0x11, 0x22, 0x33]
pLoad2 = [0xAA]
stream = byteCount(pLoad1) + byteCount(pLoad2)
received = transmit(stream, [])

print("PART A")
print("Data:", show(pLoad1) +" , "+ show(pLoad2))
print("Transmitted:", show(stream))
print("Clean Received:", show(received))
print("Recovered:", [show(x) for x in recoverByteCount(received)])

received = transmit(stream, [(0, 0x05)])
print("Corrupted Received:", show(received))
print("Recovered:", [show(x) for x in recoverByteCount(received)])

def byteStuff(payload):
    result = [FLAG]
    for byte in payload:
        if byte == FLAG or byte == ESC:
            result.append(ESC)
        result.append(byte)
    result.append(FLAG)

    return result

def recoverByteStuff(frame):
    result = []
    i = 1
    while i < len(frame) - 1:
        if frame[i] == ESC:
            i += 1
        result.append(frame[i])
        i += 1
    return result

print()
print("PART B")

tests = [[0x11, 0x22],[0x7E],[0x7D],[0x7D, 0x7E]]

for payload in tests:
    framed = byteStuff(payload)
    received = transmit(framed, [])
    recovered = recoverByteStuff(received)
    print("Data:", show(payload))
    print("Transmitted:", show(framed))
    print("Recovered:", show(recovered))

def byte2Bits(byte):
    bits = []
    for i in range(7, -1, -1):
        bits.append((byte >> i) & 1)
    return bits

def bits2Bytes(bits):
    result = []
    for i in range(0, len(bits), 8):
        byte = 0
        for j in range(8):
            byte <<= 1
            if i + j < len(bits):
                byte |= bits[i + j]
        result.append(byte)
    return result

def bitStuff(payload):
    bits = []
    count = 0
    for byte in payload:
        for bit in byte2Bits(byte):
            bits.append(bit)

            if bit == 1:
                count += 1
                if count == 5:
                    bits.append(0)
                    count = 0
            else:
                count = 0
    return bits2Bytes(bits), len(bits)


def bitUnstuff(stuffed_bytes, bit_length):
    bits = []
    for byte in stuffed_bytes:
        bits.extend(byte2Bits(byte))
    bits = bits[:bit_length]
    result = []
    count = 0
    i = 0
    while i < len(bits):
        bit = bits[i]
        result.append(bit)

        if bit == 1:
            count += 1
            if count == 5:
                i += 1
                count = 0
        else:
            count = 0
        i += 1

    return bits2Bytes(result)

print()
print("PART C")

tests = [[0xFF],[0x7E],[0xFF, 0xFF]]

for payload in tests:
    stuffed, bit_length = bitStuff(payload)
    received = transmit(stuffed, [])
    recovered = bitUnstuff(received, bit_length)

    print("Data:", show(payload))
    print("Stuffed:", show(stuffed))
    print("Bit length:", bit_length)
    print("Recovered:", show(recovered))


def byte_overhead(payload):
    framed = byteStuff(payload)
    overhead = ((len(framed) - len(payload)) / len(payload)) * 100

    return len(framed), overhead


def bit_overhead(payload):
    stuffed, bit_length = bitStuff(payload)
    payload_bits = len(payload) * 8
    overhead = ((bit_length - payload_bits) / payload_bits) * 100

    return bit_length, overhead


print()
print("PART D")

random.seed(42)

random_payload = [random.randint(0, 255) for _ in range(100)]

byte_size, byte_percent = byte_overhead(random_payload)
bit_size, bit_percent = bit_overhead(random_payload)

print("Random data")
print("Payload size:", len(random_payload), "bytes")
print("Byte stuffing size:", byte_size, "bytes")
print("Byte stuffing overhead:", byte_percent, "%")
print("Bit stuffing size:", bit_size, "bits")
print("Bit stuffing overhead:", bit_percent, "%")


worst_byte = [0x7E] * 100
worst_bit = [0xFF] * 100

byte_size, byte_percent = byte_overhead(worst_byte)
bit_size, bit_percent = bit_overhead(worst_bit)

print()
print("Worst case")
print("Byte stuffing input:", show(worst_byte[:5]), "...")
print("Byte stuffing size:", byte_size, "bytes")
print("Byte stuffing overhead:", byte_percent, "%")
print("Bit stuffing input:", show(worst_bit[:5]), "...")
print("Bit stuffing size:", bit_size, "bits")
print("Bit stuffing overhead:", bit_percent, "%")