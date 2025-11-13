<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **DSA NOTES** 🔥🐦‍🔥

<br>

## 🐦‍🔥 KADANE'S ALGORITHM

> Kadane's Algorithm: It says that, if the sum of Sub Array becomes negative then adding it to further elements will decrease the Max possible sum, so it is better to reset it to 0.
> Problem: Given an array of integers, find the Maximum Sum of Sub Array.
> Algorithm:
> 🔸 `Iterate & add each value to 'sum'`
> 🔸 `Update 'maxSum' with 'max(sum, maxSum)'`
> 🔸 `Set 'sum = 0' if 'sum < 0'`

```cpp
  vector<int> vect = {1, -2, 6, 45, 7, 3, -24, 11, -14};
  int sum = 0, maxSum = INT_MIN, st = 0, end = 0;
  for (int i = 0; i < vect.size(); i++) {
    sum += vect[i];
    if (sum > maxSum) {
      maxSum = sum;
      end = i;
    }
    if (sum < 0) {
      st = i + 1;
      sum = 0;
    }
  }
  cout << maxSum << st << end << endl ;
```

<br>

# 🐦‍🔥 **DYNAMIC PROGRAMMING**

## 🔥 What is Dynamic Programming ?

Dynamic Programming is a technique to solve problems by breaking them into overlapping subproblems and reusing solutions to those subproblems instead of recomputing them

## 🔥 When to Use DP?

You can use DP when:
♦️ The problem can be broken down into subproblems.
♦️ Subproblems overlap (repeated calculations).
♦️ The solution can be built using smaller solutions (optimal substructure).
Example: Fibonacci numbers, shortest paths, knapsack, coin change, etc.

🔸 `Overlapping Subproblems:`
Same subproblems are solved multiple times. Example: F(5) = F(4) + F(3); F(4) = F(3) + F(2) — F(3) repeats.
🔸 `Optimal Substructure:`
The optimal solution to the problem depends on the optimal solution of its subproblems. Example: Shortest path from A → C = min(A→B→C, A→D→C).

## 🔥 Techniques of DP

There are two main techniques to implement DP:

### 🔥1️⃣ Top-Down Approach (Memoization)

> We proceed from bigger problem to base case and return storing the result

- Recursive + Caching (store previously computed results).
- Avoids recomputation.

`Steps:`

- Write a recursive function for the problem.
- Store results in an array (or map).
- Before computing, check if result already exists.

`Example: Fibonacci`

```cpp
int dp[1000];
int fib(int n) {
if (n <= 1) return n;
if (dp[n] != -1) return dp[n];
return dp[n] = fib(n - 1) + fib(n - 2);
}
```

### 🔥2️⃣ Bottom-Up Approach (Tabulation)

- Iterative solution.
- Solve subproblems first and build up to the main problem.

`Steps:`

- Define a DP array.
- Initialize base cases.
- Fill the table iteratively.

`Example: Fibonacci`

```cpp
int fib(int n) {
    int dp[n+1];
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i-1] + dp[i-2];
    return dp[n];
}
```

<br>

# 🐦‍🔥 **GRAPH**

## 🔥 Traversal

### 🔥 Breadth-First-Search

### 🔥 Depth-First-Search

## 🔥 TOPOLOGICAL SORT

- Applicable for Directed Acyclic Graph (DAG) only.
- Topological Sort or Topo sort is a linear ordering of vertices in a Directed Acyclic Graph (DAG) such that for every directed edge u → v, vertex u comes before v in the ordering.

## ♦️ Using DFS

Recursively visit each node and push it into a stack after visiting all its neighbors, Then you pop from the stack to get the topological order.

> Just do the simple DFS and store the current node after the recursive call.

```cpp
void dfs(int node, vector<int> &vis, vector<vector<int>> &adj, vector<int> &collect) {
  vis[node] = 1;
  for (auto i : adj[node]) {
    if (!vis[i]) {
      dfs(i, vis, adj, collect);
    }
  }
  collect.push_back(node);
}
```

## ♦️ Using BFS - Kahn's Algorithm

**STEPS**
* Make an array of In-degree

</div>
</div>
