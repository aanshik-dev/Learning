<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **NETWORK LAYER NOTES** 🔥🐦‍🔥

<br>

## 🐦‍🔥 FACTS & ESSENTIAL DEFINITIONS

- **Network Layer (Layer 3)**: The lowest layer responsible for end-to-end (host-to-host) communication, getting packets from the original source across multiple intermediate network hops all the way to the final destination.
- **Data Plane (Forwarding)**: The local, per-router function that moves an incoming packet from an input link interface to the appropriate output link interface using the router's local forwarding table. Typically implemented in specialized hardware (ASICs/TCAM) operating at line rate (nanoseconds).
- **Control Plane (Routing)**: The network-wide logic that coordinates routers to compute the end-to-end paths that packets traverse from source to destination. Implemented in software running on the router CPU or a centralized SDN controller.
- **Store-and-Forward**: A packet must be completely received, verified for integrity (checksum), and temporarily buffered in router memory before it can be transmitted onto the next outgoing link.
- **Autonomous System (AS)**: A collection of connected routers and subnets under a single administrative control, presenting a common, clearly defined routing policy to the Internet.
- **Maximum Transmission Unit (MTU)**: The maximum frame payload size (in bytes) that a specific physical network layer can carry without fragmenting.

<br>

---

<br>

## 🐦‍🔥 5.1 NETWORK LAYER DESIGN ISSUES

### 1️⃣ Store-and-Forward Packet Switching

> 💡 **Analogy (Hinglish)**: Store-and-Forward ko ek Speed Post hub ki tarah samjho. Jab post office mein koi parcel aata hai, toh postmaster pehle pura parcel physically receive karta hai, uska address aur seal check karta hai (store), fir usko agle shahar jaane wali sahi truck mein daalta hai (forward). Aisa nahi ho sakta ki aadha dabba aate hi aage bhej de!

- **Operational Mechanism**:
  1. A source host breaks application messages into packets and transmits them to the nearest edge router (via LAN or point-to-point link).
  2. The router buffers the complete packet in memory until all bits have arrived and verifies its checksum to ensure error-free reception.
  3. The router inspects the packet header (destination IP address or virtual circuit identifier), consults its internal routing/forwarding table, and places the packet onto the queue of the appropriate outgoing transmission line.
  4. The packet moves hop-by-hop through intermediate routers until it reaches the destination host.

```
[ Host H1 ] ---> [ Router R1 ] =======> [ Router R2 ] =======> [ Router R3 ] ---> [ Host H2 ]
                  | Store: buffer        | Store: buffer        | Store: buffer
                  | Check: checksum      | Check: checksum      | Check: checksum
                  | Forward: next hop    | Forward: next hop    | Forward: deliver
```

- **Transmission vs. Propagation Delay across N Hops**:
  For a packet of length L bits over N successive links of bandwidth R bps and propagation delay d_prop:
  $$\text{Total Delay} = N \cdot \left( \frac{L}{R} \right) + N \cdot d_{prop} + \sum d_{queue}$$

<br>

### 2️⃣ Services Provided to the Transport Layer

The network layer provides an interface to the transport layer above it. Historically, two opposing engineering philosophies emerged regarding this interface:

```
+--------------------------------------------------------------------------------+
| DUMB NETWORK vs. SMART NETWORK PHILOSOPHY                                      |
+--------------------------------------------------------------------------------+
| 1. THE INTERNET PHILOSOPHY (Connectionless / Best-Effort):                     |
|    - Routers should be simple and fast: moving packets and nothing else!       |
|    - The subnet is inherently unreliable; end hosts run smart protocols (TCP) |
|      to handle error control, retransmission, and flow control (End-to-End).   |
+--------------------------------------------------------------------------------+
| 2. THE TELEPHONY / ATM PHILOSOPHY (Connection-Oriented / QoS):                 |
|    - The network core should be smart and reliable, providing strict guarantees|
|      (guaranteed bandwidth, bounded delay, zero loss) like the phone system.   |
|    - End hosts (dumb terminals/telephones) need not worry about reliability.   |
+--------------------------------------------------------------------------------+
```

> 💡 **Analogy (Hinglish)**: Internet philosophy ka manna hai ki "Sadak (network) ka kaam sirf gaadi chalne dena hai — agar gaadi kharab hui toh passenger (end host) khud mechanic bulaye". Jabki Telephony philosophy bolti hai ki "Hum train chalayenge, jisme seat reservation, khana, aur safety sab railway department (network core) ki zimmedari hogi".

- **Core Design Goals for the Network Layer Service**:
  - Services must be independent of the physical router technologies and transmission media.
  - The transport layer should be shielded from the number, topology, and physical boundaries of subnets.
  - Network addresses presented to the transport layer must follow a uniform, global numbering plan (e.g., IP addresses), spanning LANs and WANs seamlessly.

<br>

### 3️⃣ Implementation of Connectionless Service (Datagram Networks)

> 💡 **Analogy (Hinglish)**: Datagram network bilkul normal postal mail (chitthi) jaisa hai. Har chitthi ke upar pura destination address likha hota hai. Agar tumne 4 chitthiyan ek ke baad ek post box mein daali, toh zaroori nahi ki charo ek hi daak-gaadi se jayein! Koi Bhopal hoke ja sakti hai, koi Nagpur hoke, aur aage-peeche bhi pahunch sakti hain.

- **Key Principles**:
  - Packets are termed **Datagrams** (analogous to telegrams).
  - No connection setup phase: hosts inject packets into the network at any time.
  - Each datagram carries the complete destination address in its header.
  - Intermediate routers examine each incoming packet's destination address, look up their forwarding table, and choose the outgoing line.
  - Successive packets belonging to the same application stream can follow entirely different routes depending on network load or topology changes.

```
[ Host H1 ] --(Packet 1, 2, 3)--> [ Router A ]
                                     /      \
               Route via B (Fast)   /        \   Route via C (Backup)
                                   v          v
                             [ Router B ]   [ Router C ]
                                   \          /
                                    \        /
                                     v      v
                                   [ Router D ] --(Packet 2, 1, 3)--> [ Host H2 ]
                                   (Out-of-order arrival possible!)
```

- **Datagram Routing Table Example**:
  Each router maintains a table mapping destination address prefixes to outgoing interfaces.

| Destination Prefix | Next Hop Router | Outgoing Interface |
| :----------------- | :-------------- | :----------------- |
| `128.208.0.0/16`   | Router B        | `eth0`             |
| `192.168.1.0/24`   | Router C        | `eth1`             |
| Default (`0.0.0.0`)| Gateway R       | `eth2`             |

<br>

### 4️⃣ Implementation of Connection-Oriented Service (Virtual-Circuit Networks)

> 💡 **Analogy (Hinglish)**: Virtual Circuit (VC) bilkul traditional landline phone call jaisa hai. Pehle number dial karke "trin-trin" connection setup hota hai. Ek baar call connect ho gaya, toh saari aawaz (data packets) usi established circuit se travel karti hai. Packet ko pura address carry karne ki zarurat nahi hoti, sirf ek chhota sa token (VC ID) kaafi hota hai!

- **Key Principles**:
  - A path from source to destination must be explicitly established before any data packets can be transmitted. This logical path is called a **Virtual Circuit (VC)**.
  - Setup uses signaling protocols (e.g., RSVP, ATM Q.2931). During setup, intermediate routers allocate resources (buffers, bandwidth, CPU) and insert routing state into their internal tables.
  - Each packet does **not** carry the full destination address; instead, it carries a short, local **Virtual Circuit Identifier (VCI / Label)** in its header.
  - When the data transfer completes, a teardown phase releases the reserved resources and deletes the table entries.

```
Connection Setup:
Host A =========(Setup Request)=========> Router R1 ========> Router R2 ========> Host B
Host A <========(Setup Confirmed)======== Router R1 <======== Router R2 <======== Host B

Data Transfer:
Host A ---[VC: 1 | Data]---> Router R1 ---[VC: 7 | Data]---> Router R2 ---[VC: 3 | Data]---> Host B
```

- **VC Table Structure**:
  Because different circuits sharing a physical link cannot use the same VCI, each router translates incoming VCIs to outgoing VCIs on a per-hop basis:

| Incoming Line | Incoming VC # | Outgoing Line | Outgoing VC # |
| :------------ | :------------ | :------------ | :------------ |
| Line 1 (from H1) | 1          | Line 3 (to R2)| 7             |
| Line 2 (from H3) | 1          | Line 4 (to R3)| 2             |
| Line 3 (from R2) | 4          | Line 1 (to H1)| 9             |

<br>

### 5️⃣ Comparison of Virtual-Circuit and Datagram Networks

| Evaluation Metric | Datagram Network (e.g., Internet IP) | Virtual-Circuit Network (e.g., ATM, MPLS, Frame Relay) |
| :--- | :--- | :--- |
| **Circuit Setup** | ❌ None. Packets sent immediately without delay. | ✅ Compulsory setup and teardown phases required. |
| **Addressing** | Full source and destination addresses in every packet (20-40 bytes overhead). | Short VC identifier (1-4 bytes) in each packet header. |
| **Router State** | Routers maintain no per-flow connection state; only destination prefix tables. | Routers store state for every active VC traversing them. |
| **Routing Decisions** | Each packet is routed independently; routes may change dynamically. | Route is fixed during setup; all packets follow the same path. |
| **Router Failure Impact** | 🛡️ Highly resilient. Packets easily rerouted around failed routers. | ❌ Catastrophic. All VCs passing through failed router are terminated. |
| **Quality of Service (QoS)** | Difficult to guarantee; traditionally best-effort. | Easy to guarantee: resources (bandwidth/buffers) pre-allocated at setup. |
| **Congestion Control** | Reactive and complex; relies on end-point throttling (TCP) or packet drops. | Preventative: new calls rejected if insufficient bandwidth (Admission Control). |
| **Complexity Location** | At the edge (smart hosts running TCP/UDP; dumb network core). | In the network core (smart switches; dumb host terminals). |

> 📝 NOTE : The Internet chose the **Datagram model** because:
> 1. Resilience: During the Cold War (ARPANET design), military robustness against node failure was the primary design priority.
> 2. Heterogeneity: Easy to interconnect wildly different underlying network hardware.
> 3. Scaling: Routers do not keep per-flow state, allowing millions of concurrent flows without running out of memory.

<br>

---

## 🐦‍🔥 5.2 ROUTING ALGORITHMS

### 🔥 Routing vs. Forwarding & Algorithm Classification

- **Forwarding (Data Plane)**: When a packet arrives on an input link, the router inspects its header, consults its forwarding table, and directs it to the appropriate output interface.
- **Routing (Control Plane)**: The network-wide process that decides the end-to-end paths packets follow from source to destination.
- **Classes of Routing Algorithms**:
  - **Non-Adaptive (Static) Routing**: Routes do not depend on current network traffic or topology. Paths are calculated offline in advance and manually loaded into routers at boot time.
  - **Adaptive (Dynamic) Routing**: Routes change dynamically based on topological changes (link/router failures) and traffic congestion. Parameters considered include delay, packet loss, and hop count.

<br>

### 1️⃣ 5.2.1 The Optimality Principle & Sink Trees

> 💡 **Analogy (Hinglish)**: Optimality Principle ka seedha matlab hai: Agar Delhi se Mumbai jaane ka best rasta Jaipur aur Ahmedabad hoke jata hai, toh Jaipur se Mumbai jaane ka best rasta bhi wahi Ahmedabad wala hi hoga. Aisa nahi ho sakta ki Delhi wale ke liye Ahmedabad se best rasta ho, par Jaipur wale ke liye koi chamatkari naya rasta nikal aaye!

- **Statement**: If router $J$ is on the optimal path from router $I$ to router $K$, then the optimal path from $J$ to $K$ falls along the exact same route.
- **Proof by Contradiction**:
  - Suppose a route $r_{JK}'$ existed from $J$ to $K$ with lower cost than the sub-path $r_{JK}$ of the optimal path $r_{IK} = r_{IJ} + r_{JK}$.
  - Then the concatenated path $r_{IJ} + r_{JK}'$ would have total cost less than $r_{IK}$.
  - This contradicts the initial premise that $r_{IK}$ was the optimal path.
  - Hence, no better path from $J$ to $K$ can exist.

- **The Sink Tree**:
  - As a direct consequence of the Optimality Principle, the set of optimal paths from all network sources to a given destination router forms a directed tree rooted at the destination, termed a **Sink Tree**.
  - **Key Properties**:
    - A tree contains **no cycles (loops)**: each packet is delivered in a finite, bounded number of hops.
    - Sink trees are **not necessarily unique**: alternative paths with identical metric lengths may form different valid sink trees.
    - The objective of every routing algorithm is to discover and maintain the sink tree for every destination.

```
Sink Tree for Destination Node 'G':

     (A) ----> (B)
                      (C) ----> (D) ----> (G) [ROOT / SINK]
                 /
     (E) ----> (F)
```

<br>

### 2️⃣ 5.2.2 Shortest Path Routing (Dijkstra's Algorithm)

> 💡 **Analogy (Hinglish)**: Dijkstra ka algorithm bilkul Google Maps ki tarah kaam karta hai. Sabse pehle source node se start karo jiska distance 0 hai. Ab uske sabhi seedhe judhe padosiyon ka distance note karo (tentative labels). Jo sabse kareeb hai, usko "Permanent" (pakka) mark kar do. Phir wahan se agle raste dekho aur agar koi chhota shortcut mile toh distance update kar do (Relaxation). Tab tak karte raho jab tak saare shehar pakke na ho jayein!

