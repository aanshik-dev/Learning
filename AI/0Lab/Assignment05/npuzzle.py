import time
import heapq
import random
from collections import deque

timeOut = 60

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


# UCS ------------
def ucs(init, n):
  start = time.time()
  pq = []
  heapq.heappush(pq, (0, init))
  vis = {init: 0}

  while pq:
    if time.time() - start > timeOut:
      return "Timeout", timeOut, None
    depthRank, state = heapq.heappop(pq)

    if state == goal:
      return "Success", time.time() - start, depthRank
    for mov in getMoves(state, n):
      cost = depthRank + 1
      if mov not in vis or cost < vis[mov]:   
        vis[mov] = cost 
        heapq.heappush(pq, (cost, mov))
  return "Failure", time.time() - start, None


# BDS ------------
def bds(init, n):
  start =  time.time()
  
  frontq = deque([(init, 0)])
  backq = deque([(goal, 0)])
  frontvis = {init: 0}
  backvis = {goal: 0}
  
  while frontq and backq:
    if time.time() - start > timeOut:
      return "Timeout", timeOut, None
    
    fnode, fdepth = frontq.popleft()
    for fmov in getMoves(fnode, n):
      if fmov not in frontvis:
        frontvis[fmov] = fdepth + 1
        frontq.append((fmov, fdepth + 1))
        if fmov in backvis:
          depth = fdepth + backvis[fmov] + 1
          return "Success", time.time() - start, depth  
        
    bnode, bdepth = backq.popleft()
    for bmov in getMoves(bnode, n):
      if bmov not in backvis:
        backvis[bmov] = bdepth + 1
        backq.append((bmov, bdepth + 1))
        if bmov in frontvis:
          depth = bdepth + frontvis[bmov] + 1
          return "Success", time.time() - start, depth        
  return "Failure", time.time() - start, None



n = int(input(f"====== Menu ======\n8 - puzzle: 3 \n15 - puzzle: 4\nEnter the value of n: "))

# Goal State
goal = tuple(list(range(1, n*n)) + [0])

for i in range(10):
  # Initial State
  init = list(range(n*n))
  random.shuffle(init)
  init = tuple(init)

  print(f"\nInitial State {i+1}: {init}")

  #UCS
  print(f" => Running BFS")
  status, sec, path = ucs(init, n)
  print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")

  #BS
  print(f" => Running DFS")
  status, sec, path = bds(init, n)
  print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")