# 1. 802.11 MAC Header Decoder

## 1. Frame Control Field (2 Bytes)

The First byte:
| Bits | Meaning | Values |
| ---- | ---------------- | ---------------------------------------------- |
| 0–1 | Protocol Version | Normally `00` |
| 2–3 | Type | `00` = Management, `01` = Control, `10` = Data |
| 4–7 | Subtype | Depends on the frame type |

The second byte:

| Bit | Flag       | Meaning                                       |
| --- | ---------- | --------------------------------------------- |
| 0   | ToDS       | Frame is going toward the Distribution System |
| 1   | FromDS     | Frame is coming from the Distribution System  |
| 2   | More Frag  | More fragments of the frame follow            |
| 3   | Retry      | Frame is a retransmission                     |
| 4   | Power Mgmt | Station's power-management state              |
| 5   | More Data  | More buffered data is available               |
| 6   | Protected  | Frame body is protected/encrypted             |
| 7   | Order      | Strict ordering requested                     |

---

### 1.2 Control Frame Subtypes

| Subtype bits | Frame |
| ------------ | ----- |
| `1011`       | RTS   |
| `1100`       | CTS   |
| `1101`       | ACK   |

RTS contains **two addresses**, while CTS and ACK contain **one address**.

## 2. Duration/ID (2 Bytes)

For the frames in this assignment, it represents the **duration in microseconds for which the medium is reserved**.
The field is stored in **little-endian** order.

For example, `2C 00` is `0x002C = 44 µs`

## 3. Address Fields

802.11 frames can contain different numbers of addresses depending on the frame type and the ToDS/FromDS bits.

The important address roles are:

- **RA** = Receiver Address
- **TA** = Transmitter Address
- **DA** = Destination Address
- **SA** = Source Address
- **BSSID** = Basic Service Set Identifier

### 3.1 ToDS/FromDS Address Mapping

| ToDS | FromDS | Address 1 | Address 2 | Address 3 | Address 4 |
| ---: | -----: | --------- | --------- | --------- | --------- |
|    0 |      0 | RA/DA     | TA/SA     | BSSID     | —         |
|    1 |      0 | RA        | TA/SA     | DA        | —         |
|    0 |      1 | RA/DA     | TA/BSSID  | SA        | —         |
|    1 |      1 | RA        | TA        | DA        | SA        |

## 4. Sequence Control (2 Bytes)

```text
15                             4 3                  0
+-------------------------------+-------------------+
|   Sequence Number (12 Bits)   | Fragment (4 Bits) |
+-------------------------------+-------------------+
```

The Sequence Control field is also stored in **little-endian** order.

Example: F1 contains `30 1D` which gives `0x1D30` = `0001 1101 0011 0000`

Sequence Number = `0001 1101 0011` = 467 |
Fragment Number = `0000` = 0

<br>
<br>

# 2. Manual Decoding Table

| Field                           | F1                          | F3                       |
| ------------------------------- | --------------------------- | ------------------------ |
| **Frame Control binary**        | `00001000 00000001`         | `10110100 00000000`      |
| **Type / Subtype**              | Data / Data (`0000`)        | Control / RTS (`1011`)   |
| **ToDS, FromDS**                | `1, 0`                      | `0, 0`                   |
| **Other flags set**             | ToDS only                   | None                     |
| **Duration (µs)**               | `44`                        | `350`                    |
| **Address 1 (role)**            | `A4:83:E7:11:22:33` (RA)    | `A4:83:E7:11:22:33` (RA) |
| **Address 2 (role)**            | `00:50:56:AA:BB:CC` (TA/SA) | `00:50:56:AA:BB:CC` (TA) |
| **Address 3 (role)**            | `00:1A:2B:3C:4D:5E` (DA)    | Not present              |
| **Sequence no. / fragment no.** | `467 / 0`                   | Not present              |

<br>
<br>

# 3. Interpretation Questions

## Q1. F3, F4 and F5 are one exchange. Name the sender and receiver of each, and explain why the Duration drops from F3 to F4 to F5.