Dijkstra's algorithm computes the shortest paths from a single source node to all other nodes in a graph with non-negative edge weights (representing distance, bandwidth inverse, propagation delay, or economic cost).

- **Algorithm Mechanics**:
  - Each node $v$ maintains a state label: $(d(v), p(v))$, where $d(v)$ is the shortest path distance known from source to $v$, and $p(v)$ is the predecessor node on that path.
  - Nodes are partitioned into two sets:
    - **Permanent Set ($S$)**: Shortest path from source is definitively determined.
    - **Tentative Set ($Q$)**: Tentative estimates that may be updated.
  - **Step 1: Initialization**:
    - Set $d(\text{source}) = 0$, $p(\text{source}) = \text{None}$, and place source in $S$.
    - For all other nodes $v$, set $d(v) = \infty$, $p(v) = \text{None}$.
  - **Step 2: Relaxation**:
    - For the newly permanent node $u$, examine all tentative neighbors $v$:
      $$\text{If } d(u) + c(u, v) < d(v) \implies d(v) = d(u) + c(u, v), \quad p(v) = u$$
  - **Step 3: Selection**:
    - Select node $w \in Q$ having the minimum tentative distance $d(w)$.
    - Make $w$ permanent ($S \leftarrow S \cup \{w\}$, $Q \leftarrow Q \setminus \{w\}$).
  - **Step 4: Termination**:
    - Repeat Steps 2 and 3 until all nodes become permanent ($Q = \emptyset$).

---

#### 🔥 Step-by-Step Demonstration of Dijkstra's Algorithm

Consider a 6-node network graph with bidirectional weighted edges:
- Links: $(A, B) = 2$, $(A, C) = 4$, $(B, C) = 1$, $(B, D) = 7$, $(C, E) = 3$, $(D, E) = 2$, $(D, F) = 1$, $(E, F) = 5$.
- Goal: Find shortest paths from **Source A** to all destinations.

```
       (2)         (7)
   [A]-------[B]---------[D]
    |       /             | \ (1)
 (4)|    (1)/          (2)|  [F]
    |   /                 | / (5)
   [C]-------[E]----------+
       (3)
```

**Step-by-Step Execution Table**:

| Step | Working Node Selected ($u$) | Permanent Set ($S$) | Label B | Label C | Label D | Label E | Label F |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **0** (Init) | - | $\{A\}$ | $(\infty, -)$ | $(\infty, -)$ | $(\infty, -)$ | $(\infty, -)$ | $(\infty, -)$ |
| **1** | **A** ($d=0$) | $\{A\}$ | **$(2, A)$** | $(4, A)$ | $(\infty, -)$ | $(\infty, -)$ | $(\infty, -)$ |
| **2** | **B** ($d=2$) | $\{A, B\}$ | Permanent | **$(3, B)$** | $(9, B)$ | $(\infty, -)$ | $(\infty, -)$ |
| **3** | **C** ($d=3$) | $\{A, B, C\}$ | Permanent | Permanent | $(9, B)$ | **$(6, C)$** | $(\infty, -)$ |
| **4** | **E** ($d=6$) | $\{A, B, C, E\}$ | Permanent | Permanent | **$(8, E)$** | Permanent | $(11, E)$ |
| **5** | **D** ($d=8$) | $\{A, B, C, E, D\}$ | Permanent | Permanent | Permanent | Permanent | **$(9, D)$** |
| **6** | **F** ($d=9$) | All Nodes | Permanent | Permanent | Permanent | Permanent | Permanent |

- **Shortest Paths from Source A**:
  - To **B**: Path $A \to B$ (Cost: 2)
  - To **C**: Path $A \to B \to C$ (Cost: 3)
  - To **E**: Path $A \to B \to C \to E$ (Cost: 6)
  - To **D**: Path $A \to B \to C \to E \to D$ (Cost: 8)
  - To **F**: Path $A \to B \to C \to E \to D \to F$ (Cost: 9)

<br>

### 3️⃣ 5.2.3 Flooding

> 💡 **Analogy (Hinglish)**: Flooding aisi hai jaise kisi shahar mein aag lagne par ghanti bajana — har gali mein aawaz gunjti hai. Har router aane wale packet ki photocopy banata hai aur apne saare darwazon (links) se bahar fenk deta hai. Packet guarantee ke saath pahunchega, chahe beech ke aadhe raste tute ho, par duplicate packets ka toofan (broadcast storm) aa jata hai!

- **Pure Flooding**:
  - Every incoming packet is retransmitted onto every outgoing line **except** the line on which it arrived.
  - Generates an infinite number of duplicate packets unless damped.
- **Damping Techniques**:
  1. **Hop Count / Time-to-Live (TTL)**:
     - A counter initialized in the packet header (typically set to the diameter of the network).
     - Decremented by 1 at each router hop. When it hits zero, the packet is silently discarded.
  2. **Sequence Number Tracking**:
     - Source router places its ID and a monotonically increasing Sequence Number into the packet header.
     - Each router maintains a lookup list of `(Source ID, Sequence Number)` pairs it has already processed.
     - If an incoming packet's sequence number is already in the list, it is dropped immediately.
  3. **Selective Flooding**:
     - The router does not send on all lines, but only on lines that head roughly in the correct direction toward the destination.
- **Practical Applications of Flooding**:
  - **Military & Disaster Recovery Networks**: Guaranteed delivery even when significant chunks of the network are destroyed.
  - **Link State Routing Protocols (OSPF/IS-IS)**: Used to reliably flood Link State Packets (LSPs) across the entire AS.
  - **Distributed Database Updates**: Propagating critical concurrent updates simultaneously.

<br>

### 4️⃣ 5.2.4 Distance Vector Routing (Bellman-Ford Algorithm)

> 💡 **Analogy (Hinglish)**: Distance Vector routing bilkul mohalle ke padosi jaisa hai jo bolta hai: "Mujhe nahi pata pure shahar ka naksha kaisa hai, par mere padosi Sharma ji ne bola hai ki Railway Station unke ghar se 3 km door hai. Aur Sharma ji ka ghar mere ghar se 1 km hai, toh mere liye station ka distance ho gaya 1 + 3 = 4 km!" Har router sirf apne padosiyon ki sunta hai aur table update karta rehta hai.

- **Fundamental Operation**:
  - Each router maintains a **Distance Vector** table listing, for every possible network destination $y$:
    - The shortest known distance (cost/delay) $D(y)$.
    - The preferred outgoing interface/neighbor to reach $y$.
  - Periodically (e.g., every 30 seconds in RIP) and upon local topology changes, each router broadcasts its distance vector to its directly connected physical neighbors.
  - **Distributed Bellman-Ford Equation**:
    When router $x$ receives distance vectors $D_v$ from each neighbor $v$:
    $$D_x(y) = \min_{v \in \text{Neighbors}(x)} \left\{ c(x, v) + D_v(y) 
ight\}$$
    where $c(x, v)$ is the directly measured cost/delay from $x$ to neighbor $v$.

---

#### 🔥 Step-by-Step Demonstration: Distance Vector Computation at Router J

*(As presented in Lecture Slide 24 & Tanenbaum Fig. 5-9)*
Suppose Router $J$ has four physical neighbors: $A, I, H, K$.
- Measured link delays from $J$ to neighbors:
  - $c(J, A) = 8\text{ ms}$
  - $c(J, I) = 10\text{ ms}$
  - $c(J, H) = 12\text{ ms}$
  - $c(J, K) = 6\text{ ms}$
- Neighbors send their latest estimated vectors to $J$ for destinations $A$ through $L$:

| Destination | Vector from A ($D_A$) | Vector from I ($D_I$) | Vector from H ($D_H$) | Vector from K ($D_K$) | $c(J,A)+D_A$ | $c(J,I)+D_I$ | $c(J,H)+D_H$ | $c(J,K)+D_K$ | New $D_J$ (Min) | Outgoing Line |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **A** | 0 | 24 | 20 | 21 | $8+0=\mathbf{8}$ | $10+24=34$ | $12+20=32$ | $6+21=27$ | **8** | Line A |
| **B** | 12 | 36 | 31 | 28 | $8+12=\mathbf{20}$ | $10+36=46$ | $12+31=43$ | $6+28=34$ | **20** | Line A |
| **C** | 25 | 18 | 19 | 36 | $8+25=33$ | $10+18=28$ | $12+19=31$ | $6+36=42$ | **28** | Line I |
| **D** | 40 | 27 | 8 | 24 | $8+40=48$ | $10+27=37$ | $12+8=\mathbf{20}$ | $6+24=30$ | **20** | Line H |
| **E** | 14 | 7 | 30 | 22 | $8+14=22$ | $10+7=\mathbf{17}$ | $12+30=42$ | $6+22=28$ | **17** | Line I |
| **F** | 23 | 20 | 19 | 40 | $8+23=31$ | $10+20=\mathbf{30}$ | $12+19=31$ | $6+40=46$ | **30** | Line I |
| **G** | 18 | 31 | 6 | 31 | $8+18=26$ | $10+31=41$ | $12+6=\mathbf{18}$ | $6+31=37$ | **18** | Line H |
| **H** | 17 | 20 | 0 | 19 | $8+17=25$ | $10+20=30$ | $12+0=\mathbf{12}$ | $6+19=25$ | **12** | Line H |
| **I** | 21 | 0 | 14 | 22 | $8+21=29$ | $10+0=\mathbf{10}$ | $12+14=26$ | $6+22=28$ | **10** | Line I |
| **J** | 9 | 11 | 7 | 10 | $8+9=17$ | $10+11=21$ | $12+7=19$ | $6+10=16$ | **0** | Local (Self) |
| **K** | 24 | 22 | 22 | 0 | $8+24=32$ | $10+22=32$ | $12+22=34$ | $6+0=\mathbf{6}$ | **6** | Line K |
| **L** | 29 | 33 | 9 | 9 | $8+29=37$ | $10+33=43$ | $12+9=21$ | $6+9=\mathbf{15}$ | **15** | Line K |

Router $J$ updates its forwarding table with these minimum calculated delays and next hops!

---

#### 🔥 The Count-to-Infinity Problem

> 💡 **Analogy (Hinglish)**: "Good news travels fast, bad news travels at a snail's pace." Socho 3 dost hain: A, B, aur C ek seedhi line mein khade hain (A - B - C). A ke paas samosa hai. B bolta hai "A mere se 1 kadam door hai". C bolta hai "A mere se 2 kadam door hai (via B)". Ab achanak A dukan band karke chala gaya (Link down). B ko pata chala A gaya, par C ne pehle hi advertise kiya tha ki "mera distance A tak 2 hai". B sochta hai: "Arre wah! C ke paas koi doosra rasta hoga", toh B apna distance kar leta hai 2 + 1 = 3. Agli bar C dekhta hai B ka distance 3 ho gaya, toh C apna distance kar leta hai 3 + 1 = 4. Dono ek doosre ko bewakoof banate hue 5, 6, 7... infinity tak count karte rehte hain!

```
Linear Topology:  [ A ] ------- [ B ] ------- [ C ] ------- [ D ] ------- [ E ]
```

1. **Good News Propagation (Rapid Convergence)**:
   - When node $A$ boots up, in cycle 1: $B$ learns distance to $A$ is 1.
   - In cycle 2: $C$ learns distance to $A$ is 2.
   - In cycle 3: $D$ learns distance to $A$ is 3; in cycle 4: $E$ learns distance is 4.
   - Settles in exactly $N-1$ cycles!

2. **Bad News Propagation (Count-to-Infinity)**:
   - Suppose link between $A$ and $B$ suddenly breaks down.
   - $B$ detects link failure, but previously $C$ advertised: "I can reach $A$ with cost 2".
   - $B$ erroneously assumes $C$ has an independent alternative path to $A$!
   - $B$ sets its new distance to $A$: $D_B(A) = D_C(A) + 1 = 2 + 1 = 3$ (via $C$).
   - In next cycle, $C$ sees $B$'s update ($D_B(A) = 3$) and updates: $D_C(A) = D_B(A) + 1 = 4$ (via $B$).
   - The loop continues: $3, 4, 5, 6, 7, \dots \to \infty$.

| Iteration | B's distance to A | C's distance to A | D's distance to A | E's distance to A |
| :--- | :--- | :--- | :--- | :--- |
| Initial (Link OK) | 1 | 2 | 3 | 4 |
| Link A-B drops | 3 (via C) | 2 | 3 | 4 |
| Exchange 1 | 3 | 4 (via B) | 3 | 4 |
| Exchange 2 | 5 (via C) | 4 | 5 (via C) | 4 |
| Exchange 3 | 5 | 6 (via B) | 5 | 6 |
| $\dots$ | $\dots$ | $\dots$ | $\dots$ | $\dots$ |
| Infinity | 16 (Unreachable) | 16 (Unreachable) | 16 (Unreachable) | 16 (Unreachable) |

