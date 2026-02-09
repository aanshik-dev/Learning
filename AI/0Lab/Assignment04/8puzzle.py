import time
import random
from collections import deque

TIME_LIMIT = 120        # seconds
DLS_LIMIT = 20

# -------------------------
# Puzzle Utilities
# -------------------------
def goal_state(n):
    return tuple(list(range(1, n*n)) + [0])

def find_blank(state):
    return state.index(0)

def get_moves(state, n):
    idx = find_blank(state)
    r, c = divmod(idx, n)
    moves = []

    def swap(i, j):
        lst = list(state)
        lst[i], lst[j] = lst[j], lst[i]
        return tuple(lst)

    if r > 0: moves.append(swap(idx, idx - n))
    if r < n - 1: moves.append(swap(idx, idx + n))
    if c > 0: moves.append(swap(idx, idx - 1))
    if c < n - 1: moves.append(swap(idx, idx + 1))

    return moves

def random_state(n):
    lst = list(range(n*n))
    random.shuffle(lst)
    return tuple(lst)

# -------------------------
# BFS
# -------------------------
def bfs(start, n):
    start_time = time.time()
    q = deque([(start, 0)])
    visited = set([start])

    while q:
        if time.time() - start_time > TIME_LIMIT:
            return "Timeout", TIME_LIMIT, None

        state, depth = q.popleft()

        if state == goal_state(n):
            return "Success", time.time() - start_time, depth

        for nxt in get_moves(state, n):
            if nxt not in visited:
                visited.add(nxt)
                q.append((nxt, depth + 1))

    return "Failure", time.time() - start_time, None

# -------------------------
# DFS (Tree Search)
# -------------------------
def dfs(start, n):
    start_time = time.time()
    stack = [(start, 0)]

    while stack:
        if time.time() - start_time > TIME_LIMIT:
            return "Timeout", TIME_LIMIT, None

        state, depth = stack.pop()

        if state == goal_state(n):
            return "Success", time.time() - start_time, depth

        for nxt in get_moves(state, n):
            stack.append((nxt, depth + 1))

    return "Failure", time.time() - start_time, None

# -------------------------
# Depth-Limited Search
# -------------------------
def dls(start, n, limit):
    start_time = time.time()
    stack = [(start, 0)]

    while stack:
        if time.time() - start_time > TIME_LIMIT:
            return "Timeout", TIME_LIMIT, None

        state, depth = stack.pop()

        if state == goal_state(n):
            return "Success", time.time() - start_time, depth

        if depth < limit:
            for nxt in get_moves(state, n):
                stack.append((nxt, depth + 1))

    return "Failure", time.time() - start_time, None

# -------------------------
# Iterative Deepening
# -------------------------
def iterative_deepening(start, n):
    start_time = time.time()

    for limit in range(0, 50):
        stack = [(start, 0)]

        while stack:
            if time.time() - start_time > TIME_LIMIT:
                return "Timeout", TIME_LIMIT, None

            state, depth = stack.pop()

            if state == goal_state(n):
                return "Success", time.time() - start_time, depth

            if depth < limit:
                for nxt in get_moves(state, n):
                    stack.append((nxt, depth + 1))

    return "Failure", time.time() - start_time, None

# -------------------------
# Experiment Runner
# -------------------------
def run_experiment(n):
    algorithms = {
        "BFS": bfs,
        "DFS": dfs,
        "DLS": lambda s, n: dls(s, n, DLS_LIMIT),
        "ID": iterative_deepening
    }
    results = {
        "BFS": [],
        "DFS": [],
        "DLS": [],
        "ID": []
    }

    results = {alg: [] for alg in algorithms}

    for i in range(10):
        start = random_state(n)
        print(f"\nInitial State {i+1}: {start}")

        for name, algo in algorithms.items():
            print(f"  Running {name}...")
            status, t, path = algo(start, n)
            results[name].append((status, t, path))
            print(f"    → {status}, Time: {t:.2f}s, Path Length: {path}")

    return results


n = int(input("Enter n (3 for 8-puzzle, 4 for 15-puzzle): "))
run_experiment(n)
