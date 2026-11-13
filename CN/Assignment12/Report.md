# Lab 11: Quality of Service at a Router
**Course:** Computer Networks  
**Topic:** Week 11 · Network Layer / Congestion and QoS  

---

## Executive Summary
This lab implements and validates the four fundamental Quality-of-Service (QoS) mechanisms deployed in network routers to arbitrate link bandwidth and manage traffic flows:
1. **Part A: Admission Control** – Parekh-Gallagher model ensuring reserved minimum bandwidth guarantees.
2. **Part B: Traffic Policing** – Token bucket mechanism dropping non-conforming packets.
3. **Part C: Traffic Shaping** – Token bucket mechanism buffering non-conforming packets to smooth transmission.
4. **Part D: Packet Scheduling** – Weighted Fair Queuing (WFQ) compared against First-In First-Out (FIFO).

---

## Part A: Admission Control (Parekh-Gallagher Model)

### 1. Model & Setup
- **Output Link Capacity ($C$):** $10\text{ Mbps}$
- **Parekh-Gallagher Guarantee:** Under WFQ, a flow $i$ with weight $W_i$ sharing a link of capacity $C$ with total admitted weight $\sum W$ is guaranteed a minimum service rate:
  $$R_{\text{guaranteed}, i} = \left(\frac{W_i}{\sum W}\right) \cdot C$$
- **Admission Test:** A new flow $i$ is admissible if and only if, after adding $i$, **every** admitted flow (including $i$) still receives at least its requested rate:
  $$\left(\frac{W_k}{\sum_{j \in \text{Admitted} \cup \{i\}} W_j}\right) \cdot C \ge R_k, \quad \forall k \in \text{Admitted} \cup \{i\}$$

### 2. Request Sequence & Decisions
Flow setup requests arrive in the following order:

| Step | Flow | Weight ($W$) | Requested Rate ($R$) | Candidate Admitted Set | Total Weight ($\sum W$) | Guaranteed Rate Formula | Guaranteed Rate | Decision |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| 1 | $f_1$ | 1 | $2.0\text{ Mbps}$ | $\{f_1\}$ | 1 | $(1/1) \times 10$ | $10.00\text{ Mbps} \ge 2.0\text{ Mbps}$ | **ADMITTED** |
| 2 | $f_2$ | 1 | $2.0\text{ Mbps}$ | $\{f_1, f_2\}$ | 2 | $(1/2) \times 10$ | $5.00\text{ Mbps} \ge 2.0\text{ Mbps}$ | **ADMITTED** |
| 3 | $f_3$ | 2 | $4.0\text{ Mbps}$ | $\{f_1, f_2, f_3\}$ | 4 | $(2/4) \times 10$ | $5.00\text{ Mbps} \ge 4.0\text{ Mbps}$ | **ADMITTED** |
| 4 | $f_4$ | 1 | $3.0\text{ Mbps}$ | $\{f_1, f_2, f_3, f_4\}$ | 5 | $(1/5) \times 10$ | $2.00\text{ Mbps} < 3.0\text{ Mbps}$ | **REJECTED** |

**Confirmation:** $f_1$, $f_2$, and $f_3$ are admitted, and $f_4$ is rejected because it would only be guaranteed $2.0\text{ Mbps}$ against its requested rate of $3.0\text{ Mbps}$.

