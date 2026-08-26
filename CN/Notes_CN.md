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
>- **Memory / File Sizes**:
>   - 1 KB (Kilobyte) = 1,024 Bytes (2^10 Bytes)
>   - 1 MB (Megabyte) = 1,048,576 Bytes (2^20 Bytes)
>- **Time Units**:
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

where f = 1/T is the fundamental frequency, and n * f represents the n-th harmonic.

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
>    C = B * log2(1 + S/N) = 3000 * log2(1 + 1000) = 3000 * log2(1001)
>    Since 2^9 = 512 and 2^10 = 1024, log2(1001) ~= 9.967.
>    C ~= 3000 * 9.967 = 29,901 bps ~= 30 Kbps
> 2. Using Nyquist formula C = 2 * B * log2(L):
>    29901 = 2 * 3000 * log2(L) => 29901 = 6000 * log2(L)
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
- **Line-of-Sight Distance**: Due to Earth's curvature, microwave towers must be spaced periodically. Max distance d ~= 7.14 * sqrt(K * h) km where h is tower height.
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
   S * B = (1/8) * [ (-1)(-1) + (1)(-1) + (-3)(1) + (3)(-1) + (-1)(1) + (-3)(1) + (-1)(1) + (1)(-1) ]
   S * B = (1/8) * [ 1 - 1 - 3 - 3 - 1 - 3 - 1 - 1 ] = -8 / 8 = -1
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

## 🐦‍🔥 3. THE DATA LINK LAYER (PART 1: FRAMING, ERROR CONTROL & FLOW CONTROL)

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
| 4️⃣ **Coding Violations** | Physical line code reserved signals (e.g., 4B/5B, Manchester) | Requires physical layer hardware encoding support          |

---

### 1️⃣ Byte Count Method

The frame header contains an integer specifying the exact number of bytes in the frame.

- **Problem**: If an error corrupts the count field (e.g., a count of 5 becomes 7), the receiver misinterprets frame boundaries for all subsequent frames, losing synchronization permanently until a resynchronization mechanism kicks in.

```
Frame 1 (5 bytes)    Frame 2 (5 bytes)    Frame 3 (8 bytes)
  [ 5 ] A B C D        [ 5 ] E F G H        [ 8 ] I J K L M N O P
    |                    |                    |
    v                    v (Bit error turns 5 into 7)
  [ 5 ] A B C D        [ 7 ] E F G H [ 8 ] I  <-- Frame 2 boundary shifted!
                                           ^
                                           | Next frame header misread here!
```

---

### 2️⃣ Flag Bytes with Byte Stuffing (PPP Standard)

Frames start and end with a special delimiter byte called a **Flag Byte** (typically `0x7E` or `01111110`).

> 📝 **BYTE STUFFING RULES (PPP Standard)**:
> If the payload data itself contains a byte identical to `FLAG` (`0x7E`), the sender inserts a special **Escape Byte** (`ESC` = `0x7D`) before it, and XORs the byte with `0x20`.
>
> - Data byte `0x7E` -> Sent as `0x7D 0x5E` (`0x7E ^ 0x20 = 0x5E`)
> - Data byte `0x7D` -> Sent as `0x7D 0x5D` (`0x7D ^ 0x20 = 0x5D`)
> - Byte `< 0x20` (Control Chars) -> Sent as `0x7D (b ^ 0x20)`
>
> **Receiver Action**: Whenever the receiver sees `0x7D`, it discards `0x7D` and XORs the next byte with `0x20` to reconstruct the original data byte!

```
Original Payload (Hex):    0x45   0x7E   0x7D   0x20
Stuffed Frame Sent:  0x7E  0x45  [0x7D 0x5E] [0x7D 0x5D] 0x20  0x7E
                     ^                                          ^
                Start Flag                                  End Flag
```

---

### 3️⃣ Flag Bits with Bit Stuffing (HDLC Standard)

Frames start and end with the 8-bit flag sequence `01111110` (`0x7E`).

> 📝 **BIT STUFFING RULE (SENDER)**:
> Whenever the sender's data link layer detects **five consecutive 1s** in the payload data stream, it automatically inserts a **0 bit** into the outgoing bit stream.
>
> **DE-STUFFING RULE (RECEIVER)**:
> Whenever the receiver sees five consecutive 1s followed by a 0 bit, it automatically strips the 0 bit. If followed by a 1 bit, it is the `01111110` flag delimiter (or an error if six 1s followed by a 1)!

```
Original Payload:     0 1 1 0 1 1 1 1 1 1 1 0 0 1
                                ^^^^^
Sender Stuffing:      0 1 1 0 1 1 1 1 1 0 1 1 0 0 1   (0 bit stuffed after five 1s)
                                ^^^^^ ^
Receiver Destuffing:  0 1 1 0 1 1 1 1 1 1 1 0 0 1     (0 bit removed)
```

---

### 4️⃣ Physical Layer Coding Violations (4B/5B & Manchester)

Used in networks where the physical line code contains signal redundancy:

#### A. Manchester Encoding Violations
In Manchester encoding, every bit must have a mid-bit transition (Low-to-High for 1, High-to-Low for 0). High-High and Low-Low signal states over an entire bit interval are illegal for data and serve as explicit frame boundary indicators.

#### B. 4B/5B Line Code Specification
In 4B/5B encoding, 4 data bits are mapped into 5-bit symbol code words:
- **Efficiency**: $4/5 = 80\%$ bandwidth efficiency.
- **Constraints**: Each valid 5-bit symbol contains at least two 1s and no more than three trailing/leading zeros to guarantee clock synchronization.
- **Special Control Symbols**: Out of 32 possible 5-bit combinations, 16 map to data hexadecimal digits (`0` to `F`), and the remaining 16 reserved codes represent control delimiters:

