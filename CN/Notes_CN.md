<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **COMPUTER NETWORKS NOTES** 🔥🐦‍🔥

<br>

## 🐦‍🔥 FACTS & ESSENTIAL DEFINITIONS

- **Computer Network**: A collection of autonomous computers interconnected by a single technology to exchange information and share resources.
- **Autonomous**: No single computer can forcibly start, stop, or control another host on the network.
- **Protocol**: A set of rules and conventions governing how two or more communicating entities exchange information over a network.
- **Node**: Any active electronic device connected to a network capable of creating, receiving, or transmitting information (e.g., hosts, routers, switches).
- **Link**: The physical or logical communication channel connecting two adjacent nodes.

<br>

## 🔥 Uses of Computer Networks

| Category                 | Typical 2026 Use Cases                                 | Key Characteristics & Drivers                                         |
| :----------------------- | :----------------------------------------------------- | :-------------------------------------------------------------------- |
| 🔥 Business Applications | Cloud computing, SaaS suites, E-commerce, Data centers | Resource sharing, high availability, centralized data management      |
| 🔥 Home & Personal       | Streaming (4K/8K video), Smart-Home IoT, Online Gaming | High bandwidth, low latency requirements, symmetric/asymmetric access |
| 🔥 Mobile & Wearables    | 5G/6G cellular, Wi-Fi 6E/7, GPS, Mobile payments       | Mobility support, dynamic handover, power efficiency                  |

> 📝 NOTE : Wireless and Mobile are distinct concepts:
>
> - **Wireless**: Communication without physical cables (refers to the physical medium).
> - **Mobile**: The communication device moves between different networks during operation.
>   A device can be wireless but fixed (e.g., Wi-Fi router), wired and non-mobile (desktop PC), or both wireless and mobile (smartphone on 5G).

<br>

## 🔥 Social, Legal & Policy Issues

- **Net Neutrality**: The principle that Internet Service Providers (ISPs) must treat all data on the Internet equally, without discriminating or charging differently by user, content, website, or application.
- **Privacy & Data Protection**: Online tracking, surveillance, and regulatory frameworks (e.g., GDPR) governing data ownership and cross-border transfers.
- **Security & Harm**: Defending infrastructure against ransomware, botnets, Denial of Service (DDoS) attacks, and supply-chain vulnerabilities.
- **Content & Speech**: Intellectual property enforcement (DMCA), anti-censorship, content moderation, and provenance of digital media.

<br>

## 🐦‍🔥 NETWORK CLASSIFICATION BY SCALE

| Scale               | Type         | Full Form                 | Typical Radius / Span | Example Technologies                                           |
| :------------------ | :----------- | :------------------------ | :-------------------- | :------------------------------------------------------------- |
| Square meter        | PAN          | Personal Area Network     | 1 m - 10 m            | Bluetooth, NFC, Ultra-Wideband (UWB)                           |
| Room / Building     | LAN          | Local Area Network        | 10 m - 1 km           | Switched Ethernet (IEEE 802.3), Wi-Fi (IEEE 802.11)            |
| City                | MAN          | Metropolitan Area Network | 10 km - 50 km         | Cable TV networks, Fiber to the Home (FTTH), 5G Fixed Wireless |
| Country / Continent | WAN          | Wide Area Network         | 100 km - 1000 km      | ISP backbone networks, MPLS, SD-WAN                            |
| Planet              | Internetwork | The Internet              | Global (> 10,000 km)  | Worldwide collection of interconnected autonomous systems (AS) |

<br>

## 🐦‍🔥 NETWORK SOFTWARE & PROTOCOL LAYERING

### 1️⃣ Layering Principles

- **Modularity**: Network functionality is broken down into a hierarchy of layers, each built upon its predecessor.
- **Abstraction**: Layer N on one machine carries on a virtual communication with Layer N on another machine using a set of rules called the **Layer N Protocol**.
- **Interface**: Defines which primitive operations and services the lower layer offers to the upper layer.
- **Service**: A set of primitives (operations) that a layer provides to the layer above it.

> 📝 NOTE : **Philosopher - Translator - Secretary Metaphor**:
>
> - **Layer 3 (Philosophers)**: Exchange ideas (high-level communication) without caring about language or delivery mode.
> - **Layer 2 (Translators)**: Translate ideas into an agreed common language (e.g., Dutch -> Finnish) without knowing delivery details.
> - **Layer 1 (Secretaries)**: Transport the text via physical means (email, fax, phone) without understanding the philosophy.
>   Any layer can be modified or replaced independently as long as its interfaces remain unchanged!

### 2️⃣ Encapsulation & Decapsulation

- As data moves down the stack, each layer appends its own control information in the form of a **Header** (H) and sometimes a **Trailer** (T).
- The combination of header and payload at Layer N forms the **`Protocol Data Unit (PDU)`** for Layer N.
- At the destination host, the process is reversed (**Decapsulation**), stripping headers layer-by-layer.

```
[ Application Data ]                                      (Payload)
    |
    v
[ H_trans | Application Data ]                            (Transport Segment / Datagram)
    |
    v
[ H_net | H_trans | Application Data ]                    (Network Packet)
    |
    v
[ H_link | H_net | H_trans | Application Data | T_link ]  (Data Link Frame)
    |
    v
 1 0 1 1 0 0 1 0 1 0 0 1 1 0 0 1 0 1 0 1 1 0              (Physical Bit Stream)
```

<br>

## 🔥 Connection-Oriented vs. Connectionless Services

| Feature           | Connection-Oriented Service                     | Connectionless Service                               |
| :---------------- | :---------------------------------------------- | :--------------------------------------------------- |
| Setup Phase       | Explicit connection setup and teardown required | No setup required; packets sent immediately          |
| Path              | All data typically follows the established path | Each packet (datagram) is routed independently       |
| Order Guarantee   | Data delivered in exact order sent              | Packets may arrive out of order or be lost           |
| Overhead          | Higher initial delay (setup phase)              | Zero setup delay; higher per-packet header overhead  |
| Telephone Analogy | Traditional Landline Phone Call                 | Postal Mail / Postal Service                         |
| Examples          | Reliable Byte Stream (TCP), Virtual Circuits    | Unreliable Datagram (UDP, IP), Acknowledged Datagram |

<br>

## 🐦‍🔥 REFERENCE MODELS

### 1️⃣ The OSI 7-Layer Reference Model (ISO/IEC 7498-1)

Developed by the International Organization for Standardization (ISO).

