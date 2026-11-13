# Domain 06: Computer Science Fundamentals (CN, OS, OOP & DSA)

This guide provides targeted revision for core CS concepts essential for software engineering technical interviews: **Computer Networks (CN)**, **Operating Systems (OS)**, **Object-Oriented Programming (OOP)**, and high-frequency **Data Structures & Algorithms (DSA)** patterns.

---

## 1. Computer Networks (CN)

### 1.1 The OSI Model vs. TCP/IP Model
| Layer (OSI) | Protocol Data Unit (PDU) | Protocols / Technologies | Function |
| :--- | :--- | :--- | :--- |
| **7. Application** | Data / Messages | HTTP/HTTPS, DNS, WebSockets, SMTP, FTP | User-facing application protocols |
| **6. Presentation** | Data | TLS/SSL, JSON, gzip | Encryption, compression, data representation |
| **5. Session** | Data | RPC, NetBIOS | Session management and checkpointing |
| **4. Transport** | Segment (TCP) / Datagram (UDP) | TCP, UDP | End-to-end delivery, port numbers, flow/congestion control |
| **3. Network** | Packet | IP (IPv4/IPv6), ICMP, BGP, OSPF | Logical addressing and path routing across networks |
| **2. Data Link** | Frame | Ethernet, Wi-Fi (802.11), MAC | Node-to-node framing, physical MAC addressing |
| **1. Physical** | Bits | Fiber optics, RJ45 copper, radio waves | Physical transmission of raw bitstreams |

---

### 1.2 TCP vs. UDP
| Feature | TCP (Transmission Control Protocol) | UDP (User Datagram Protocol) |
| :--- | :--- | :--- |
| **Connection** | Connection-oriented (3-way handshake) | Connectionless |
| **Reliability** | Guaranteed delivery (retransmission of lost packets) | Best-effort delivery (packets can be dropped or duplicated) |
| **Ordering** | In-order sequencing guaranteed | Packets may arrive out of order |
| **Overhead** | Higher (20-60 byte header, ACK packets, flow control) | Minimal (8 byte header) |
| **Use Cases** | Web pages (HTTP), File transfers, Emails, SSH | Video streaming, VoIP, DNS lookups, Online gaming |

#### TCP 3-Way Handshake & 4-Way Teardown
- **Handshake (Connection Establishment):**
  1. Client $\to$ Server: `SYN` (Sequence number = $X$)
  2. Server $\to$ Client: `SYN-ACK` (Sequence number = $Y$, Acknowledgment number = $X+1$)
  3. Client $\to$ Server: `ACK` (Acknowledgment number = $Y+1$)
- **Teardown (Connection Termination):**
  1. Client $\to$ Server: `FIN`
  2. Server $\to$ Client: `ACK` (Server may still send remaining pending data)
  3. Server $\to$ Client: `FIN`
  4. Client $\to$ Server: `ACK` (Client enters `TIME_WAIT` state for $2 \times \text{MSL}$ to ensure final ACK was delivered)

---

### 1.3 What Happens When You Type a URL in the Browser?
A classic senior interview question:
1. **URL Parsing:** Browser parses protocol (`https`), host (`farmfresh.com`), port (`443`), path (`/dashboard`).
2. **DNS Resolution:**
   - Checks browser cache $\to$ OS cache (`hosts` file) $\to$ Local Router cache $\to$ ISP Recursive Resolver.
   - Recursive query: Root DNS (`.`) $\to$ TLD DNS (`.com`) $\to$ Authoritative DNS (`farmfresh.com`) $\to$ returns IP address.
3. **TCP 3-Way Handshake:** Initiated with server IP on port 443.
4. **TLS/SSL Handshake:**
   - Client Hello (supported cipher suites, TLS version).
   - Server Hello + SSL Certificate (signed by a CA).
   - Key Exchange (Diffie-Hellman / ECDHE) to agree on a symmetric session key.
5. **HTTP Request & Response:** Browser sends `GET /dashboard HTTP/1.1` with headers. Server processes request through middleware and returns HTML payload (`200 OK`).
6. **Critical Rendering Path (CRP):**
   - DOM Tree construction from HTML.
   - CSSOM Tree construction from CSS.
   - Render Tree calculation (DOM + CSSOM).
   - Layout (reflow): calculating geometry/dimensions.
   - Paint: rasterizing pixels onto screen.

---

### 1.4 HTTP Evolution: HTTP/1.1 vs HTTP/2 vs HTTP/3
- **HTTP/1.1:** Persistent connections (`Keep-Alive`), but suffers from **Head-of-Line (HoL) Blocking** at the application layer (only 1 request active at a time per TCP socket; browsers hack around this by opening 6 concurrent connections per host).
- **HTTP/2:** Single TCP connection using **Multiplexing** (binary framing into streams), header compression (**HPACK**), and Server Push. Still has TCP-level HoL blocking if a packet drops.
- **HTTP/3:** Replaces TCP with **QUIC** over UDP. Eliminates TCP HoL blocking; connection migration between Wi-Fi and Cellular without reconnection drops.