| Symbol Name | 5-Bit Symbol | Meaning / Purpose |
| :--- | :--- | :--- |
| `J` | `11000` | Start of Frame Delimiter (Part 1) |
| `K` | `10001` | Start of Frame Delimiter (Part 2) |
| `T` | `01101` | End of Frame Delimiter (Part 1) |
| `R` | `00111` | End of Frame Delimiter (Part 2) |
| `S` | `11001` | Set / Reset Command |
| `H` | `00100` | Halt / Error Indicator |
| `I` | `11111` | Idle Line State |

> 🌟 **4B/5B Framing**: A frame is explicitly bounded by `JK` at the start (`11000 10001`) and `TR` at the end (`01101 00111`). Because `JK` and `TR` never occur in valid payload data, frame boundaries are recognized immediately without bit or byte stuffing!

<br>

## 🐦‍🔥 ERROR CONTROL & CHANNEL CHARACTERISTICS

### 1️⃣ Noise Models & Error Types
1. **Thermal Noise**: Random Gaussian background noise causing isolated, independent **single-bit errors**.
2. **Burst Noise**: Impulse noise (lightening, transient power surges, wireless deep fading) causing long contiguous blocks of corrupted bits.
3. **Erasure Channel**: Analog signal level is corrupted such that the receiver cannot decide between 0 and 1, declaring the bit to be "erased" or lost.

### 2️⃣ Error Correction (FEC) vs. Error Detection + Retransmission
- **Forward Error Correction (FEC)**: Sender appends enough redundant check bits so that receiver can identify and correct errors without retransmission.
- **Error Detection + Retransmission (ARQ)**: Sender appends a small checksum. If receiver detects an error, it discards the frame and requests retransmission.

| Property | Error Detection + ARQ | Forward Error Correction (FEC) |
| :--- | :--- | :--- |
| Primary Medium | Reliable links (Fiber Optics, Twisted Pair LANs) | High-noise links (Wireless, Satellite, Deep Space) |
| Bit Error Rate (BER) | Low ($10^{-10}$ to $10^{-12}$) | High ($10^{-3}$ to $10^{-6}$) |
| Overhead | Extremely low (e.g., 32-bit CRC per 1500-byte frame) | Substantial (10% to 50% extra check bits) |
| Latency | High variability (retransmission round-trip time) | Deterministic & immediate decoding |

> 🛡 **Worked Trade-off Analysis (Slide 44)**:
> Consider a channel with BER $= 10^{-6}$ transmitting blocks of 1000 bits.
> - **Strategy 1: Single Parity Bit (Detection)**:
>   Appends 1 bit per block. 1 in every 1000 blocks incurs an error and requires retransmission (1001 extra bits sent). Total cost to send $10^6$ bits $\approx 1000 \text{ parity bits} + 1001 \text{ retransmitted bits} = 2001 \text{ overhead bits}$.
> - **Strategy 2: Hamming Code (Correction)**:
>   Requires 10 check bits per 1000-bit block. Total cost for $10^6$ bits $= 10,000 \text{ check bits}$.
>
> 🌟 **Conclusion**: On low BER channels, error detection is over 5x more efficient than error correction!

<br>

## 🐦‍🔥 ERROR DETECTION & ERROR CORRECTION THEORY

### 1️⃣ Code Taxonomy & Definitions
- **Message Bits ($m$)**: Information bits from upper layer.
- **Check / Redundant Bits ($r$)**: Extra protection bits appended by DLL.
- **Codeword Length ($n$)**: Total transmitted block length ($n = m + r$).
- **Code Rate**: The fraction of useful information bits $= m / n$.

> 📝 **Three Independent Code Classification Properties**:
> 1. **Block Code**: The $r$ check bits are computed solely as a function of the $m$ data bits in the *same* block.
> 2. **Systematic Code**: The $m$ data bits are sent directly, unencoded, alongside the $r$ check bits.
> 3. **Linear Code**: The $r$ check bits are computed via linear operations (Modulo-2 / XOR addition) on the data bits.
>
> *Note*: A code can possess any combination of these properties. The Hamming Code studied below is **Block, Systematic, and Linear** all at once!

### 2️⃣ Code Sparseness
All $2^m$ possible messages are legal data, but check bits restrict valid codewords to a small subset of the $2^n$ space.
The fraction of valid codewords is:
$$\text{Sparseness} = \frac{2^m}{2^n} = \frac{1}{2^r}$$
It is this sparseness (large gaps between valid codewords in $n$-dimensional space) that enables error detection and correction!

---

### 3️⃣ Hamming Distance & Error Bounds

The **Hamming Distance** between two binary codewords is the number of bit positions in which they differ (computed via XOR and counting 1s).
The **Hamming Distance of a Code ($d_{min}$)** is the minimum Hamming distance between any pair of valid codewords in that code.

#### Theorem 1: Error Detection Limit
To detect $d$ single-bit errors, the code must have:
$$d_{min} \ge d + 1$$
*Reason*: No $d$ single-bit errors can transform one valid codeword into another valid codeword.

#### Theorem 2: Error Correction Limit
To correct $d$ single-bit errors, the code must have:
$$d_{min} \ge 2d + 1$$
*Reason*: Even after $d$ single-bit errors occur, the corrupted codeword remains closer (in Hamming distance) to the original valid codeword than to any other valid codeword.

---

### 🛡 Worked Example: Distance d=5 Code (Slide 35)

> 📝 **PROBLEM**: Consider a code with only four valid 10-bit codewords:
> - $C_1 = 0000000000$
> - $C_2 = 0000011111$
> - $C_3 = 1111100000$
> - $C_4 = 1111111111$
>
> 1. Calculate the minimum Hamming distance $d_{min}$.
> 2. Determine its error detection and correction capabilities.
> 3. Decode the received codeword $R = 0000000111$.