| Layer # | Layer Name       | Primary Function & Responsibility                                        | Data Unit (PDU)         |
| :------ | :--------------- | :----------------------------------------------------------------------- | :---------------------- |
| 7️⃣      | **Application**  | User-facing network services (HTTP, FTP, SMTP, DNS)                      | Data / Message          |
| 6️⃣      | **Presentation** | Data formatting, character conversion, encryption, compression           | Data                    |
| 5️⃣      | **Session**      | Dialogue control, token management, synchronization checkpoints          | Data                    |
| 4️⃣      | **Transport**    | End-to-end reliability, segmentation, flow control, port addressing      | Segment / User Datagram |
| 3️⃣      | **Network**      | Routing across multiple hops, logical addressing (IP addresses)          | Packet / Datagram       |
| 2️⃣      | **Data Link**    | Hop-to-hop reliable transmission, framing, error control, MAC addressing | Frame                   |
| 1️⃣      | **Physical**     | Raw transmission of bits over physical medium (voltages, light, radio)   | Bits                    |

### 2️⃣ The TCP/IP Reference Model & The Modern 5-Layer Model

| Layer # | OSI 7-Layer  | TCP/IP (Original 4-Layer) | Hybrid 5-Layer (Used in Course) | Protocols & Standards                 |
| :------ | :----------- | :------------------------ | :------------------------------ | :------------------------------------ |
| 5       | Application  | Application               | **Application**                 | HTTP, DNS, SMTP, SSH, RTP, QUIC       |
| 4       | Presentation | (Merged into Application) |                                 |                                       |
| 3       | Session      |                           |                                 |                                       |
| 2       | Transport    | Transport                 | **Transport**                   | TCP, UDP, QUIC                        |
| 1       | Network      | Internet                  | **Network**                     | IPv4, IPv6, ICMP, OSPF, BGP           |
| 0       | Data Link    | Link / Network Interface  | **Data Link**                   | Ethernet (802.3), Wi-Fi (802.11), PPP |
| -       | Physical     |                           | **Physical**                    | UTP, Fiber Optics, 4B/5B, QAM         |

> 📝 NOTE : Comparison of OSI vs. TCP/IP:
>
> - **OSI Model**: Clear distinction between Services, Interfaces, and Protocols. Standardized before protocols were written (overly theoretical). Session and Presentation layers are rarely used.
> - **TCP/IP Model**: Protocols came first; model was a description of existing protocols. Extremely successful, but does not clearly distinguish service vs interface vs protocol.

<br>

## 🌟 Modern Network Lens (2026 Perspective)

- **QUIC & HTTP/3**: Web traffic is moving from TCP+TLS to QUIC (built over UDP at user level), eliminating head-of-line blocking.
- **Ubiquitous Encryption**: TLS 1.3 is default; security is no longer an optional add-on layer.
- **Dual Stack IPv4 / IPv6**: The "narrow waist" of the Internet now coexists as IPv4 and IPv6.
- **CDNs & Middleboxes**: Most web content is served from edge Content Delivery Networks (CDNs) rather than origin servers.

<br>

## 🌿 Metric Units in Computer Networks

> 📝 NOTE : Data rates use decimal powers of 10, whereas memory/storage sizes use binary powers of 2!
>
> - **Bandwidth / Speed**:
>   - 1 Kbps = 1,000 bps (10^3 bits/sec)
>   - 1 Mbps = 1,000,000 bps (10^6 bits/sec)
>   - 1 Gbps = 1,000,000,000 bps (10^9 bits/sec)
> - **Memory / File Sizes**:
>   - 1 KB (Kilobyte) = 1,024 Bytes (2^10 Bytes)
>   - 1 MB (Megabyte) = 1,048,576 Bytes (2^20 Bytes)
> - **Time Units**:
>   - 1 millisecond (ms) = 10^-3 sec
>   - 1 microsecond (us) = 10^-6 sec
>   - 1 nanosecond (ns) = 10^-9 sec

<br>

---

<br>

## 🐦‍🔥 2. THE PHYSICAL LAYER

## 🔥 Theoretical Basis for Data Communication

### 1️⃣ Fourier Analysis

Any periodic signal g(t) with period T can be constructed as an infinite sum of sines and cosines:

```
g(t) = c/2 + sum( a_n * sin(2 * pi * n * f * t) + b_n * cos(2 * pi * n * f * t) )
```

where f = 1/T is the fundamental frequency, and n \* f represents the n-th harmonic.

### 2️⃣ Bandwidth-Limited Signals

- Physical transmission media attenuate higher frequencies more severely than lower frequencies.
- The **Bandwidth (B)** of a transmission medium is the range of frequencies it can pass without unacceptable signal degradation (measured in Hertz, Hz).
- Restricting bandwidth truncates higher harmonics, rounding off digital square waves. If too many harmonics are lost, the receiver cannot distinguish between 0 and 1.

```
Square Wave (Ideal):   [___|¯¯¯|___|¯¯¯|___]  (Requires infinite bandwidth)
Limited Harmonics:    (~~~\___/~~~\___/~~~)  (Distorted but readable)
Severely Band-limited:(-------------------)  (Unreadable garbage)
```

<br>

## 🐦‍🔥 Fundamental Limits on Data Rate

### 1️⃣ Symbol Rate (Baud) vs. Bit Rate

- **Symbol (Baud) Rate (S)**: The number of signal state changes (symbols) per second. Unit: Baud.
- **Bit Rate (R)**: The number of bits transmitted per second. Unit: bps.
- If a signal has L distinct voltage/signal levels, each symbol carries V = log2(L) bits:

```
Bit Rate (R) = Baud Rate (S) * log2(L)
```

### 2️⃣ Nyquist Bit Rate Theorem (Noiseless Channel)

Formulated by Harry Nyquist (1928). If an arbitrary signal has been passed through a low-pass filter of bandwidth B, the maximum symbol transmission rate without Inter-Symbol Interference (ISI) is 2B baud.

```
Max Bit Rate (C_Nyquist) = 2 * B * log2(L)  (bits/sec)
```

- B = Channel Bandwidth in Hertz (Hz)
- L = Number of discrete signal/voltage levels
- **Limitation**: Assumes a completely noiseless channel (an unattainable ideal).

### 3️⃣ Signal-to-Noise Ratio (SNR) & Shannon Capacity (Noisy Channel)

Formulated by Claude Shannon (1948). Physical channels suffer from thermal noise, which limits how closely spaced signal levels can be without causing errors.

- **Signal-to-Noise Ratio (SNR)**:

```
SNR = Signal Power / Noise Power
```

- Expressed in decibels (dB):

```
SNR_dB = 10 * log10(Signal Power / Noise Power)
```

> 📝 NOTE : Convert dB to linear ratio using S/N = 10^(SNR_dB / 10).
> Example: 30 dB -> S/N = 10^(30/10) = 10^3 = 1000.

- **Shannon Capacity Theorem**:

```
Max Capacity (C_Shannon) = B * log2(1 + S/N)  (bits/sec)
```

- **Key Takeaways**:
  1. C_Shannon represents an absolute theoretical maximum error-free transmission rate.
  2. Shannon capacity does **not** depend on the number of signal levels L.
  3. Nyquist tells us how many levels L are needed to achieve a target rate, while Shannon tells us if the channel noise will allow those levels to be distinguished!

