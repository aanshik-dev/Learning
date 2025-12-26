<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **DSA NOTES** 🔥🐦‍🔥

<br>

## 🐦‍🔥 WHAT IS DSA?

Data Structures → Way to store and organize data
Algorithms → Step-by-step procedures to solve problems efficiently

### 🔥 Why do we need Data Structures?

- To handle large data efficiently
- To reduce time complexity
- To optimize memory usage
- To make programs scalable

<br>

## 🐦‍🔥 TIME & SPACE COMPLEXITY

### 🔥 Time complexity

It tells how execution time grows with input size (n).

> 📝 NOTE : We always consider worst case complexity

| Notation | Name        | Example                 |
| :------- | ----------- | ----------------------- |
| O(1)     | Constant    | Access array element    |
| O(logn)  | Logarithmic | Binary Search           |
| O(n)     | Linear      | Linear Search           |
| O(nlogn) | Linear Log  | Merge Sort              |
| O(n²)    | Quadratic   | Bubble / Selection Sort |
| O(2ⁿ)    | Exponential | Recursive Fibonacci     |

### 🔥 Space Complexity

Extra memory used by algorithm.

```cpp
int arr[100];   // O(1) space
int arr[n];     // O(n) space
```

### 🔥 Asymptotic Notations

| Symbol | Name  | Meaning      |
| :----: | ----- | ------------ |
|   O    | Big-O | Worst case   |
|   Ω    | Omega | Best case    |
|   Θ    | Theta | Average case |

<br>

## 🐦‍🔥 TYPES OF DATA STRUCTURES

## 🔥 Linear Data Structures

Data stored sequentially

- Array
- Linked List
- Stack
- Queue
- Deque

## 🔥 Non-Linear Data Structures

Hierarchical or network based

- Tree
- Graph
- Heap
- Hash Table

<br>

## 🐦‍🔥 ARRAY

### 🔥 What is an Array?

An Array is a collection of elements of same data type stored in contiguous memory locations.

```cpp
int arr[5] = {10, 20, 30, 40, 50};
```

- Fixed size
- Same data type
- Index-based access
- Stored in contiguous memory

| Operation | Time |
| --------- | ---- |
| Access    | O(1) |
| Traversal | O(n) |
| Search    | O(n) |
| Insertion | O(n) |
| Deletion  | O(n) |

### 🔥 Searching In Array

- Linear Search
- Binary Search

```cpp
int l = 0, r = n-1;
while(l <= r){
  int mid = l + (r-l)/2;
  if(arr[mid] == key) return mid;
  else if(arr[mid] < key) l = mid + 1;
  else r = mid - 1;
}
```

<br>

## 🐦‍🔥 Sorting In Array

### 🔥 Bubble Sort

Idea: Repeatedly swap adjacent elements if they’re in wrong order.

```cpp
for(int i=0;i<n;i++){
  for(int j=0;j<n-i-1;j++){
    if(arr[j] > arr[j+1])
      swap(arr[j], arr[j+1]);
  }
}  // O(n²)  // O(1) // Stable
```

### 🔥 Selection Sort

Idea: Pick minimum element and place it at correct position.

```cpp
for(int i=0;i<n-1;i++){
  int minIdx = i;
  for(int j=i+1;j<n;j++){
    if(arr[j] < arr[minIdx])
      minIdx = j;
  }
  swap(arr[i], arr[minIdx]);
}  // O(n²)  // O(1) // Not Stable
```

### 🔥 Insertion Sort

Idea: Insert current element into its correct position in sorted part.

```cpp
for(int i = 1; i < n; i++){
  int key = arr[i];
  int j = i - 1;
  while(j >= 0 && arr[j] > key){
    arr[j + 1] = arr[j];
    j--;
  }
  arr[j + 1] = key;
}  // O(n²)  // O(1) // Stable
```

### 🔥 Merge Sort

Idea: Divide array, sort halves, then merge.

```cpp
void merge(int arr[], int l, int m, int r){
  int n1 = m - l + 1, n2 = r - m;
  int L[n1], R[n2];

  for(int i=0;i<n1;i++) L[i] = arr[l+i];
  for(int i=0;i<n2;i++) R[i] = arr[m+1+i];

  int i=0,j=0,k=l;
  while(i<n1 && j<n2){
    if(L[i] <= R[j]) arr[k++] = L[i++];
    else arr[k++] = R[j++];
  }

  while(i<n1) arr[k++] = L[i++];
  while(j<n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r){
  if(l >= r) return;
  int m = l + (r - l)/2;
  mergeSort(arr, l, m);
  mergeSort(arr, m+1, r);
  merge(arr, l, m, r);
} // O(nlogn)  // O(n) // Stable
```

### 🔥 Quick Sort

Idea: Choose pivot, partition, recursively sort.