**SOLUTION**:
1. Computing pairwise Hamming distances:
   - $d(C_1, C_2) = 5$, $d(C_1, C_3) = 5$, $d(C_1, C_4) = 10$
   - $d(C_2, C_3) = 10$, $d(C_2, C_4) = 5$, $d(C_3, C_4) = 5$
   Minimum Hamming distance $d_{min} = 5$.
2. Capabilities:
   - Error detection: $d_{min} \ge d + 1 \Rightarrow 5 \ge d + 1 \Rightarrow d = 4$ (Can detect up to 4 bit errors).
   - Error correction: $d_{min} \ge 2d + 1 \Rightarrow 5 \ge 2d + 1 \Rightarrow d = 2$ (Can correct up to 2 bit errors).
3. Decoding $R = 0000000111$:
   - $d(R, C_1) = 3$
   - $d(R, C_2) = 2$  <-- MINIMUM DISTANCE!
   - $d(R, C_3) = 8$
   - $d(R, C_4) = 5$
   Assuming at most double errors ($d \le 2$), the receiver decodes $R$ as **$C_2 = 0000011111$**! ✅

---

### 4️⃣ Check Bits Bound for Single-Error Correction

Each of the $2^m$ legal messages requires $n+1$ distinct $n$-bit patterns dedicated to it (itself plus $n$ distance-1 illegal neighbors):
$$(m + r + 1) \cdot 2^m \le 2^{m+r} \implies (m + r + 1) \le 2^r$$

| Data Bits ($m$) | Min Check Bits ($r$) | Codeword Length ($n=m+r$) | Inequality Check $(m+r+1) \le 2^r$ |
| :---: | :---: | :---: | :---: |
| 1 | 2 | 3 | $4 \le 4$ ✅ |
| 4 | 3 | 7 | $8 \le 8$ ✅ |
| 7 | 4 | 11 | $12 \le 16$ ✅ |
| 11 | 4 | 15 | $16 \le 16$ ✅ |
| 57 | 6 | 63 | $64 \le 64$ ✅ |

<br>

## 🐦‍🔥 HAMMING CODE (SINGLE ERROR CORRECTION)

Developed by Richard Hamming. It is a linear, systematic block code with $d_{min} = 3$.

### 1️⃣ Bit Position & Parity Coverage Rules
1. Number codeword bit positions from 1 to $n$ (left to right).
2. Bit positions that are **powers of 2** ($1, 2, 4, 8, 16, \dots$) hold **Check Bits** ($p_1, p_2, p_4, p_8, \dots$).
3. All remaining positions ($3, 5, 6, 7, 9, 10, 11, \dots$) hold **Data Bits** ($d_1, d_2, d_3, \dots$).
4. **Coverage Rule**: Check bit $p_i$ (at position $i$) checks all bit positions $k$ whose binary expansion contains $i$ (i.e., $k \text{ AND } i = i$).

For $m = 7, r = 4, n = 11$ Hamming (11, 7) code:

```
Bit Positions:   1    2    3    4    5    6    7    8    9    10   11
Content:        p1   p2   d1   p4   d2   d3   d4   p8   d5   d6   d7
```

- $p_1$ checks positions: 1, 3, 5, 7, 9, 11 (binary LSB = 1)
- $p_2$ checks positions: 2, 3, 6, 7, 10, 11 (binary 2nd bit = 1)
- $p_4$ checks positions: 4, 5, 6, 7 (binary 3rd bit = 1)
- $p_8$ checks positions: 8, 9, 10, 11 (binary 4th bit = 1)

<br>

## 🛡 Worked Step-by-Step Example: Hamming Code

> 📝 **PROBLEM**:
> Encode the 7-bit message $M = 1000001$ ($d_1 d_2 d_3 d_4 d_5 d_6 d_7 = 1,0,0,0,0,0,1$) using Hamming (11, 7) code with Even Parity.
> Then, simulate a bit flip at position 5 during transmission and show how the receiver locates and corrects the error!

### Step 1: Place Data Bits into Positions
- Pos 1: $p_1$
- Pos 2: $p_2$
- Pos 3: $d_1 = 1$
- Pos 4: $p_4$
- Pos 5: $d_2 = 0$
- Pos 6: $d_3 = 0$
- Pos 7: $d_4 = 0$
- Pos 8: $p_8$
- Pos 9: $d_5 = 0$
- Pos 10: $d_6 = 0$
- Pos 11: $d_7 = 1$

Codeword Draft: `[p1] [p2] 1 [p4] 0 0 0 [p8] 0 0 1`

### Step 2: Compute Check Bits (Even Parity)
- $p_1 = \text{XOR}(\text{Pos } 3, 5, 7, 9, 11) = 1 \oplus 0 \oplus 0 \oplus 0 \oplus 1 = 0$
- $p_2 = \text{XOR}(\text{Pos } 3, 6, 7, 10, 11) = 1 \oplus 0 \oplus 0 \oplus 0 \oplus 1 = 0$
- $p_4 = \text{XOR}(\text{Pos } 5, 6, 7) = 0 \oplus 0 \oplus 0 = 0$
- $p_8 = \text{XOR}(\text{Pos } 9, 10, 11) = 0 \oplus 0 \oplus 1 = 1$

**Transmitted Codeword**: `0 0 1 0 0 0 0 1 0 0 1`

---

### Step 3: Transmission Error Simulation
Suppose an error flips **Bit Position 5** from 0 to 1:
**Received Codeword**: `0 0 1 0 1 0 0 1 0 0 1`

---