### 4️⃣ Three Rate Ceilings Compared

```
Nyquist Rate (Noiseless Ceiling) >= Shannon Capacity (Physical Cap) >= Achieved Rate (Hardware)
```

<br>

## 🛡 Worked Numerical Examples: Channel Capacity

> 📝 **PROBLEM 1**: A telephone line has a bandwidth of 3000 Hz and an SNR_dB of 30 dB.
>
> 1. Calculate the maximum theoretical bit rate (Shannon capacity).
> 2. How many signal levels L are required to achieve this capacity according to Nyquist?
>
> **SOLUTION**:
>
> 1. Convert SNR_dB to linear scale: S/N = 10^(30/10) = 1000.
>    C = B _ log2(1 + S/N) = 3000 _ log2(1 + 1000) = 3000 _ log2(1001)
>    Since 2^9 = 512 and 2^10 = 1024, log2(1001) ~= 9.967.
>    C ~= 3000 _ 9.967 = 29,901 bps ~= 30 Kbps
> 2. Using Nyquist formula C = 2 _ B _ log2(L):
>    29901 = 2 _ 3000 _ log2(L) => 29901 = 6000 \* log2(L)
>    log2(L) = 29901 / 6000 ~= 4.98 => L = 2^4.98 ~= 32 signal levels

<br>

## 🐦‍🔥 TRANSMISSION MEDIA

```
                     Transmission Media
                             |
         +-------------------+-------------------+
         |                                       |
    Guided Media                           Unguided Media
  (Wired / Bounded)                      (Wireless / Unbounded)
         |                                       |
  +------+------+------+                  +------+------+------+
  |             |      |                  |             |      |
Twisted      Coaxial Optical            Radio       Microwave Infrared &
 Pair         Cable   Fiber             Waves        Waves    Lightwave
```

<br>

## 🔥 1. Guided Transmission Media

### A. Twisted Pair Cable

Consists of two insulated copper wires twisted together in a helical spiral.

- **Why Twist?**: Twisting ensures that both wires experience equal electromagnetic interference from external sources. The induced noise in adjacent twists cancels out by differential signalling.
- **Categories of UTP (Unshielded Twisted Pair)**:
  - **Cat 3**: Up to 16 MHz, used for legacy telephone lines & 10BASE-T Ethernet.
  - **Cat 5 / Cat 5e**: Up to 100 MHz, 4 pairs, standard for 100BASE-TX & 1000BASE-T.
  - **Cat 6 / Cat 6a**: Up to 250 MHz / 500 MHz, tighter twists, splines, supports 10 Gbps Ethernet up to 55m.
  - **Cat 7**: Up to 600 MHz, individually shielded pairs (STP).

### B. Coaxial Cable

Consists of a solid copper inner conductor surrounded by an insulating layer, covered by a conductive braided metal shield, and enclosed in a protective outer jacket.

- **Baseband Coaxial (50 Ohm)**: Used for digital transmission (e.g., early 10BASE5 / 10BASE2 Ethernet).
- **Broadband Coaxial (75 Ohm)**: Used for analog cable TV and high-speed cable Internet (DOCSIS), bandwidth up to 1 GHz.

### C. Optical Fiber

Transmits information as pulses of light through a high-purity strand of glass (silica).

- **Physics of Operation**: Based on **Total Internal Reflection**. Light traveling in a medium with refractive index n1 (core) strikes the boundary of a medium with a lower refractive index n2 (cladding).
  - If the angle of incidence theta > theta_c (critical angle), light is completely reflected inside the core.
  - Critical angle equation: sin(theta_c) = n2 / n1 where n1 > n2.

- **Fiber Construction**:
  1. **Core**: Inner glass strand (n1).
  2. **Cladding**: Glass casing with lower refractive index (n2).
  3. **Jacket / Buffer**: Protective plastic coating.

- **Types of Fiber**:
  - **Single-Mode Fiber (SMF)**: Core diameter is very small (8 - 10 um), roughly equal to light wavelength. Light travels in a straight line without bouncing. Zero modal dispersion; used for long-distance backbones (tens of km).
  - **Multi-Mode Fiber (MMF)**: Core diameter is larger (50 - 62.5 um). Light rays enter at multiple angles and follow multiple paths (modes). Modal dispersion occurs; suitable for short distance LANs (< 500m).

- **Light Sources**:

| Feature         | LED (Light Emitting Diode)     | Semiconductor Laser                  |
| :-------------- | :----------------------------- | :----------------------------------- |
| Data Rate       | Lower (up to hundreds of Mbps) | Very High (multi-Gbps to Tbps)       |
| Distance        | Short distance (LANs)          | Long distance (WANs, Subsea cables)  |
| Spectral Width  | Wide wavelength distribution   | Narrow, monochromatic beam           |
| Cost & Lifetime | Low cost, long lifetime        | Higher cost, active cooling required |

### D. Copper vs. Optical Fiber Comparison

| Property      | Copper (Twisted Pair / Coax)                | Optical Fiber                                 |
| :------------ | :------------------------------------------ | :-------------------------------------------- |
| Bandwidth     | Moderate (100 MHz - 1 GHz)                  | Ultra-High (50 THz)                           |
| Attenuation   | High (repeaters every 1 - 5 km)             | Extremely low (repeaters every 50 - 100 km)   |
| EMI Immunity  | Susceptible to electromagnetic interference | Completely immune to EMI & power surges       |
| Security      | Easy to tap without detection               | Very difficult to tap; light leakage detected |
| Weight & Size | Heavy, bulky cable bundles                  | Lightweight, thin fiber strands               |

<br>

## 🔥 2. Unguided (Wireless) Transmission Media

```
     3 Hz             300 MHz          300 GHz              300 THz
-------+-----------------+----------------+--------------------+-------> Frequency
       |   RADIO WAVES   |   MICROWAVES   |  INFRARED / LIGHT  |
```

### A. Radio Waves (3 kHz - 300 MHz)

- **Properties**: Easy to generate, omnidirectional (travel in all directions), can easily penetrate walls and solid structures.
- **Propagation Modes**:
  - **VLF** (Very Low Freq) **/ LF / MF (< 3 MHz)**: Follow the curvature of the earth (**Ground Waves / Surface Waves**).
  - **HF (3 - 30 MHz)**: Bounce off the ionosphere (**Sky Waves**), enabling transoceanic radio broadcasts.
  - **VHF / UHF (> 30 MHz)**: Straight line-of-sight propagation; blocked by obstacles.

### B. Microwave Transmission (300 MHz - 300 GHz)

