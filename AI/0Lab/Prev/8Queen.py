# 8Queen
import matplotlib.pyplot as plt
import numpy as np
import time
import heapq
import random

n = 8
timeout = 60

# Generate random board
def randomBoard(n):
    return tuple(random.randint(0, n-1) for _ in range(n))


# Count attacking queen pairs
def attackingPairs(state):
    attacks = 0
    for i in range(n):
        for j in range(i+1, n):
            if state[i] == state[j] or abs(state[i]-state[j]) == abs(i-j):
                attacks += 1
    return attacks


# Heuristic 1
def h1(state):
    return attackingPairs(state)


# Heuristic 2 (weighted diagonal conflicts)
def h2(state):
    attacks = 0
    for i in range(n):
        for j in range(i+1, n):
            if state[i] == state[j]:
                attacks += 2
            elif abs(state[i]-state[j]) == abs(i-j):
                attacks += 1
    return attacks


# Custom heuristic
def customHur(state):
    return max(h1(state), h2(state))


# Generate neighbor states
def getMoves(state):
    moves = []
    for col in range(n):
        for row in range(n):
            if row != state[col]:
                new = list(state)
                new[col] = row
                moves.append(tuple(new))
    return moves


# A* Search
def Astar(init, heuristic):
    start = time.time()
    pq = []
    heapq.heappush(pq, (heuristic(init), 0, init))
    vis = {init:0}

    while pq:
        if time.time() - start > timeout:
            return "Timeout", timeout, len(vis)
        f, g, node = heapq.heappop(pq)
        if heuristic(node) == 0:
            return "Success", time.time() - start, len(vis)
        for mov in getMoves(node):
            newCost = g + 1
            if mov not in vis or newCost < vis[mov]:
                vis[mov] = newCost
                heapq.heappush(pq,(newCost + heuristic(mov), newCost, mov))
    return "Failure", time.time() - start, len(vis)



# Greedy Best First Search
def greedyBFS(init, heuristic):
    start = time.time()
    pq = []
    heapq.heappush(pq,(heuristic(init),init))
    vis = set([init])

    while pq:
        if time.time() - start > timeout:
            return "Timeout", timeout, len(vis)
        h, node = heapq.heappop(pq)
        if heuristic(node) == 0:
            return "Success", time.time() - start, len(vis)
        for mov in getMoves(node):
            if mov not in vis:
                vis.add(mov)
                heapq.heappush(pq,(heuristic(mov),mov))
    return "Failure", time.time() - start, len(vis)



heuristics = {
    "AttackingPairs": h1,
    "Weighted": h2,
    "Custom": customHur
}


astar_time = {h: [] for h in heuristics}
astar_nodes = {h: [] for h in heuristics}

greedy_time = {h: [] for h in heuristics}
greedy_nodes = {h: [] for h in heuristics}


for i in range(10):

    init = randomBoard(n)
    print(f"\nInitial Board {i+1}: {init}")

    print(" => Running A*...")
    for hname, hfunc in heuristics.items():

        status, sec, nodes = Astar(init, hfunc)

        astar_time[hname].append(sec)
        astar_nodes[hname].append(nodes)

        print(f"  -> {hname} : {status}, Time: {sec:.2f}s, Nodes: {nodes}")


    print(" => Running Greedy BFS...")
    for hname, hfunc in heuristics.items():

        status, sec, nodes = greedyBFS(init, hfunc)

        greedy_time[hname].append(sec)
        greedy_nodes[hname].append(nodes)

        print(f"  -> {hname} : {status}, Time: {sec:.2f}s, Nodes: {nodes}")



labels = list(heuristics.keys())

astar_avg_time = np.array([np.mean(astar_time[h]) for h in heuristics])
greedy_avg_time = np.array([np.mean(greedy_time[h]) for h in heuristics])

astar_avg_nodes = np.array([np.mean(astar_nodes[h]) for h in heuristics])
greedy_avg_nodes = np.array([np.mean(greedy_nodes[h]) for h in heuristics])


x = range(len(labels))


# Time Plot
plt.figure()

plt.bar(x, astar_avg_time, width=0.4, label="A*", align='center')
plt.bar([i+0.4 for i in x], greedy_avg_time, width=0.4, label="Greedy", align='center')

plt.xticks([i+0.2 for i in x], labels)

plt.ylabel("Average Time (seconds)")
plt.title("8 Queens Execution Time")

plt.legend()
plt.show()


# Nodes Plot
plt.figure()

plt.bar(x, astar_avg_nodes, width=0.4, label="A*", align='center')
plt.bar([i+0.4 for i in x], greedy_avg_nodes, width=0.4, label="Greedy", align='center')

plt.xticks([i+0.2 for i in x], labels)

plt.ylabel("Average Nodes Expanded")
plt.title("8 Queens Nodes Expanded")

plt.legend()
plt.show()