### 3. Written Answers for Part A
- **Which flow's guarantee the rejection protects:**
  1. **Directly:** Flow $f_4$ fails its own admission requirement because its guaranteed share under weight 1 is $\frac{1}{5} \times 10 = 2.0\text{ Mbps} < 3.0\text{ Mbps}$.
  2. **Protection of existing flows:** The rejection protects **all three currently admitted flows ($f_1, f_2,$ and $f_3$)** from QoS degradation.
     - The sum of requested rates for the admitted flows is:
       $$\sum_{k=1}^3 R_k = 2.0 + 2.0 + 4.0 = 8.0\text{ Mbps}$$
     - On a $10.0\text{ Mbps}$ link, only $10.0 - 8.0 = 2.0\text{ Mbps}$ of spare capacity remains.
     - If the router attempted to accommodate $f_4$'s request of $3.0\text{ Mbps}$ by increasing its weight $W_4$ so that $\left(\frac{W_4}{4 + W_4}\right) \cdot 10 \ge 3 \implies W_4 \ge \frac{12}{7} \approx 1.714$, the guaranteed rates for the existing flows would drop to:
       - $f_1$: $\frac{1}{4 + 1.714} \times 10 = 1.75\text{ Mbps} < 2.0\text{ Mbps}$ (VIOLATED)
       - $f_2$: $\frac{1}{4 + 1.714} \times 10 = 1.75\text{ Mbps} < 2.0\text{ Mbps}$ (VIOLATED)
       - $f_3$: $\frac{2}{4 + 1.714} \times 10 = 3.50\text{ Mbps} < 4.0\text{ Mbps}$ (VIOLATED)
     - Total bandwidth demand would be $8.0 + 3.0 = 11.0\text{ Mbps} > 10.0\text{ Mbps}$. Thus, rejecting $f_4$ protects the strict SLA commitments made to $f_1$, $f_2$, and $f_3$.

- **Weight or Rate $f_4$ would need to be admitted:**
  - **Rate Required:** Flow $f_4$ would need to reduce its requested rate to **$R_4 \le 2.0\text{ Mbps}$** (the remaining unallocated link capacity).
  - **Weight Required:**
    - With $R_4 = 2.0\text{ Mbps}$, its original weight **$W_4 = 1$** is sufficient, providing $\frac{1}{5} \times 10 = 2.0\text{ Mbps}$.
    - If $f_4$ insists on requesting $R_4 = 3.0\text{ Mbps}$, **no valid weight exists** that can admit $f_4$, because the total required rate ($11\text{ Mbps}$) exceeds physical link capacity ($10\text{ Mbps}$).

---

## Part B: Traffic Policing (Token Bucket Dropping)

### 1. Setup & Algorithm
- **Fill rate ($r$):** $1.0\text{ token / time unit}$
- **Bucket capacity ($b$):** $4.0\text{ tokens}$
- **Initial bucket state:** Full ($4.0\text{ tokens}$ at $t = 0$)
- **Packet size ($L$):** $1.0\text{ token / packet}$
- **Trace:** A burst of 6 packets arriving at $t = 0$, followed by single packets at $t = 5$ and $t = 6$.
- **Mechanism:** If tokens $\ge L$, packet passes and $L$ tokens are removed. Otherwise, packet is **dropped** immediately (no buffer).

### 2. Execution Trace

| Packet # | Arrival Time ($t$) | Tokens Available Before | Action | Tokens Remaining | Status |
|:---:|:---:|:---:|:---:|:---:|:---:|
| 1 | 0 | 4.0 | Conforms ($\ge 1$) | 3.0 | **PASS** |
| 2 | 0 | 3.0 | Conforms ($\ge 1$) | 2.0 | **PASS** |
| 3 | 0 | 2.0 | Conforms ($\ge 1$) | 1.0 | **PASS** |
| 4 | 0 | 1.0 | Conforms ($\ge 1$) | 0.0 | **PASS** |
| 5 | 0 | 0.0 | Non-conforming ($< 1$) | 0.0 | **DROP** |
| 6 | 0 | 0.0 | Non-conforming ($< 1$) | 0.0 | **DROP** |
| 7 | 5 | $\min(4.0, 0 + 5 \times 1) = 4.0$ | Conforms ($\ge 1$) | 3.0 | **PASS** |
| 8 | 6 | $\min(4.0, 3 + 1 \times 1) = 4.0$ | Conforms ($\ge 1$) | 3.0 | **PASS** |

**Summary:** 6 packets passed, exactly 2 packets dropped.

### 3. Written Answers for Part B
- **Why exactly two packets are dropped in terms of bucket capacity:**
  The token bucket starts full with a maximum capacity of $b = 4$ tokens. At time $t = 0$, a burst of 6 packets arrives instantaneously ($\Delta t = 0$). Since no elapsed time occurs between these packet arrivals, 0 new tokens accrue during the burst. The first 4 packets consume all 4 available tokens, completely emptying the bucket. When packets 5 and 6 arrive, 0 tokens are available. Because a policer lacks buffering capabilities, non-conforming packets cannot wait and are dropped immediately. Therefore, exactly $6 - 4 = 2$ packets are dropped due to the bucket capacity limit of $b = 4$.