- **Properties**: Highly directional, straight line-of-sight transmission using parabolic dish antennas. Does not penetrate walls well.
- **Line-of-Sight Distance**: Due to Earth's curvature, microwave towers must be spaced periodically. Max distance d ~= 7.14 _ sqrt(K _ h) km where h is tower height.
- **Multipath Fading**: Signals taking slightly different paths (refracted off atmospheric layers) may arrive out of phase and cancel out the signal.

### C. Infrared & Millimeter Waves

- Used for short-range communication (remote controls, wireless mice, IrDA).
- Cannot pass through solid walls -> high security, zero inter-room interference, no regulatory license needed.

### D. Unlicensed ISM Bands

- **Industrial, Scientific, and Medical (ISM) Bands**: Frequencies set aside internationally for unlicensed, low-power devices.
- Key Bands: 2.4 GHz (2.400 - 2.4835 GHz) and 5 GHz (5.725 - 5.850 GHz).
- Devices: Wi-Fi, Bluetooth, Zigbee, microwave ovens, cordless phones.

<br>

## 🐦‍🔥 DIGITAL MODULATION & MULTIPLEXING

### 1️⃣ Baseband Encoding Schemes

Converting binary data into digital signal voltage levels.

- **NRZ-L (Non-Return to Zero Level)**: High voltage = 0, Low voltage = 1.
- **NRZ-I (Non-Return to Zero Invert)**: Transition at start of bit time = 1, No transition = 0.
- **Manchester Encoding**: Transition in the middle of every bit interval. Low-to-High = 1, High-to-Low = 0. Ensures self-clocking and zero DC bias, but requires double the bandwidth (50% efficiency).
- **Differential Manchester**: Mid-bit transition always occurs (for clocking). Transition at start of bit = 0, No transition at start = 1.
- **4B/5B Line Code**: Maps 4 data bits into 5-bit code words containing at least two 1s and no more than three consecutive 0s. Achieves 80% bandwidth efficiency.

```
Bit Stream:          1          0          1          1          0
             +--+       +----------+--+       +--+       +----------+
NRZ-L        |  |       |          |  |       |  |       |          |
             +  +-------+          +  +-------+  +-------+          +
             |          |          |          |          |          |
             +--+    +--+--+    +--+--+    +--+--+    +--+-------+  |
Manchester   |  |    |     |    |     |    |     |    |          |  |
             +  +----+     +----+     +----+     +----+          +--+
```

### 2️⃣ Multiplexing Techniques

- **FDM (Frequency Division Multiplexing)**: Divided channel frequency spectrum into separate narrower frequency bands (e.g., Radio broadcasting, Cable TV).
- **TDM (Time Division Multiplexing)**: Allocates the entire channel bandwidth to one user for a short, repeating time slot (e.g., T1/E1 carrier systems).
- **WDM (Wavelength Division Multiplexing)**: FDM applied to optical fibers using different light wavelengths (colors).
- **CDMA (Code Division Multiple Access)**: All users transmit simultaneously over the full frequency spectrum. Each station is assigned a unique m-bit orthogonal vector called a **Chip Sequence**.

<br>

## 🛡 CDMA Mathematical Worked Example

> 📝 **PROBLEM**: Four stations A, B, C, D are assigned the following 8-chip orthogonal vectors:
>
> - A = (-1, -1, -1, +1, +1, -1, +1, +1)
> - B = (-1, -1, +1, -1, +1, +1, +1, -1)
> - C = (-1, +1, -1, -1, -1, +1, +1, +1)
> - D = (-1, +1, -1, +1, -1, -1, -1, -1)
>
> Station A transmits bit 1 (+A), Station B transmits bit 0 (-B), Station C is silent (0), and Station D transmits bit 1 (+D).
>
> 1. Calculate the combined signal S on the channel.
> 2. Show how a receiver recovers the bit sent by Station B.

**SOLUTION**:

1. **Combined Signal Calculation**:
   - +A = (-1, -1, -1, +1, +1, -1, +1, +1)
   - -B = (+1, +1, -1, +1, -1, -1, -1, +1)
   - C_silent = (0, 0, 0, 0, 0, 0, 0, 0)
   - +D = (-1, +1, -1, +1, -1, -1, -1, -1)

   Summing components component-wise:
   S = (+A) + (-B) + C_silent + (+D) = (-1, +1, -3, +3, -1, -3, -1, +1)

2. **Recovering Station B's Data**:
   Compute the inner product of combined signal S with Station B's chip sequence:
   S _ B = (1/8) _ [ (-1)(-1) + (1)(-1) + (-3)(1) + (3)(-1) + (-1)(1) + (-3)(1) + (-1)(1) + (1)(-1) ]
   S _ B = (1/8) _ [ 1 - 1 - 3 - 3 - 1 - 3 - 1 - 1 ] = -8 / 8 = -1
   Since the inner product result is -1, Station B transmitted **Bit 0**! ✅

<br>

## 🐦‍🔥 SWITCHING & TELEPHONE SYSTEM

### Comparison of Switching Techniques

| Parameter         | Circuit Switching        | Packet Switching (Datagram)        | Message Switching                  |
| :---------------- | :----------------------- | :--------------------------------- | :--------------------------------- |
| Dedicated Path    | Required in advance      | No dedicated path                  | No dedicated path                  |
| Call Setup Delay  | High initial setup delay | Zero call setup delay              | Zero call setup delay              |
| Bandwidth         | Fixed & reserved         | Dynamic (Statistical Multiplexing) | Dynamic                            |
| Store-and-Forward | No store-and-forward     | Packet-level store-and-forward     | Whole message store-and-forward    |
| Congestion        | At setup time            | Per-packet queuing delay           | At intermediate nodes (disk space) |

<br>

---

<br>

## 🐦‍🔥 3. THE DATA LINK LAYER

## 🔥 Design Issues in Data Link Layer

The Data Link Layer (DLL) receives raw bit streams from the Physical Layer and presents a clean, error-free hop-to-hop communication interface to the Network Layer.

```
 Host A (Sender)                                              Host B (Receiver)
+---------------+                                           +---------------+
| Network Layer |  ------ Packet / Datagram (Virtual) ----->| Network Layer |
+---------------+                                           +---------------+
       |                                                           ^
       v (Packet)                                                  | (Packet)
+---------------+                                           +---------------+
| Data Link L2  |  ====== Data Link Frame Transmission =====>| Data Link L2  |
+---------------+                                           +---------------+
       |                                                           ^
       v (Raw Bits)                                                | (Raw Bits)
+---------------+                                           +---------------+
| Physical L1   |  ------- Physical Medium (Copper/Fiber) ->| Physical L1   |
+---------------+                                           +---------------+
```

### 1️⃣ Core Responsibilities

1. **Framing**: Dividing the raw bit stream into discrete, recognizable units called **Frames**.
2. **Error Control**: Detecting and correcting transmission errors (lost frames, corrupted bits, duplicate frames).
3. **Flow Control**: Preventing a fast sender from overwhelming a slow receiver.
4. **Interface to Network Layer**: Providing well-defined service primitives to Layer 3.

