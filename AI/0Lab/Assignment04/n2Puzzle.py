import random
import time
from collections import deque

def bfs(init, n, goal):
  start = time.time()
  q = deque([init])


  if(init == goal):
    return "Success", 




n = int(input(f"====== Menu ======\n8 - puzzle: 3 \n15 - puzzle: 4\nEnter the value of n: "))

# Goal State
goal = tuple(list(range(1, n*n)) + [0])

for i in range(10):
  # Initial State
  init = list(range(n*n))
  random.shuffle(init)
  init = tuple(init)

  print(f"\nInitial State {i+1}: {init}")

  #bfs
  print(f" => Running BFS")
  status, sec, path = bfs(init, n)
  print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")

  print(f" => Running DFS")
  # status, sec, path = dfs(init, n)
  print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")

  print(f" => Running DLS")
  # status, sec, path = dls(init, n)
  print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")

  print(f" => Running ID")
  # status, sec, path = iterDeep(init, n)
  print(f"    -> {status}, Time: {sec:.2f}s, Path Length: {path}")

  