- **Remedies for Count-to-Infinity**:
  - **Define Infinity as Small Constant**: In RIP, $\infty = 16$. The counting loop stops after 16 iterations.
  - **Split Horizon**: A router never advertises a destination route back out the same interface from which it learned that route. (Since $C$ learned route to $A$ from $B$, $C$ will never report route to $A$ back to $B$).
  - **Split Horizon with Poisoned Reverse**: Instead of omitting the advertisement, $C$ explicitly advertises to $B$ that its distance to $A$ is $\infty$. This immediately kills the two-node loop.
  - **Limitation**: Split Horizon solves 2-node loops, but fails in complex topologies with 3-node or larger loops ($A \to B \to C \to D \to A$).

<br>

### 5️⃣ 5.2.5 Link State Routing

> 💡 **Analogy (Hinglish)**: Link State routing ka philosophy hai: "Tell everyone about your neighbors!" Distance Vector mein log pure shahar ki adhuri khabar sirf padosi ko dete the. Link State mein har router sirf apne direct judhe links aur unka kharcha (cost) ek parchi (LSP) par likhta hai, aur us parchi ko pure network mein broadcast kar deta hai. Sabhi routers ke paas pure network ka identical naksha (map) ban jata hai, aur har koi apne computer par baithkar Dijkstra chala kar sabse best rasta nikal leta hai. No loops, no count-to-infinity!

Every router executes **5 fundamental steps**:

```
+-----------------------------------------------------------------------------------+
| 5 STEPS OF LINK STATE ROUTING:                                                    |
| 1. Discover its neighbors and learn their network addresses (HELLO packets).      |
| 2. Measure the delay or cost to each of its neighbors (ECHO / PING packets).      |
| 3. Construct a Link State Packet (LSP) containing all neighbor costs.            |
| 4. Flood the LSP reliably to all other routers in the entire network.             |
| 5. Run Dijkstra's algorithm independently on the full map to compute sink tree.  |
+-----------------------------------------------------------------------------------+
```

#### Step 1: Discovering Neighbors
- Upon boot, a router sends a special `HELLO` packet on all point-to-point lines (or multicasts to `224.0.0.5` on LANs).
- The router at the other end responds with its own identity.
- When both routers see each other's ID in the HELLO, a bidirectional adjacency is confirmed.

#### Step 2: Measuring Link Cost
- To measure line delay, the router transmits an `ECHO` packet.
- The neighbor timestamps and immediately returns it.
- Dividing the round-trip time (RTT) by 2 gives an accurate estimate of link delay.
- Alternatively, link bandwidth or an administrator-set metric is used (e.g., in OSPF: $\text{Cost} = 10^8 / \text{Bandwidth in bps}$).

#### Step 3: Building Link State Packets (LSP)
- An LSP contains:
  1. Sender's Router ID.
  2. Sequence Number (32-bit counter, incremented with every new LSP).
  3. Age (TTL countdown timer in seconds).
  4. List of directly connected neighbors and their corresponding link metrics.

```
+------------------------------------+
| SENDER ID:        Router B         |
| SEQUENCE NUMBER:  0x00000042       |
| AGE:              60 seconds       |
+------------------------------------+
| Neighbor A:       Cost = 4         |
| Neighbor C:       Cost = 2         |
| Neighbor F:       Cost = 6         |
+------------------------------------+
```

#### Step 4: Distributing Link State Packets (Reliable Flooding)
- Fundamental mechanism: Flooding with duplicate control and acknowledgments.
- **Sequence Numbering**: When a router receives an LSP:
  - If sequence number is higher than the recorded version, it is accepted, updated in the link state database, and flooded on all other interfaces.
  - If sequence number is lower or equal, it is discarded as an obsolete duplicate.
  - To prevent sequence number wrap-around, 32-bit counters are used.
- **The Age Field**:
  - The Age field starts at a default value (e.g., 3600 seconds or 60 seconds) and is decremented by 1 every second at each router.
  - When Age reaches 0, the link state information is purged from the database, eliminating ghost records of crashed routers.
- **Router Database Flags**:
  Each LSP entry in a router's table has `Send flags` (which links need to transmit this LSP) and `ACK flags` (which links must acknowledge receipt).

| Source | Seq # | Age | Link 1 Send | Link 1 ACK | Link 2 Send | Link 2 ACK | Link 3 Send | Link 3 ACK | Data |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Router A | 21 | 58 | 0 | 0 | 1 | 0 | 0 | 1 | Neighbors & Costs |
| Router B | 45 | 40 | 1 | 0 | 0 | 1 | 0 | 0 | Neighbors & Costs |
| Router C | 12 | 59 | 0 | 1 | 0 | 0 | 1 | 0 | Neighbors & Costs |

#### Step 5: Computing Routes
- Once a router possesses the complete set of LSPs from all nodes, it constructs the identical global network graph.
- It then executes **Dijkstra's Algorithm** locally with itself as the root, producing the shortest path forwarding table.

---

#### 🔥 Comparison: Distance Vector vs. Link State Routing

| Dimension | Distance Vector (e.g., RIP) | Link State (e.g., OSPF, IS-IS) |
| :--- | :--- | :--- |
| **Knowledge Distribution** | "Tell neighbors about the whole world." | "Tell the whole world about your direct neighbors." |
| **Network View** | Local/Myopic: Router only knows what direct neighbors report. | Global: Every router holds the complete, identical topology map. |
| **Convergence Speed** | Slow; prone to routing loops and Count-to-Infinity. | Extremely fast; changes flooded immediately without loops. |
| **Bandwidth Overhead** | Periodic large updates; low on small nets, degrades on large nets. | Small LSPs flooded only on event/change; highly efficient. |
| **CPU / Memory Usage** | Minimal computation ($O(k)$ vector lookup). | High memory for database; $O(N \log N)$ CPU for Dijkstra. |
| **Scalability** | Limited ($\le 15$ hops in RIP). | Massive; easily scales to tens of thousands of nodes via Areas. |

<br>

### 6️⃣ 5.2.6 Hierarchical Routing

> 💡 **Analogy (Hinglish)**: Socho agar duniya ke har postman ko duniya ke har ek ghar ka rasta yaad rakhna pade, toh uska dimaag phat jayega! Isliye hierarchy banayi jaati hai: Pincode -> State -> City -> Locality -> House number. Jaipur ka postman sirf Jaipur ki galiyan janta hai; agar packet Chennai ka hai, toh wo chupchap use "State Border Post" (Gateway) par bhej deta hai. Isse routing table chhoti ho jaati hai!

- **The Problem of Scale**:
  - As networks grow, maintaining a flat routing table becomes impossible:
    - Memory consumption in routers explodes ($O(N)$ entries).
    - CPU time to scan and update tables spikes.
    - Routing update packet overhead saturates network bandwidth.
- **Hierarchical Solution**:
  - Routers are partitioned into **Regions** (or **Areas**).
  - Routers within the same region know all details about how to route packets internally.
  - Routers know nothing about the internal structure of other regions; they only know how to route to the region's border router (**Area Border Router - ABR**).
  - Can be extended to multi-level hierarchies: Clusters $\to$ Zones $\to$ Regions.

```
Hierarchical Architecture:

+-------------------+          +-------------------+
|     REGION 1      |          |     REGION 2      |
|  (R1) --- (R2)    |          |   (R4) --- (R5)   |
|     \     /       |          |     \     /       |
|      (ABR1)=======|==========|======(ABR2)       |
+-------------------+          +-------------------+
```

- **Trade-off: Table Size vs. Path Suboptimality**:
  - **Advantage**: Routing table size plummets from $N$ to a tiny fraction (e.g., entries for local routers + entries for remote regions).
  - **Disadvantage**: Path suboptimality. Because border gateways aggregate information, the chosen inter-region path might not be the true global shortest path!
- **Mathematical Optimal Hierarchy Depth**:
  - Kleinrock and Kamoun (1977) proved that for an $N$-router network, the optimal number of hierarchical levels is:
    $$k pprox \ln(N)$$
  - With optimal clustering, the total number of routing table entries per router is reduced to:
    $$\text{Optimal Entries} pprox e \cdot \ln(N)$$
  - *Example*: For $N = 720$ routers:
    - Flat table: $720$ entries.
    - Two-level hierarchy (24 regions of 30 routers): Table size $= 30 \text{ (local)} + 23 \text{ (regions)} = 53$ entries (over $13\times$ reduction!).

<br>

---

## 🐦‍🔥 5.3 CONGESTION CONTROL ALGORITHMS

### 1️⃣ Understanding Network Congestion

> 💡 **Analogy (Hinglish)**: Network congestion bilkul Diwali ke time highway ke toll plaza jaisa hai! Jab sadak par gaadiyan normal hoti hain, toh sab mast 80 km/h par chalte hain. Lekin jab achanak hazaron gaadiyan toll booth par aa jaati hain (capacity se zyada), toh lambi line lag jaati hai. Agar line aur lambi ho jaye toh gaadiyan hilna band ho jaati hain aur throughput zero ho jata hai! Buffer badhana matlab toll plaza ke peeche parking lot bada kar dena — gaadiyan aur der tak phasi rahengi, unka petrol (timeout) khatam hoga aur log dobara gaadiyan lekar nikal aayenge (retransmissions), jisse jam aur bhayanak ho jayega!

- **Definition of Congestion**:
  - When the aggregate traffic offered by all sources exceeds the processing or transmission capacity of intermediate routers and links.
  - Manifests as queue buildup, increased latency, packet drops, and a sharp degradation in delivered throughput.

```
Delivered
Throughput
   ^
   |                 Ideal Performance (Infinite Capacity)
   |              . '
   |            . '  Knee (Delay starts increasing)
   |          . '  . - - - - - - Max Capacity
   |        . '  . '
   |      . '  . '     |    . '  . '     \  Cliff (Severe Congestion Collapse)
   |  . '  . '           | . ' . '           \___________
   +-------------------------------------> Offered Load
```

- **The Bufferbloat Phenomenon**:
  - Intuition suggests adding massive RAM buffers to routers would eliminate packet loss.
  - **Reality**: Excessively large buffers worsen congestion! Packets sit in enormous FIFO queues for hundreds of milliseconds.
  - The sender's transport layer (TCP) times out because RTT spikes. TCP assumes packets are lost and retransmits them.
  - Now, both the original delayed packet and the retransmitted packet clog the buffers, compounding the collapse (**Congestive Collapse**).

- **Congestion Control vs. Flow Control**:

| Dimension | Flow Control | Congestion Control |
| :--- | :--- | :--- |
| **Scope** | Point-to-point / End-to-end (Unicast sender-receiver). | Global / Network-wide (All hosts and intermediate routers). |
| **Objective** | Prevent a fast sender from swamping a slow receiver. | Prevent the aggregate traffic from overloading network links/switches. |
| **Mechanism** | Receiver sends window updates (TCP `rwnd`) to sender. | Routers detect bottlenecks, drop packets, or send choke signals. |
| **Involved Entities** | Only the communicating endpoints (Transport layer). | Endpoints + All intermediate routers (Network layer). |

<br>

### 2️⃣ Approaches to Congestion Control

Congestion control techniques are divided into two fundamental philosophies:

```
+------------------------------------------------------------------------------------+
| CONGESTION CONTROL PARADIGMS                                                       |
+------------------------------------------------------------------------------------+
| 1. OPEN-LOOP (PREVENTATIVE):                                                       |
|    - Avoid congestion by good design upfront; do not let it happen!                |
|    - Tools: Traffic Shaping, Admission Control, Resource Reservation, Policing.    |
+------------------------------------------------------------------------------------+
| 2. CLOSED-LOOP (REACTIVE / FEEDBACK-DRIVEN):                                       |
|    - Monitor network dynamically, detect congestion, and throttle back sources.     |
|    - Tools: Choke Packets, Hop-by-Hop Backpressure, ECN, Load Shedding.            |
+------------------------------------------------------------------------------------+
```

<br>

### 3️⃣ 5.3.2 Traffic-Aware Routing

- **Dynamic Link Metrics**:
  - Instead of static metrics (bandwidth inverse or hop count), routing algorithms assign dynamic link costs based on current load, queue delays, and propagation times:
    $$\text{Link Cost} = \text{Propagation Delay} + rac{\text{Average Queue Length}}{\text{Capacity}}$$
- **The Route Oscillation Problem**:
  - When traffic shifts from congested link $L_1$ to uncongested link $L_2$, link $L_2$ suddenly becomes heavily loaded.
  - The routing algorithm recalculates shortest paths, observing that $L_2$ is now expensive and $L_1$ is idle.
  - All traffic instantly swings back to $L_1$!
  - This causes continuous **ping-pong oscillations**, degrading stability.
- **Remedies**:
  1. **Multipath Routing (ECMP)**: Split traffic across multiple candidate paths proportionally rather than dumping all packets onto a single path.
  2. **Damped / Filtered Metrics**: Update link metrics using exponentially smoothed averages over long intervals.

<br>

### 4️⃣ 5.3.3 Admission Control

> 💡 **Analogy (Hinglish)**: Admission control cinema hall ke ticket counter jaisa hai. Jab hall ki saari 200 seats bhar jaati hain, toh bahar "HOUSEFULL" ka board laga diya jata hai. Naye logon ko andar aane ki permission hi nahi di jaati taaki andar baithe logon ka movie experience kharab na ho!