---

## Part C: Traffic Shaping (Token Bucket Buffering)

### 1. Setup & Algorithm
- **Parameters:** Identical token bucket ($r = 1.0$, $b = 4.0$, starts full with 4 tokens, packet size $L = 1.0$), applied to the same trace.
- **Mechanism:** Non-conforming packets are **buffered** in a queue and released as soon as sufficient tokens accrue at rate $r$. No packets are dropped.

### 2. Execution Trace & Delays

| Packet # | Arrival Time ($t_{\text{arr}}$) | Release Time ($t_{\text{rel}}$) | Delay ($t_{\text{rel}} - t_{\text{arr}}$) | Tokens Left After Release | Status |
|:---:|:---:|:---:|:---:|:---:|:---:|
| 1 | 0.0 | 0.0 | 0.0 | 3.0 | **DELIVERED** |
| 2 | 0.0 | 0.0 | 0.0 | 2.0 | **DELIVERED** |
| 3 | 0.0 | 0.0 | 0.0 | 1.0 | **DELIVERED** |
| 4 | 0.0 | 0.0 | 0.0 | 0.0 | **DELIVERED** |
| 5 | 0.0 | 1.0 | 1.0 | 0.0 | **DELIVERED** |
| 6 | 0.0 | 2.0 | 2.0 | 0.0 | **DELIVERED** |
| 7 | 5.0 | 5.0 | 0.0 | 2.0 | **DELIVERED** |
| 8 | 6.0 | 6.0 | 0.0 | 2.0 | **DELIVERED** |

**Summary:** All 8 packets delivered, 0 dropped. Packets 1–4, 7, 8 experienced 0 delay; Packet 5 experienced delay 1.0; Packet 6 experienced delay 2.0.

### 3. Written Answers for Part C
- **Delay Report & Comparison with Part B:**
  - In **Part B (Policing)**, non-conforming packets 5 and 6 suffered permanent packet loss (dropped at $t = 0$), resulting in only a 75% delivery rate. Packets that passed had 0 delay.
  - In **Part C (Shaping)**, 100% packet delivery is achieved (zero loss). Packets 1–4 depart immediately at $t = 0$. Packet 5 is buffered and leaves at $t = 1$ (delay = 1.0 unit), and Packet 6 is buffered behind it and leaves at $t = 2$ (delay = 2.0 units). Packets 7 and 8 arrive when tokens are replenished and depart immediately at $t = 5$ and $t = 6$ (delay = 0.0 units).
- **The single fundamental difference producing drops in one and delays in the other:**
  - **The presence of a packet buffer (queue).**
  - **Policing is memoryless:** It has no buffer for excess traffic. If tokens are unavailable at the exact instant of packet arrival, the packet is discarded immediately.
  - **Shaping incorporates a buffer:** It stores excess non-conforming packets in memory and meters their release according to token generation rate $r$, intentionally exchanging latency (delay) to eliminate packet loss and produce a smooth output stream.

---

## Part D: Packet Scheduling (WFQ vs FIFO)

### 1. Setup & Formula
- **Admitted Flows (from Part A):**
  - Flow 1: Weight $w = 1$, Packets: $A(0, 8), F(10, 6)$
  - Flow 2: Weight $w = 1$, Packets: $B(5, 6), D(8, 9), H(20, 8)$
  - Flow 3: Weight $w = 2$, Packets: $C(5, 10), E(8, 8), G(11, 10)$
- **WFQ Finish Number Computation:**
  $$F_i = \max(\text{arrival}_i, F_{\text{prev in same flow}}) + \frac{\text{length}_i}{w_i}$$
  Packets are transmitted in strictly increasing order of finish number $F$.

### 2. Finish Number Step-by-Step Derivation

