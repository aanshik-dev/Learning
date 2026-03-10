import numpy as np
import random

# Number of cities
n = int(input("Enter the number of cities: "))

# Cost matrix input as flattened array
cost_Mat = np.array(list(map(int, input("Enter the cost matrix: ").split())))
cost_Mat = np.reshape(cost_Mat, (n,n))

# Generates a random initial state with 0 as start and end
def start():
  init = list(range(1,n))
  random.shuffle(init)
  init = [0] + init + [0]
  return init

# Cost of the path
def cost(path):
  cost = 0
  for i in range(len(path)-1):
    cost += cost_Mat[path[i]][path[i+1]]
  return cost

# Generates all possible neighbour states
def neighbours(init):
  childs = []
  for i in range(1, n-1):
    for j in range(i+1, n):
      child = init.copy()
      child[i], child[j] = init[j], init[i]
      childs.append(child)
  return childs

# Hill Climbing with best improved neighbour
def hill_climb():
  init = start()
  pathCost  = cost(init)
  while True:
    flag = False  #flag set to no best neighbour
    for child in neighbours(init):
      if cost(child) < pathCost:
        flag = True  # best neighbour found
        init = child  # update current state
        pathCost = cost(child)  # update current cost
    if not flag:
      return init, pathCost

# Simulated Annealing
def simul_anneal(temp, cool,iter):
  init = start()
  pathCost = cost(init)
  for _ in range(iter):
    if temp < 1e-8:   # stop if temperature too small
            break
    child = random.choice(neighbours(init))
    delta = cost(child) - pathCost
    if delta < 0 or random.random() < np.exp(-delta / temp):
      init = child
      pathCost = cost(child)
    temp *= cool
  return init, pathCost

sim_param = {
  "config1" : [1000, 0.995, 100*n*n],
  "config2" : [500, 0.990, 50*n*n],
  "config3" : [2000, 0.900, 200*n*n]
}

path, totalcost = hill_climb()
print("\n==== Hill Climbing ====")
print(" -> ".join(map(str, path)))
print(f"Total Cost: {totalcost}")

print("\n==== Simulated Annealing ====")
for conf, param in sim_param.items():
  print(f" >>> T = {param[0]} | cool = {param[1]} | K = {param[2]}")
  path, totalcost = simul_anneal(param[0], param[1], param[2])
  print(" -> ".join(map(str, path)))
  print(f"Total Cost: {totalcost}")
print("")


# Input: [5]   0 10 15 20 25 10 0 35 25 17 15 35 0 30 28 20 25 30 0 23 25 17 28 23 0
# Output: 0 -> 2 -> 3 -> 4 -> 1 -> 0,  Cost: 95

# Input: [7]   0 12 10 19 8 14 16 12 0 3 7 2 6 20 10 3 0 6 20 4 9 19 7 6 0 4 12 8 8 2 20 4 0 11 5 14 6 4 12 11 0 13 16 20 9 8 5 13 0
# Output: 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 0,  Cost: 48