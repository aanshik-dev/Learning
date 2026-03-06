<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **AI - NOTES** 🔥🐦‍🔥

⚡ BY - THE AANSHIK-DEV

<br>

## 🐦‍🔥 INTELLIGENT AGENT

### 🔥 What is an agent ?

| Agent            | Sensors           | Actuators        |
| ---------------- | ----------------- | ---------------- |
| Human            | Eyes, ears        | Hands, legs      |
| Robot            | Camera, IR sensor | Motors           |
| Chess AI         | Board state       | Move pieces      |
| Self-driving car | Lidar, camera     | Steering, brakes |

### 🔥 Agent Function and Agent Program

<br>

## 🐦‍🔥 RATIONAL AGENT

An agent is rational if it:

- Chooses an action that maximizes expected performance
- Given:
  - percept history
  - knowledge of environment
  - available actions

<br>

## 🐦‍🔥 Types of Environment

### 🔥 Fully Observable vs Partially Observable

- Fully observable: agent sees entire state
  👉 Chess

- Partially observable: limited info
  👉 Driving in fog

### 🔥 Deterministic vs Stochastic

- Deterministic: next state fully determined
  👉 Chess
- Stochastic: randomness involved
  👉 Poker, real-world driving

### 🔥 Episodic vs Sequential

- Episodic: each action independent
  👉 Image classification
- Sequential: actions affect future
  👉 Chess, navigation

### 🔥 Static vs Dynamic

- Static: environment doesn’t change
  👉 Crossword puzzle
- Dynamic: changes while agent thinks
  👉 Traffic system

### 🔥 Discrete vs Continuous

- Discrete: finite actions/states
  👉 Board games
- Continuous: infinite states
  👉 Robot motion

### 🔥 Single-agent vs Multi-agent

- Single-agent: puzzle solving
- Multi-agent: chess, markets

<br>

## 🐦‍🔥 Types of Agents (CORE MODELS)

### 🔥 Simple Reflex Agent

- Acts only on current percept
- Uses condition–action rules
  ❌ No memory
  ❌ Fails in partially observable environments

### 🔥 Model-Based Reflex Agent

- Maintains internal state
- Tracks world changes
  ✅ Handles partial observability

### 🔥 Goal-Based Agent

- Has a goal
- Uses search & planning
  👉 Example: GPS navigation

### 🔥 Utility-Based Agent

- Uses utility function
- Chooses action with max utility
  👉 Handles trade-offs (speed vs safety)

### 🔥 Learning Agent

Improves with experience
Components:

- Performance element
- Learning element
- Critic
- Problem generator

| Algorithm | Complete | Optimal            |
| --------- | -------- | ------------------ |
| BFS       | Yes      | Yes (unit cost)    |
| DFS       | No       | No                 |
| DLS       | No       | No                 |
| IDDFS     | Yes      | Yes                |
| UCS       | Yes      | Yes                |
| Greedy    | No       | No                 |
| A*        | Yes      | Yes (admissible h) |
| BDS       | Yes      | Yes (unit cost)    |


