# BGP simulator with local preference, AS-path, and lowest next-hop tie-break


def best_route(as_num, advertised_routes, localpref):
    # Select best route among candidate routes from neighbors
    candidates = []
    for neighbor, route in advertised_routes.items():
        if route is None:
            continue
        advertised_path, _ = route
        candidate_path = (neighbor,) + advertised_path
        # Loop prevention: reject route if deciding AS is already in candidate AS-path
        if as_num in candidate_path:
            continue
        pref = localpref.get(as_num, {}).get(neighbor, 100)
        candidates.append((pref, len(candidate_path), neighbor, candidate_path))

    if not candidates:
        return None

    # Decision rule: highest localpref, shortest AS-path, lowest next-hop AS
    candidates.sort(key=lambda c: (-c[0], c[1], c[2]))
    best = candidates[0]
    return (best[3], best[2])


def run_bgp(peerings, origin, localpref):
    # Run synchronous rounds of BGP until convergence
    routes = {node: None for node in peerings}
    routes[origin] = ((), None)

    while True:
        changed = False
        new_routes = dict(routes)
        for node in peerings:
            if node == origin:
                continue
            advertised = {peer: routes[peer] for peer in peerings[node]}
            best = best_route(node, advertised, localpref)
            if best != routes[node]:
                new_routes[node] = best
                changed = True
        routes = new_routes
        if not changed:
            break

    return routes


def format_path(as_path):
    # Format tuple of AS numbers as comma-separated string
    if not as_path:
        return ""
    return ", ".join(f"AS{n}" for n in as_path)


def print_results(scenario_name, routes, origin):
    # Print converged routes for all nodes except origin
    print(scenario_name)
    print(f"{'AS':<6} {'AS-path':<20} {'Next hop':<10}")
    for node in sorted(routes.keys()):
        if node == origin:
            continue
        route = routes[node]
        if route is not None:
            path_str = format_path(route[0])
            next_hop_str = f"AS{route[1]}" if route[1] is not None else "-"
            print(f"AS{node:<4} {path_str:<20} {next_hop_str:<10}")
        else:
            print(f"AS{node:<4} {'None':<20} {'None':<10}")
    print()


def main():
    # Define peerings graph
    peerings = {
        1: [2, 3],
        2: [1, 3, 4],
        3: [1, 2, 5],
        4: [2, 5, 6],
        5: [3, 4, 6],
        6: [4, 5],
    }
    origin = 1

    # Part A: print topology and peerings
    print("Part A: Topology and Peerings")
    for node in sorted(peerings.keys()):
        peers_str = ", ".join(f"AS{p}" for p in peerings[node])
        print(f"AS{node} peers with: {peers_str}")
    print()

    # Part B: unit check on AS6 under Scenario 1
    as6_advertised = {
        4: ((2, 1), 2),
        5: ((3, 1), 3),
    }
    as6_best = best_route(6, as6_advertised, {})
    print("Part B: AS6 Decision Check (Scenario 1 tie-break)")
    print(f"AS6 best route: path={format_path(as6_best[0])}, next_hop=AS{as6_best[1]}")
    print()

    # Part C: Scenario 1 (Default local preference 100)
    routes_s1 = run_bgp(peerings, origin, {})
    print_results("Scenario 1: Default Policy (all localpref = 100)", routes_s1, origin)

    # Part D: Scenario 2 (AS6 prefers routes from AS5 with localpref 200)
    pref_s2 = {6: {5: 200}}
    routes_s2 = run_bgp(peerings, origin, pref_s2)
    print_results("Scenario 2: AS6 sets localpref 200 on routes from AS5", routes_s2, origin)

    # Part D: Scenario 3 (AS5 de-prefers routes from AS3 with localpref 50)
    pref_s3 = {5: {3: 50}}
    routes_s3 = run_bgp(peerings, origin, pref_s3)
    print_results("Scenario 3: AS5 sets localpref 50 on routes from AS3", routes_s3, origin)


if __name__ == "__main__":
    main()