<br>

## 🔥 Services Provided to the Network Layer

1️⃣ **Unacknowledged Connectionless Service**:

- Source transmits independent frames without destination acknowledgement.
- No connection establishment or release.
- Lost frames are not recovered at DLL (left to upper layers).
- **Use case**: Low error-rate links (Ethernet LANs) or real-time traffic (Voice over IP).

2️⃣ **Acknowledged Connectionless Service**:

- Each frame sent is individually acknowledged by the receiver.
- If a frame does not arrive within a specified timeout, it is retransmitted.
- **Use case**: Unreliable / noisy channels (Wi-Fi 802.11).

3️⃣ **Acknowledged Connection-Oriented Service**:

- Connection setup before data transfer; frames numbered and delivered in exact order.
- Each frame is guaranteed to be received exactly once.
- Rare at the Data Link Layer in modern networks.

<br>

## 🐦‍🔥 FRAMING METHODS

Since the Physical Layer delivers an uninterrupted stream of raw bits, the Data Link Layer must break bits into discrete frames so that checksums can be computed.

```
+---------------+------------------+---------------+
| Frame Header  | Payload (Packet) | Frame Trailer |
+---------------+------------------+---------------+
```

### Four Standard Framing Methods

| Method                   | Mechanism                                               | Primary Drawback / Resynchronization Issue                 |
| :----------------------- | :------------------------------------------------------ | :--------------------------------------------------------- |
| 1️⃣ **Byte Count**        | Header field specifies total number of bytes in frame   | A single count bit error causes complete desynchronization |
| 2️⃣ **Byte Stuffing**     | Special Flag Bytes (0x7E) delimit frame boundaries      | High overhead if data contains many flag/escape bytes      |
| 3️⃣ **Bit Stuffing**      | Special Flag Pattern (01111110) with zero-bit insertion | Variable frame length depending on payload content         |
| 4️⃣ **Coding Violations** | Physical line code reserved signals (e.g., Manchester)  | Requires physical layer hardware encoding support          |

---

### 1️⃣ Byte Count Method

The frame header contains an integer specifying the exact number of bytes in the frame.

- **Problem**: If an error corrupts the count field (e.g., a count of 5 becomes 7), the receiver misinterprets frame boundaries for all subsequent frames, losing synchronization permanently until a resync mechanism kicks in.

---

### 2️⃣ Flag Bytes with Byte Stuffing (PPP Standard)

Frames start and end with a special delimiter byte called a **Flag Byte** (typically 0x7E or 01111110).

> 📝 **BYTE STUFFING RULES**:
> If the payload data itself contains a byte identical to `FLAG` (0x7E), the sender inserts a special **Escape Byte** (`ESC` = 0x7D) before it.
>
> - Data byte `FLAG` -> Sent as `ESC FLAG`
> - Data byte `ESC` -> Sent as `ESC ESC`
>   The receiver strips the first `ESC` and treats the following byte as literal data.

```
Original Data:       A   [FLAG]   B
After Stuffing:      [FLAG]   A   [ESC]  [FLAG]   B   [FLAG]

Original Data:       A   [ESC]   B
After Stuffing:      [FLAG]   A   [ESC]  [ESC]    B   [FLAG]
```

---

### 3️⃣ Flag Bits with Bit Stuffing (HDLC Standard)

Frames start and end with the 8-bit flag sequence `01111110` (0x7E).

> 📝 **BIT STUFFING RULE**:
> Whenever the sender's data link layer detects **five consecutive 1s** in the payload data stream, it automatically inserts a **0 bit** into the outgoing bit stream.
>
> **RECEIVER DE-STUFFING RULE**:
> Whenever the receiver sees five consecutive 1s followed by a 0 bit, it automatically strips the 0 bit. If followed by a 1 bit, it is the `01111110` flag delimiter!

```
Original Data:      01101111111001
Stuffed Bit Stream: 011011111011001   (0 inserted after five 1s)
                     ^^^^^ ^
Received Data:      01101111111001    (0 stripped by receiver)
```

---

### 4️⃣ Physical Layer Coding Violations

Used in networks where the physical line code contains redundancy:

- **Manchester Code**: 1 is Low-to-High, 0 is High-to-Low. High-High and Low-Low signal states are illegal for data, and are used as frame boundary indicators.
- **4B/5B Code**: 4 bits mapped to 5-bit symbols. Out of 32 possible 5-bit patterns, 16 map to data and remaining unused patterns (e.g., `J` = `11000`, `K` = `10001`) indicate start/end of frame.

<br>

## 🐦‍🔥 ERROR DETECTION AND ERROR CORRECTION

Physical transmission channels suffer from random thermal noise (isolated single-bit errors) and burst noise (fading, impulse noise causing contiguous corrupted bits).

### 1️⃣ Fundamental Concepts

- **Message Bits (m)**: Information bits from upper layer.
- **Check / Redundant Bits (r)**: Extra protection bits appended by DLL.
- **Codeword Length (n)**: Total transmitted block length (n = m + r).
- **Code Rate**: The ratio of useful information bits to total bits = m / n.

### 2️⃣ Code Properties

- **Block Code**: The r check bits are computed solely as a function of the m data bits in the same block.
- **Systematic Code**: The m data bits are sent directly, unencoded, alongside the r check bits.
- **Linear Code**: The r check bits are computed via linear operations (XOR / Modulo-2 addition) on the data bits.

<br>

## 🔥 Hamming Distance & Error Bounds

### 1️⃣ Definition of Hamming Distance

The **Hamming Distance** between two binary codewords of equal length is the number of bit positions in which they differ (computed via XOR and counting 1s).

> 📝 **EXAMPLE**:
> Codeword 1: `10110101`
> Codeword 2: `10010001`
> XOR Result: `00100100` -> Hamming Distance = 2.

The **Hamming Distance of a Code** (d_min) is the minimum Hamming distance between any pair of valid codewords in that code.

### 2️⃣ Error Detection & Correction Capabilities

1️⃣ **To Detect d Single-Bit Errors**:
A code must have a minimum Hamming distance of:

```
d_min >= d + 1
```

_Reason_: No d single-bit errors can transform one valid codeword into another valid codeword.

2️⃣ **To Correct d Single-Bit Errors**:
A code must have a minimum Hamming distance of:

```
d_min >= 2d + 1
```

_Reason_: Even after d single-bit errors occur, the corrupted codeword remains closer (in Hamming distance) to the original valid codeword than to any other valid codeword.

---

### 3️⃣ Check Bits Bound for Single-Error Correction

To correct any single-bit error in an n-bit codeword (n = m + r), each of the 2^m valid messages requires n + 1 distinct bit patterns dedicated to it (itself plus n illegal distance-1 neighbors).