```py
import time
import heapq
from collections import deque

# Global timeout (seconds)
TIME_LIMIT = 10


# =========================
# BFS
# =========================
def bfs(init, n):
    start = time.time()
    q = deque([(init, 0)])
    visited = set([init])

    while q:
        if time.time() - start > TIME_LIMIT:
            return "Timeout", TIME_LIMIT, len(visited), None

        state, depth = q.popleft()

        if state == goal:
            return "Success", time.time() - start, len(visited), depth

        for mov in getMoves(state, n):
            if mov not in visited:
                visited.add(mov)
                q.append((mov, depth + 1))

    return "Failure", time.time() - start, len(visited), None


# =========================
# DFS (Graph Search)
# =========================
def dfs(init, n):
    start = time.time()
    stack = [(init, 0)]
    visited = set()

    while stack:
        if time.time() - start > TIME_LIMIT:
            return "Timeout", TIME_LIMIT, len(visited), None

        state, depth = stack.pop()

        if state == goal:
            return "Success", time.time() - start, len(visited), depth

        if state not in visited:
            visited.add(state)
            for mov in getMoves(state, n):
                stack.append((mov, depth + 1))

    return "Failure", time.time() - start, len(visited), None


# =========================
# Depth Limited Search
# =========================
def dls(init, n, limit=20):
    start = time.time()
    stack = [(init, 0)]
    visited = set()

    while stack:
        if time.time() - start > TIME_LIMIT:
            return "Timeout", TIME_LIMIT, len(visited), None

        state, depth = stack.pop()

        if state == goal:
            return "Success", time.time() - start, len(visited), depth

        if depth < limit and state not in visited:
            visited.add(state)
            for mov in getMoves(state, n):
                stack.append((mov, depth + 1))

    return "Failure", time.time() - start, len(visited), None


# =========================
# Iterative Deepening
# =========================
def iterDeep(init, n, max_depth=50):
    start = time.time()

    for limit in range(max_depth):
        stack = [(init, 0)]
        visited = set()

        while stack:
            if time.time() - start > TIME_LIMIT:
                return "Timeout", TIME_LIMIT, None, None

            state, depth = stack.pop()

            if state == goal:
                return "Success", time.time() - start, None, depth

            if depth < limit and state not in visited:
                visited.add(state)
                for mov in getMoves(state, n):
                    stack.append((mov, depth + 1))

    return "Failure", time.time() - start, None, None


# =========================
# Uniform Cost Search
# =========================
def ucs(init, n):
    start = time.time()
    pq = [(0, init)]
    visited = {}

    while pq:
        if time.time() - start > TIME_LIMIT:
            return "Timeout", TIME_LIMIT, len(visited), None

        cost, state = heapq.heappop(pq)

        if state == goal:
            return "Success", time.time() - start, len(visited), cost

        if state not in visited or cost < visited[state]:
            visited[state] = cost
            for mov in getMoves(state, n):
                heapq.heappush(pq, (cost + 1, mov))

    return "Failure", time.time() - start, len(visited), None


# =========================
# Bidirectional Search
# =========================
def bds(init, n):
    start = time.time()

    front_q = deque([(init, 0)])
    back_q = deque([(goal, 0)])

    front_vis = {init: 0}
    back_vis = {goal: 0}

    while front_q and back_q:
        if time.time() - start > TIME_LIMIT:
            return "Timeout", TIME_LIMIT, len(front_vis) + len(back_vis), None

        # Forward
        node, depth = front_q.popleft()
        for mov in getMoves(node, n):
            if mov not in front_vis:
                front_vis[mov] = depth + 1
                front_q.append((mov, depth + 1))
                if mov in back_vis:
                    total_depth = depth + 1 + back_vis[mov]
                    return "Success", time.time() - start, len(front_vis) + len(back_vis), total_depth

        # Backward
        node, depth = back_q.popleft()
        for mov in getMoves(node, n):
            if mov not in back_vis:
                back_vis[mov] = depth + 1
                back_q.append((mov, depth + 1))
                if mov in front_vis:
                    total_depth = depth + 1 + front_vis[mov]
                    return "Success", time.time() - start, len(front_vis) + len(back_vis), total_depth

    return "Failure", time.time() - start, len(front_vis) + len(back_vis), None


# =========================
# A* Search
# =========================
def Astar(init, n, heuristic):
    start = time.time()
    pq = [(heuristic(init, n), 0, init)]
    visited = {}

    while pq:
        if time.time() - start > TIME_LIMIT:
            return "Timeout", TIME_LIMIT, len(visited), None

        f, g, state = heapq.heappop(pq)

        if state == goal:
            return "Success", time.time() - start, len(visited), g

        if state not in visited or g < visited[state]:
            visited[state] = g
            for mov in getMoves(state, n):
                new_cost = g + 1
                heapq.heappush(pq, (new_cost + heuristic(mov, n), new_cost, mov))

    return "Failure", time.time() - start, len(visited), None


# =========================
# Greedy Best First Search
# =========================
def greedyBFS(init, n, heuristic):
    start = time.time()
    pq = [(heuristic(init, n), init)]
    visited = set([init])

    while pq:
        if time.time() - start > TIME_LIMIT:
            return "Timeout", TIME_LIMIT, len(visited), None

        _, state = heapq.heappop(pq)

        if state == goal:
            return "Success", time.time() - start, len(visited), None

        for mov in getMoves(state, n):
            if mov not in visited:
                visited.add(mov)
                heapq.heappush(pq, (heuristic(mov, n), mov))

    return "Failure", time.time() - start, len(visited), None
```

</div>
</div>