### Step 4: Receiver Syndrome Calculation
The receiver re-calculates parity for each coverage group:
- $S_1 = \text{XOR}(1, 3, 5, 7, 9, 11) = 0 \oplus 1 \oplus 1 \oplus 0 \oplus 0 \oplus 1 = 1$ (Fail!)
- $S_2 = \text{XOR}(2, 3, 6, 7, 10, 11) = 0 \oplus 1 \oplus 0 \oplus 0 \oplus 0 \oplus 1 = 0$ (Pass)
- $S_4 = \text{XOR}(4, 5, 6, 7) = 0 \oplus 1 \oplus 0 \oplus 0 = 1$ (Fail!)
- $S_8 = \text{XOR}(8, 9, 10, 11) = 1 \oplus 0 \oplus 0 \oplus 1 = 0$ (Pass)

**Syndrome Vector** $S = (S_8 S_4 S_2 S_1)_2 = (0 1 0 1)_2 = 5_{10}$.

> 🌟 **RESULT**: The binary syndrome $0101_2 = 5$ points directly to **Bit Position 5**!
> The receiver flips Pos 5 back ($1 
ightarrow 0$) and extracts original message $1000001$! ✅

<br>

## 🐦‍🔥 REED-SOLOMON & ADVANCED ERROR CORRECTING CODES

### 1️⃣ Reed-Solomon (RS) Codes
Reed-Solomon codes are non-binary linear block codes that operate on $m$-bit **symbols** (typically bytes, $m=8$, in Galois Field $GF(256)$).

- **Parameters**: An $RS(n, k)$ code appends $n-k$ check symbols to $k$ data symbols (total block length $n$ symbols).
- **Correction Capability**: Can correct up to $t$ symbol errors anywhere in the block:
$$t = \frac{n - k}{2}$$
- **Burst Error Protection**: Since RS codes operate on whole byte symbols, a continuous burst of 16 corrupted bits that spans across 2 adjacent bytes affects only **2 symbols**. While a bit-level Hamming code is overwhelmed by a 16-bit burst, an $RS(255, 223)$ code (which can correct up to $t = (255-223)/2 = 16$ symbol errors) corrects the burst easily!
- **Applications**: CDs, DVDs, Blu-ray, Barcodes/QR codes, Satellite communication, 5G NR, ADSL modems.

### 2️⃣ Low-Density Parity-Check (LDPC) Codes
Linear block codes specified by a sparse parity-check matrix containing mostly zeros. Decoded using iterative belief propagation algorithms, performing extremely close to the Shannon Limit. Used in modern Wi-Fi (802.11n/ac/ax) and 5G NR.

<br>

## 🐦‍🔥 ERROR DETECTING CODES

### 1️⃣ Parity Schemes & 2D Interleaving

- **Single Parity Bit**: Appends 1 bit to make total number of 1s even (Even Parity). $d_{min}=2$; detects single-bit errors, fails on even-number bit flips.
- **2D Parity / Interleaving**: Data arranged in a matrix of $k$ rows and $n$ columns. A parity bit is computed for each column. Transmission occurs row-by-row.

```
Row 1:   1  0  1  1  0  1  0
Row 2:   0  1  1  0  1  0  1
Row 3:   1  1  0  1  1  0  0
Row 4:   0  0  1  1  0  1  1
         -------------------
Parity:  0  0  1  1  0  0  0  (Column Parity Row)
```

> 🛡 **Worked Burst Error Demonstration**:
> Suppose a noise burst corrupts a continuous sequence of 12 bits during row-by-row transmission.
> Because bits are transmitted row-by-row but parity is checked column-by-column, the 12-bit burst error is spread across 12 distinct columns!
> Each column experiences only a **single-bit error**, allowing the column parity to reliably detect (and with 2D row-column parity, correct) the entire 12-bit burst! ✅

---

### 2️⃣ Internet Checksum

Used in IP, UDP, and TCP headers.

- **Algorithm**:
  1. Adjacent 8-bit bytes are paired into 16-bit integers.
  2. Compute 1's complement sum of all 16-bit words (carries beyond 16 bits are wrapped around and added to the LSB).
  3. Complement the final sum to produce the 16-bit checksum.

#### 🛡 Worked Step-by-Step Hex Example (Slide 49)

> 📝 **PROBLEM**: Calculate the IP header checksum for the following 20-byte IP header given in hexadecimal:
> `4500 0073 0000 4000 4011 0000 c0a8 0001 c0a8 00c7` (Checksum field initialized to `0000`).

**SOLUTION**:
1. Pair bytes into 16-bit words and sum them up:
   $$4500 + 0073 + 0000 + 4000 + 4011 + 0000 + c0a8 + 0001 + c0a8 + 00c7$$
   Summing in hex:
   - $4500 + 0073 = 4573$
   - $4573 + 4000 = 8573$
   - $8573 + 4011 = \text{C}584$
   - $\text{C}584 + \text{C}0\text{A}8 = 1862C$
   - $1862C + 0001 = 1862D$
   - $1862D + \text{C}0\text{A}8 = 246D5$
   - $246D5 + 00\text{C}7 = 2479C$

2. Wrap around 16-bit end-around carries:
   The total sum is $2479C_{16}$ (2 is the carry beyond 16 bits).
   $$\text{Sum} = 479C + 2 = 479E_{16}$$

3. Take 1's Complement of $479E_{16}$:
   $$FFFF - 479E = B861_{16}$$
   **Calculated Checksum**: **`B861`** ✅

4. **Receiver Verification**:
   The receiver sums all 16-bit words including `B861`:
   $$2479C + B861 = 2FFFD \implies FFFD + 2 = FFFF_{16}$$
   Taking the 1's complement of $FFFF_{16}$ yields **`0000`** (Zero error detected)! ✅

---

### 3️⃣ Cyclic Redundancy Check (CRC / Polynomial Codes)

CRC treats bit strings as polynomials with binary coefficients ($0$ and $1$).

