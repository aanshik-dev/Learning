"""
Lab Task 1 -- Routing Table: Longest Prefix Match (LPM) Lookup
===================================================================
Computer Networks Lab | Network Layer -- IP Routing Tables and Routing Decisions

A router's routing table is a list of entries, each an (network, prefix
length, next hop) triple. When a packet arrives, the router compares
the packet's destination address against EVERY entry, finds every entry
whose network/prefix the address falls inside, and forwards according
to whichever MATCHING entry has the longest (most specific) prefix --
this is the Longest Prefix Match (LPM) rule.

WHAT IS ALREADY DONE FOR YOU
-----------------------------
- ip_to_int / int_to_ip : convert between "a.b.c.d" strings and the
  32-bit unsigned integer representation (uses struct + socket).
- The __main__ self-check block at the bottom (do not change it).

WHAT YOU MUST IMPLEMENT
-------------------------
Fill in the three pieces marked # TODO: the prefix_to_mask() helper,
and the add_route() / lookup() methods of RoutingTable. Do not change
any method signatures.
"""
import socket
import struct


def ip_to_int(ip_str: str) -> int:
    return struct.unpack("!I", socket.inet_aton(ip_str))[0]


def int_to_ip(ip_int: int) -> str:
    return socket.inet_ntoa(struct.pack("!I", ip_int))


def prefix_to_mask(prefix_length: int) -> int:
    """Return the 32-bit subnet mask (as an int) corresponding to a given
    CIDR prefix length. E.g. prefix_to_mask(24) should equal the integer
    value of 255.255.255.0, and prefix_to_mask(0) should equal 0
    (matches everything -- this is what a default route uses).

    Hint: a /n mask has its top n bits set to 1 and the remaining
    (32 - n) bits set to 0. Building it with a left shift
    (0xFFFFFFFF << (32 - n)) works for every case EXCEPT n = 0, which
    you should special-case (shifting left by 32 is undefined/wrong in
    this context) and simply return 0 for.
    """
    # TODO: implement this
    raise NotImplementedError


class RoutingTable:
    def __init__(self):
        self.routes = []  # you decide what to store per route; a tuple works well

    def add_route(self, network: str, prefix_length: int, next_hop: str, label: str = ""):
        """Add one routing table entry. `network` is a dotted-decimal
        string (e.g. "172.20.4.0"), `prefix_length` is the CIDR prefix
        (0-32), `next_hop` is either an IP address string or the literal
        string "directly connected (...)", and `label` is just a free-
        text name you can use later for printing/debugging.

        Store whatever you need in self.routes so that lookup() (below)
        can use it. A convenient choice: append a tuple
        (network_int_masked, prefix_length, mask_int, next_hop, label),
        where network_int_masked = ip_to_int(network) & prefix_to_mask(prefix_length)
        (masking the stored network address protects you from a caller
        passing a network string that doesn't already have its host
        bits zeroed).
        """
        # TODO: implement this
        raise NotImplementedError

    def lookup(self, dest_ip: str):
        """Return the forwarding decision for `dest_ip` using Longest
        Prefix Match, or None if NO entry matches at all (meaning: no
        route, including no default route).

        Steps:
          1. Convert dest_ip to its 32-bit integer form.
          2. For every stored route, check whether
             (dest_int & that route's mask) == that route's stored
             (masked) network -- if so, it's a match.
          3. Among ALL matching routes, keep the one with the LARGEST
             prefix_length (ties should not occur in this lab's test
             data, so you don't need to worry about breaking them).
          4. If you found a best match, return a dict:
                 {"next_hop": <next_hop str>,
                  "label": <label str>,
                  "matched_prefix_length": <int>}
             If nothing matched at all, return None.
        """
        # TODO: implement this
        raise NotImplementedError


# ---------------------------------------------------------------------
# Self-check -- run this file directly (`python task1_routing_table.py`)
# This uses the EXACT same routing table as Numerical Exercise N1, so
# you can cross-check your hand-worked answers against your code here.
# ---------------------------------------------------------------------
if __name__ == "__main__":
    rt = RoutingTable()
    rt.add_route("0.0.0.0", 0, "198.51.100.1", "default")
    rt.add_route("172.20.0.0", 16, "10.10.10.2", "R-A")
    rt.add_route("172.20.4.0", 22, "10.10.10.3", "R-B")
    rt.add_route("172.20.4.128", 25, "10.10.10.4", "R-C")
    rt.add_route("192.0.2.0", 24, "directly connected (eth1)", "direct")

    tests = ["172.20.4.200", "172.20.4.5", "172.20.9.9", "192.0.2.77", "203.0.113.50"]
    for dest in tests:
        print(dest, "->", rt.lookup(dest))

    # ---- Expected output (self-check / matches Numerical Exercise N1) ----
    # 172.20.4.200 -> {'next_hop': '10.10.10.4', 'label': 'R-C', 'matched_prefix_length': 25}
    # 172.20.4.5   -> {'next_hop': '10.10.10.3', 'label': 'R-B', 'matched_prefix_length': 22}
    # 172.20.9.9   -> {'next_hop': '10.10.10.2', 'label': 'R-A', 'matched_prefix_length': 16}
    # 192.0.2.77   -> {'next_hop': 'directly connected (eth1)', 'label': 'direct', 'matched_prefix_length': 24}
    # 203.0.113.50 -> {'next_hop': '198.51.100.1', 'label': 'default', 'matched_prefix_length': 0}

    expected = [
        ("10.10.10.4", 25), ("10.10.10.3", 22), ("10.10.10.2", 16),
        ("directly connected (eth1)", 24), ("198.51.100.1", 0),
    ]
    for dest, (exp_nh, exp_pl) in zip(tests, expected):
        result = rt.lookup(dest)
        assert result is not None, f"{dest}: expected a match but got None"
        assert result["next_hop"] == exp_nh, f"{dest}: expected next_hop {exp_nh}, got {result['next_hop']}"
        assert result["matched_prefix_length"] == exp_pl, f"{dest}: expected prefix /{exp_pl}, got /{result['matched_prefix_length']}"

    # A destination with no match at all (table has no default route this time)
    rt_no_default = RoutingTable()
    rt_no_default.add_route("172.20.0.0", 16, "10.10.10.2", "R-A")
    assert rt_no_default.lookup("8.8.8.8") is None, "Expected no route (None) when nothing matches and there's no default"

    print("\nSelf-check PASSED.")