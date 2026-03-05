import heapq
import numpy as np

file = open("./Learning/AI/0Lab/Prev/graph_data.txt", "r")
file.seek(0)
data = file.read().split("\n")
nd, edges = data[0].split(" ")
nd, edges = int(nd), int(edges)

i = 1
nodes = []
while i < len(data) and len(data[i].split(" ")) == 2:
  nodes.append(tuple(map(float, data[i].split(" "))))
  i += 1

edges = []
while i < len(data) and len(data[i].split(" ")) == 3:
  edges.append(tuple(data[i].split(" ")))
  i += 1

graph = np.full((nd, nd), -1.0)

for edge in edges:
  graph[int(edge[0])][int(edge[1])] = float(edge[2])
  graph[int(edge[1])][int(edge[0])] = float(edge[2])

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
  for i in range(nd):
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
