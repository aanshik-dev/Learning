import matplotlib.pyplot as plt
import numpy as np
import time
import heapq
import random

k = 20
timeout = 60

def swap(state, i, j):
  state = list(state)
  state[i], state[j] = state[j] , state[i]
  return tuple(state)


def getMoves(state, n):
  moves = []
  blank = state.index(0)
  row = blank // n
  col = blank % n
  
  if row > 0: moves.append(swap(state, blank, blank-n))
  if row < n-1: moves.append(swap(state, blank, blank+n))
  if col > 0: moves.append(swap(state, blank, blank-1))
  if col < n-1: moves.append(swap(state, blank, blank+1))
  return moves


def shuffle(state, n):
  state = list(state)
  for i in range(k):
    state = random.choice(getMoves(state, n))
  return state

# h1 (Misplaced Tiles): The number of tiles not in their goal position.
def misTiles(state, n):
  mis = 0 
  for i in range(n*n):
    if state[i] != 0 and state[i] != i+1: mis += 1
  return mis

# h2 (Manhattan Distance): The sum of the vertical and horizontal distances of tiles from their goal positions.
def manHattan(state, n):
  dis = 0
  for i in range(n*n):
    if state[i] != 0:
      dis += abs((state[i]-1)//n - i//n) + abs((state[i]-1)%n - i%n)
  return dis

# h3 (Custom Heuristic): A custom heuristic of your design. It must be admissible.
def customHur(state, n):
  return max(misTiles(state, n), manHattan(state, n))


def Astar(init, n, heuristic):
  start = time.time()
  pq = []
  heapq.heappush(pq, (heuristic(init, n), 0, init))
  vis = {init: 0}

  while pq:
    if time.time() - start > timeout:
      return "Timeout", timeout, len(vis)
    f, g, node = heapq.heappop(pq)

    if node == goal: return "Success", time.time() - start, len(vis)
    for mov in getMoves(node, n):
      newCost = g + 1
      if mov not in vis or newCost < vis[mov]:
        vis[mov] = newCost
        heapq.heappush(pq,(newCost + heuristic(mov, n), newCost, mov))
  return "Failure", time.time() - start, len(vis)


def greedyBFS(init, n, heuristic):
  start = time.time()
  pq = []
  heapq.heappush(pq, (heuristic(init, n), init))
  vis = set([init])

  while pq:
    if time.time() - start > timeout:
      return "Timeout", timeout, len(vis)
    h, node = heapq.heappop(pq)

    if node == goal: return "Success", time.time() - start, len(vis)
    for mov in getMoves(node, n):
      if mov not in vis:
        vis.add(mov)
        heapq.heappush(pq, (heuristic(mov, n), mov))
  return "Failure", time.time() - start, len(vis)



heuristics = {
  "Misplaced": misTiles,
  "Manhattan": manHattan,
  "Custom": customHur
}

astar_time = {h: [] for h in heuristics}
astar_nodes = {h: [] for h in heuristics}
greedy_time = {h: [] for h in heuristics}
greedy_nodes = {h: [] for h in heuristics}

n = int(input(f"====== Menu ======\n8 - puzzle: 3 \n15 - puzzle: 4\nEnter the value of n: "))

goal = tuple(list(range(1,n*n)) + [0])

for i in range(10):
  init = shuffle(goal,n)
  print(f"\nInitial State {i+1}: {init}")

  # AStar ---------------
  print(" => Running A*...")
  for hname, hfunc in heuristics.items():
    status, sec, nodes = Astar(init, n, hfunc)
    astar_time[hname].append(sec)
    astar_nodes[hname].append(nodes)
    print(f"  -> {hname} : {status}, Time: {sec:.2f}s, nodes Explored: {nodes}")
  
  # Greedy Best FS ---------------
  print(" => Running Greedy BFS...")
  for hname, hfunc in heuristics.items():
    status, sec, nodes = greedyBFS(init, n, hfunc)
    greedy_time[hname].append(sec)
    greedy_nodes[hname].append(nodes)
    print(f"  -> {hname} : {status}, Time: {sec:.2f}s, nodes Explored: {nodes}")

print("")

labels = list(heuristics.keys())

astar_avg_time = np.array([np.mean(astar_time[h]) for h in heuristics])
greedy_avg_time = np.array([np.mean(greedy_time[h]) for h in heuristics])

astar_avg_nodes = np.array([np.mean(astar_nodes[h]) for h in heuristics])
greedy_avg_nodes = np.array([np.mean(greedy_nodes[h]) for h in heuristics])


x = range(len(labels))

# Execution Time Plot
plt.figure()
plt.bar(x, astar_avg_time, width=0.4, label="A*", align='center')
plt.bar([i+0.4 for i in x], greedy_avg_time, width=0.4, label="Greedy", align='center')
plt.xticks([i+0.2 for i in x], labels)
plt.ylabel("Average Time (seconds)")
plt.title(f"Average Execution Time (n={n})")
plt.legend()
plt.show()

# Nodes Expanded Plot
plt.figure()
plt.bar(x, astar_avg_nodes, width=0.4, label="A*", align='center')
plt.bar([i+0.4 for i in x], greedy_avg_nodes, width=0.4, label="Greedy", align='center')
plt.xticks([i+0.2 for i in x], labels)
plt.ylabel("Average Nodes Expanded")
plt.title(f"Nodes Expanded (n={n})")
plt.legend()
plt.show()