```
(m + r + 1) * 2^m <= 2^(m+r)  =>  (m + r + 1) <= 2^r
```

| Data Bits (m) | Min Check Bits (r) | Total Codeword Length (n = m+r) | Inequality Check (m+r+1) <= 2^r |
| :-----------: | :----------------: | :-----------------------------: | :-----------------------------: |
|       1       |         2          |                3                |            4 <= 4 ✅            |
|       4       |         3          |                7                |            8 <= 8 ✅            |
|       7       |         4          |               11                |           12 <= 16 ✅           |
|      11       |         4          |               15                |           16 <= 16 ✅           |
|      57       |         6          |               63                |           64 <= 64 ✅           |

<br>

## 🐦‍🔥 HAMMING CODE (SINGLE ERROR CORRECTION)

Developed by Richard Hamming. It is a linear, systematic block code with d_min = 3.

### 1️⃣ Bit Position & Parity Coverage Rules

1. Number codeword bit positions from 1 to n (left to right).
2. Bit positions that are **powers of 2** (1, 2, 4, 8, 16, ...) hold **Check Bits** (p1, p2, p4, p8, ...).
3. All remaining positions (3, 5, 6, 7, 9, 10, 11, ...) hold **Data Bits** (d1, d2, d3, ...).
4. **Coverage Rule**: Check bit p_i (at position i) checks all bit positions k whose binary expansion contains i (i.e., k AND i = i).

For m = 7, r = 4, n = 11 Hamming (11, 7) code:

```
Bit Positions:   1    2    3    4    5    6    7    8    9    10   11
Content:        p1   p2   d1   p4   d2   d3   d4   p8   d5   d6   d7
```

- p1 checks positions: 1, 3, 5, 7, 9, 11 (binary LSB = 1)
- p2 checks positions: 2, 3, 6, 7, 10, 11 (binary second bit = 1)
- p4 checks positions: 4, 5, 6, 7 (binary third bit = 1)
- p8 checks positions: 8, 9, 10, 11 (binary fourth bit = 1)

<br>

## 🛡 Worked Step-by-Step Example: Hamming Code

> 📝 **PROBLEM**:
> Encode the 7-bit message M = 1000001 (d1 d2 d3 d4 d5 d6 d7 = 1,0,0,0,0,0,1) using Hamming (11, 7) code with Even Parity.
> Then, simulate a bit flip at position 5 during transmission and show how the receiver locates and corrects the error!

### Step 1: Place Data Bits into Positions

- Pos 1: p1
- Pos 2: p2
- Pos 3: d1 = 1
- Pos 4: p4
- Pos 5: d2 = 0
- Pos 6: d3 = 0
- Pos 7: d4 = 0
- Pos 8: p8
- Pos 9: d5 = 0
- Pos 10: d6 = 0
- Pos 11: d7 = 1

Codeword Draft: `[p1] [p2] 1 [p4] 0 0 0 [p8] 0 0 1`

### Step 2: Compute Check Bits (Even Parity)

- p1 = XOR(Pos 3, 5, 7, 9, 11) = 1 ^ 0 ^ 0 ^ 0 ^ 1 = 0
- p2 = XOR(Pos 3, 6, 7, 10, 11) = 1 ^ 0 ^ 0 ^ 0 ^ 1 = 0
- p4 = XOR(Pos 5, 6, 7) = 0 ^ 0 ^ 0 = 0
- p8 = XOR(Pos 9, 10, 11) = 0 ^ 0 ^ 1 = 1

**Transmitted Codeword**: `0 0 1 0 0 0 0 1 0 0 1`

---

### Step 3: Transmission Error Simulation

Suppose an error flips **Bit Position 5** from 0 to 1:
**Received Codeword**: `0 0 1 0 1 0 0 1 0 0 1`

---

### Step 4: Receiver Syndrome Calculation

The receiver re-calculates parity for each coverage group:

- S1 = XOR(1, 3, 5, 7, 9, 11) = 0 ^ 1 ^ 1 ^ 0 ^ 0 ^ 1 = 1 (Fail!)
- S2 = XOR(2, 3, 6, 7, 10, 11) = 0 ^ 1 ^ 0 ^ 0 ^ 0 ^ 1 = 0 (Pass)
- S4 = XOR(4, 5, 6, 7) = 0 ^ 1 ^ 0 ^ 0 = 1 (Fail!)
- S8 = XOR(8, 9, 10, 11) = 1 ^ 0 ^ 0 ^ 1 = 0 (Pass)

**Syndrome Vector** S = (S8 S4 S2 S1)\_2 = (0 1 0 1)\_2 = 5_10.

> 🌟 **RESULT**: The binary syndrome 0101_2 = 5 points directly to **Bit Position 5**!
> The receiver flips Pos 5 back (1 -> 0) and extracts original message 1000001! ✅

<br>

## 🐦‍🔥 REED-SOLOMON & OTHER ERROR CORRECTING CODES

- **Reed-Solomon (RS) Codes**: Non-binary block codes operating on m-bit symbols (typically bytes, GF(256)). An RS(n, k) code appends n-k check symbols to k data symbols and can correct up to t = (n - k) / 2 symbol errors.
  - _Key Advantage_: Excellent at correcting **burst errors** (since a burst of corrupted bits usually affects consecutive bytes within one symbol).
  - _Applications_: CDs, DVDs, Blu-ray, Barcodes/QR codes, Satellite communication, 5G NR.
- **LDPC (Low-Density Parity-Check)**: Linear block codes with sparse parity check matrices. Performs extremely close to the Shannon Limit; used in 802.11n/ac/ax Wi-Fi and 5G.

<br>

## 🐦‍🔥 ERROR DETECTING CODES

### 1️⃣ Parity (1D & 2D Interleaving)

- **Single Parity Bit**: Appends 1 bit to make total number of 1s even (Even Parity). Minimum distance d=2; detects single-bit errors, fails on even-number bit flips.
- **2D Parity / Interleaving**: Data arranged in a matrix of k rows and n columns. A parity bit is computed for each column. Transmission occurs row-by-row.
  - _Burst Error Protection_: A continuous burst error of length up to n bits affects at most 1 bit per column, transforming a fatal burst error into easily detectable single-bit errors per column!

```
Row 1:   1  0  1  1  0  1  0
Row 2:   0  1  1  0  1  0  1
Row 3:   1  1  0  1  1  0  0
Row 4:   0  0  1  1  0  1  1
         -------------------
Parity:  0  0  1  1  0  0  0  (Column Parity Row)
```

---

### 2️⃣ Internet Checksum

Used in IP, UDP, and TCP headers.

- **Algorithm**:
  1. Adjacent 8-bit bytes are paired into 16-bit integers.
  2. Compute 1's complement sum of all 16-bit words.
  3. Complement the final sum to get the checksum.
- **Verification**: Summing all 16-bit words including the checksum field yields 0xFFFF (all 1s). Taking its 1's complement yields 0x0000 (no error).

