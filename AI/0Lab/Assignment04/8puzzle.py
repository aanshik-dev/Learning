import time
import random
from collections import deque
import matplotlib

timeLim = 120

def swap(state, i, j):
  state = list(state)
  state[i], state[j] = state[j], state[i]
  return tuple(state)

def getMoves(state, n):
  moves = []
  idx = state.index(0)
  r, c = idx//n, idx%n

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
    for nxt in moves:
        if nxt not in vis:
            vis.add(nxt)
            q.append((nxt, depth + 1))

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
      for nxt in getMoves(state, n):
        stack.append((nxt, depth + 1))

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
          for nxt in getMoves(state, n):
            stack.append((nxt, depth + 1))

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
            for nxt in getMoves(state, n):
              stack.append((nxt, depth + 1))

    return "Failure", time.time() - start, None



n = int(input(f"====== Menu ======\n8 - puzzle: 3 \n15 - puzzle: 4\nEnter the value of n: "))

# Goal State
goal = tuple(list(range(1, n*n)) + [0])
Stats = []

for i in range(10):
  # Initial State
  init = list(range(n*n))
  random.shuffle(init)
  init = tuple(init)

  print(f"\nInitial State {i+1}: {init}")

  #BFS
  print(f" => Running BFS")
  status, sec, path = bfs(init, n)
  print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")
  
  #DFS
  print(f" => Running DFS")
  status, sec, path = dfs(init, n)
  print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")

  #DLS
  print(f" => Running DLS")
  status, sec, path = dls(init, n)
  print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")

  #ID
  print(f" => Running ID")
  status, sec, path = iterDeep(init, n)
  print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")


  