- A $k$-bit frame is represented as polynomial:
$$M(x) = a_{k-1} x^{k-1} + a_{k-2} x^{k-2} + \dots + a_0 x^0$$
  - Example: Bit string `110001` $
ightarrow M(x) = x^5 + x^4 + 1$.

#### A. Polynomial Arithmetic (Modulo 2)
- Modulo 2 arithmetic without carries or borrows.
- **Addition and Subtraction are both equivalent to XOR ($\oplus$)**:
  - $0 \oplus 0 = 0$, $1 \oplus 1 = 0$, $1 \oplus 0 = 1$, $0 \oplus 1 = 1$.

#### B. CRC Generation Algorithm
Given message polynomial $M(x)$ of length $m$ bits and an agreed Generator Polynomial $G(x)$ of degree $r$:

1. Append $r$ zero bits to the end of the frame (representing $M(x) \cdot x^r$).
2. Divide the bit string $M(x) \cdot x^r$ by $G(x)$ using **Modulo-2 Binary Division**.
3. The $r$-bit remainder $R(x)$ is the CRC checksum.
4. Subtract/XOR the remainder from $M(x) \cdot x^r$ to form transmitted frame $T(x) = M(x) \cdot x^r \oplus R(x)$.

---

### 🛡 Worked Step-by-Step Example: CRC Division

> 📝 **PROBLEM**:
> Frame Payload $M = 110101$ (6 bits).
> Generator Polynomial $G(x) = x^3 + x + 1 
ightarrow$ Bit string `1011` (Degree $r = 3$).
> Compute the transmitted frame $T(x)$.

### Step 1: Append $r = 3$ zeros to $M$
$$M \cdot x^3 = 110101000$$

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

Remainder $R = 111$.

### Step 3: Form Transmitted Frame $T(x)$
$$T(x) = 110101000 \oplus 111 = 110101111$$
Transmitted Frame: `1 1 0 1 0 1 1 1 1` ✅

---

### 4️⃣ CRC Error Detection Proofs & Guarantees

Let $T(x)$ be the transmitted codeword polynomial, $E(x)$ be the error polynomial added by channel noise, and $T'(x) = T(x) \oplus E(x)$ be the received frame.
The receiver computes $T'(x) / G(x) = (T(x) \oplus E(x)) / G(x) = E(x) / G(x)$.
An error goes undetected **if and only if** $E(x)$ is cleanly divisible by $G(x)$!

1. **Single-Bit Errors**: $E(x) = x^i$.
   If $G(x)$ has two or more terms (e.g. $x^r + \dots + 1$), $G(x)$ can never divide $x^i$. Thus, **ALL single-bit errors are detected**!
2. **Double-Bit Errors**: $E(x) = x^i + x^j = x^j (x^{i-j} + 1)$.
   If $G(x)$ does not divide $x^k + 1$ for any $k \le \text{frame length}$, **ALL double-bit errors are detected**!
3. **Odd Number of Bit Errors**:
   Any polynomial with an odd number of terms has no factor of $(x+1)$. If $G(x)$ contains $(x+1)$ as a factor, **ALL odd numbers of bit errors are detected**!
4. **Burst Errors of Length $k \le r$**: $E(x) = x^i (x^{k-1} + \dots + 1)$.
   The degree of the burst term is $k-1 < r$. Since degree of $G(x)$ is $r$, $G(x)$ cannot divide it. Thus, **ALL burst errors of length $\le r$ are detected with 100% certainty**!
5. **Burst Errors of Length $k = r + 1$**: Undetected with probability $2^{-(r-1)}$.
6. **Burst Errors of Length $k > r + 1$**: Undetected with probability $2^{-r}$.

<br>

---

<br>

## 🐦‍🔥 4. DATA LINK LAYER PROTOCOLS & REAL-WORLD IMPLEMENTATIONS (CHAPTER 4)

## 🔥 Elementary Data Link Protocols

### 1️⃣ Protocol Environment & Programming Primitives

In standard protocol design (as presented in Tanenbaum), protocols are event-driven software modules operating with clear abstractions:

```
                  +-----------------------+
                  |     Network Layer     |
                  +-----------------------+
                     |                 ^
  from_network_layer |                 | to_network_layer
                     v                 |
                  +-----------------------+
                  |    Data Link Layer    |  <-- Peer Protocol Software
                  +-----------------------+
                     |                 ^
   to_physical_layer |                 | from_physical_layer
                     v                 |
                  +-----------------------+
                  |    Physical Layer     |
                  +-----------------------+
```

#### Shared C-Like Primitive Definitions & Data Types:
```c
typedef enum { frame_arrival, cksum_err, timeout } event_type;
typedef unsigned int seq_nr;

typedef struct {
    unsigned char data[MAX_PKT];
} packet;

typedef struct {
    seq_nr seq;          // Sequence number
    seq_nr ack;          // Acknowledgement number
    int kind;            // Frame type (DATA, ACK, NAK)
    packet info;         // Data payload
    unsigned int cksum;  // Checksum
} frame;

// Protocol API primitives provided by environment:
void wait_for_event(event_type *event);
void from_network_layer(packet *p);
void to_network_layer(packet *p);
void from_physical_layer(frame *r);
void to_physical_layer(frame *s);
void start_timer(seq_nr k);
void stop_timer(seq_nr k);
```

---

### 2️⃣ Protocol 1: Simplex Utopian Protocol

- **Assumptions**: Unidirectional data transfer; perfectly reliable physical channel (zero bit errors or lost frames); infinite receiver buffer space and instant processing.

```c
// Sender Protocol 1
void sender1(void) {
    packet buffer;
    frame s;
    while (true) {
        from_network_layer(&buffer);
        s.info = buffer;
        to_physical_layer(&s);
    }
}

// Receiver Protocol 1
void receiver1(void) {
    frame r;
    event_type event;
    while (true) {
        wait_for_event(&event);
        from_physical_layer(&r);
        to_network_layer(&r.info);
    }
}
```

