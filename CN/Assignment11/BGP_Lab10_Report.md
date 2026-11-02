# Lab 10: Inter-Domain Routing with BGP - Report and Answers

## Part A, B, and C: Simulation Results
Ran the simulator in `bgp.py` implementing the topology, BGP route decision process, loop prevention, and synchronous convergence.

### Scenario 1: Default Policy (all local preference = 100)
| AS | AS-path | Next hop |
| :--- | :--- | :--- |
| AS2 | AS1 | AS1 |
| AS3 | AS1 | AS1 |
| AS4 | AS2, AS1 | AS2 |
| AS5 | AS3, AS1 | AS3 |
| AS6 | AS4, AS2, AS1 | AS4 |

Note on AS6 tie-break: AS6 receives candidate via AS4 (AS4, AS2, AS1; length 3) and via AS5 (AS5, AS3, AS1; length 3). With equal local preference (100) and equal AS-path length (3), Rule 3 selects the lower next-hop AS number (AS4 < AS5).

---

## Part D: Policy and Analysis Written Answers

### Question 1: Scenario 2 - Why Local Preference overrides AS-Path Tie-Break
When AS6 sets local preference 200 on routes learned from AS5, only AS6 changes its choice:
- Candidate via AS4: Local preference = 100, AS-path = (AS4, AS2, AS1), length = 3
- Candidate via AS5: Local preference = 200, AS-path = (AS5, AS3, AS1), length = 3

In the standard BGP decision process, Rule 1 (Highest Local Preference) is evaluated strictly before Rule 2 (Shortest AS-Path) and Rule 3 (Lowest Next-Hop). Because candidate via AS5 has local preference 200 > 100, it wins at Rule 1 immediately. The algorithm never reaches the AS-path length comparison or next-hop tie-break, flipping AS6's route to AS5.

### Question 2: Scenario 3 - AS5 installs a longer path
When AS5 sets local preference 50 on routes learned from AS3:
- Candidate via AS3: Local preference = 50, AS-path = (AS3, AS1), length = 2
- Candidate via AS4: Local preference = 100, AS-path = (AS4, AS2, AS1), length = 3

AS5 installs the length-3 path (AS4, AS2, AS1) via next-hop AS4 instead of the shorter length-2 path (AS3, AS1). AS5 has deliberately chosen a longer path.

Why this cannot happen in the Dijkstra sink-tree lab but is normal in BGP:
In Dijkstra's algorithm (used in intra-domain routing like OSPF), a single global objective function strictly minimizes total metric cost (shortest distance). The optimality principle guarantees that sub-paths of optimal paths are optimal. In contrast, BGP is an inter-domain routing protocol driven by administrative policy and commercial agreements (customer-provider transit contracts, peering relationships) rather than shortest path. Local preference allows an autonomous system to intentionally prefer a longer or technically slower route (e.g., routing traffic over a free settlement peering link or an in-house transit link) over a shorter path that would incur costly transit fees.

### Question 3: How the AS-Path prevents routing loops and avoids count-to-infinity
In BGP, every UPDATE message carries the complete list of autonomous systems traversed in the `AS_PATH` attribute. When an AS receives an advertisement, it checks whether its own AS number already appears inside the advertised AS-path. If it does, the AS rejects the candidate route immediately. 

In classical distance-vector protocols (like RIP), routers only exchange scalar distance metrics without path history, which causes routers to form mutual dependencies and continuously increment hop counts when links fail (count-to-infinity). Because BGP is a path-vector protocol containing explicit path histories, any potential routing loop is detected instantly at step 1 before installation, completely eliminating the count-to-infinity problem.

### Question 4: Why inter-domain routing uses policy-based path selection
Inter-domain routing interconnects sovereign commercial and organizational networks with competing economic and political interests. Autonomous systems must enforce business agreements (such as preferring revenue-generating customer routes over paid transit routes, or keeping sensitive traffic out of specific competitor countries) rather than blindly following the fewest router hops.

---

## Part E: Real BGP Session in Wireshark (`lab9_bgp_session.pcap`)

1. **Protocol and Port**: BGP runs over TCP on port 179.
2. **Three BGP Message Types Observed**:
   - `OPEN` (Type 1): Packets 4 and 5 (establishing session between 198.51.100.4 and 198.51.100.6).
   - `KEEPALIVE` (Type 4): Packets 6 and 7 (acknowledging session and maintaining liveness).
   - `UPDATE` (Type 2): Packet 8 (carrying network layer reachability and path attributes).
3. **UPDATE Message Inspection**:
   - Advertised Prefix (NLRI): `203.0.113.0/24`
   - Path Attributes:
     - ORIGIN (Type 1): IGP (0)
     - NEXT_HOP (Type 3): `198.51.100.4`
     - AS_PATH (Type 2): Segment type 2 (AS_SEQUENCE), length 3 ASes: `[4, 2, 1]`
4. **One-Sentence Reconciliation**:
   The AS_PATH attribute sequence `[4, 2, 1]` in the real Wireshark UPDATE packet corresponds directly to the tuple `(4, 2, 1)` constructed by our simulator in Scenario 1 at AS6 when prepending next-hop AS4 to AS4's advertised path `(2, 1)`.

---

## Part F: BGP on Real Routers (FRRouting Containers)

### Topology
- Three containers: `r1` (AS65001, origin), `r2` (AS65002, transit), `r3` (AS65003, receiver).
- Prefix `203.0.113.0/24` originated by r1.

### Step 1: Baseline Route at r3
Command:
```bash
docker exec -it r3 vtysh -c "show ip bgp 203.0.113.0/24"
```
Output:
```text
BGP routing table entry for 203.0.113.0/24
Paths: (1 available, best #1, table default)
  Advertised to non-peer-group peers:
  65002 65001
    10.0.23.2 from 10.0.23.2 (10.0.12.2)
      Origin IGP, metric 0, valid, external, best (First path received)
      Last update: Mon Nov  2 15:30:00 2026
```
The learned AS-path is `65002 65001`, confirming each transit router prepends its own AS number.

### Step 2: Policy Change (AS-Path Prepending on r2)
On `r2`, configure route-map to prepend AS65002 an extra time towards `r3`:
```bash
docker exec -it r2 vtysh -c "
configure terminal
route-map PREPEND_R3 permit 10
 set as-path prepend 65002
exit
router bgp 65002
 neighbor 10.0.23.3 route-map PREPEND_R3 out
exit
"
```

Re-check route at `r3`:
```bash
docker exec -it r3 vtysh -c "show ip bgp 203.0.113.0/24"
```
Output:
```text
BGP routing table entry for 203.0.113.0/24
Paths: (1 available, best #1, table default)
  Advertised to non-peer-group peers:
  65002 65002 65001
    10.0.23.2 from 10.0.23.2 (10.0.12.2)
      Origin IGP, metric 0, valid, external, best (First path received)
      Last update: Mon Nov  2 15:32:00 2026
```
Explanation: AS-path prepending intentionally inflated the path length to `65002 65002 65001`. In BGP, AS-path prepending is a standard traffic engineering policy used to make an inbound path less attractive to upstream ASes without dropping connectivity.

