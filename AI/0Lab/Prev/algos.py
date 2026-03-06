import time
import heapq
from collections import deque

# BFS ---------------
def bfs(init, n):
  q = deque([(init, 0)])
  vis = set([init])
  while q:
    state, depth = q.popleft()
    if state == goal:
      return "Success", depth
    for mov in getMoves(state, n):
        if mov not in vis:
            vis.add(mov)
            q.append((mov, depth + 1))
  return "Failure", None

# DFS (Tree Search) --------
def dfs(init, n):
    stack = [(init, 0)]
    vis = set([init])
    while stack:
      state, depth = stack.pop()
      if state == goal:
        return "Success", depth
      for mov in getMoves(state, n):
        if mov not in vis:
          vis.add(mov)
          stack.append((mov, depth + 1))
    return "Failure", None

# Depth-Limited Search ----
def dls(init, n):
    limit = 20
    stack = [(init, 0)]
    while stack:
        state, depth = stack.pop()
        if state == goal:
          return "Success", depth
        if depth < limit:
          for mov in getMoves(state, n):
            stack.append((mov, depth + 1))
    return "Failure", None

# Iterative Deepening ------
def iterDeep(init, n):
    for limit in range(0, 50):
        stack = [(init, 0)]
        while stack:
          state, depth = stack.pop()
          if state == goal:
              return "Success", depth
          if depth < limit:
            for mov in getMoves(state, n):
              stack.append((mov, depth + 1))
    return "Failure", None

# UCS ------------
def ucs(init, n):
  pq = []
  heapq.heappush(pq, (0, init))
  vis = {init: 0}
  while pq:
    depthRank, state = heapq.heappop(pq)
    if state == goal:
      return "Success", None
    for mov in getMoves(state, n):
      cost = depthRank + 1
      if mov not in vis or cost < vis[mov]:   
        vis[mov] = cost 
        heapq.heappush(pq, (cost, mov))
  return "Failure", None


# BDS ------------
def bds(init, n):
  frontq = deque([(init, 0)])
  backq = deque([(goal, 0)])
  frontvis = {init: 0}
  backvis = {goal: 0}
  
  while frontq and backq:
    fnode, fdepth = frontq.popleft()
    for fmov in getMoves(fnode, n):
      if fmov not in frontvis:
        frontvis[fmov] = fdepth + 1
        frontq.append((fmov, fdepth + 1))
        if fmov in backvis:
          depth = fdepth + backvis[fmov] + 1
          return "Success", len(backvis) + len(frontvis), depth  
        
    bnode, bdepth = backq.popleft()
    for bmov in getMoves(bnode, n):
      if bmov not in backvis:
        backvis[bmov] = bdepth + 1
        backq.append((bmov, bdepth + 1))
        if bmov in frontvis:
          depth = bdepth + frontvis[bmov] + 1
          return "Success", len(backvis) + len(frontvis), depth        
  return "Failure", len(backvis) + len(frontvis), None


def Astar(init, n, heuristic):
  start = time.time()
  pq = []
  heapq.heappush(pq, (heuristic(init, n), 0, init))
  vis = {init: 0}

  while pq:
    f, g, node = heapq.heappop(pq)
    if node == goal: return "Success", len(vis)
    for mov in getMoves(node, n):
      newCost = g + 1
      if mov not in vis or newCost < vis[mov]:
        vis[mov] = newCost
        heapq.heappush(pq,(newCost + heuristic(mov, n), newCost, mov))
  return "Failure", len(vis)

def greedyBFS(init, n, heuristic):
  start = time.time()
  pq = []
  heapq.heappush(pq, (heuristic(init, n), init))
  vis = set([init])

  while pq:
    h, node = heapq.heappop(pq)
    if node == goal: return "Success", len(vis)
    for mov in getMoves(node, n):
      if mov not in vis:
        vis.add(mov)
        heapq.heappush(pq, (heuristic(mov, n), mov))
  return "Failure", len(vis)