---

### 3️⃣ Protocol 2: Simplex Stop-and-Wait Protocol (Error-Free Channel)

- **Assumptions**: Error-free channel, but receiver has **finite processing speed and buffer space**.
- **Flow Control Mechanism**: Sender transmits 1 frame, then stops and waits for an explicit Acknowledgement frame (`ACK`) from receiver before transmitting the next frame.

```
Sender                                              Receiver
  |                                                    |
  | ------------------ Frame Data -------------------> | (Passes data to L3)
  |                                                    |
  | <----------------- ACK Frame --------------------  | (Grants permission for next frame)
  |                                                    |
  | ------------------ Frame Data -------------------> |
```

```c
// Sender Protocol 2
void sender2(void) {
    packet buffer;
    frame s, r;
    event_type event;
    while (true) {
        from_network_layer(&buffer);
        s.info = buffer;
        to_physical_layer(&s);
        wait_for_event(&event);  // Wait for ACK arrival
        from_physical_layer(&r);
    }
}

// Receiver Protocol 2
void receiver2(void) {
    frame r, s;
    event_type event;
    while (true) {
        wait_for_event(&event);
        from_physical_layer(&r);
        to_network_layer(&r.info);
        to_physical_layer(&s);   // Send dummy ACK frame
    }
}
```

---

### 4️⃣ Protocol 3: Simplex Stop-and-Wait for Noisy Channel (PAR)

- **Assumptions**: Physical channel can corrupt or completely drop frames and ACKs.
- **Positive Acknowledgement with Retransmission (PAR)**:
  - Sender sets a **Timer** when transmitting a frame. If ACK does not arrive before timeout, sender retransmits.
  - **Sequence Numbers**: Required to prevent duplicate frame delivery when ACKs are delayed or lost.
  - **1-Bit Sequence Numbers ($0$ and $1$)**: Because ambiguity only exists between frame $m$ and its immediate successor $m+1$, 1-bit sequence numbers are necessary and sufficient!

```c
// Sender Protocol 3 (PAR)
void sender3(void) {
    seq_nr next_frame_to_send = 0;
    packet buffer; frame s, r; event_type event;
    from_network_layer(&buffer);
    while (true) {
        s.info = buffer;
        s.seq = next_frame_to_send;
        to_physical_layer(&s);
        start_timer(s.seq);
        wait_for_event(&event);
        if (event == frame_arrival) {
            from_physical_layer(&r);
            if (r.ack == next_frame_to_send) {
                stop_timer(r.ack);
                from_network_layer(&buffer);
                next_frame_to_send = 1 - next_frame_to_send; // Alternate 0 <-> 1
            }
        } else if (event == timeout) {
            to_physical_layer(&s);  // Retransmit
            start_timer(s.seq);
        }
    }
}

// Receiver Protocol 3 (PAR)
void receiver3(void) {
    seq_nr frame_expected = 0;
    frame r, s; event_type event;
    while (true) {
        wait_for_event(&event);
        if (event == frame_arrival) {
            from_physical_layer(&r);
            if (r.seq == frame_expected) {
                to_network_layer(&r.info);
                frame_expected = 1 - frame_expected;
            }
            s.ack = 1 - frame_expected; // ACK last valid frame
            to_physical_layer(&s);
        }
    }
}
```

<br>

## 🐦‍🔥 SLIDING WINDOW PROTOCOLS

Full-duplex communication allows simultaneous bidirectional data transfer. **Piggybacking** attaches the ACK number into the header of an outgoing data frame to avoid sending standalone ACK frames.

```
Sender Window (Ws):      [  3   4   5   6  ] 7   8   9
                          ^               ^
                          |               |
                    First unACKed      Last frame sent
```

### 1️⃣ 1-Bit Sliding Window Protocol

Sender window $W_s = 1$, Receiver window $W_r = 1$. Sequence numbers alternate between 0 and 1.

#### Pathological Duplicate Frame Cycle (Resiliency Analysis)
If both stations transmit simultaneously (e.g. Host A and Host B both initiate sending frame 0 at time $t=0$), the protocol enters a pathological lockstep state:
- Each host receives frame 0, accepts it, and sends ACK 0 piggybacked on its next frame 1.
- However, when ACK 0 arrives, each host interprets it as an ACK for its previous frame, but then receives duplicate copies of frame 0!
- Every frame is delivered **twice** to the network layer, cutting effective bandwidth in half!

---

### 2️⃣ Go-Back-N (GBN) Protocol

Pipelining protocol that allows the sender to transmit up to $W_s$ frames before receiving an ACK.

```
Sender Window (Ws = 7):   [ 0  1  2  3  4  5  6 ] 7  0  1
Receiver Window (Wr = 1): [ 0 ]
```

#### A. Bandwidth-Delay Product & Optimal Window Size
Let $t_{trans} = L / R$ be frame transmission time, $t_{prop}$ be one-way propagation delay.
The round-trip delay is $2 \cdot t_{prop}$. The number of frames that fit into the channel pipe during one round-trip is:
$$a = \frac{t_{prop}}{t_{trans}}$$
$$\text{Optimal Window Size } w = 2 \cdot a + 1 = 1 + \frac{2 \cdot t_{prop} \cdot R}{L}$$

#### B. Link Efficiency Formula
$$\eta = \min\left(1, \frac{W_s}{1 + 2a}
ight)$$

#### C. Mathematical Proof: Maximum Sender Window Bound ($W_s \le 2^m - 1$)
For $m$-bit sequence numbers, total sequence space is $2^m$.

