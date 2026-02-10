import time
import random
from collections import deque
import matplotlib.pyplot as plt
import numpy as np

timeLim = 60

def swap(state, i, j):
  state = list(state)
  state[i], state[j] = state[j], state[i]
  return tuple(state)

def getMoves(state, n):
  moves = []
  idx = state.index(0)
  r = idx//n
  c = idx%n

  if r > 0: moves.append(swap(state, idx, idx - n))
  if r < n - 1: moves.append(swap(state, idx, idx + n))
  if c > 0: moves.append(swap(state, idx, idx - 1))
  if c < n - 1: moves.append(swap(state, idx, idx + 1))
  return moves


# BFS ---------------
def bfs(init, n):
  start = time.time()
  q = deque([(init, 0)])
  vis = set([init])
  
  while q:
    if time.time() - start > timeLim:
      return "Timeout", timeLim, None
    state, depth = q.popleft()

    if state == goal:
      return "Success", time.time() - start, depth
  
    moves = getMoves(state, n)
    for mov in moves:
        if mov not in vis:
            vis.add(mov)
            q.append((mov, depth + 1))

  return "Failure", time.time() - start, None

# DFS (Tree Search) --------
def dfs(init, n):
    start = time.time()
    stack = [(init, 0)]

    while stack:
      if time.time() - start > timeLim:
        return "Timeout", timeLim, None
      state, depth = stack.pop()

      if state == goal:
        return "Success", time.time() - start, depth
      for mov in getMoves(state, n):
        stack.append((mov, depth + 1))

    return "Failure", time.time() - start, None

# Depth-Limited Search ----
def dls(init, n):
    limit = 20
    start = time.time()
    stack = [(init, 0)]

    while stack:
        if time.time() - start > timeLim:
          return "Timeout", timeLim, None
        state, depth = stack.pop()

        if state == goal:
          return "Success", time.time() - start, depth

        if depth < limit:
          for mov in getMoves(state, n):
            stack.append((mov, depth + 1))

    return "Failure", time.time() - start, None

# Iterative Deepening ------
def iterDeep(init, n):
    start = time.time()

    for limit in range(0, 50):
        stack = [(init, 0)]

        while stack:
          if time.time() - start > timeLim:
              return "Timeout", timeLim, None
          state, depth = stack.pop()
          if state == goal:
              return "Success", time.time() - start, depth

          if depth < limit:
            for mov in getMoves(state, n):
              stack.append((mov, depth + 1))

    return "Failure", time.time() - start, None



n = int(input(f"====== Menu ======\n8 - puzzle: 3 \n15 - puzzle: 4\nEnter the value of n: "))

# Goal State
goal = tuple(list(range(1, n*n)) + [0])

stats = {
  "BFS": {
    "time": [],"success": 0,"path": []
  },
  "DFS": {
    "time": [],"success": 0,"path": []
  },
  "DLS": {
    "time": [],"success": 0,"path": []
  },
  "ID": {
    "time": [],"success": 0,"path": []
  }
}

search = {
  "BFS": bfs,
  "DFS": dfs,
  "DLS": dls,
  "ID": iterDeep
}

for i in range(10):
  # Initial State
  init = list(range(n*n))
  random.shuffle(init)
  init = tuple(init)

  print(f"\nInitial State {i+1}: {init}")

  for algo in search:
    print(f" => Running {algo}")
    status, sec, path = search[algo](init, n)
    stats[algo]["time"].append(sec)
    if status == "Success":
      stats[algo]["path"].append(path)
      stats[algo]["success"] += 1
    print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")

avgTime = {}
successRate = {}
avgPath = {}

for algo in stats:
    avgTime[algo] = np.mean(stats[algo]["time"])
    successRate[algo] = (stats[algo]["success"] / 10) * 100
    if stats[algo]["path"]:
        avgPath[algo] = np.mean(stats[algo]["path"])
    else:
        avgPath[algo] = 0


algos = list(avgTime.keys())
times = list(avgTime.values())
rates = list(successRate.values())
paths = list(avgPath.values())

plt.figure()
plt.bar(algos, times)
plt.ylabel("Average Time (seconds)")
plt.title(f"Average Execution Time (n={n})")
plt.show()

plt.figure()
plt.bar(algos, rates)
plt.ylabel("Success Rate (%)")
plt.ylim(0, 100)
plt.title(f"Success Rate (n={n})")
plt.show()

plt.figure()
plt.bar(algos, paths)
plt.ylabel("Average Path Length")
plt.title(f"Average Solution Length (n={n})")
plt.show()
