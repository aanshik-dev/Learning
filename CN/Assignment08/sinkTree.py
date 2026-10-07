# Topology edges: (u, v, cost)
edges = [
    ("A", "B", 2),
    ("A", "C", 5),
    ("B", "C", 1),
    ("B", "D", 4),
    ("C", "E", 3),
    ("D", "E", 1),
    ("D", "F", 2),
    ("E", "F", 6)
]

nodes = sorted(list({u for u, v, _ in edges} | {v for u, v, _ in edges}))


def build_graph(edge_list):
    g = {n: {} for n in nodes}
    for u, v, w in edge_list:
        g[u][v] = w
        g[v][u] = w
    return g


def dijkstra(g, sink):
    dist = {n: float("inf") for n in nodes}
    parent = {n: None for n in nodes}
    dist[sink] = 0
    unvisited = set(nodes)

    while unvisited:
        u = min(unvisited, key=lambda n: (dist[n], n))
        unvisited.remove(u)

        for v, cost in g[u].items():
            if v in unvisited:
                new_cost = dist[u] + cost
                if new_cost < dist[v]:
                    dist[v] = new_cost
                    parent[v] = u
                elif new_cost == dist[v]:
                    if parent[v] is None or u < parent[v]:
                        parent[v] = u

    return dist, parent


def get_sink_tree(parent, sink):
    return [(n, parent[n]) for n in nodes if n != sink]


def verify_tree(nodes, tree_edges, sink):
    # N - 1 edges
    n = len(nodes)
    if len(tree_edges) != n - 1:
        return False, "Edge count is not N - 1"

    # Check cycles and reachability to sink
    parent_map = dict(tree_edges)
    visited_all = set()

    for node in nodes:
        if node == sink:
            visited_all.add(node)
            continue
        curr = node
        seen = set()
        while curr != sink:
            if curr in seen or curr not in parent_map:
                return False, f"Cycle or disconnection detected at node {curr}"
            seen.add(curr)
            curr = parent_map[curr]
        visited_all.add(node)

    if len(visited_all) != n:
        return False, "Not all routers reach the sink"

    return True, "Valid spanning tree (N-1 edges, connected, acyclic)"


def printTable(label, g, sink):
    dist, parent = dijkstra(g, sink)
    tree_edges = get_sink_tree(parent, sink)

    print(f"\n{label} (Sink = {sink}):")

    # Costs
    cost_str = ", ".join(f"{n} = {dist[n]}" for n in nodes)
    print(f"  Cost to {sink}: {cost_str}")

    # Next hops
    next_hops = [f"{n} to {parent[n]}" for n in nodes if n != sink]
    print(f"  Next hop toward {sink}: {', '.join(next_hops)}")

    # Sink-tree edges
    edges_str = ", ".join(f"({u}, {v})" for u, v in tree_edges)
    print(f"  Sink-tree edges (node, parent): {edges_str}")

    # Forwarding table
    print(f"  Forwarding Table for Sink {sink}:")
    print("    Router | Next Hop | Total Cost")
    print("    -------+----------+-----------")
    for n in nodes:
        nh = parent[n] if n != sink else "-"
        print(f"      {n}    |    {nh}     |    {dist[n]}")

    return dist, parent, tree_edges


# Part A: Represent topology
graph = build_graph(edges)
print("Part A: Network Topology Adjacency List")
for u in nodes:
    nbrs = ", ".join(f"{v}:{graph[u][v]}" for v in sorted(graph[u]))
    print(f"  Router {u} -> {nbrs}")

# Part B & C: Vectors 1 and 2
dist1, parent1, tree1 = printTable("Vector 1", graph, "F")
dist2, parent2, tree2 = printTable("Vector 2", graph, "A")

# Part D: Modified topology (D-F cost 2 -> 9)
edges_mod = [
    ("A", "B", 2),
    ("A", "C", 5),
    ("B", "C", 1),
    ("B", "D", 4),
    ("C", "E", 3),
    ("D", "E", 1),
    ("D", "F", 9),
    ("E", "F", 6)
]
graph_mod = build_graph(edges_mod)
dist3, parent3, tree3 = printTable("Vector 3 (Modified link D-F = 9)", graph_mod, "F")

# Part D: Spanning tree verification
print("\nPart D: Spanning Tree Verifications")
v1_ok, v1_msg = verify_tree(nodes, tree1, "F")
print(f"  Vector 1 Tree: {v1_msg}")
v3_ok, v3_msg = verify_tree(nodes, tree3, "F")
print(f"  Vector 3 Tree: {v3_msg}")

# Part D: Changed edges
print("\nPart D: Edge Changes (Vector 1 -> Vector 3)")
set1 = set(tree1)
set3 = set(tree3)
removed = sorted(list(set1 - set3))
added = sorted(list(set3 - set1))
for r, a in zip(removed, added):
    print(f"  Edge changed for node {r[0]}: was ({r[0]}, {r[1]}) -> now ({a[0]}, {a[1]})")