> 🛡 **PROOF BY COUNTEREXAMPLE (Why $W_s \le 2^m - 1$ is Mandatory)**:
> Suppose sequence numbers are 2-bit ($m=2$, sequence space $0, 1, 2, 3$, size $2^2 = 4$).
> Suppose we incorrectly set $W_s = 2^m = 4$.
> 1. Sender transmits frames 0, 1, 2, 3 ($W_s = 4$).
> 2. Receiver receives all 4 frames, sends cumulative ACK 3, and advances its expected sequence number to **0**.
> 3. **CRITICAL FAILURE**: Suppose ALL ACKs are lost in transit!
> 4. Sender times out and retransmits frame **0**.
> 5. Receiver is expecting frame **0** (the new frame 0 of the next window). It accepts retransmitted frame 0 as NEW DATA! Duplicate frame delivered! ❌
>
> 🌟 **Conclusion**: To prevent overlap between retransmitted frames and new frames, $W_s$ must never exceed $2^m - 1$! For $m=2$, $W_s \le 3$.

---

### 3️⃣ Selective Repeat (SR) Protocol

Avoids retransmitting undamaged frames by maintaining a receiver window $W_r > 1$ and buffering out-of-order frames.

```
Sender Window (Ws = 4):   [ 3  4  5  6 ] 7  0  1
Receiver Window (Wr = 4): [ 3  4  5  6 ]
```

#### Mathematical Proof: Window Size Bound ($W_s + W_r \le 2^m \Rightarrow W_s = W_r \le 2^{m-1}$)

> 🛡 **PROOF (Overlap Prevention)**:
> Suppose sequence numbers are $m$-bit (space $2^m$).
> When receiver acknowledges a window, its receive window moves forward by up to $W_r$.
> To ensure the new receiver window does not overlap with the old unacknowledged sender window in modulo $2^m$ arithmetic:
> $$W_s + W_r \le 2^m$$
> Since maximum efficiency occurs when $W_s = W_r$:
> $$W_s = W_r \le 2^{m-1}$$
>
> *Example*: For 3-bit sequence numbers ($2^3 = 8$), maximum window size for Selective Repeat is $W_s = W_r = 4$!

---

### 4️⃣ Comprehensive Comparison of Sliding Window Protocols

| Property | Stop-and-Wait | Go-Back-N (GBN) | Selective Repeat (SR) |
| :--- | :--- | :--- | :--- |
| Sender Window Size ($W_s$) | $1$ | $2^m - 1$ | $2^{m-1}$ |
| Receiver Window Size ($W_r$) | $1$ | $1$ | $2^{m-1}$ |
| Acknowledgement Type | Individual | Cumulative | Individual / Negative ACK (`NAK`) |
| Out-of-Order Receiver Buffer | No | No (Silently Discarded) | Yes (Buffered in memory) |
| Retransmission Target | Single frame | Entire window ($N$ frames) | Only lost/corrupted frame |
| Link Utilization Efficiency | Low ($\frac{1}{1+2a}$) | High ($\frac{W_s}{1+2a}$) | Maximum ($\frac{W_s}{1+2a}$) |
| Receiver Complexity | Minimal | Low | High (Sorting & Buffer Mgmt) |

<br>

## 🐦‍🔥 REAL-WORLD DATA LINK PROTOCOLS

### 1️⃣ Packet over SONET (PoS)
Used over wide-area optical fiber links (backbones). SONET (Synchronous Optical Network) provides Physical Layer framing (e.g. STS-3 / OC-3 at 155.52 Mbps), while PPP encapsulates IP packets into SONET payloads.

---

### 2️⃣ Point-to-Point Protocol (PPP)

Standard data link protocol for point-to-point router links, dial-up, and ADSL.

```
+----------+----------+----------+----------+--------------------+----------+
|   Flag   | Address  | Control  | Protocol |  Payload (Data)    | FCS CRC  |
| 1 Byte   | 1 Byte   | 1 Byte   | 2 Bytes  | Variable (<= MRU)  | 2/4 Bytes|
|  0x7E    |   0xFF   |   0x03   |          |                    |          |
+----------+----------+----------+----------+--------------------+----------+
```

#### Field Breakdown:
- **Flag**: `0x7E` (`01111110`) frame delimiter.
- **Address**: `0xFF` (All-stations broadcast address; PPP does not assign individual node addresses).
- **Control**: `0x03` (Unnumbered Information frame).
- **Protocol**: Specifies payload PDU type:
  - `0x0021`: IPv4 Datagram
  - `0x0057`: IPv6 Datagram
  - `0xC021`: Link Control Protocol (LCP)
  - `0xC023`: Password Authentication Protocol (PAP)
  - `0xC223`: Challenge Handshake Authentication Protocol (CHAP)
  - `0x8021`: IP Control Protocol (IPCP)
- **FCS**: 16-bit or 32-bit CRC checksum.

#### PPP Link Phase & LCP State Transition Diagram:

```
   [ DEAD ] -------- (Physical Link Detected) -------> [ ESTABLISH ]
      ^                                                     |
      | (Link Failure)                          (LCP Config Agreed)
      |                                                     v
   [ TERMINATE ] <--- (Teardown) --- [ OPEN ] <--- [ AUTHENTICATE ]
```

1. **DEAD**: Physical layer link is inactive.
2. **ESTABLISH**: LCP negotiates link parameters (MRU, Async Control Character Map).
3. **AUTHENTICATE**: Optional authentication phase (PAP or CHAP).
   - **PAP (Password Auth Protocol)**: 2-way handshake; sends username/password in cleartext (Insecure).
   - **CHAP (Challenge Handshake Auth Protocol)**: 3-way handshake; server sends random Challenge string, client hashes Challenge + Password using MD5 and returns Response. Password never travels over the wire!