---

## 2. Operating Systems (OS)

### 2.1 Processes vs. Threads
| Metric | Process | Thread |
| :--- | :--- | :--- |
| **Definition** | An executing instance of a program | The smallest unit of execution within a process |
| **Address Space** | Isolated memory space (own heap, stack, data) | Shares process heap, code, and file descriptors; has own private stack |
| **Creation Cost** | High (memory allocation, page table creation) | Low (lightweight) |
| **Context Switch** | Slow (flushing CPU cache, swapping page tables) | Fast (no page table swap required) |
| **Communication** | IPC required (pipes, sockets, shared memory) | Direct memory access via shared variables (requires synchronization locks) |

---

### 2.2 Concurrency, Deadlocks & Synchronization
- **Race Condition:** Outcome depends on non-deterministic interleaving of threads accessing shared mutable state.
- **Mutex (Mutual Exclusion):** Binary locking mechanism. Only the thread that acquired the mutex can unlock it.
- **Semaphore:** Counter-based signaling mechanism:
  - *Counting Semaphore:* Controls access to a finite pool of resources (e.g., database connection pool of size 10).
- **Deadlock:** A state where two or more threads are permanently blocked, each waiting for a lock held by the other.
  - **Coffman Conditions (All 4 must hold simultaneously for a deadlock):**
    1. *Mutual Exclusion:* Resource cannot be shared.
    2. *Hold and Wait:* Process holding a resource can request additional resources.
    3. *No Preemption:* Resources cannot be forcibly seized.
    4. *Circular Wait:* A closed chain of processes exists where each process waits for a resource held by the next.

---

### 2.3 Virtual Memory and Paging
- **Virtual Address Space:** Isolates processes from physical RAM. CPU Memory Management Unit (MMU) translates virtual addresses to physical frame addresses using **Page Tables**.
- **Page Fault:** Triggered when a process accesses a page that is mapped in virtual memory but not currently loaded into physical RAM. The OS fetches it from secondary storage (swap/disk).
- **Thrashing:** Excessive paging occurring when the active working set exceeds available physical RAM, causing the OS to spend more time swapping pages than executing instructions.

---

## 3. Object-Oriented Programming (OOP) & SOLID Principles

### 3.1 Four Core Pillars of OOP
1. **Encapsulation:** Bundling data and methods operating on that data inside a class while restricting direct access to internal state (access modifiers `private`, `protected`).
2. **Abstraction:** Hiding complex implementation details and exposing only essential interfaces.
3. **Inheritance:** Enabling a new class to acquire properties and behaviors of an existing class (code reuse).
4. **Polymorphism:** Ability of an interface or method to take multiple forms (Method Overloading compile-time vs Method Overriding runtime).

---

### 3.2 SOLID Principles for Full-Stack Developers
- **S - Single Responsibility Principle (SRP):** A class or module should have one, and only one, reason to change (e.g., separate database query logic from business pricing calculations).
- **O - Open/Closed Principle (OCP):** Software entities should be open for extension, but closed for modification (e.g., adding a new payment gateway by implementing a `PaymentStrategy` interface rather than editing existing `if/else` statements).
- **L - Liskov Substitution Principle (LSP):** Subtypes must be substitutable for their base types without altering program correctness.
- **I - Interface Segregation Principle (ISP):** Clients should not be forced to depend on interfaces they do not use (prefer small, cohesive interfaces).
- **D - Dependency Inversion Principle (DIP):** High-level modules should not depend on low-level modules; both should depend on abstractions (e.g., Express controllers depend on an abstract `NotificationService`, not directly on the concrete `Nodemailer` implementation).

---

## 4. High-Yield DSA Patterns for Full-Stack Interviews

1. **Two Pointers & Sliding Window:**
   - Efficient for subarray/substring searches, array partitioning, and in-place transformations in $O(N)$ time and $O(1)$ space.
2. **Hash Maps & Sets ($O(1)$ Lookups):**
   - Essential for fast caching, frequency counts, grouping data, and deduplication.
3. **BFS & DFS (Graphs & Trees):**
   - BFS (Queue) for shortest path in unweighted graphs or zone delivery hops.
   - DFS (Recursion/Stack) for nested tree traversals, deep object cloning, dependency resolution.
4. **Monotonic Stack / Queue:**
   - Finding next greater/smaller elements in $O(N)$ linear time.
5. **Topological Sort:**
   - Detecting cycles and resolving task/build execution order (Directed Acyclic Graphs).