- **Application in Virtual-Circuit Networks**:
  - Widely employed in connection-oriented architectures (ATM, MPLS, RSVP).
  - When a host requests a new Virtual Circuit, it declares its traffic characteristics and required bandwidth.
  - Intermediate routers evaluate whether they have sufficient spare capacity along the requested path.
  - If any router is congested or cannot guarantee resources:
    1. The connection request is rejected (**Admission Denied**).
    2. Alternatively, the path is routed around the congested hotspot through longer, uncongested links.

```
Concealing Congestion via Rerouting:

[ Source A ] ======> [ Router R1 ] ===== (Hotspot/Congested) =====> [ Router R2 ] ======> [ Dest B ]
                            \                                            ^
                             \========> [ Router R3 ] ==================/
                                         (Rerouted Alternate Path)
```

<br>

### 5️⃣ 5.3.4 Traffic Throttling Mechanisms

When congestion builds up in a connectionless network, routers must signal traffic sources to slow down.

#### 1. Choke Packets
- A congested router samples incoming packets. For an overloaded output line, it generates a special **Choke Packet** and sends it directly back to the original source host.
- The choke packet contains the destination address found in the trigger packet.
- Upon receipt, the source throttles its transmission rate to that destination by a fixed fraction (e.g., reduces rate by 50%).
- **Flaw**: Significant propagation delay on long-distance links!
  - *Example*: For a transatlantic link from New York to San Francisco (RTT = 30 ms) operating at 155 Mbps:
    $$\text{Data in transit during choke propagation} = 30\text{ ms} \times 155\text{ Mbps} = 4.65\text{ Megabits}$$
  - More than 4.6 Megabits of additional data enters the congested router before the sender slows down!

#### 2. Hop-by-Hop Backpressure Choke Packets
- To eliminate the round-trip propagation delay penalty, the choke packet affects **every intermediate router** along the return path.
- The immediate upstream router must immediately throttle its forwarding rate and buffer data locally.
- Provides instantaneous relief at the bottleneck router without waiting for the signal to reach the distant source host.

```
End-to-End Choke Packet:
[ Source ] <---------------------------------------- [ Congested Router ]
(Long RTT delay before source throttles; pipe keeps pouring data!)

Hop-by-Hop Backpressure:
[ Source ] <==== [ Router 1 ] <==== [ Router 2 ] <==== [ Congested Router ]
(Every intermediate hop immediately slows down forwarding!)
```

#### 3. Explicit Congestion Notification (ECN)
- Rather than generating new choke packets (which add traffic to an already congested network!), routers mark bits directly in the headers of existing data packets.
- Defined in RFC 3168 using two bits in the IPv4 Type of Service / IPv6 Traffic Class field:
  - `ECT (ECN-Capable Transport)`: Set by sender if it supports ECN.
  - `CE (Congestion Encountered)`: Set by a congested router when its queue exceeds a warning threshold.
- **Operation Loop**:
  1. Congested router flips `CE = 1` on forwarded data packets.
  2. Destination receives marked packet and reflects this signal by setting the `ECE (ECN-Echo)` flag in its next TCP ACK.
  3. Sender receives `ECE`, throttles its congestion window (just as if a packet loss had occurred), and confirms by setting `CWR (Congestion Window Reduced)`.

<br>

### 6️⃣ 5.3.5 Load Shedding & Packet Dropping Policies

When router queues overflow despite throttling, packets must be discarded (**Load Shedding**).

> 💡 **Analogy (Hinglish)**: "Wine vs. Milk" policy CN ka sabse mazedaar concept hai! 
> - **Wine (Sharab)**: Umar ke saath aur behtar hoti hai. File transfer (jaise zip file ya software download) mein purane packets bohot keemti hote hain kyunki unko download karne mein pehle hi mehnat aur time lag chuka hai. Agar naya packet drop karoge toh chalega, purana drop kiya toh pura download fail ho jayega!
> - **Milk (Doodh)**: Umar ke saath phat jata hai (sour ho jata hai). Real-time video/voice call (Zoom/YouTube live) mein naya packet taaza doodh hai! Jo 2 second purana frame tha wo baasi ho chuka hai, use drop kar do, naya wala packet dikhao!

- **Dropping Philosophies**:
  - **Wine Policy (Drop New, Keep Old)**: Best for bulk file transfers and document downloads where retransmitting an early packet wastes substantial prior bandwidth.
  - **Milk Policy (Drop Old, Keep New)**: Best for multimedia streaming and interactive gaming where stale frames are useless and the latest frame maintains synchronization.
  - **Priority-Based Dropping**: Packets carry a drop preference bit. Commercial traffic or routing control packets are shielded; low-priority scavenger traffic is dropped first.

#### Random Early Detection (RED)
- Dropping packets only when the buffer is 100% full causes **Global Synchronization**: all TCP connections lose packets simultaneously, throttle back together, and then ramp up together, causing wild bandwidth swings.
- **RED Algorithm**:
  - Router computes the **Exponentially Weighted Moving Average (EWMA)** of queue length:
    $$Q_{avg} = (1 - lpha) \cdot Q_{avg} + lpha \cdot Q_{instant}$$
  - Two queue thresholds are configured: $TH_{min}$ and $TH_{max}$.
    - If $Q_{avg} < TH_{min}$: Accept all incoming packets.
    - If $TH_{min} \le Q_{avg} < TH_{max}$: Drop (or ECN-mark) incoming packets with probability $p$, where $p$ grows linearly from 0 to $p_{max}$.
    - If $Q_{avg} \ge TH_{max}$: Discard all arriving packets ($p = 1.0$).
- **Key Advantage**: Connections sending the highest data rates have proportionately more packets in the queue, meaning RED statistically targets aggressive flows, forcing them to back off without synchronizing the entire network!

<br>

---

## 🐦‍🔥 5.4 QUALITY OF SERVICE (QoS)

### 1️⃣ Application Requirements & QoS Metrics

> 💡 **Analogy (Hinglish)**: QoS ka matlab hai har customer ko uski zaroorat ke hisaab se service dena. Socho ek VIP passenger ko airport par fast-track security chahiye (low latency), ek courier company ko bulk trucks chahiye (high throughput), aur ek surgeon ko bilkul uninterrupted zero-jitter live feed chahiye. Network layer ko in alag-alag flows ki requirements samajhni padti hain!

Quality of Service represents the performance guarantees a network provides to distinct application data streams (**flows**).

- **The Four Critical QoS Performance Metrics**:
  1. **Bandwidth / Throughput**: Minimum data rate (bps) continuously guaranteed to the flow.
  2. **Latency / Delay**: Time taken for a packet to traverse the network from source to destination.
  3. **Jitter**: The statistical variation in packet arrival times (delay variance). Critical for audio/video playback.
  4. **Reliability / Packet Loss**: The percentage of packets that arrive intact without corruption or drop.

| Application Type | Bandwidth Need | Delay Sensitivity | Jitter Sensitivity | Loss Tolerance |
| :--- | :--- | :--- | :--- | :--- |
| **IP Telephony (VoIP)** | Low (32-64 kbps) | ⚠️ Strict (<150 ms) | ⚠️ Strict (<30 ms) | ✅ Tolerates 1-2% loss |
| **Video Streaming** | 🔥 High (5-25 Mbps) | Tolerates 1-5 sec buffering | Moderate (buffer absorbed) | ✅ Tolerates small loss |
| **Interactive Gaming** | Low (50-100 kbps) | ⚠️ Strict (<50 ms) | ⚠️ Strict (<20 ms) | ⚠️ Low tolerance |
| **File Transfer / Web** | Burst / Variable | Delay insensitive | Completely insensitive | ❌ ZERO tolerance (Lossless) |

<br>

### 2️⃣ Traffic Shaping vs. Traffic Policing

```
+------------------------------------------------------------------------------------+
| SHAPING vs. POLICING                                                               |
+------------------------------------------------------------------------------------+
| - Traffic Shaping (Sender / Edge): Smoothes out bursty transmission by buffering   |
|   excess packets and releasing them at an agreed steady rate.                      |
| - Traffic Policing (Network Ingress): Monitors incoming traffic against the agreed |
|   Service Level Agreement (SLA). Violating packets are dropped or remarked.        |
+------------------------------------------------------------------------------------+
```

> 💡 **Analogy (Hinglish)**: 
> - **Traffic Shaping**: Jaise ek patient ko dawai ki 500mg ki dose ek hi second mein injection se na dekar drip lagakar dheere-dheere 1 ghante mein di jaati hai (Smoothing out bursts).
> - **Traffic Policing**: Jaise metro station par security guard: agar tumhara bag size limit se bada hai, toh guard ya toh bag phenk deta hai (drop) ya extra fine ki stamp laga deta hai (remarking)!

<br>

### 3️⃣ Traffic Shaping Algorithms

#### 1. The Leaky Bucket Algorithm (1986)

> 💡 **Analogy (Hinglish)**: Ek aisi balti socho jiske pendhe (bottom) mein ek chhota chhed hai. Upar se nal (tap) se paani chahe kitna bhi achanak gire (bursty input), neeche chhed se paani hamesha ek constant fixed speed se hi tapkega (rigid constant output). Agar upar se balti ki capacity se zyada paani daal diya, toh balti bhar kar overflow ho jayegi aur extra paani (packets) baha kar fek diya jayega!

```
    [ Bursty Packet Arrival ]
               |
               v
      +-----------------+
      |  LEAKY BUCKET   |  Capacity = B packets
      |  ~~~~~~~~~~~~~  |
      +--------+--------+
               |
               | Constant Rate: rho packets/sec
               v
     [ Smooth Output Stream ]
```

- **Mechanism**:
  - Each host has an internal queue (bucket) of finite capacity $B$.
  - Packets arrive unpredictably and are placed into the queue.
  - At every clock tick, exactly 1 packet (or fixed number of bytes) is transmitted onto the network at rate $
ho$.
  - If a packet arrives when the bucket is full, it is discarded (**overflow**).
- **Limitation**: Enforces a strictly rigid output rate. Even if the network line is completely idle, an application with a sudden valid burst cannot transmit faster than $
ho$!

---

#### 2. The Token Bucket Algorithm

> 💡 **Analogy (Hinglish)**: Token bucket system bilkul amusement park ya metro tokens jaisa hai. Bucket mein har second $R$ tokens aate hain (man lo 2 token/sec) aur balti mein maximum $B$ tokens jama ho sakte hain. Agar tum chupchap baithe ho, toh tokens balti mein collect hote rahenge. Fir achanak tumhare 5 dost aaye (bursty traffic), agar balti mein 5 tokens hain, toh turant 5 logon ko entry mil jayegi! Token bucket burst ko allow karta hai, jabki Leaky bucket burst ko bilkul forbid karta tha.

```
      [ Token Generator: R tokens/sec ]
                     |
                     v
             +---------------+
             | TOKEN BUCKET  |  Capacity = B tokens
             | * * * * * * * |  (Unused tokens accumulate)
             +-------+-------+
                     |
                     | Token matched with packet
                     v
   [ Arriving Packets ] ====> [ Transmit at full link speed C ]
```

- **Mechanism**:
  - A token generator deposits tokens into a bucket of capacity $B$ at a constant rate of $R$ tokens/second.
  - If the bucket fills up to $B$, newly arriving tokens overflow and are discarded (packets are **never** discarded by the token bucket).
  - To transmit a packet of $k$ bytes, the host must capture and remove $k$ tokens from the bucket.
  - If fewer than $k$ tokens exist, the packet waits in an input queue until sufficient tokens accumulate.
- **Mathematical Burst Duration Analysis**:
  Let:
  - $B$ = Token bucket capacity (bytes)
  - $R$ = Token arrival rate (bytes/sec)
  - $C$ = Maximum physical transmission line capacity (bytes/sec), where $C > R$.
  - $S$ = Maximum duration of the burst at peak transmission speed $C$.

  During the burst of duration $S$, the total data transmitted equals the tokens initially in the bucket plus newly generated tokens:
  $$C \cdot S = B + R \cdot S$$
  Solving for burst duration $S$:
  $$S = rac{B}{C - R}$$
  The maximum data volume transmitted during this burst interval is:
  $$\text{Data Volume} = C \cdot S = rac{C \cdot B}{C - R}$$

---

#### 🔥 Comparison: Leaky Bucket vs. Token Bucket

| Feature | Leaky Bucket | Token Bucket |
| :--- | :--- | :--- |
| **Output Rate** | Strictly constant ($
ho$); rigid pacing. | Average rate $R$, but permits bursts up to line speed $C$. |
| **Discards** | Discards **packets** when bucket overflows. | Discards **tokens** when bucket fills; packets wait in buffer. |
| **Idle Behavior** | Does not save credit; idle periods are lost. | Accumulates tokens up to capacity $B$ for future bursts. |
| **Use Case** | Strict bandwidth limiting; ATM cell pacing. | Internet traffic shaping; burst-tolerant QoS. |

> 📝 NOTE : In practice, high-performance routers place a **Token Bucket followed by a Leaky Bucket**:
> 1. Token bucket meters the traffic and limits burst volume to $B$.
> 2. Leaky bucket smooths out the burst peak, capping the maximum egress rate below the physical channel saturation point.

<br>

### 4️⃣ Packet Scheduling Algorithms

When multiple flows share an output interface queue, the router's scheduler decides which packet to transmit next.

```
       +-----------------------+
       |   PACKET SCHEDULERS   |
       +-----------+-----------+
                   |
       +-----------+-----------+-----------+
       |                       |           |
    [ FIFO ]             [ Fair Queuing ] [ Weighted Fair Queuing ]
 (Single Queue)          (Bit-by-bit RR)  (Weighted Shares per flow)
```

