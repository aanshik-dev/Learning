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
  if row < n-1: moves.append(swap(state, blank, blank+1))
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


def Astar(init, n):
  start = time.time()
  pq = []
  heapq.heappush(pq, (misTiles(init), 0, init))
  vis = {init: 0}

  while pq:
    if time.time() - start > timeout:
      return "Timeout",timeout, len(vis)
    f, cost, node = heapq.heappop(pq)

    if node == goal: return "Success", time.time() - start, len(vis)
    for mov in getMoves(node, n):
      newCost = cost + 1
      if mov not in vis or newCost < vis[mov]:
        vis[mov] = newCost
        newF =  newCost + misTiles(mov)
        heapq.heappush(pq, (newF, newCost, mov))
  return "Failure", time.time() - start, len(vis)


def greedBest(init, n):
  start = time.time()
  pq = []
  heapq.heappush(pq, (misTiles(init),0, init))
  vis = {init: 0}

  while pq:
    if time.time() - start > timeout:
      return "Timeout",timeout, len(vis)
    hur, cost, node = heapq.heappop(pq)

    if node == goal: return "Success", start - time.time(), len(vis)
    for mov in getMoves(node, n):
      newCost = cost + 1
      if mov not in vis or newCost < vis[mov]:
        vis[mov] = newCost
        newF =  newCost + misTiles(mov)
        heapq.heappush(pq, (misTiles(mov), newCost, mov))
  return "Failure", start-time.time(), len(vis)





n = int(input(f"====== Menu ======\n8 - puzzle: 3 \n15 - puzzle: 4\nEnter the value of n: "))

goal = tuple(list(range(1,n*n)) + [0])

for i in range(10):
  init = shuffle(goal,n)
  print(init)
  # AStar
  print("Running A*...")
  time, nodes = Astar()