```cpp
int partition(int arr[], int low, int high){
  int pivot = arr[high];
  int i = low - 1;

  for(int j = low; j < high; j++){
    if(arr[j] < pivot){
      i++;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i+1], arr[high]);
  return i + 1;
}

void quickSort(int arr[], int low, int high){
  if(low < high){
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
} // O(nlogn)  // O(logn) // Not Stable
```

### 🔥 Heap Sort

Idea: Build max heap, extract elements one by one.

```cpp
void heapify(int arr[], int n, int i){
  int largest = i;
  int l = 2*i + 1;
  int r = 2*i + 2;

  if(l < n && arr[l] > arr[largest]) largest = l;
  if(r < n && arr[r] > arr[largest]) largest = r;

  if(largest != i){
    swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

void heapSort(int arr[], int n){
  for(int i = n/2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  for(int i = n - 1; i > 0; i--){
    swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
} // O(nlogn)  // O(1) // Not Stable
```

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

## 🔥 What is a Graph ?

- A Graph G(V, E) is a collection of vertices (V) and edges (E) that connect pairs of vertices.

## 🔥 2️⃣ Terminology

| Term            | Meaning                                           |
| --------------- | ------------------------------------------------- |
| Vertex          | A node in the graph                               |
| Edge            | Connection between two vertices                   |
| Degree          | Number of edges incident to a vertex              |
| Path            | Sequence of connected vertices                    |
| Cycle           | Path that starts and ends at the same vertex      |
| Connected Graph | Every vertex is reachable from every other vertex |
| Component       | A disconnected subgraph of a larger graph         |

## 🔥 2️⃣ Types of Graph

| Type                         | Description                                   |
| ---------------------------- | --------------------------------------------- |
| **Directed Graph (Digraph)** | Edges have a direction (A → B)                |
| **Undirected Graph**         | Edges have no direction (A — B)               |
| **Weighted Graph**           | Each edge has a weight (distance, cost, etc.) |
| **Unweighted Graph**         | All edges are equal                           |
| **Cyclic Graph**             | Contains at least one cycle                   |
| **Acyclic Graph (DAG)**      | No cycles exist                               |
| **Connected Graph**          | Single component                              |
| **Disconnected Graph**       | Multiple components                           |
| **Complete Graph (Kn)**      | Each vertex connected to all others           |
| **Tree**                     | Acyclic connected graph                       |

---

## 🔥 3️⃣ Graph Representation

### 🔸 Adjacency Matrix

- 2D matrix of size `V x V`.
- `matrix[i][j] = 1` if there is an edge from i → j, else 0.
- Space Complexity: O(V²)

### 🔸 Adjacency List

- Array of vectors/lists where each vertex stores its neighbors.
- Space Efficient: O(V + E)

```cpp
vector<vector<int>> adj(V);
for (auto edge : edges) {
  int u = edge[0], v = edge[1];
  adj[u].push_back(v);
  adj[v].push_back(u); // remove for directed graph
}
```

### 🔸 Adjacency List

- List of edges stored as pairs (u,v)
- Mostly used for algorithms like Kruskal's

## 🔥4️⃣ Graph Traversal

### 🔸 Breadth-First-Search (BFS)

> Level-order traversal using Queue (FIFO)

`STEPS:`

- Pick a source node, mark as visited.
- Push to queue.
- Pop node → visit its neighbors → mark visited → push unvisited ones.
- Continue until queue is empty

```cpp
void bfs(int start, vector<vector<int>> &adj, vector<int> &vis) {
  queue<int> q;
  q.push(start);
  vis[start] = 1;
  while (!q.empty()) {
    int node = q.front(); q.pop();
    cout << node << " ";
    for (auto i : adj[node]) {
      if (!vis[i]) {
        vis[i] = 1;
        q.push(i);
      }
    }
  }
}
```

### 🔸 Depth-First-Search (BFS)

> Recursive traversal (Stack implicitly used)

`STEPS:`

- Pick a source node, mark as visited.
- Push to stack.
- Pop node → visit its neighbors → mark visited → push unvisited ones.
- Continue until stack is empty

```cpp
void dfs(int node, vector<vector<int>> &adj, vector<int> &vis) {
  stack<int> st;
  st.push(node);
  vis[node] = 1;
  while (!st.empty()) {
    int curr = st.top();
    st.pop();
    cout << curr << " ";
    for (auto i : adj[curr]) {
      if (!vis[i]) {
        st.push(i);
        vis[i] = 1;
      }
    }
  }
}
```

> 📝 NOTE : Recursion method is mostly used which uses stack internally.

```cpp
void dfs(int node, vector<vector<int>> &adj, vector<int> &vis) {
  vis[node] = 1;
  cout << node << " ";
  for (auto i : adj[node]) {
    if (!vis[i]) {
      dfs(i, adj, vis);
    }
  }
}
```

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

`STEPS: `

- Make an array of In-degree, There surely be a node with 0 In-degree
- Push all such nodes to Queue.
- Pop the first node and decrement the indegree of connected neighbours by 1
- If any neighbor's In-degree becomes 0 then push that too.
- Continue until the queue is empty.

</div>
</div>