#### 1. First-In, First-Out (FIFO)
- Arriving packets join a single tail-drop queue; transmitted strictly in order of arrival.
- **Fatal Flaw**: Aggressive, greedy UDP flows saturate queue buffers, starving well-behaved TCP connections (**Flow Starvation**).

#### 2. Fair Queuing (FQ)
- The router maintains separate FIFO queues for each active flow.
- A naive packet-by-packet round robin unfairly favors flows sending large 1500-byte packets over flows sending small 64-byte voice packets.
- **Solution (Bit-by-Bit Round Robin)**: FQ simulates bit-by-bit round-robin service (Generalized Processor Sharing - GPS).
- The router computes the virtual finishing time $F_i$ for each arriving packet $i$:
  $$F_i = \max(A_i, F_{i-1}) + L_i$$
  where $A_i$ is arrival timestamp, $L_i$ is packet length in bits, and $F_{i-1}$ is finishing time of previous packet in that flow.
- Packets are scheduled in order of **increasing virtual finish time** $F_i$.

#### 3. Weighted Fair Queuing (WFQ)
- Generalization of FQ supporting differentiated priority classes by assigning each flow $k$ a weight $w_k$:
  $$F_i = \max(A_i, F_{i-1}) + rac{L_i}{w_k}$$
- A flow with weight $w = 2$ receives twice the bandwidth and finishes its virtual service in half the time compared to a flow with weight $w = 1$.

```
Weighted Fair Queuing Scheduler Architecture:

Flow 1 (Weight = 2) [P1: 1000B] [P2: 1000B] ----                                                  \     [ WFQ Scheduler ]
Flow 2 (Weight = 1) [P3: 1000B] -------------------> ===> [ Transmission Line ]
                                                  /     (Sorted by Finish Time F_i)
Flow 3 (Weight = 1) [P4: 500B]  ----------------/
```

<br>

### 5️⃣ Admission Control & Flow Specifications

- **Flow Specification (RFC 2210 Flowspec)**:
  - Before a flow is admitted, sender and network agree on traffic parameters:
    - **Token Rate ($R$)**: Average long-term data rate (bytes/s).
    - **Bucket Depth ($B$)**: Maximum burst size (bytes).
    - **Peak Rate ($p$)**: Maximum transmission speed.
    - **Minimum Packet Size ($m$)**: Floor for policing calculation.
    - **Maximum Packet Size ($M$)**: MTU limit.
- **Parekh-Gallager Delay Bound Theorem (1993, 1994)**:
  - If a source is shaped by a Token Bucket $(R, B)$ and all $K$ intermediate routers employ Weighted Fair Queuing (WFQ), the end-to-end packet delay $D$ is **strictly bounded**:
    $$D \le rac{B}{R} + (K - 1) \cdot rac{M}{R} + \sum_{m=1}^K P_m$$
  - where $P_m$ is the propagation delay of link $m$.
  - **Significance**: Mathematically proves that an IP network can provide guaranteed hard real-time delay ceilings without packet loss!

<br>

### 6️⃣ IP Quality of Service Architectures

To deliver QoS across the global Internet, the IETF developed two distinct architectures:

```
+------------------------------------------------------------------------------------+
| INTSERV vs. DIFFSERV                                                               |
+------------------------------------------------------------------------------------+
| - Integrated Services (IntServ / RSVP): Per-flow reservation; stateful core.       |
| - Differentiated Services (DiffServ): Class-based aggregation; stateless core.     |
+------------------------------------------------------------------------------------+
```

#### 1. Integrated Services (IntServ) & RSVP (RFC 2205)
- **Concept**: Hard QoS guarantees provisioned for every individual data stream.
- **RSVP (Resource ReSerVation Protocol)**:
  - **Receiver-Driven**: Receivers request bandwidth reservations. Enables massive scalability in multicast sessions where different receivers possess different display capabilities.
  - **Signaling Exchange**:
    1. Sender transmits a downstream `PATH` message to destination, recording the router path and flow characteristics (Tspec).
    2. Receiver generates an upstream `RESV` message traveling back along the exact reverse path, carrying the reservation request (Rspec).
    3. Intermediate routers verify available capacity (Admission Control). If approved, they allocate buffers and bandwidth.
  - **Soft State**: Reservations expire automatically unless refreshed periodically by refresh messages (e.g., every 30 seconds).
- **The Collapse of IntServ in the Internet Core**:
  - Core transit routers handle millions of concurrent flows. Storing per-flow reservations and running per-flow WFQ queues caused catastrophic CPU and memory exhaustion (**State Explosion**).

---

#### 2. Differentiated Services (DiffServ - RFC 2474)

> 💡 **Analogy (Hinglish)**: DiffServ Indian Railways jaisa hai! Train ke engine ko har passenger ka naam ya ticket janne ki koi zaroorat nahi hai. Train mein bas coaches divided hain: First AC, AC 3-Tier, Sleeper, aur General (Classes). Edge par TC ticket check karta hai aur passenger ko uske coach mein bitha deta hai. Core network (train) bas coach ke hisaab se service deti hai!

- **Key Principles**:
  - **Stateless Core**: Core routers do not track individual flows.
  - **Edge Classification & Marking**: Ingress boundary routers inspect packets, classify them into broad service classes, and mark the 6-bit **Differentiated Services Code Point (DSCP)** in the IP header.
  - **Per-Hop Behaviors (PHB)**: Core routers inspect only the DSCP bits to determine queue scheduling and drop precedence.

```
IPv4 Type of Service / IPv6 Traffic Class Byte:
+---+---+---+---+---+---+---+---+
|       DSCP (6 bits)   |ECN (2)|
+---+---+---+---+---+---+---+---+
```

- **Two Primary Standard PHBs**:
  1. **Expedited Forwarding (EF - RFC 3246)**:
     - Designed to simulate a dedicated virtual leased line.
     - Provides low loss, low latency, and low jitter.
     - EF packets are prioritized over all other traffic and given dedicated bandwidth (e.g., voice traffic marked `DSCP 101110 = 46`).
  2. **Assured Forwarding (AF - RFC 2597)**:
     - Defines 4 independent traffic classes, each allocated guaranteed queue bandwidth via WFQ.
     - Within each class, packets are assigned one of 3 Drop Precedences: **Low**, **Medium**, or **High**.
     - Implemented using Weighted Random Early Detection (WRED): when congestion strikes, high-drop packets are discarded first.

| AF Classes | Class 1 (Bronze) | Class 2 (Silver) | Class 3 (Gold) | Class 4 (Platinum) |
| :--- | :--- | :--- | :--- | :--- |
| **Low Drop Precedence** | AF11 (`001010`) | AF21 (`010010`) | AF31 (`011010`) | AF41 (`100010`) |
| **Medium Drop Precedence** | AF12 (`001100`) | AF22 (`010100`) | AF32 (`011100`) | AF42 (`100100`) |
| **High Drop Precedence** | AF13 (`001110`) | AF23 (`010110`) | AF33 (`011110`) | AF43 (`100110`) |

<br>

---

## 🐦‍🔥 5.5 INTERNETWORKING

### 1️⃣ How Networks Differ

The global Internet is not a single, homogeneous network; it is an "inter-network" stitching together thousands of radically different physical and logical systems.

| Dimension of Difference | Examples of Network Variation |
| :--- | :--- |
| **Service Model** | Connectionless (IP, UDP) vs. Connection-oriented (ATM, X.25, MPLS). |
| **Addressing Systems** | 32-bit flat/hierarchical IPv4, 128-bit IPv6, 48-bit Ethernet MAC, E.164 phone numbers. |
| **Maximum Packet Size (MTU)**| Ethernet (1500 B), Wi-Fi (2272 B), FDDI (4352 B), ZigBee 802.15.4 (127 B). |
| **Quality of Service (QoS)** | Best-effort (Standard IP) vs. Guaranteed CBR/VBR (ATM, IntServ, DiffServ). |
| **Error Handling** | Reliable hop-by-hop retransmission (Wi-Fi 802.11) vs. Unreliable drop-on-error (Ethernet). |
| **Routing Protocols** | OSPF (Link state), RIP (Distance vector), BGP (Path vector). |

<br>

### 2️⃣ Connecting Heterogeneous Networks

Depending on which OSI layer the connection is established, interconnecting devices differ fundamentally:

```
+------------------------------------------------------------------------------------+
| INTERCONNECTING DEVICES ACROSS THE PROTOCOL STACK                                  |
+------------------------------------------------------------------------------------+
| Layer 7 (Application):  APPLICATION GATEWAYS (Translates email formats / SMS / API)|
| Layer 4 (Transport):    TRANSPORT GATEWAYS (Connects TCP to SCTP / QUIC)           |
| Layer 3 (Network):      ROUTERS (Forwards packets based on IP addresses)           |
| Layer 2 (Data Link):    BRIDGES / SWITCHES (Forwards frames based on MAC addresses)|
| Layer 1 (Physical):     REPEATERS / HUBS (Regenerates electrical/optical bits)     |
+------------------------------------------------------------------------------------+
```

> 💡 **Analogy (Hinglish)**:
> - **Repeater (L1)**: Jaise loudspeaker — aawaz dheemi ho gayi toh amplify karke aage fenk di.
> - **Switch (L2)**: Jaise society ka security guard — har aane wale courier ka flat number (MAC) padhta hai aur us building ke andar bhej deta hai.
> - **Router (L3)**: Jaise shahar ka main post office — jo shahar ke bahar ke addresses (IP address) samajhta hai aur alag-alag highway (heterogeneous links) par gaadiyan bhejta hai.
> - **Application Gateway (L7)**: Jaise do alag bhasha bolne wale logon ke beech ka human translator (jaise WhatsApp message ko SMS format mein translate karna).

<br>

### 3️⃣ Tunneling

> 💡 **Analogy (Hinglish)**: Tunneling ka sabse best example hai Eurotunnel (France se England tak train se gaadi le jaana). Socho tumhari car (IPv6 packet) France mein hai aur use England jana hai, par beech mein samundar (IPv4 network) hai jisme car chal hi nahi sakti! Toh car ko ek badi rail-gaadi (IPv4 packet) ke dabbe mein load kar diya jata hai. Train samundar paar karti hai, aur doosre kinare car train se bahar nikal kar dobara normal sadak par chalne lagti hai. Car ko koi modification nahi karni padi!

- **Concept**:
  - Used when two networks of the same type (e.g., IPv6) need to communicate across an intermediate transit network of a different type (e.g., legacy IPv4).
  - The multiprotocol ingress router encapsulates the entire source packet (header and payload) inside the payload field of an outer transit packet.
  - The transit network simply routes the outer packet using its native addressing.
  - The egress router strips the outer header (**decapsulation**) and injects the original packet into the destination network.

```
Tunneling Architecture:

[ IPv6 Host ] ---> [ Ingress Router ] ===================> [ Egress Router ] ---> [ IPv6 Dest ]
                    Encapsulates:                           Decapsulates:
                    [ IPv4 Header | IPv6 Packet ]           Strips IPv4 Header
```

- **Prominent Use Cases**:
  - **IPv6 Transition (6to4, Teredo)**: Carrying IPv6 packets across IPv4 Internet backbones.
  - **Virtual Private Networks (VPNs / IPsec)**: Encapsulating private corporate intranet packets securely across the public Internet.

<br>

### 4️⃣ Internetwork Routing

- Internetwork routing operates in a **two-level hierarchical structure**:
  - **Intra-Domain Routing (Interior Gateway Protocols - IGP)**:
    - Routing inside a single Autonomous System (AS).
    - Protocols: OSPF, IS-IS, RIP.
    - Optimized for shortest paths, low latency, and high performance.
  - **Inter-Domain Routing (Exterior Gateway Protocols - EGP)**:
    - Routing between different Autonomous Systems.
    - Protocol: BGP-4 (Border Gateway Protocol).
    - Driven by economic policies, political agreements, and transit contracts rather than shortest technical path.

<br>

### 5️⃣ Packet Fragmentation & Reassembly

Each physical network technology enforces a **Maximum Transmission Unit (MTU)**: the maximum IP packet size (including header) that can fit inside its link frame.
- *Examples*: Ethernet MTU = 1500 bytes; PPPoE MTU = 1492 bytes; WLAN MTU = 2272 bytes.

#### Fragmentation Strategies: Transparent vs. Non-Transparent

```
+------------------------------------------------------------------------------------+
| 1. TRANSPARENT FRAGMENTATION:                                                      |
|    - Fragments are created at an entry router and REASSEMBLED at an exit router   |
|      before leaving the small-MTU network.                                         |
|    - Higher layers and downstream networks are completely oblivious.               |
|    - Drawback: Exit router needs massive buffers; packets must exit via same node. |
+------------------------------------------------------------------------------------+
| 2. NON-TRANSPARENT FRAGMENTATION (Used in IPv4):                                   |
|    - Fragments travel independently across the Internet as standalone packets.     |
|    - Reassembly occurs ONLY at the final destination host!                         |
|    - Drawback: Header overhead duplicated across all fragments.                     |
+------------------------------------------------------------------------------------+
```

---

#### 🔥 IPv4 Fragmentation Header Fields