<br>

## 🐦‍🔥 CYCLIC REDUNDANCY CHECK (CRC / POLYNOMIAL CODES)

CRC treats bit strings as polynomials with binary coefficients (0 and 1).

- A k-bit frame is represented as polynomial M(x) = a*(k-1) \* x^(k-1) + a*(k-2) _ x^(k-2) + ... + a_0 _ x^0.
  - Example: Bit string `110001` -> M(x) = x^5 + x^4 + 1.

### 1️⃣ Polynomial Arithmetic (Modulo 2)

- Performed modulo 2 without carries for addition or borrows for subtraction.
- **Addition and Subtraction are both equivalent to XOR (^)**:
  - 0 ^ 0 = 0, 1 ^ 1 = 0, 1 ^ 0 = 1, 0 ^ 1 = 1.

### 2️⃣ CRC Generation Algorithm

Given a message polynomial M(x) of length m bits and an agreed Generator Polynomial G(x) of degree r:

1️⃣ Append r zero bits to the end of the frame (representing M(x) _ x^r).
2️⃣ Divide the bit string M(x) _ x^r by G(x) using **Modulo-2 Binary Division**.
3️⃣ The r-bit remainder R(x) is the CRC checksum.
4️⃣ Subtract/XOR the remainder from M(x) _ x^r to form the transmitted frame T(x) = M(x) _ x^r ^ R(x).

> 📝 **RECEIVER VERIFICATION**:
> The receiver divides received T'(x) by G(x). If the remainder is **0**, no error was detected!

<br>

## 🛡 Worked Step-by-Step Example: CRC Division

> 📝 **PROBLEM**:
> Frame Payload M = 110101 (6 bits).
> Generator Polynomial G(x) = x^3 + x + 1 -> Bit string 1011 (Degree r = 3).
> Compute the transmitted frame T(x).

### Step 1: Append r = 3 zeros to M

M \* x^3 = 110101000

### Step 2: Modulo-2 Division of `110101000` by `1011`

```
               111101   (Quotient)
        --------------
1 0 1 1 | 1 1 0 1 0 1 0 0 0
          1 0 1 1
          -------
            1 1 0 0
            1 0 1 1
            -------
              1 1 1 1
              1 0 1 1
              -------
                1 0 0 0
                1 0 1 1
                -------
                  0 1 1 0  (Bring down 0 -> 0110, quotient bit 0)
                  0 0 0 0
                  -------
                    1 1 0 0
                    1 0 1 1
                    -------
                      1 1 1  <-- Remainder R(x) (3 bits)
```

Remainder R = 111.

### Step 3: Form Transmitted Frame T(x)

T(x) = 110101000 ^ 111 = 110101111

Transmitted Frame: `1 1 0 1 0 1 1 1 1` ✅

---

### 3️⃣ Standard CRC Polynomials & Error Detection Capabilities

- **CRC-16**: G(x) = x^16 + x^15 + x^2 + 1
- **CRC-CCITT**: G(x) = x^16 + x^12 + x^5 + 1
- **CRC-32 (Ethernet 802.3 & PKZIP)**: G(x) = x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1

> 🌟 **CRC GUARANTEES (Degree r generator)**:
>
> 1. Detects ALL single-bit errors (if G(x) has >= 2 terms).
> 2. Detects ALL double-bit errors (if G(x) does not divide x^k + 1).
> 3. Detects ALL odd numbers of bit errors (if G(x) contains factor (x+1)).
> 4. Detects ALL burst errors of length <= r.

<br>

---

<br>

## 🐦‍🔥 ELEMENTARY DATA LINK PROTOCOLS

### Assumptions for Protocol Analysis

- Data Link Layer routines `from_network_layer()`, `to_physical_layer()`, `from_physical_layer()`, `to_network_layer()`.
- Packet: Data unit exchanged between DLL and Network Layer.
- Frame: Data unit exchanged between DLL peers containing header, payload, and trailer.

---

### 1️⃣ Protocol 1: Simplex Utopian Protocol

- **Assumptions**: Unidirectional data transmission; perfectly reliable channel (no noise); infinite receiver buffer and instant processing.
- **Sender**: Loop forever: fetch packet, build frame, send frame.
- **Receiver**: Loop forever: wait for event, receive frame, pass packet to network layer.

---

### 2️⃣ Protocol 2: Simplex Stop-and-Wait (Error-Free Channel)

- **Assumptions**: Error-free channel, but receiver has finite processing speed/buffer space.
- **Mechanism**: Flow control added. Sender sends 1 frame, then stops and waits for a dummy Acknowledgement (`ACK`) frame from receiver before sending next frame.

```
Sender                                 Receiver
  |                                       |
  | -------- Frame 0 -------------------->| (Processes frame)
  |                                       |
  |<------- ACK Frame -------------------| (Sends ACK)
  |                                       |
  | -------- Frame 1 -------------------->|
```

---

### 3️⃣ Protocol 3: Simplex Stop-and-Wait for Noisy Channel (PAR)

- **Assumptions**: Channel can corrupt or drop frames/ACKs.
- **Mechanism (Positive Acknowledgement with Retransmission)**:
  - Sender starts a **Timer** when transmitting a frame.
  - If ACK does not arrive before timer expires (Timeout), sender retransmits frame.
  - **Sequence Numbers**: 1-bit sequence numbers (0 and 1) added to frame headers to prevent duplicate frames when ACKs are delayed or lost.

<br>

## 🐦‍🔥 SLIDING WINDOW PROTOCOLS

Full-duplex communication allows bidirectional data transfer. **Piggybacking** attaches ACK numbers into outgoing data frame headers to save bandwidth.

```
Sender Window (Ws):      [  3   4   5   6  ] 7   8   9
                          ^               ^
                          |               |
                    First unACKed      Last frame sent
```

### 1️⃣ 1-Bit Sliding Window Protocol (Stop-and-Wait Variant)

- Sender window size Ws = 1, Receiver window size Wr = 1.
- Uses 1-bit sequence numbers (0 and 1).
- **Efficiency (eta)**:
  Let t_trans = L / R be frame transmission time, t_prop be propagation delay.

```
Efficiency (eta) = t_trans / (t_trans + 2 * t_prop) = 1 / (1 + 2*a)   where a = t_prop / t_trans
```

> 📝 NOTE : On high bandwidth-delay product links (a >> 1), Stop-and-Wait efficiency drops close to 0%!

---

### 2️⃣ Go-Back-N (GBN) Protocol

Pipelining protocol that allows the sender to transmit multiple frames before receiving an ACK.

- **Sender Window Size**: Ws = 2^m - 1 (where m is sequence number bits).
- **Receiver Window Size**: Wr = 1.
- **Acknowledgements**: Uses **Cumulative Acknowledgements** (ACK_k acknowledges all frames up to k).
- **Error Handling**: If frame k is lost or corrupted, receiver silently discards frame k and ALL subsequent frames (Wr = 1). Sender times out and **retransmits ALL frames from k onwards** ("Goes Back N").

