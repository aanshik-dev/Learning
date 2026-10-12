"""
Lab Task 2 -- Multi-Hop Forwarding Simulation
=================================================
Computer Networks Lab | Network Layer -- IP Routing Tables and Routing Decisions

A single routing decision (Task 1) only tells you the NEXT router a
packet goes to -- not its whole path. This task simulates a packet
crossing several routers in sequence, each one independently making
its own forwarding decision (by consulting its OWN routing table), the
same way real routers do: no router knows the packet's whole path in
advance, it only knows "what's my next hop for this destination?".

WHAT IS ALREADY DONE FOR YOU
-----------------------------
- A complete, working copy of the RoutingTable class from Task 1 (you
  do not need your Task 1 answer to run this file -- it is fully
  self-contained). You do not need to modify this class.
- The network topology below (three routers, R1 -- R2 -- R3, connecting
  two host subnets), already built into working RoutingTable objects
  for you, plus `ip_owner`, a dict mapping each point-to-point link's
  IP address to the router that owns it -- this is what lets your
  simulator figure out "given a next-hop IP, which router do I go to
  next?".
- The __main__ self-check block at the bottom (do not change it).

WHAT YOU MUST IMPLEMENT
-------------------------
Fill in trace_path() below, following its docstring exactly.

Topology:

    HostA                                                     HostB
  192.168.1.0/24                                           192.168.2.0/24
        |                                                         |
       [R1] ---- 10.0.12.0/30 ---- [R2] ---- 10.0.23.0/30 ---- [R3]
     .1    .2(R1)            (R2).2  .1(R2)             (R3).2  .1

  (R1's interface on the R1-R2 link is 10.0.12.1; R2's is 10.0.12.2.
   R2's interface on the R2-R3 link is 10.0.23.1; R3's is 10.0.23.2.)
"""
import socket
import struct


def ip_to_int(ip_str: str) -> int:
    return struct.unpack("!I", socket.inet_aton(ip_str))[0]


def prefix_to_mask(prefix_length: int) -> int:
    if prefix_length == 0:
        return 0
    return (0xFFFFFFFF << (32 - prefix_length)) & 0xFFFFFFFF


class RoutingTable:
    """PROVIDED, fully working -- same behaviour as a correct Task 1 solution."""
    def __init__(self):
        self.routes = []

    def add_route(self, network, prefix_length, next_hop, label=""):
        mask = prefix_to_mask(prefix_length)
        net_int = ip_to_int(network) & mask
        self.routes.append((net_int, prefix_length, mask, next_hop, label))

    def lookup(self, dest_ip):
        dest_int = ip_to_int(dest_ip)
        best = None
        for net_int, prefix_length, mask, next_hop, label in self.routes:
            if (dest_int & mask) == net_int:
                if best is None or prefix_length > best[0]:
                    best = (prefix_length, next_hop, label)
        if best is None:
            return None
        return {"next_hop": best[1], "label": best[2], "matched_prefix_length": best[0]}


# ---------------------------------------------------------------------
# PROVIDED -- the topology, already built. Do not modify.
# ---------------------------------------------------------------------
R1 = RoutingTable()
R1.add_route("192.168.1.0", 24, "directly connected (R1-eth0)", "direct")
R1.add_route("10.0.12.0", 30, "directly connected (R1-eth1)", "direct")
R1.add_route("0.0.0.0", 0, "10.0.12.2", "default-to-R2")

R2 = RoutingTable()
R2.add_route("10.0.12.0", 30, "directly connected (R2-eth0)", "direct")
R2.add_route("10.0.23.0", 30, "directly connected (R2-eth1)", "direct")
R2.add_route("192.168.1.0", 24, "10.0.12.1", "toward-R1")
R2.add_route("192.168.2.0", 24, "10.0.23.2", "toward-R3")

R3 = RoutingTable()
R3.add_route("192.168.2.0", 24, "directly connected (R3-eth1)", "direct")
R3.add_route("10.0.23.0", 30, "directly connected (R3-eth0)", "direct")
R3.add_route("0.0.0.0", 0, "10.0.23.1", "default-to-R2")

routers = {"R1": R1, "R2": R2, "R3": R3}

# Maps a router's own interface IP to the name of the router that owns it.
# Given a next-hop IP address returned by a lookup(), this tells you which
# router object to consult next.
ip_owner = {
    "10.0.12.1": "R1", "10.0.12.2": "R2",
    "10.0.23.1": "R2", "10.0.23.2": "R3",
}


def trace_path(start_router: str, dest_ip: str, max_hops: int = 10):
    """Simulate a packet addressed to `dest_ip` starting its journey at
    the router named `start_router` (e.g. "R1"), hopping from router to
    router according to each router's OWN routing table, until it is
    delivered, dropped (no route), or exceeds max_hops (treat this as a
    routing loop).

    Return a list of (router_name, description) tuples, ONE PER HOP,
    in the order the packet visited them, where description is a short
    string you construct yourself (see the expected output in the
    self-check below for the exact wording to match).

    Algorithm:
      1. Start with current = start_router, and an empty path list.
      2. Loop (up to max_hops times):
           a. result = routers[current].lookup(dest_ip)
           b. If result is None: append
              (current, "NO ROUTE -- packet dropped") to path and
              return path immediately -- the packet is dropped here.
           c. Otherwise, append
              (current, f"next_hop={result['next_hop']} (matched /{result['matched_prefix_length']})")
              to path.
           d. If result['next_hop'] starts with "directly connected":
              the packet has arrived at its destination subnet -- return
              path immediately (delivered).
           e. Otherwise, result['next_hop'] is the IP address of the
              NEXT router's interface. Look it up in `ip_owner` to find
              that router's name, and set current to it, then continue
              the loop.
      3. If the loop finishes without returning (max_hops exceeded),
         append ("---", "TTL exceeded / loop") to path and return it.
    """
    # TODO: implement this
    raise NotImplementedError


# ---------------------------------------------------------------------
# Self-check -- run this file directly (`python task2_forwarding_simulation.py`)
# ---------------------------------------------------------------------
if __name__ == "__main__":
    path = trace_path("R1", "192.168.2.77")
    for hop in path:
        print(hop)

    # ---- Expected output (self-check) ----
    # ('R1', 'next_hop=10.0.12.2 (matched /0)')
    # ('R2', 'next_hop=10.0.23.2 (matched /24)')
    # ('R3', 'next_hop=directly connected (R3-eth1) (matched /24)')
    assert len(path) == 3, f"Expected a 3-hop path, got {len(path)} entries: {path}"
    assert path[0][0] == "R1" and "10.0.12.2" in path[0][1]
    assert path[1][0] == "R2" and "10.0.23.2" in path[1][1]
    assert path[2][0] == "R3" and "directly connected" in path[2][1]
    print("\nSelf-check PASSED (R1 -> R2 -> R3 -> delivered).")

    # A second trace in the reverse direction, for your own exploration
    # (not checked by an assert -- just look at the output and make sure
    # it makes sense to you given the topology above).
    print("\nReverse direction (HostB -> HostA), starting at R3:")
    for hop in trace_path("R3", "192.168.1.50"):
        print(hop)