IPv4 datagram headers allocate 3 specific fields (32 bits total) to govern fragmentation:

```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|       Identification          |Flags|     Fragment Offset     |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                 /                            DF: bit 1   MF: bit 2
```

1. **Identification (16 bits)**: Unique ID assigned by source host to correlate all fragments of a single original datagram.
2. **Flags (3 bits)**:
   - Bit 0: Reserved (must be 0).
   - **DF (Don't Fragment)**: $1 =$ Do not fragment under any circumstances. If packet > MTU, drop and return ICMP error.
   - **MF (More Fragments)**: $1 =$ More fragments follow; $0 =$ This is the last fragment.
3. **Fragment Offset (13 bits)**: Specifies where this fragment's payload belongs relative to the start of the original datagram.
   - **Crucial Rule**: Measured in units of **8-byte (64-bit) blocks**! Therefore, every fragment payload (except the last) must be a multiple of 8 bytes.

---

#### 🔥 Comprehensive Numerical Demonstration of IPv4 Fragmentation

- **Original Datagram**:
  - Total Length = 4000 bytes (20 bytes IPv4 Header + 3980 bytes Data Payload).
  - Identification = `0xABCD`, $\text{DF} = 0$, $\text{MF} = 0$, $\text{Offset} = 0$.
- **Encountered Link MTU**: 1500 bytes.
  - Maximum data payload per fragment $= 1500 - 20 = 1480$ bytes.
  - Check divisibility by 8: $1480 / 8 = 185$ (Valid integer!).

**Fragmentation Execution Breakdown**:

| Fragment # | Header Length | Payload Data | Total Length | Identification | DF Flag | MF Flag | Fragment Offset (in 8-byte units) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Fragment 1** | 20 bytes | 1480 bytes (Bytes 0 to 1479) | **1500 bytes** | `0xABCD` | 0 | **1** | $0 / 8 = \mathbf{0}$ |
| **Fragment 2** | 20 bytes | 1480 bytes (Bytes 1480 to 2959) | **1500 bytes** | `0xABCD` | 0 | **1** | $1480 / 8 = \mathbf{185}$ |
| **Fragment 3** | 20 bytes | 1020 bytes (Bytes 2960 to 3979) | **1040 bytes** | `0xABCD` | 0 | **0** | $2960 / 8 = \mathbf{370}$ |

*Verification*: Total payload recovered at destination host $= 1480 + 1480 + 1020 = 3980$ bytes. Exact match!

---

#### 🔥 Path MTU Discovery (PMTUD)

> 💡 **Analogy (Hinglish)**: Path MTU Discovery aisi hai jaise ek parcel sender pehle ek bada box bhejta hai jiske upar likha hota hai: "Kripya ise todo mat (DF=1)". Agar raaste mein koi chhota pul (narrow bridge) aaya, toh wahan ka inspector parcel wapas bhej deta hai ek slip ke saath: "Bhai, mera pul sirf 1400 byte jhel sakta hai". Ab sender agli baar se 1400 byte ka hi packet banata hai. Isse raaste ke routers ko baar-baar packet kaatne-phadne ki mehnat nahi karni padti!

- **Why Modern Networks Avoid Fragmentation**:
  - If any single fragment is dropped by noise or buffer overflow, the entire original datagram must be retransmitted by TCP.
  - Fragments lack TCP port numbers (only Fragment 0 has transport headers), confusing stateful firewalls and NAT boxes.
- **PMTUD Mechanism (RFC 1191)**:
  1. Source sets the `DF = 1` bit in all outgoing IP packets.
  2. If an intermediate router receives a packet larger than its link MTU:
     - The router drops the packet.
     - The router sends an **ICMP Destination Unreachable** message back to the sender, specifically **Code 4: Fragmentation Needed and DF Set**, including the **Next-Hop MTU** value.
  3. Source receives the ICMP error, updates its internal Path MTU cache for that destination, and segments subsequent data to fit.
  4. The process repeats until packets reach the destination without being dropped.

<br>

---

## 🐦‍🔥 5.6 THE NETWORK LAYER IN THE INTERNET

### 1️⃣ 5.6.1 The IP Version 4 Protocol

The IPv4 protocol is the bedrock of the Internet, providing an unreliable, connectionless, best-effort packet delivery service.

```
IPv4 Datagram Header Layout (32-Bit Width):

 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|Version|  IHL  |Type of Service/DSCP|       Total Length       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|         Identification        |Flags|     Fragment Offset     |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  Time to Live |    Protocol   |        Header Checksum        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                       Source IP Address                       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Destination IP Address                     |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Options (0 to 40 Bytes)                    |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                            Payload                            |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

#### Detailed Header Fields Breakdown

1. **Version (4 bits)**:
   - Protocol version. Always `4` (`0100` in binary) for IPv4.
2. **IHL - Internet Header Length (4 bits)**:
   - Length of the header measured in **32-bit (4-byte) words**.
   - Minimum value is $5$ ($5 \times 4 = 20\text{ bytes}$ when no options are present).
   - Maximum value is $15$ ($15 \times 4 = 60\text{ bytes}$ with max options).
3. **Type of Service / DSCP & ECN (8 bits)**:
   - Originally ToS (precedence and delay/throughput flags).
   - Redefined by DiffServ: Upper 6 bits = **DSCP (Differentiated Services Code Point)**; Lower 2 bits = **ECN (Explicit Congestion Notification)**.
4. **Total Length (16 bits)**:
   - Combined length of header plus data payload in bytes.
   - Theoretical maximum: $2^{16} - 1 = 65,535\text{ bytes}$.
5. **Identification (16 bits)**:
   - Unique integer assigned by sender to tie fragmented pieces together.
6. **Flags (3 bits)**:
   - Bit 0: Reserved (0).
   - Bit 1: **DF (Don't Fragment)** ($1 =$ router cannot fragment).
   - Bit 2: **MF (More Fragments)** ($1 =$ more fragments follow, $0 =$ last fragment).
7. **Fragment Offset (13 bits)**:
   - Offset of fragment payload in 8-byte chunks relative to original datagram.
8. **Time to Live - TTL (8 bits)**:
   - Hop counter to prevent routing loops from circulating packets forever.
   - Decremented by at least 1 at every router hop. When $\text{TTL} = 0$, packet is dropped and an ICMP Time Exceeded message is returned.
9. **Protocol (8 bits)**:
   - Specifies the Layer 4 transport protocol payload:
     - `1` = **ICMP**
     - `2` = **IGMP**
     - `6` = **TCP**
     - `17` = **UDP**
     - `89` = **OSPF**
10. **Header Checksum (16 bits)**:
    - 16-bit 1's complement sum of the header only (payload is checked by TCP/UDP).
    - **Must be recomputed at every router** because TTL decrements at each hop!
11. **Source IP Address (32 bits)**: Originating host's IP address.
12. **Destination IP Address (32 bits)**: Intended recipient's IP address.
13. **Options (Variable length, 0 to 40 bytes)**:
    - Security, Record Route, Timestamp, Loose Source Routing, Strict Source Routing.

<br>

### 2️⃣ 5.6.2 IP Addresses & Addressing Architecture

Every host and router interface on the Internet has a unique 32-bit logical address, written in dotted-decimal format (e.g., `192.0.2.1`).

#### Historical Classful Addressing (Pre-1993)

Originally, addresses were partitioned into 5 rigid classes based on high-order bits:

```
Class A (Prefix: 0)     [0 | 7-bit Network | 24-bit Host ID]       Range: 0.0.0.0 - 127.255.255.255
Class B (Prefix: 10)    [10 | 14-bit Network | 16-bit Host ID]     Range: 128.0.0.0 - 191.255.255.255
Class C (Prefix: 110)   [110 | 21-bit Network | 8-bit Host ID]     Range: 192.0.0.0 - 223.255.255.255
Class D (Prefix: 1110)  [1110 | 28-bit Multicast Group ID]         Range: 224.0.0.0 - 239.255.255.255
Class E (Prefix: 1111)  [1111 | Reserved / Experimental]           Range: 240.0.0.0 - 255.255.255.255
```

- **Why Classful Addressing Failed**:
  - Class A was far too massive ($16.7\text{ million}$ hosts), wasting millions of addresses.
  - Class C was far too tiny ($256$ hosts), unable to support medium businesses.
  - Everyone requested Class B ($65,536$ hosts), leading to rapid exhaustion of Class B space by 1992.

---

#### 🔥 Subnetting & Subnet Masks

> 💡 **Analogy (Hinglish)**: Subnetting bilkul ek bade joint family ke makan ko alag-alag flats mein convert karne jaisa hai. Bahar se postman ke liye makan number ek hi hai (University Network Address). Par ghar ke andar ek router laga hai jo flat number (Subnet ID) dekhkar packet ko Computer Science department, Electrical department ya Art department ke kamre mein bhej deta hai. Subnet mask wo filter hai jo batata hai ki kitne bits ghar ke address ke hain aur kitne bits kamre ke!

- **Concept**:
  - Allows an organization to split a single large IP network block into multiple smaller internal networks (**subnets**) without requesting additional prefixes from the outside Internet.
  - Outside routers see only the single aggregated prefix; internal routers inspect the **Subnet Bits**.
- **The Subnet Mask**:
  - A 32-bit sequence with binary `1`s covering network and subnet bits, and binary `0`s covering host bits.
  - **Bitwise AND Forwarding Logic**:
    $$\text{Subnet Match} = (\text{Destination IP Address}) \ \mathbf{AND} \ (\text{Subnet Mask})$$

---

#### 🔥 Comprehensive Numerical Subnetting Example

*(From Lecture Slide 67-74: University Block Allocation)*
- The University is allocated the block `128.208.0.0/16`.
- Internal allocation requirements:
  - **Computer Science (CS)**: Needs $1/2$ of total address space.
  - **Electrical Engineering (EE)**: Needs $1/4$ of total address space.
  - **Art Department**: Needs $1/8$ of total address space.
  - **Spare / Unallocated**: Needs $1/8$ of total address space.

**Mathematical Subnet Partitioning**:

| Department | Share | Subnet Bits Needed ($k$) | Prefix Length | Subnet Mask | Host Bits | Usable Addresses | 3rd Octet Range |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **CS** | $1/2 = 1/2^1$ | 1 bit (`1`) | `/17` | `255.255.128.0` | 15 bits | $2^{15} - 2 = \mathbf{32,766}$ | `128` to `255` |
| **EE** | $1/4 = 1/2^2$ | 2 bits (`00`) | `/18` | `255.255.192.0` | 14 bits | $2^{14} - 2 = \mathbf{16,382}$ | `0` to `63` |
| **Art** | $1/8 = 1/2^3$ | 3 bits (`011`)| `/19` | `255.255.224.0` | 13 bits | $2^{13} - 2 = \mathbf{8,190}$ | `96` to `127` |
| **Unallocated**| $1/8 = 1/2^3$ | 3 bits (`010`)| `/19` | `255.255.224.0` | 13 bits | $2^{13} - 2 = \mathbf{8,190}$ | `64` to `95` |

**Binary Demonstration**:
- University Base Prefix: `10000000 11010000` (128.208)
- CS Prefix (`/17`): `10000000 11010000 1` | `xxxxxxx xxxxxxxx` $\to$ `128.208.128.0/17`
- EE Prefix (`/18`): `10000000 11010000 00` | `xxxxxx xxxxxxxx` $\to$ `128.208.0.0/18`
- Unallocated (`/19`): `10000000 11010000 010` | `xxxxx xxxxxxxx` $\to$ `128.208.64.0/19`
- Art Prefix (`/19`): `10000000 11010000 011` | `xxxxx xxxxxxxx` $\to$ `128.208.96.0/19`

*Router Forwarding Verification*:
Suppose a packet arrives with destination `128.208.100.15`:
1. Test CS Mask (`255.255.128.0`):
   `128.208.100.15 AND 255.255.128.0` = `128.208.0.0` $
e$ `128.208.128.0` (Mismatch).
2. Test EE Mask (`255.255.192.0`):
   `128.208.100.15 AND 255.255.192.0` = `128.208.64.0` $
e$ `128.208.0.0` (Mismatch).
3. Test Art Mask (`255.255.224.0`):
   `100` in binary = `01100100`. Mask `224` = `11100000`.
   `01100100 AND 11100000` = `01100000` (`96`).
   Result: `128.208.96.0` matches Art Subnet! Packet forwarded out Art interface.

---

#### 🔥 Classless Inter-Domain Routing (CIDR) & Route Aggregation

- Introduced by RFC 1519 in 1993 to eliminate classful boundaries and combat routing table explosion.
- **Prefix Notation**: Written as `IP_Address/prefix_length` (e.g., `192.0.2.0/24`).
- **Route Aggregation (Supernetting)**:
  - Multiple small contiguous network prefixes are merged into a single larger prefix announced to core Internet routers.
  - *Example (Slide 80)*: An ISP has block starting at `194.24.0.0`:
    - Cambridge: Needs 2048 addresses $\to$ assigns `194.24.0.0/21` (Addresses `194.24.0.0` to `194.24.7.255`).
    - Edinburgh: Needs 1024 addresses $\to$ assigns `194.24.8.0/22` (Addresses `194.24.8.0` to `194.24.11.255`).
    - Oxford: Needs 4096 addresses $\to$ assigns `194.24.16.0/20` (Addresses `194.24.16.0` to `194.24.31.255`).
  - Outside routers advertise just `194.24.0.0/19` (aggregating all three into 1 routing entry!).
- **The Longest Prefix Match (LPM) Rule**:
  - When an incoming destination IP address matches multiple routing entries of differing lengths, the router **must** forward the packet along the interface associated with the **longest matching prefix** (the most specific route).

---

#### 🔥 Special IP Addresses

| IP Address / Range | Function & Scope |
| :--- | :--- |
| `0.0.0.0 /32` | "This host on this network" (Used as source address during DHCP boot). |
| `0.0.0.0 /0` | Default route in router forwarding tables. |
| `255.255.255.255` | Limited Local Broadcast (Delivered to all hosts on local LAN; never crossed by routers). |
| Subnet Base + All 1s | Directed Broadcast (e.g., `128.208.255.255` broadcasts to all hosts in that specific subnet). |
| `127.0.0.0 /8` | Loopback Interface (e.g., `127.0.0.1` localhost; packets processed internally by OS stack). |
| `169.254.0.0 /16` | APIPA (Automatic Private IP Addressing / Link-local fallback when DHCP fails). |
| `10.0.0.0 /8` | RFC 1918 Private IP Space (Enterprise networks; not routable on public Internet). |
| `172.16.0.0 /12` | RFC 1918 Private IP Space (`172.16.0.0` to `172.31.255.255`). |
| `192.168.0.0 /16` | RFC 1918 Private IP Space (Home & SOHO LANs). |

---

#### 🔥 Network Address Translation (NAT)

> 💡 **Analogy (Hinglish)**: NAT box ek office ke receptionist jaisa hai! Company mein 500 employees hain par company ka bahar ek hi landline phone number hai. Jab employee #12 andar se bahar kisi ko call karta hai, toh receptionist connection jodti hai aur register mein likh leti hai: "Extension 12 is talking on Line 1". Bahar wale ko sirf company ka main number dikhta hai. Jab bahar se aawaz aati hai, receptionist register dekh kar call extension 12 par connect kar deti hai. Isse company ko 500 alag telephone number khareedne nahi pade!

- **Motivation**: Extreme shortage of public IPv4 addresses.
- **Operation (NAPT / PAT - Port Address Translation)**:
  - Inside a private network, all hosts use RFC 1918 addresses (`192.168.1.x`).
  - The NAT router is assigned a single public IP address by the ISP (e.g., `198.51.100.3`).
  - When an internal host sends an outbound packet:
    - NAT replaces the private source IP and port with its own public IP and an available ephemeral port.
    - NAT records the mapping in its **Translation Table**.
  - When incoming response packets arrive:
    - NAT inspects the destination port, looks up its table, replaces the destination IP and port with the original private host IP/port, and forwards inside.

```
NAT Operation Walkthrough:

[ Host 192.168.1.10:5001 ] ---> [ NAT Router (198.51.100.3) ] ---> [ Web Server 142.250.190.46:80 ]
                                 Replaces Source:
                                 192.168.1.10:5001 -> 198.51.100.3:20001
```

**NAT Translation Table**:

| Internal Source (Private IP:Port) | External Source (NAT Public IP:Port) | Remote Destination |
| :--- | :--- | :--- |
| `192.168.1.10:5001` | `198.51.100.3:20001` | `142.250.190.46:80` |
| `192.168.1.15:5001` | `198.51.100.3:20002` | `142.250.190.46:80` |

- **Architectural Issues & Criticisms of NAT**:
  1. Violates the fundamental **End-to-End Principle** of the Internet.
  2. Modifies Layer 4 port numbers inside Layer 3 routers (layering violation).
  3. Prevents incoming connections: external clients cannot initiate connections to servers hosted behind NAT.
  4. Breaks protocols that embed IP addresses inside their payload (e.g., FTP `PORT` command, SIP VoIP).
  5. **Traversal Workarounds**: STUN (RFC 5389), TURN, UPnP, and Static Port Forwarding.

<br>

### 3️⃣ 5.6.3 IP Version 6 (IPv6)

Designed as the long-term successor to IPv4 to resolve address exhaustion permanently.

#### IPv6 40-Byte Fixed Header Layout

```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|Version| Traffic Class |           Flow Label                  |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|         Payload Length        |  Next Header  |   Hop Limit   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                                               |
+                                                               +
|                                                               |
+                     Source IPv6 Address                       +
|                          (128 Bits)                           |
+                                                               +
|                                                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                                               |
+                                                               +
|                                                               |
+                  Destination IPv6 Address                     +
|                          (128 Bits)                           |
+                                                               +
|                                                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

- **IPv6 Header Simplifications**:
  1. **Fixed 40-byte Size**: Eliminates the variable-length IHL field; hardware parsers process headers at wire speed.
  2. **No Checksum**: Removed completely to accelerate router forwarding. (Error checking handled by Layer 2 CRC and Layer 4 TCP/UDP).
  3. **No Intermediate Fragmentation**: Routers **never** fragment IPv6 packets! If a packet is too large, it is dropped, and an ICMPv6 "Packet Too Big" message is returned (enforcing Path MTU Discovery).
  4. **Next Header Field (8 bits)**: Daisy-chains optional **Extension Headers** (e.g., Hop-by-Hop, Routing, Fragment, ESP, AH, Destination Options).

- **IPv6 Addressing Notation**:
  - 128-bit address written as 8 groups of 4 hexadecimal digits:
    `2001:0db8:85a3:0000:0000:8a2e:0370:7334`
  - **Zero Compression Rule**: One sequence of consecutive groups of zeros can be compressed as `::` once per address:
    `2001:db8:85a3::8a2e:370:7334`
  - **IPv4-Mapped IPv6 Address**: Used by dual-stack nodes: `::ffff:192.0.2.1`.

<br>

### 4️⃣ 5.6.4 Internet Control Protocols

Companion protocols operating alongside IP at the network layer:

#### 1. ICMP - Internet Control Message Protocol (RFC 792)

> 💡 **Analogy (Hinglish)**: ICMP network ka "error courier" hai. Jab postman (IP) packet deliver nahi kar pata (raaste mein road block hai ya recipient mar chuka hai), toh post office sender ko ek red letter wapas bhejta hai: "Bhai, tera parcel deliver nahi ho saka kyunki Destination Unreachable tha".

- Carried directly inside IP datagrams (`Protocol = 1`).
- **Core Message Types**:
  - **Type 8, Code 0**: Echo Request (Used by `ping`).
  - **Type 0, Code 0**: Echo Reply (Ping response).
  - **Type 3**: Destination Unreachable:
    - Code 0 = Network unreachable.
    - Code 1 = Host unreachable.
    - Code 3 = Port unreachable.
    - Code 4 = Fragmentation needed and DF set (used by PMTUD).
  - **Type 11, Code 0**: Time Exceeded (TTL hit 0 during transit; utilized by `traceroute` to map router hops).
  - **Type 5**: Redirect (Informs sender to use a shorter alternative local gateway).

---

#### 2. ARP - Address Resolution Protocol (RFC 826)

> 💡 **Analogy (Hinglish)**: ARP ek classroom teacher jaisa hai. Teacher ke paas Roll Number (IP address) hai, par use dekhna hai ki us roll number ka kaunsa bachha physically classroom mein baitha hai (MAC address). Teacher khadi hokar pure kamre mein chilati hai: "Roll 25 kaun hai?" (ARP Broadcast). Baki 59 bachhe sunkar shant rehte hain, sirf Roll 25 khada hokar bolta hai: "Sir, main Rahul hoon, ye raha mera ID card" (ARP Unicast Reply)!

- Bridges Layer 3 (32-bit IP address) to Layer 2 (48-bit Ethernet MAC address) on the same local broadcast link.
- **Protocol Flow**:
  1. Source host $H_1$ wants to send to $H_2$ on same LAN; knows $H_2$'s IP, needs $H_2$'s MAC.
  2. $H_1$ broadcasts an **ARP Request** frame to Ethernet address `FF:FF:FF:FF:FF:FF`.
  3. All hosts on the LAN receive the frame; only $H_2$ recognizes its IP address.
  4. $H_2$ returns an **ARP Reply** directly to $H_1$'s MAC address via **Unicast**.
  5. Both hosts cache the mapping in their local **ARP Table / Cache** with a timeout (typically 20 minutes).
- **Remote Subnet Delivery**: If the destination IP is on a remote network, the sender uses ARP to resolve the MAC address of its **Default Gateway (Local Router)**, NOT the destination host!

---

#### 3. DHCP - Dynamic Host Configuration Protocol (RFC 2131)

> 💡 **Analogy (Hinglish)**: DHCP hotel ke reception jaisa hai. Jab tum hotel pahunchte ho, toh tumhare paas koi kamra (IP address) nahi hota. Receptionist tumhara naam register karta hai aur 2 din ke liye Room 302 ki chaabi (lease) de deta hai, saath hi Wi-Fi password (DNS) aur hotel guide (Gateway) deta hai. Check-out time khatam hone par chaabi wapas deni padti hai ya lease extend karni padti hai.

- Automates client network setup via UDP (Server Port 67, Client Port 68).
- **The D-O-R-A Process**:
  1. **Discover**: Unconfigured client broadcasts `DHCPDISCOVER` (`255.255.255.255`) with source `0.0.0.0`.
  2. **Offer**: DHCP server reserves an IP and broadcasts/unicasts `DHCPOFFER` proposing: IP Address, Subnet Mask, Default Gateway, DNS Server IPs, and Lease Time.
  3. **Request**: Client broadcasts `DHCPREQUEST` publicly announcing which server's offer it accepts.
  4. **Acknowledge (ACK)**: Chosen server sends `DHCPACK` confirming the binding and starting the lease timer.
- **DHCP Relay Agent**: Broadcasts cannot cross routers. A Relay Agent configured on the local router intercepts DHCP broadcasts and unicasts them to a centralized DHCP server on another subnet.

<br>

### 5️⃣ 5.6.5 Multi-Protocol Label Switching (MPLS)

- Traditional IP routing requires parsing variable-length prefixes in software at every router hop.
- MPLS (RFC 3031) introduces a **Layer 2.5 "Shim" Header** inserted between the Layer 2 frame header and the Layer 3 IP header.

```
MPLS Shim Header Format (32 Bits Total):

 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                Label (20 Bits)                | Exp/QoS |S|TTL|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                                 (3 bits)  | (8)
                                                  S-bit: bit 23
```

- **Header Fields**:
  - **Label (20 bits)**: The fixed-length index used for line-rate switching lookups.
  - **Exp / QoS (3 bits)**: Traffic class for CoS / DiffServ queueing.
  - **S (Bottom-of-Stack, 1 bit)**: Set to `1` for the innermost label; `0` if more labels follow.
  - **TTL (8 bits)**: Time-to-Live counter decremented to prevent loops.

- **Forwarding Equivalence Class (FEC)**:
  - A group of packets forwarded in the same manner over the same path with identical QoS treatment (e.g., all traffic matching `198.51.100.0/24` with high priority).
  - The FEC is mapped to an MPLS label at the network ingress.

- **MPLS Router Roles**:
  - **Label Edge Router (LER / Ingress Router)**: Classifies arriving standard IP packets, assigns an FEC, prepends the 32-bit MPLS label, and forwards.
  - **Label Switching Router (LSR / Core Router)**: Swaps the incoming label for an outgoing label using a simple, fast hardware table lookup (**Label Swapping**) and forwards.
  - **Egress LER**: Strips the label (**Pop**) and forwards the native IP datagram.

- **Label Stacking**:
  - Packets can carry a stack of labels (LIFO).
  - Enables hierarchical tunneling: an outer label routes through an ISP backbone tunnel, while an inner label preserves customer VPN identification.

<br>

### 6️⃣ 5.6.6 OSPF - Open Shortest Path First (RFC 2328)

- **Characteristics**:
  - Premier Interior Gateway Protocol (IGP) for large corporate and campus networks.
  - Open IETF standard based on **Link State Routing**.
  - Operates directly over IP (`Protocol 89`).
  - Rapid convergence; completely free of Count-to-Infinity.
  - Supports Equal-Cost Multi-Path (ECMP).

- **Hierarchical Area Architecture**:
  - An Autonomous System (AS) is partitioned into logical **Areas**.
  - **Backbone Area (Area 0 / 0.0.0.0)**: Central hub. All inter-area traffic must transit Area 0.
  - **Area Border Router (ABR)**: Connects one or more non-backbone areas to Area 0; injects summary routes.
  - **AS Boundary Router (ASBR)**: Connects the AS to external networks; imports external routes.
  - **Stub Area**: An edge area with a single exit point; avoids external route flooding, substituting a simple default route (`0.0.0.0/0`).

```
OSPF Two-Level Hierarchy:

           +---------------------------------+
           |       BACKBONE (AREA 0)         |
           |         [ Backbone R ]          |
           +----------------+----------------+
                           /  \
             Area Border  /    \  Area Border
               Router    /      \   Router
                        v        v
           +--------------+    +--------------+
           |    AREA 1    |    |    AREA 2    |
           | [ Internal ] |    | [ Internal ] |
           +--------------+    +--------------+
```

- **Five OSPF Packet Types**:
  1. `Hello`: Discovers neighbors, elects Designated Routers (DR/BDR), and verifies bidirectional connectivity (sent every 10 s).
  2. `Database Description (DBD)`: Summary of link state database used during initial adjacency synchronization.
  3. `Link State Request (LSR)`: Requests missing or outdated LSAs from neighbor.
  4. `Link State Update (LSU)`: Transports one or more Link State Advertisements (LSAs) during flooding.
  5. `Link State Acknowledgment (LSAck)`: Reliably confirms receipt of LSUs.

- **Designated Router (DR) & Backup DR (BDR)**:
  - On broadcast multi-access links (Ethernet LANs), having $N$ routers establish peer-to-peer adjacencies would generate $N(N-1)/2$ adjacencies and massive LSP flooding overhead.
  - Routers elect a **DR** and **BDR**. All other routers (`DROther`) form adjacencies only with the DR/BDR, reducing adjacencies to $2(N-1)$.

<br>

### 7️⃣ 5.6.7 BGP - Border Gateway Protocol (BGP-4, RFC 4271)

> 💡 **Analogy (Hinglish)**: OSPF ghar ke andar ka parivarik mamla hai jahan sab ek dusre ko sach batate hain aur shortest path nikalte hain. BGP do deshon ke beech ki international diplomacy hai! Har country (AS) ka apna kanoon (routing policy) hota hai. BGP bolta hai: "Mujhe farak nahi padta ki shortest path kya hai, main apne dushman ke network se apna traffic nahi guzarunga, aur kisi dusre ka traffic tabhi uthaunga jab wo mujhe paise dega!" BGP pure Internet ka international trade contract hai.

- **Characteristics**:
  - The de facto **Inter-Domain (Inter-AS)** routing protocol of the global Internet.
  - Operates over **TCP Port 179** for reliable connection management.
  - Employs **Path Vector Routing**: Advertisements list the complete sequence of Autonomous Systems traversed (**AS-PATH**).

- **AS Types & Peering Policies**:
  - **Stub AS**: Single connection to the Internet; carries no transit traffic.
  - **Multihomed AS**: Connected to multiple transit providers for redundancy; refuses transit traffic between them.
  - **Transit AS**: Large telecom/ISP backbone (Tier-1 / Tier-2) that charges fees to carry third-party packets.
  - **Business Relationships**:
    - **Transit (Customer-Provider)**: Customer pays ISP for upstream Internet access.
    - **Peering**: Two ISPs exchange traffic destined strictly for each other's customers free of charge at Internet Exchange Points (IXPs).

```
BGP AS-PATH Propagation & Loop Prevention:

[ AS 10 ] ===(110.23/16 | AS-PATH: 10)====> [ AS 50 ] ===(110.23/16 | AS-PATH: 50, 10)====> [ AS 100 ]
                                                                                                  |
                                          If AS 10 sees its own number in AS-PATH: <--------------+
                                          REJECT ROUTE IMMEDIATELY! (Loop Detected)
```

- **Loop Prevention via AS-PATH**:
  - Each BGP router appends its own AS Number (ASN) to the `AS-PATH` attribute before advertising to external peers.
  - If a router sees its **own ASN** inside an incoming AS-PATH, it immediately discards the advertisement, preventing routing loops!
- **eBGP vs. iBGP**:
  - **eBGP (External BGP)**: Runs across border links between routers in different ASes.
  - **iBGP (Internal BGP)**: Distributes external routes learned via eBGP among all routers within the same AS.

<br>

### 8️⃣ Internet Multicasting & Mobile IP Brief Overview

- **Internet Multicasting (5.6.8)**:
  - Uses Class D addresses (`224.0.0.0/4`).
  - **IGMP (Internet Group Management Protocol)**: Used by hosts to join or leave multicast groups on their local subnet.
  - **PIM (Protocol Independent Multicast)**: Used by routers to construct efficient multicast distribution trees (Sparse Mode / Dense Mode).
- **Mobile IP (5.6.9)**:
  - Allows mobile devices to roam between networks without changing their home IP address.
  - Uses a **Home Agent (HA)** on the home network and a **Foreign Agent (FA)** on the visited network.
  - The mobile node obtains a temporary **Care-of Address (CoA)**; the Home Agent encapsulates incoming packets in a tunnel to the Care-of Address (**Triangular Routing**).

<br>

---

## 🐦‍🔥 PROTOCOL SUMMARIES QUICK REFERENCE

This section provides concise, high-yield summary cards for every major network layer protocol covered in the syllabus and lecture slides.

<br>

### 🛡️ 1. IPv4 (Internet Protocol Version 4)
- **Layer & RFC**: Layer 3 (Network Layer) | RFC 791 (1981).
- **Addressing**: 32-bit logical addresses written in dotted decimal (e.g., `192.0.2.1`).
- **Core Mechanism**: Connectionless, unreliable, best-effort packet delivery. Datagrams routed independently.
- **Key Header Fields**: Version (`4`), IHL, DSCP/ECN, Total Length, ID/Flags/Offset (Fragmentation), TTL (hop limit), Protocol (`6`=TCP, `17`=UDP), Checksum.
- **Strengths**: 🛡️ Extremely resilient, simple router implementation, massive global adoption.
- **Limitations**: ❌ 32-bit address exhaustion, header checksum recomputed at every hop, no native QoS guarantees.

<br>

### 🛡️ 2. IPv6 (Internet Protocol Version 6)
- **Layer & RFC**: Layer 3 (Network Layer) | RFC 8200 (Internet Standard 2017).
- **Addressing**: 128-bit addresses in 8 colon-hexadecimal blocks (e.g., `2001:db8::1`).
- **Core Mechanism**: Fixed 40-byte base header with daisy-chained extension headers. Intermediate router fragmentation eliminated (enforces PMTUD).
- **Key Header Fields**: Version (`6`), Traffic Class, Flow Label, Payload Length, Next Header, Hop Limit, Source & Destination IP (128 bits each). Checksum removed.
- **Strengths**: 🛡️ Colossal address space ($3.4 \times 10^{38}$), faster hardware switching, built-in Flow Label for QoS.
- **Limitations**: ❌ Incompatible with IPv4 (requires transition mechanisms: Dual-Stack, Tunneling, NAT64).

<br>

### 🛡️ 3. ICMP (Internet Control Message Protocol)
- **Layer & RFC**: Layer 3 (Companion to IP) | RFC 792 (`IP Protocol = 1`).
- **Core Mechanism**: Reports errors, network reachability, and diagnostic signals back to the originating sender.
- **Key Messages**:
  - Echo Request / Reply (`Type 8 / 0`): Used by `ping`.
  - Destination Unreachable (`Type 3`): Network, host, or port unreachable, and "Fragmentation Needed but DF set" (PMTUD).
  - Time Exceeded (`Type 11`): TTL dropped to 0 in transit (used by `traceroute`).
  - Redirect (`Type 5`): Informs host of an optimal local gateway.
- **Strengths**: 🛡️ Indispensable for network diagnostics, troubleshooting, and dynamic MTU negotiation.
- **Limitations**: ❌ Often blocked by corporate firewalls due to security/reconnaissance risks (Ping floods, smurf attacks).

<br>

### 🛡️ 4. ARP (Address Resolution Protocol)
- **Layer & RFC**: Layer 2.5 (Link / Network boundary) | RFC 826.
- **Core Mechanism**: Dynamically maps a known 32-bit IPv4 address to a 48-bit physical Ethernet/Wi-Fi MAC address on the local broadcast link.
- **Exchange**: Broadcast Request (`FF:FF:FF:FF:FF:FF`) $\to$ Unicast Reply. Results cached in host ARP Table.
- **Special Forms**: Proxy ARP (router answers for remote host), Gratuitous ARP (detects IP address conflicts).
- **Strengths**: 🛡️ Fully automatic; eliminates manual MAC address configuration.
- **Limitations**: ❌ Vulnerable to ARP Spoofing / Cache Poisoning (no authentication). Does not scale across routers.

<br>

### 🛡️ 5. DHCP (Dynamic Host Configuration Protocol)
- **Layer & RFC**: Application layer protocol configuring Network layer | RFC 2131 (UDP Client 68, Server 67).
- **Core Mechanism**: "Plug-and-play" automatic leasing of IP addresses, subnet masks, default gateways, and DNS servers.
- **Exchange (D-O-R-A)**:
  1. `DHCPDISCOVER` (Broadcast from `0.0.0.0`)
  2. `DHCPOFFER` (Server proposal)
  3. `DHCPREQUEST` (Client selection)
  4. `DHCPACK` (Server confirmation and lease start)
- **DHCP Relay Agent**: Intercepts local client broadcasts and unicasts them to a centralized server across subnets.
- **Strengths**: 🛡️ Eliminates static IP configuration errors; reclaims idle IP addresses via leases.
- **Limitations**: ❌ Single point of failure if relay/server fails; susceptible to Rogue DHCP servers (mitigated by DHCP Snooping).

<br>

### 🛡️ 6. RIP (Routing Information Protocol)
- **Layer & RFC**: Application layer routing daemon (`routed`), UDP Port 520 | RFC 1058 (v1), RFC 2453 (v2).
- **Type**: Interior Gateway Protocol (IGP) | Distance Vector (Bellman-Ford).
- **Metric**: Hop count strictly (Minimum cost path).
- **Limits & Timers**:
  - Maximum metric $= 15$ hops; $16 = \infty$ (Unreachable).
  - Periodic advertisements every 30 seconds; neighbor timeout after 180 seconds.
- **Strengths**: 🛡️ Extremely simple to configure and understand; tiny memory and CPU footprint.
- **Limitations**: ❌ Prone to Count-to-Infinity, slow convergence, unsuited for networks larger than 15 hops.

<br>

### 🛡️ 7. OSPF (Open Shortest Path First)
- **Layer & RFC**: Network Layer (`IP Protocol = 89`) | RFC 2328 (OSPFv2), RFC 5340 (OSPFv3).
- **Type**: Interior Gateway Protocol (IGP) | Link State (Dijkstra's Shortest Path First).
- **Metric**: Cost inversely proportional to link bandwidth ($\text{Cost} = 10^8 / \text{Bandwidth}$).
- **Core Mechanism**:
  - Every router builds the identical topological graph of the network and computes the sink tree locally using Dijkstra.
  - Divided into hierarchical **Areas** connected through **Backbone Area 0**.
  - Designated Router (DR) and Backup DR (BDR) elected on multi-access LANs to minimize flooding.
  - 5 Packet Types: Hello, DBD, LSR, LSU, LSAck.
- **Strengths**: 🛡️ Rapid convergence, loop-free, supports Equal-Cost Multi-Path (ECMP), scales to massive corporate networks.
- **Limitations**: ❌ High memory usage for Link State Database; significant CPU load running Dijkstra.

<br>

### 🛡️ 8. BGP (Border Gateway Protocol - BGP-4)
- **Layer & RFC**: Application / Transport (`TCP Port 179`) | RFC 4271.
- **Type**: Exterior Gateway Protocol (EGP) | Path Vector Routing.
- **Core Mechanism**:
  - Exchanged between Autonomous Systems (ASes) across the global Internet.
  - Advertisements carry reachability (NLRI) alongside the full sequence of ASes traversed (**AS-PATH**).
  - Loop prevention: Routers drop routes containing their own AS number.
  - Routing decisions driven by business relationships (Customer-Provider Transit vs. Peering) and economic policies rather than shortest physical distance.
- **Strengths**: 🛡️ Highly scalable (powers the global Internet), flexible policy enforcement, loop-free path vector design.
- **Limitations**: ❌ Slow convergence (BGP route flapping); vulnerable to BGP Hijacking without RPKI cryptographic validation.

<br>

### 🛡️ 9. MPLS (Multi-Protocol Label Switching)
- **Layer & RFC**: "Layer 2.5" Shim Protocol | RFC 3031.
- **Core Mechanism**:
  - Inserts a 32-bit shim header (20-bit label) between Layer 2 frame and Layer 3 IP header.
  - Packets grouped into Forwarding Equivalence Classes (FECs) at ingress (LER).
  - Core routers (LSRs) forward packets by swapping fixed-length labels at line-rate hardware speeds, avoiding complex IP prefix lookups.
  - Supports **Label Stacking** for VPN tunneling and Traffic Engineering (MPLS-TE).
- **Strengths**: 🛡️ High-speed hardware forwarding, flexible traffic engineering, carrier-grade L2/L3 VPN support.
- **Limitations**: ❌ Complex control plane (requires LDP / RSVP-TE signaling); extra 4-byte header overhead per label.

<br>

### 🛡️ 10. RSVP (Resource ReSerVation Protocol)
- **Layer & RFC**: Network Control Protocol | RFC 2205 (`IP Protocol = 46`).
- **Core Architecture**: Integrated Services (IntServ) signalling protocol.
- **Core Mechanism**:
  - Receiver-initiated resource reservation along the reverse path of multicast/unicast spanning trees.
  - `PATH` messages travel downstream from sender, recording router paths.
  - `RESV` messages travel upstream from receivers, allocating buffer memory and bandwidth at each router.
  - Maintains **Soft State**: periodic refresh messages required to sustain reservations.
- **Strengths**: 🛡️ Delivers mathematically guaranteed QoS (Parekh-Gallager delay bounds), ideal for mission-critical multimedia.
- **Limitations**: ❌ Fails to scale in the public Internet core due to per-flow state explosion; superseded by DiffServ.

<br>

---
</div>
</div>