4. **NETWORK**: NCP protocols (e.g., IPCP) configure network layer parameters (assigning dynamic IPv4 address, DNS servers).
5. **OPEN**: Data transfer phase.
6. **TERMINATE**: Link teardown via LCP terminate frames.

---

### 3️⃣ ADSL (Asymmetric Digital Subscriber Line)

Provides broadband Internet over legacy copper twisted-pair telephone local loops.

```
[ Customer PC ] ---> [ ADSL Modem ] ---> (Splitter) === Local Loop ===> [ DSLAM ] ---> [ ISP Core ]
```

#### A. Architecture & DSLAM
- **POTS Splitter**: Filters high-frequency data signals from low-frequency voice signals ($0-4\text{ kHz}$).
- **DSLAM (DSL Access Multiplexer)**: Located at telephone central office; terminates hundreds of customer ADSL lines and multiplexes traffic onto high-speed optical backbones.

#### B. Frequency Spectrum Allocation & Discrete Multi-Tone (DMT)
ADSL divides the $1.1\text{ MHz}$ copper frequency spectrum into **256 independent subchannels** of $4.3125\text{ kHz}$ bandwidth:

```
  0   4 kHz     25 kHz           138 kHz                       1.1 MHz
  +-----+---------+----------------+------------------------------+
  | Voice| Guard   | Upstream Data  | Downstream Data              |
  | (0-5)| Band    | (Channels 6-31)| (Channels 32-255)            |
  +-----+---------+----------------+------------------------------+
```

- Subchannels 0–5 ($0-4\text{ kHz}$): POTS Voice.
- Subchannels 6–31 ($25-138\text{ kHz}$): Upstream Data (Customer to ISP).
- Subchannels 32–255 ($138-1104\text{ kHz}$): Downstream Data (ISP to Customer).
- **DMT Modulation**: Each subchannel uses QAM modulation. Subchannels experiencing high noise carry fewer bits per baud (e.g. QAM-4), while clean subchannels carry up to 15 bits per baud (QAM-32768).

#### C. ADSL Protocol Stack

```
+------------------------------------+
|               IP                   |
+------------------------------------+
|              PPP                   |
+------------------------------------+
|       AAL5 (ATM Adaptation L5)    |
+------------------------------------+
|       ATM (Asynchronous Transfer)  |
+------------------------------------+
|       ADSL Physical (DMT / Copper) |
+------------------------------------+
```

<br>

---

<br>

## 🐦‍🔥 5. MEDIUM ACCESS CONTROL (MAC) SUBLAYER (CHAPTER 5)

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
- Vulnerable period $= 2 \cdot  au$ (where $ au$ is frame duration).
- Throughput equation ($G =$ offered load):
$$S = G \cdot e^{-2G}$$
- Maximum Throughput $= \frac{1}{2e} \approx 0.184$ (18.4%) at $G = 0.5$.

2️⃣ **Slotted ALOHA**:
- Time divided into discrete slots of duration $ au$. Stations can only transmit at slot boundaries.
- Vulnerable period $=  au$.
- Throughput equation:
$$S = G \cdot e^{-G}$$
- Maximum Throughput $= \frac{1}{e} \approx 0.368$ (36.8%) at $G = 1.0$.

---

### 2️⃣ CSMA (Carrier Sense Multiple Access) Protocols

Stations listen to the channel before transmitting ("Listen Before Talk").

1️⃣ **1-Persistent CSMA**:
- Listen to channel. If idle, transmit immediately (probability 1). If busy, continuously sense channel until idle, then transmit immediately.
- High collision chance if multiple stations were waiting.

2️⃣ **Non-Persistent CSMA**:
- Listen to channel. If idle, transmit. If busy, wait a random time interval before sensing again. Reduces collisions, but increases idle delay.

3️⃣ **p-Persistent CSMA** (Slotted channels):
- If channel is idle, transmit frame with probability $p$, and defer to next slot with probability $1-p$.

---

### 3️⃣ CSMA/CD (Carrier Sense Multiple Access with Collision Detection)

Standard used in classic Wired Ethernet (IEEE 802.3).

- **Listen While Transmitting**: Sender monitors channel during transmission. If collision detected, abort transmission immediately, transmit a **Jam Signal**, and execute **Binary Exponential Backoff**.

> 🛡 **BINARY EXPONENTIAL BACKOFF**:
> After $c$ collisions, sender picks random slot $k$ in range $[0, 2^{\min(c, 10)} - 1]$ and waits $k \cdot 512 \text{ bit times}$ ($51.2\ \mu\text{s}$) before retrying. Aborts after 16 failed attempts.

> 📝 **MINIMUM FRAME SIZE DERIVATION**:
> To ensure a sender detects a collision before completing transmission, transmission time $t_{trans}$ must be at least twice the end-to-end propagation delay ($2 \cdot t_{prop}$):
> $$t_{trans} \ge 2 \cdot t_{prop} \implies \frac{L_{min}}{R} \ge 2 \cdot t_{prop} \implies L_{min} = 2 \cdot t_{prop} \cdot R$$
> For $10\text{ Mbps}$ Ethernet over $2.5\text{ km}$ max distance ($t_{prop} = 25.6\ \mu\text{s}$):
> $$L_{min} = 2 \cdot (25.6  imes 10^{-6}\text{ s}) \cdot (10^7\text{ bps}) = 512\text{ bits} = 64\text{ Bytes}$$

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
- **Type / Length**: If $\le 1500$, specifies payload length; if $\ge 1536$, specifies EtherType protocol (e.g., `0x0800` for IPv4).
- **Data Payload**: 46 to 1500 bytes (padded if $< 46$ bytes to meet 64-byte $L_{min}$).
- **FCS (Frame Check Sequence)**: 4-byte CRC-32 checksum.

<br>

</div>
</div>
