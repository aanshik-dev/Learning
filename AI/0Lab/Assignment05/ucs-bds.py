import time
import heapq
import random
from collections import deque
from matplotlib import pyplot as plt
import numpy as np

timeOut = 60
k = 20

def swap(state, i, j):
  state = list(state)
  state[i], state[j] = state[j], state[i]
  return tuple(state)

def getMoves(state, n):
  moves = []
  blank = state.index(0)
  row = blank // n  # 1
  col = blank % n  # 2
  
  if row > 0: moves.append(swap(state, blank, blank-n)) # top
  if row < n-1: moves.append(swap(state, blank, blank + n)) # bottom
  if col > 0: moves.append(swap(state, blank, blank-1)) # left
  if col < n-1: moves.append(swap(state, blank, blank+1)) # left
  return moves

def shuffle(state):
  state = list(state)
  for i in range(k):
    moves = getMoves(state, n)
    state = random.choice(moves)
  return state

# UCS ------------
def ucs(init, n):
  start = time.time()
  pq = []
  heapq.heappush(pq, (0, init))
  vis = {init: 0}

  while pq:
    if time.time() - start > timeOut:
      return "Timeout", timeOut, len(vis), None
    depthRank, state = heapq.heappop(pq)

    if state == goal:
      return "Success", time.time() - start, len(vis), None
    for mov in getMoves(state, n):
      cost = depthRank + 1
      if mov not in vis or cost < vis[mov]:   
        vis[mov] = cost 
        heapq.heappush(pq, (cost, mov))
  return "Failure", time.time() - start, len(vis), None


# BDS ------------
def bds(init, n):
  start =  time.time()
  
  frontq = deque([(init, 0)])
  backq = deque([(goal, 0)])
  frontvis = {init: 0}
  backvis = {goal: 0}
  
  while frontq and backq:
    if time.time() - start > timeOut:
      return "Timeout", timeOut, len(backvis) , None
    
    fnode, fdepth = frontq.popleft()
    for fmov in getMoves(fnode, n):
      if fmov not in frontvis:
        frontvis[fmov] = fdepth + 1
        frontq.append((fmov, fdepth + 1))
        if fmov in backvis:
          depth = fdepth + backvis[fmov] + 1
          return "Success", time.time() - start, len(backvis) + len(frontvis), depth  
        
    bnode, bdepth = backq.popleft()
    for bmov in getMoves(bnode, n):
      if bmov not in backvis:
        backvis[bmov] = bdepth + 1
        backq.append((bmov, bdepth + 1))
        if bmov in frontvis:
          depth = bdepth + frontvis[bmov] + 1
          return "Success", time.time() - start, len(backvis) + len(frontvis), depth        
  return "Failure", time.time() - start, len(backvis) + len(frontvis), None


stats = {
  "ucs" : {
    "time" : [],
    "visNodes": []
  },
  "bds" : {
    "time" : [],
    "visNodes": []
  }
}

n = int(input(f"====== Menu ======\n8 - puzzle: 3 \n15 - puzzle: 4\nEnter the value of n: "))

# Goal State
goal = tuple(list(range(1, n*n)) + [0])

for i in range(10):
  # Initial State
  init = shuffle(goal)

  print(f"\nInitial State {i+1}: {init}")

  #UCS
  print(f" => Running UCS")
  status, sec, nodes, path = ucs(init, n)
  stats["ucs"]["time"].append(sec)
  stats["ucs"]["visNodes"].append(nodes)
  print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")

  #BDS
  print(f" => Running BDS")
  status, sec, nodes, path = bds(init, n)
  stats["bds"]["time"].append(sec)
  stats["bds"]["visNodes"].append(nodes)
  print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")

avgTime = []
avgNodes = []

for algo in stats:
  avgTime.append(np.mean(stats[algo]["time"]))
  avgNodes.append(np.mean(stats[algo]["visNodes"]))

plt.figure()
plt.bar(["UCS", "BDS"], avgTime)
plt.ylabel("Average Time (seconds)")
plt.xlabel("Algorithms")
plt.title(f"Average Execution Time (n={n})")
plt.show()

plt.figure()
plt.bar(["UCS", "BDS"], avgNodes)
plt.ylabel("Average Explored Nodes")
plt.xlabel("Algorithms")
plt.title(f"Average Nodes Explored (n={n})")
plt.show()