| Packet | Flow | Weight ($w$) | Arrival | Length | Finish Number Formula | Finish Number ($F$) |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **A** | Flow 1 | 1 | 0 | 8 | $\max(0, 0) + 8/1 = 0 + 8$ | **8.0** |
| **C** | Flow 3 | 2 | 5 | 10 | $\max(5, 0) + 10/2 = 5 + 5$ | **10.0** |
| **B** | Flow 2 | 1 | 5 | 6 | $\max(5, 0) + 6/1 = 5 + 6$ | **11.0** |
| **E** | Flow 3 | 2 | 8 | 8 | $\max(8, 10) + 8/2 = 10 + 4$ | **14.0** |
| **F** | Flow 1 | 1 | 10 | 6 | $\max(10, 8) + 6/1 = 10 + 6$ | **16.0** |
| **G** | Flow 3 | 2 | 11 | 10 | $\max(11, 14) + 10/2 = 14 + 5$ | **19.0** |
| **D** | Flow 2 | 1 | 8 | 9 | $\max(8, 11) + 9/1 = 11 + 9$ | **20.0** |
| **H** | Flow 2 | 1 | 20 | 8 | $\max(20, 20) + 8/1 = 20 + 8$ | **28.0** |

### 3. Transmission Order Comparison
- **WFQ Scheduled Order:**
  $$\mathbf{A \longrightarrow C \longrightarrow B \longrightarrow E \longrightarrow F \longrightarrow G \longrightarrow D \longrightarrow H}$$
  *(Finish numbers: A: 8, C: 10, B: 11, E: 14, F: 16, G: 19, D: 20, H: 28)*
- **FIFO Scheduled Order:**
  $$\mathbf{A \longrightarrow B \longrightarrow C \longrightarrow D \longrightarrow E \longrightarrow F \longrightarrow G \longrightarrow H}$$
  *(Arrival times: A: 0, B: 5, C: 5, D: 8, E: 8, F: 10, G: 11, H: 20)*

### 4. Written Answers for Part D
- **How the weight-2 flow is served:**
  - Flow 3 has weight $w = 2$, double that of Flow 1 and Flow 2 ($w = 1$).
  - In the finish number formula, packet length is divided by weight ($\frac{L}{w} = \frac{L}{2}$). Therefore, Flow 3 consumes virtual time at half the rate per byte, earning **$50\%$ of the total link bandwidth** ($2 / (1+1+2)$), while Flows 1 and 2 each receive $25\%$.
  - **Key Examples of WFQ Priority:**
    1. **Packet C vs Packet B:** Both arrive at $t = 5$. Packet C has length 10, whereas Packet B has length 6. Under FIFO, B would be served before or with C. Under WFQ, because Flow 3 has weight 2, $F(C) = 5 + 10/2 = 10$, while $F(B) = 5 + 6/1 = 11$. **C is transmitted before B** despite being larger.
    2. **Packet G vs Packet D:** Packet D arrives at $t = 8$, while Packet G does not arrive until $t = 11$. Under FIFO, D is transmitted well ahead of G. Under WFQ, Packet D finishes at $F(D) = 20$, while Packet G finishes at $F(G) = 19$. **G jumps ahead of D** because Flow 3's high weight accelerates its packet drain rate.

- **How WFQ protects a flow from being starved by another:**
  - In **FIFO**, all packets are placed into a single shared queue. If an aggressive or malicious flow sends continuous back-to-back large packets, it completely saturates the queue, starving other flows and causing unbounded delay and packet drops.
  - In **WFQ**, each flow maintains its own virtual transmission sequence. If an aggressive flow floods the router, its finish numbers grow rapidly ($F_k = F_{k-1} + L_k / w$).
  - When another well-behaved flow transmits a packet, its finish number is calculated using its current arrival time: $F = \max(\text{arrival}, F_{\text{prev}}) + L / w$, which produces a small finish number.
  - The router always selects the packet with the lowest finish number. Thus, well-behaved flows immediately jump ahead of backlogged bursts from aggressive flows.
  - WFQ guarantees **flow isolation**: each flow $i$ is guaranteed at least its fair share of bandwidth $\frac{W_i}{\sum W} \cdot C$, strictly preventing starvation regardless of how heavily other flows overload the link.

