import heapq
import numpy as np
import matplotlib.pyplot as plt

file = open("./Learning/AI/0Lab/Prev/graph_data.txt", "r")
data = file.read().split("\n")
n, e = data[0].split(" ")
n, e = int(n), int(e)

i = 1
nodes = []
for k in range(n):
  nodes.append(tuple(map(float, data[i].split())))
  i += 1

edges = []
graph = np.full((n, n), -1.0)

for k in range(i, i+e):
  u, v, w = data[k].split()
  u,v,w = int(u), int(v), float(w)
  edges.append((int(u), int(v), float(w)))
  graph[u][v] = w
  graph[v][u] = w

plt.figure()
xs = [i[0] for i in nodes]
ys = [i[1] for i in nodes]
plt.scatter(xs, ys)
plt.title("Graph")
plt.xlabel("X")
plt.ylabel("Y")

for u,v,w in edges:
  x1, y1 = nodes[u]
  x2, y2 = nodes[v]
  plt.plot([x1, x2], [y1, y2])

start = int(input("Enter start node: "))
end = int(input("Enter end node: "))

if start >= len(nodes) or end >= len(nodes):
  print("Invalid node")
  exit()

def hur(node, end):
  sx, sy = nodes[node]
  ex, ey = nodes[end]
  x = ((sx - ex)**2+ (sy - ey)**2)**0.5
  return x

def childs(node):
  res = []
  for i in range(n):
    if graph[node][i] != -1:
      res.append(i)
  return res

def Astar(start, end):
  pq = []
  heapq.heappush(pq, (hur(start, end), 0, start))
  vis = {start: 0}
  parent = {start: None}

  while pq:
    f, g, node = heapq.heappop(pq)
    if node == end: 
      path = []
      cur = end
      while cur is not None:
        path.append(cur)
        cur = parent[cur]
      path.reverse()
      return path, g
    for child in childs(node):
      newCost = g + graph[node][child]
      if child not in vis or newCost < vis[child]:
        vis[child] = newCost
        parent[child] = node
        heapq.heappush(pq,(newCost + hur(child, end), newCost, child))
  return []
  

path, cost = Astar(start, end)
print(" -> ".join(map(str, path)))
print(f"Total Cost: {cost:.2f}")

plt.show()