> 📝 **SENDER WINDOW BOUND PROOF**:
> For m-bit sequence numbers, Ws MUST be <= 2^m - 1.
> If Ws = 2^m, and all ACKs for a full window are lost, sender retransmits sequence numbers 0 ... 2^m - 1. The receiver cannot tell if these are new frames or retransmissions!

---

### 3️⃣ Selective Repeat (SR) Protocol

Avoids wasting bandwidth by retransmitting ONLY corrupted or lost frames.

- **Sender Window Size**: Ws = 2^(m-1).
- **Receiver Window Size**: Wr = 2^(m-1).
- **Mechanism**: Receiver maintains a window buffer. Out-of-order valid frames are accepted and buffered. Receiver sends a **Negative Acknowledgement (NAK)** for missing frames.
- Sender retransmits **only** the frame specified by NAK or timeout.

> 📝 **WINDOW BOUND RULE**:
> To prevent overlap between unacknowledged frames and new frames:
> Ws + Wr <= 2^m => Ws = Wr = 2^(m-1)

---

### 4️⃣ Comprehensive Comparison of Sliding Window Protocols

| Property                     | Stop-and-Wait    | Go-Back-N (GBN)          | Selective Repeat (SR)       |
| :--------------------------- | :--------------- | :----------------------- | :-------------------------- |
| Sender Window (Ws)           | 1                | 2^m - 1                  | 2^(m-1)                     |
| Receiver Window (Wr)         | 1                | 1                        | 2^(m-1)                     |
| ACK Type                     | Individual       | Cumulative               | Individual / Negative (NAK) |
| Out-of-Order Receiver Buffer | No               | No (Discarded)           | Yes (Buffered)              |
| Retransmission on Loss       | Single frame     | Entire window (N frames) | Only lost frame             |
| Link Utilization Efficiency  | Low (1 / (1+2a)) | High (Ws / (1+2a))       | Maximum (Ws / (1+2a))       |

<br>

---

<br>

## 🐦‍🔥 MEDIUM ACCESS CONTROL (MAC) SUBLAYER

The MAC sublayer is the lower portion of Data Link Layer (Layer 2a), responsible for coordinating access to a shared broadcast channel.

```
+------------------------------------+
| Logical Link Control (LLC) (802.2) |  <-- Layer 2b
+------------------------------------+
| Medium Access Control (MAC)        |  <-- Layer 2a
+------------------------------------+
```

<br>

## 🔥 Multiple Access Protocols

```
                      Multiple Access Protocols
                                  |
     +----------------------------+----------------------------+
     |                            |                            |
 Random Access               Controlled Access           Channelization
(Contention-based)           (Collision-free)           (Static Sharing)
     |                            |                            |
 +---+---+                    +---+---+                    +---+---+
 |       |                    |       |                    |   |   |
ALOHA  CSMA                 Bitmap Token-Passing          FDM TDM CDMA
```

---

### 1️⃣ ALOHA Protocols (Devised by Norman Abramson)

1️⃣ **Pure ALOHA**:

- Transmit whenever data is ready.
- If collision occurs, wait a random time and retransmit.
- Vulnerable period = 2 \* tau (where tau is frame duration).
- Throughput equation (G = offered load):

```
S = G * e^(-2G)
```

- Maximum Throughput = 1 / (2\*e) ~= 0.184 (18.4%) at G = 0.5.

2️⃣ **Slotted ALOHA**:

- Time divided into discrete slots of duration tau. Stations can only transmit at slot boundaries.
- Vulnerable period = tau.
- Throughput equation:

```
S = G * e^(-G)
```

- Maximum Throughput = 1 / e ~= 0.368 (36.8%) at G = 1.0.

---

### 2️⃣ CSMA (Carrier Sense Multiple Access) Protocols

Stations listen to the channel before transmitting ("Listen Before Talk").

1️⃣ **1-Persistent CSMA**:

- Listen to channel. If idle, transmit immediately (probability 1). If busy, continuously sense channel until idle, then transmit immediately.
- High collision chance if multiple stations were waiting.

2️⃣ **Non-Persistent CSMA**:

- Listen to channel. If idle, transmit. If busy, wait a random time interval before sensing again. Reduces collisions, but increases idle delay.

3️⃣ **p-Persistent CSMA** (Slotted channels):

- If channel is idle, transmit frame with probability p, and defer to next slot with probability 1-p.

---

### 3️⃣ CSMA/CD (Carrier Sense Multiple Access with Collision Detection)

Standard used in classic Wired Ethernet (IEEE 802.3).

- **Listen While Transmitting**: Sender monitors channel during transmission. If collision detected, abort transmission immediately, transmit a **Jam Signal**, and execute **Binary Exponential Backoff**.

> 🛡 **BINARY EXPONENTIAL BACKOFF**:
> After c collisions, sender picks random slot k in range [0, 2^(min(c, 10)) - 1] and waits k \* 512 bit times (51.2 us) before retrying. Aborts after 16 failed attempts.

> 📝 **MINIMUM FRAME SIZE DERIVATION**:
> To ensure a sender detects a collision before completing transmission, transmission time t_trans must be at least twice the end-to-end propagation delay (2 _ t_prop):
> t_trans >= 2 _ t_prop => L_min / R >= 2 _ t_prop => L_min = 2 _ t_prop _ R
> For 10 Mbps Ethernet over 2.5 km max distance (t_prop = 25.6 us):
> L_min = 2 _ (25.6 _ 10^-6 s) _ (10^7 bps) = 512 bits = 64 Bytes

---

### 4️⃣ Ethernet (IEEE 802.3) Frame Format

```
+----------+-----+-------------+------------+----------+---------------+---------+
| Preamble | SFD | Dest Addr   | Src Addr   | Type/Len | Data Payload  | FCS CRC |
| 7 Bytes  | 1 B | 6 Bytes     | 6 Bytes    | 2 Bytes  | 46-1500 Bytes | 4 Bytes |
+----------+-----+-------------+------------+----------+---------------+---------+
```

- **Preamble**: 7 bytes `10101010` for clock synchronization.
- **Start Frame Delimiter (SFD)**: 1 byte `10101011` indicating start of frame.
- **Destination & Source MAC**: 6-byte unique physical hardware addresses (IEEE OUI).
- **Type / Length**: If <= 1500, specifies payload length; if >= 1536, specifies EtherType protocol (e.g., `0x0800` for IPv4).
- **Data Payload**: 46 to 1500 bytes (padded if < 46 bytes to meet 64-byte L_min).
- **FCS (Frame Check Sequence)**: 4-byte CRC-32 checksum.

<br>

</div>
</div>
