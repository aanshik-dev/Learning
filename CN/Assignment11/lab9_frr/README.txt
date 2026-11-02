Lab 9 - BGP on real routers (FRRouting containers)

Topology:
  r1 (AS65001) --10.0.12.0/24-- r2 (AS65002) --10.0.23.0/24-- r3 (AS65003)
  r1 originates 203.0.113.0/24.

Bring it up:
  docker compose up -d

Check the route r3 learned (expect AS_PATH 65002 65001):
  docker exec -it r3 vtysh -c "show ip bgp 203.0.113.0/24"

Capture the BGP session on the r2-r3 link, then open in Wireshark:
  docker exec r2 tcpdump -i eth1 -w /tmp/bgp.pcap tcp port 179
  (or run tcpdump on the host bridge for n23)

Policy experiment:
  On r3, de-prefer the route (set local-preference) or on r2 prepend its AS,
  then re-check "show ip bgp" and capture the new UPDATE.

Tear down:
  docker compose down
