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

  # BFS
  print(f"    Running BFS...")
  status, t, path = bfs(init, n, goal)
  print(f"    → {status}, Time: {t:.2f}s, Path Length: {path}")


print(f"Start state: {start}")
print(f"Goal state: {goal}")