### F3 - RTS

```text
Sender / TA = 00:50:56:AA:BB:CC
Receiver / RA = A4:83:E7:11:22:33

00:50:56:AA:BB:CC  ---RTS---> A4:83:E7:11:22:33  Duration (350 µs)
```

This duration reserves the medium for the remaining exchange.

### F4 - CTS

```text
Sender = A4:83:E7:11:22:33
Receiver = 00:50:56:AA:BB:CC

A4:83:E7:11:22:33  ---CTS---> 00:50:56:AA:BB:CC  Duration (324 µs)
```

The duration is smaller because part of the previously reserved exchange has already been consumed by the RTS/CTS exchange.

### F5 - ACK

```text
A4:83:E7:11:22:33  ---ACK---> 00:50:56:AA:BB:CC  Duration (0 µs)
```

At this point the reserved exchange has finished, so no additional medium reservation is needed.
The Duration field represents the remaining reservation time, so it decreases as the exchange progresses.

---

## Q2. A station that hears only F4 sets its NAV. For how many microseconds, and which slide mechanism does this implement?

F4 has `Duration = 324 µs` Therefore, a station that hears F4 sets its NAV for 324 µs. This implements **virtual carrier sensing using the Network Allocation Vector (NAV)**.

The station does not need to physically detect the transmitter's signal to know that the medium is reserved. It uses the Duration information in the frame to defer transmission.

---

## Q3. F2 has the Retry flag set. How does the receiver use the Retry bit together with the sequence number to discard duplicates?

F2 has:

```text
Retry = 1
Sequence Number = 468
Fragment Number = 0
```

The receiver keeps track of previously received frames using their sequence and fragment numbers, If a frame arrives with: `Retry = 1` and the same **Sequence Number** and **Fragment Number** as a frame that was already successfully received, the receiver recognizes it as a duplicate retransmission.

Therefore, the duplicate frame can be discarded instead of delivering the same data to the upper layer twice.
The receiver checks whether sequence `468`, fragment `0` has already been received.

---

## Q4. Why does F6 need a fourth address? Sketch the path it takes, using the WDS figure from the slides.

F6 has:

```text
ToDS = 1
FromDS = 1
```

When both bits are set, the frame is travelling through a **Wireless Distribution System (WDS)**.

The normal three-address format is not sufficient because the frame must preserve both:

- the final destination, and
- the original source.

Therefore, a fourth address is required.

For F6:

```text
RA = 02:11:22:33:44:55
TA = 02:66:77:88:99:AA
DA = 00:50:56:AA:BB:CC
SA = A4:83:E7:11:22:33
```

The general path is:

```text
Original Source
     |
     | SA
     v
Wireless Distribution System
     |
     | wireless bridge/link
     v
Intermediate AP / WDS node
     |
     | TA / RA information
     v
Destination
     |
     | DA
     v
Final Receiver
```

The fourth address allows the original source address to be retained while the transmitter and receiver addresses describe the current wireless hop.

---

## Summary Table of All Six Frames

| Frame | Type    | Subtype | ToDS | FromDS | Other Flags | Duration | Addresses | Sequence / Fragment | EtherType |
| ----- | ------- | ------- | ---: | -----: | ----------- | -------: | --------: | ------------------- | --------- |
| F1    | Data    | Data    |    1 |      0 | —           |       44 |         3 | 467 / 0             | `0x0800`  |
| F2    | Data    | Data    |    0 |      1 | Retry       |       44 |         3 | 468 / 0             | `0x0800`  |
| F3    | Control | RTS     |    0 |      0 | —           |      350 |         2 | —                   | —         |
| F4    | Control | CTS     |    0 |      0 | —           |      324 |         1 | —                   | —         |
| F5    | Control | ACK     |    0 |      0 | —           |        0 |         1 | —                   | —         |
| F6    | Data    | Data    |    1 |      1 | More Frag   |       44 |         4 | 469 / 1             | `0x0800`  |
