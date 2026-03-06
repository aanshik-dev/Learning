#sudoku
import numpy as np
import time
import heapq
import matplotlib.pyplot as plt
from copy import deepcopy

timeout = 60

# Example Sudoku (0 = empty)
initial_grid = [
[5,3,0,0,7,0,0,0,0],
[6,0,0,1,9,5,0,0,0],
[0,9,8,0,0,0,0,6,0],
[8,0,0,0,6,0,0,0,3],
[4,0,0,8,0,3,0,0,1],
[7,0,0,0,2,0,0,0,6],
[0,6,0,0,0,0,2,8,0],
[0,0,0,4,1,9,0,0,5],
[0,0,0,0,8,0,0,7,9]
]


def find_empty(grid):
    for i in range(9):
        for j in range(9):
            if grid[i][j] == 0:
                return i,j
    return None


def valid(grid, r, c, num):
    if num in grid[r]:
        return False
    for i in range(9):
        if grid[i][c] == num:
            return False
    box_r = (r//3)*3
    box_c = (c//3)*3

    for i in range(3):
        for j in range(3):
            if grid[box_r+i][box_c+j] == num:
                return False
    return True


def getMoves(grid):
    pos = find_empty(grid)
    if not pos:
        return []
    r,c = pos
    moves = []
    for num in range(1,10):
        if valid(grid,r,c,num):
            new_grid = deepcopy(grid)
            new_grid[r][c] = num
            moves.append(new_grid)
    return moves


# Heuristic 1: number of empty cells
def emptyCells(grid):
    count = 0
    for r in grid:
        count += r.count(0)
    return count


# Heuristic 2: total possible values remaining
def remainingOptions(grid):
    score = 0
    for r in range(9):
        for c in range(9):
            if grid[r][c] == 0:
                options = 0
                for num in range(1,10):
                    if valid(grid,r,c,num):
                        options += 1
                score += options
    return score


# Custom heuristic
def customHeuristic(grid):
    return max(emptyCells(grid), remainingOptions(grid)//5)

def isGoal(grid):
    return find_empty(grid) == None

def Astar(init, heuristic):

    start = time.time()
    pq = []
    heapq.heappush(pq,(heuristic(init),0,init))
    visited = set()
    nodes = 0

    while pq:
        if time.time()-start > timeout:
            return "Timeout", timeout, nodes
        f,g,node = heapq.heappop(pq)
        nodes += 1

        if isGoal(node):
            return "Success", time.time()-start, nodes
        key = tuple(map(tuple,node))
        if key in visited:
            continue
        visited.add(key)
        for move in getMoves(node):
            heapq.heappush(pq,(g+1+heuristic(move),g+1,move))

    return "Failure", time.time()-start, nodes



def greedyBFS(init, heuristic):

    start = time.time()

    pq = []
    heapq.heappush(pq,(heuristic(init),init))

    visited = set()
    nodes = 0

    while pq:

        if time.time()-start > timeout:
            return "Timeout", timeout, nodes

        h,node = heapq.heappop(pq)
        nodes += 1

        if isGoal(node):
            return "Success", time.time()-start, nodes

        key = tuple(map(tuple,node))
        if key in visited:
            continue

        visited.add(key)

        for move in getMoves(node):

            heapq.heappush(pq,(heuristic(move),move))

    return "Failure", time.time()-start, nodes



heuristics = {
    "EmptyCells": emptyCells,
    "RemainingOptions": remainingOptions,
    "Custom": customHeuristic
}

astar_time = {h:[] for h in heuristics}
astar_nodes = {h:[] for h in heuristics}
greedy_time = {h:[] for h in heuristics}
greedy_nodes = {h:[] for h in heuristics}


for hname,hfunc in heuristics.items():

    print("\nA* with",hname)
    status,sec,nodes = Astar(initial_grid,hfunc)
    print(status,sec,nodes)

    astar_time[hname].append(sec)
    astar_nodes[hname].append(nodes)


    print("Greedy BFS with",hname)
    status,sec,nodes = greedyBFS(initial_grid,hfunc)
    print(status,sec,nodes)

    greedy_time[hname].append(sec)
    greedy_nodes[hname].append(nodes)



labels = list(heuristics.keys())

astar_avg_time = [np.mean(astar_time[h]) for h in heuristics]
greedy_avg_time = [np.mean(greedy_time[h]) for h in heuristics]

astar_avg_nodes = [np.mean(astar_nodes[h]) for h in heuristics]
greedy_avg_nodes = [np.mean(greedy_nodes[h]) for h in heuristics]

x = range(len(labels))


plt.figure()
plt.bar(x,astar_avg_time,width=0.4,label="A*")
plt.bar([i+0.4 for i in x],greedy_avg_time,width=0.4,label="Greedy")
plt.xticks([i+0.2 for i in x],labels)
plt.ylabel("Time")
plt.title("Sudoku Execution Time")
plt.legend()
plt.show()


plt.figure()
plt.bar(x,astar_avg_nodes,width=0.4,label="A*")
plt.bar([i+0.4 for i in x],greedy_avg_nodes,width=0.4,label="Greedy")
plt.xticks([i+0.2 for i in x],labels)
plt.ylabel("Nodes Expanded")
plt.title("Sudoku Nodes Expanded")
plt.legend()
plt.show()