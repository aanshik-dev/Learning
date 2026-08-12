<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **DSA NOTES** 🔥🐦‍🔥

<br>

<details>
<summary><b> 📋 TABLE OF CONTENTS</b></summary>

### ⚡ PART 1 - DATA STRUCTURES

| Topic                     | Anchors              |
| ------------------------- | -------------------- |
| 🔢 Array                  | [Jump](#array)       |
| 🔗 Linked List            | [Jump](#linked-list) |
| 🥞 Stack                  | [Jump](#stack)       |
| 🚏 Queue & Deque          | [Jump](#queue)       |
| 🌳 Tree & BST             | [Jump](#tree)        |
| ⛏ Heap                    | [Jump](#heap)        |
| 🗄 Hashing                | [Jump](#hashing)     |
| 🕸 Graph (representation) | [Jump](#graph)       |

### ⚡ PART 2 - ALGORITHMS

| Topic                                | Anchors               |
| ------------------------------------ | --------------------- |
| 🔍 Searching                         | [Jump](#searching)    |
| 🔁 Recursion & Backtracking          | [Jump](#recursion)    |
| 🧮 Two Pointers & Sliding Window     | [Jump](#two-pointers) |
| ➕ Prefix Sum & Difference Array     | [Jump](#prefix)       |
| 📈 Greedy                            | [Jump](#greedy)       |
| 📌 Kadane's Algorithm                | [Jump](#kadane)       |
| 🧠 Dynamic Programming               | [Jump](#dp)           |
| 🌐 Graph Algorithms                  | [Jump](#graph-algos)  |
| 🔤 String Algorithms                 | [Jump](#string)       |
| 🧮 Number Theory & Math              | [Jump](#math)         |
| 💠 Bit Manipulation                  | [Jump](#bitmanip)     |
| 🃏 Sorting                           | [Jump](#sorting)      |
| 🎓 Advanced (Segment Tree & Fenwick) | [Jump](#advanced)     |

</details>

<br>
<hr>

<a id="intro"></a>

<details>
<summary><b>✨ INTRODUCTION - WHAT IS DSA ?</b></summary>

## 🐦‍🔥 WHAT IS DSA?

Data Structures → Way to store and organize data
Algorithms → Step-by-step procedures to solve problems efficiently

### 🔥 Why do we need Data Structures?

- To handle large data efficiently
- To reduce time & space complexity
- To optimize memory usage
- To make programs scalable

### 🔥 Categories

- **Linear** : data placed in sequence - Array, Linked List, Stack, Queue, Deque
- **Non-Linear** : hierarchical / networked (Tree, Graph, Heap, Hash Table)

</details>

<a id="complexity"></a>

<details>
<summary><b>🕐 TIME &amp; SPACE COMPLEXITY</b></summary>

### 🔥 Time complexity

It tells how execution time grows with input size (n).

> 📝 NOTE : We always consider **worst case** complexity (Big-O).

| Notation | Name        | Example                 |
| :------- | ----------- | ----------------------- |
| O(1)     | Constant    | Access array element    |
| O(logn)  | Logarithmic | Binary Search           |
| O(n)     | Linear      | Linear Search           |
| O(nlogn) | Linear Log  | Merge Sort              |
| O(n²)    | Quadratic   | Bubble / Selection Sort |
| O(2ⁿ)    | Exponential | Recursive Fibonacci     |

### 🔥 Space Complexity

Extra memory used by an algorithm (besides input).

```cpp
int arr[100];   // O(1) space
int arr[n];     // O(n) space
```

### 🔥 Asymptotic Notations

| Symbol | Name      | Meaning                    |
| :----: | --------- | -------------------------- |
|   O    | Big-O     | Worst case                 |
|   Ω    | Big-Omega | Best case                  |
|   Θ    | Big-Theta | Tight bound (exact growth) |

</details>

<br>
<hr>

<br>

## 🐦‍🔥 **PART 1 - DATA STRUCTURES**

<br>
<a id="array"></a>
<details>
<summary><b>🔢 ARRAY</b></summary>

### 🔥 What is an Array?

An Array is a collection of elements of **same data type** stored in **contiguous memory** locations.

```cpp
int arr[5] = {10, 20, 30, 40, 50};
```

- Fixed size
- Same data type
- Index-based access
- Contiguous memory

### 🔥 Operations & Complexities

| Operation            | Time     |
| -------------------- | -------- |
| Access               | O(1)     |
| Traversal            | O(n)     |
| Search (unsorted)    | O(n)     |
| Search (sorted)      | O(log n) |
| Insertion / Deletion | O(n)     |

### 🔥 Two-Dimensional Array

```cpp
int mat[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
```

- `mat[i][j]` → element at row i, column j (0-indexed)
- Stored **row-major** in memory

### 🔥 Important Problems

- Two Sum (hash map) - LeetCode 1
- Maximum Subarray → see Kadane's
- Merge Intervals
- Product of Array Except Self

</details>

<a id="linked-list"></a>

<details>
<summary><b>🔗 LINKED LIST</b></summary>

### 🔥 What is a Linked List ?

A linear DS where each element is a **Node** containing:

> data + pointer to next node

```cpp
struct Node {
  int data;
  Node* next;
  Node(int val) : data(val), next(nullptr) {}
};
```

### 🔥 Operations & Complexity

| Operation      | Time | Why                              |
| -------------- | ---- | -------------------------------- |
| Access the kth | O(n) | must walk                        |
| Insert at head | O(1) | pointer swap                     |
| Insert at tail | O(n) | walk to end (O(1) with tail ptr) |
| Delete at head | O(1) | pointer swap                     |
| Search         | O(n) | walk                             |

### 🔥 Insert at Head

```cpp
void insertAtHead(Node* &head, int val){
  Node* temp = new Node(val);
  temp->next = head;
  head = temp;
}
```

### 🔥 Insert at Tail

```cpp
void insertAtTail(Node* &head, int val){
  Node* temp = new Node(val);
  if (head == nullptr) { head = temp; return; }
  Node* it = head;
  while (it->next) it = it->next;
  it->next = temp;
}
```

### 🔥 Traversal

```cpp
for (Node* it = head; it != nullptr; it = it->next)
  cout << it->data << " ";
```

### 🔥 Floyd's Cycle Detection

> Slow pointer moves 1 step, fast pointer 2 steps. If they ever meet → ❗ cycle exists.

Example: list `1 → 2 → 3 → 4 → 2 (loop)` - slow & fast meet inside the loop.

```cpp
bool hasCycle(Node* head){
  Node* slow = head, *fast = head;
  while (fast && fast->next){
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) return true;
  }
  return false;
}
```

### 🔥 Types

| Type     | Extra fields     | Use case     |
| -------- | ---------------- | ------------ |
| Singly   | data, next       | general      |
| Doubly   | data, next, prev | easy reverse |
| Circular | last → head      | queues       |

### 🎯 Applications

- Building stacks & queues
- Browser forward/back (doubly)
- Graph adjacency lists
- Memory free-list in OS

</details>

<a id="stack"></a>

<details>
<summary><b>🥞 STACK (LIFO)</b></summary>

### 🔥 What is a Stack?

**Last In First Out** - like a pile of plates. insertion & deletion both at the **top**.

| Operation | STL method   | Complexity |
| --------- | ------------ | ---------- |
| Push      | `st.push(x)` | O(1)       |
| Pop       | `st.pop()`   | O(1)       |
| Top       | `st.top()`   | O(1)       |
| Empty     | `st.empty()` | O(1)       |

```cpp
stack<int> st;
st.push(10); st.push(20); st.push(30);
cout << st.top();   // 30
st.pop();           // removes 30
```

### 🔥 Implement using vector

```cpp
vector<int> st;
st.push_back(10);      // push
st.pop_back();         // pop
int topv = st.back();  // top
```

### 🔥 Classic Problem - Balanced Parentheses

> Input: `"{[()]}"` → valid, `"(])"` → invalid

```cpp
bool isValid(string s){
  stack<char> st;
  for(char c : s){
    if (c == '(' || c == '[' || c == '{') st.push(c);
    else {
      if (st.empty()) return false;
      char top = st.top(); st.pop();
      if ((c == ')' && top != '(') ||
          (c == ']' && top != '[') ||
          (c == '}' && top != '{')) return false;
    }
  }
  return st.empty();
}
```

### 🔥 Monotonic Stack

> Stack that always keeps elements in increasing (or decreasing) order.
> Example - **Next Greater Element (NGE)** to the right.

```
arr = [4, 5, 2, 6]
NGE = [5, 6, 6, -1]
```

```cpp
vector<int> nextGreater(vector<int>& a){
  int n = a.size();
  vector<int> res(n, -1);
  stack<int> st;
  for (int i = n-1; i >= 0; i--){
    while (!st.empty() && a[st.top()] <= a[i]) st.pop();
    if (!st.empty()) res[i] = a[st.top()];
    st.push(i);
  }
  return res;
}
```

### 🎯 Applications

- Recursion (function calls / call stack)
- Undo / Redo, Browser Back
- Expression evaluation (infix → postfix)
- Reversing a list / string

</details>

<a id="queue"></a>

<details>
<summary><b>🚗 QUEUE &amp; DEQUE (FIFO)</b></summary>

### 🔥 Queue

**First In First Out** - like a line of people. Insert at rear, remove from front.

| Operation | STL         | Complexity |
| --------- | ----------- | ---------- |
| Push      | `q.push(x)` | O(1)       |
| Pop       | `q.pop()`   | O(1)       |
| Front     | `q.front()` | O(1)       |
| Back      | `q.back()`  | O(1)       |

```cpp
queue<int> q;
q.push(1); q.push(2); q.push(3);
cout << q.front();   // 1
q.pop();             // now front is 2
```

### 🔥 Circular Queue (concept)

Uses array with **modulo arithmetic** so the rear wraps around:

```cpp
rear = (rear + 1) % size;
front = (front + 1) % size;
```

Reuses space by wrapping around instead of shifting.

### 🔥 Deque (Double Ended Queue)

```cpp
deque<int> dq;
dq.push_back(1);   dq.push_front(2);
dq.pop_back();     dq.pop_front();
// O(1) both operations - "deque"
```

### 🔥 Priority Queue (implemented by Heap)

```cpp
priority_queue<int> mx;   // max-heap
priority_queue<int, vector<int>, greater<int>> mn;  // min-heap
mx.push(5); mx.push(1); mx.push(3);
cout << mx.top();    // 5
```

### 🎯 Applications

- BFS (graph traversal)
- CPU scheduling, printers, OS tasks
- Sliding window max - deque
- Dijkstra uses min-heap (priority_queue)

</details>

<a id="tree"></a>

<details>
<summary><b>🌳 TREE &amp; BST</b></summary>

### 🔥 What is a Tree ?

A **hierarchical** structure with nodes connected by edges. One **root**, children below.

| Term           | Meaning                        |
| -------------- | ------------------------------ |
| Root           | top node                       |
| Node           | element                        |
| Edge           | connector                      |
| Leaf           | node with zero children        |
| Parent / Child | direct relationship            |
| Depth          | edges from root                |
| Height         | longest path from node to leaf |

### 🔥 Binary Tree

Each node has at **most 2 children** (called left & right).

```cpp
struct Node {
  int data;
  Node* left;
  Node* right;
  Node(int val) : data(val), left(nullptr), right(nullptr) {}
};
```

### 🔥 Types

| Type                 | Property                                 |
| -------------------- | ---------------------------------------- |
| Full Binary Tree     | every node has 0 or 2 children           |
| Complete Binary Tree | all levels filled except last (all left) |
| Perfect Binary Tree  | all leaves same depth                    |
| BST                  | left < node < right                      |

### 🔥 Binary Search Tree (BST)

> For every node: **left subtree < node < right subtree** (smaller left, bigger right)

- Search : if key == root → found; if key < root → left (else right)
- Complexity: O(log n) average, O(n) worst (skewed tree)

```
         8
       /   \
      3     10
     / \      \
    1   6      14
```

**Search 6:** 8(>) → left 3(<) → right 6 ✅ (visited only 3 nodes!)

```cpp
bool searchBST(Node* root, int key){
  if (root == nullptr) return false;
  if (root->data == key) return true;
  if (key < root->data) return searchBST(root->left, key);
  return searchBST(root->right, key);
}
```

**Insert**

```cpp
Node* insertBST(Node* root, int val){
  if (!root) return new Node(val);
  if (val < root->data) root->left = insertBST(root->left, val);
  else root->right = insertBST(root->right, val);
  return root;
}
```

**Delete - 3 cases**

1. Leaf → delete directly
2. One child → replace with child
3. Two children → replace with in-order successor (smallest in right subtree)

### 🔥 Traversals

| Traversal   | Order            | Use                       |
| ----------- | ---------------- | ------------------------- |
| In-order    | L → Root → R     | get sorted array from BST |
| Pre-order   | Root → L → R     | serialize, copy tree      |
| Post-order  | L → R → Root     | delete tree               |
| Level-order | ROW by row (BFS) | shortest path in tree     |

```cpp
void inorder(Node* root){
  if (!root) return;
  inorder(root->left);
  cout << root->data << " ";
  inorder(root->right);
}
```

### 🔥 Balanced BST / AVL Tree

- Difference between left & right height from any node ≤ 1
- Rotations (LL, LR, RR, RL) restore balance after insert/delete
- Guarantees **O(log n)** always

> 📝 NOTE : `std::map`, `std::set` in C++ are balanced BSTs (Red-Black tree) internally.

### 🎯 Applications

- File explorer (hierarchy of files)
- Databases (BST indexes)
- Syntax trees in compilers
- Heap (see below) is a complete binary tree

</details>

<a id="heap"></a>

<details>
<summary><b>⛏ HEAP</b></summary>

### 🔥 What is a Heap?

A **complete binary tree** stored in an **array** where the heap property is maintained:

- **Max Heap**: parent ≥ children → root = LARGEST
- **Min Heap**: parent ≤ children → root = SMALLEST

### 🔥 Array Storage

If node index = i then:

| Relation    | Index     |
| ----------- | --------- |
| left child  | 2\*i + 1  |
| right child | 2\*i + 2  |
| parent      | (i-1) / 2 |

### 🔥 Operations

| Operation     | Complexity              |
| ------------- | ----------------------- |
| Peek (top)    | O(1)                    |
| Insert (push) | O(log n) → bubble up    |
| Pop root      | O(log n) → heapify down |

### 🔥 Insert - Bubble Up (min-heap example)

```cpp
void insertHeap(vector<int>& h, int val){
  h.push_back(val);
  int i = h.size() - 1;
  while (i > 0 && h[i] < h[(i-1)/2]){
    swap(h[i], h[(i-1)/2]);
    i = (i-1) / 2;
  }
}
```

### 🔥 Delete Root - Heapify Down

```cpp
void heapify(vector<int>& h, int n, int i){ // assume i violates property
  int smallest = i;
  int l = 2*i + 1, r = 2*i + 2;
  if (l < n && h[l] < h[smallest]) smallest = l;
  if (r < n && h[r] < h[smallest]) smallest = r;
  if (smallest != i){
    swap(h[i], h[smallest]);
    heapify(h, n, smallest);
  }
}
```

### 🔥 Build Heap in O(n)

Start from last non-leaf node, heapify downwards:

```cpp
for (int i = n/2 - 1; i >= 0; i--)
  heapify(h, n, i);
```

### 🔥 C++ STL

```cpp
priority_queue<int> maxheap;                       // max-heap
priority_queue<int, vector<int>, greater<int>> mn; // min-heap
```

### 🎯 Applications

- **Heap Sort** (see Sorting below)
- K largest / smallest elements (heap of size K)
- Median of stream (2 heaps)
- Dijkstra's, prim's algorithm

</details>

<a id="hashing"></a>

<details>
<summary><b>🗄 HASHING (HASH TABLE)</b></summary>

### 🔥 Idea

Map **keys → values** using a **hash function** → access nearly **O(1)**.

```
hash("apple")  →  5
hash("mango")  →  1
```

### 🔥 Key Terms

| Term          | Meaning                     |
| ------------- | --------------------------- |
| Hash function | key → index                 |
| Bucket        | a slot / list at that index |
| Collision     | two keys map to same index  |
| Load factor   | keys / table size           |

### 🔥 Handling Collisions

**1. Chaining** - each bucket stores a linked list:

```cpp
vector<list<int>> table(size);
```

**2. Open Addressing** - probe next free slot:

- Linear: `(hash + 1) % size`
- Quadratic: `(hash + i*i) % size`

### 🔥 C++ Hash Containers

```cpp
unordered_map<string, int> m;   // O(1) avg for insert/delete/find
unordered_set<int> st;
map<string, int> ordered;       // balanced tree - O(log n), sorted
```

### 🎯 Applications

- Counting frequency of elements
- Two Sum (map num → index)
- Detect duplicates in O(n)
- Caching (LRU)
- Avoiding a large boolean array (sparse)

</details>

<a id="graph"></a>

<details>
<summary><b>🌐 GRAPHS - Definition &amp; Representation</b></summary>

### 🔥 What is a Graph ?

- A Graph `G(V, E)` - Set of **vertices** V + **edges** E connecting pairs.

| Term      | Meaning                              |
| --------- | ------------------------------------ |
| Vertex    | node                                 |
| Edge      | line                                 |
| Degree    | number of edges touching vertex      |
| Path      | sequence of connected vertices       |
| Cycle     | path starting and ending same vertex |
| Connected | every two vertices connected         |
| Component | maximal connected subgraph           |

### 🔥 Types of Graph

| Type       | Description                  |
| ---------- | ---------------------------- |
| Directed   | edges have direction (A → B) |
| Undirected | no direction                 |
| Weighted   | edges have cost              |
| Unweighted | edges equal unit             |

### 🔥 Representations

**1. Adjacency Matrix - `vector<vector<int>>` O(V²)**

```cpp
vector<vector<int>> adj(V, vector<int>(V, 0));
adj[u][v] = 1;   // edge u→v  (weight instead of 1 if weighted)
// find edge: O(1) - check adj[u][v]
```

**2. Adjacency List - most common, O(V + E)**

```cpp
vector<vector<int>> adj(V);
adj[u].push_back(v);
adj[v].push_back(u);   // omit if directed
```

**3. Edge List - sorted weights, Kruskal prefers**

```cpp
vector<pair<int, int>> edges;
edges.push_back({u, v});
```

### 🔥 Which one to use?

|            | Matrix | List   | Edge List |
| ---------- | ------ | ------ | --------- |
| Space      | O(V²)  | O(V+E) | O(E)      |
| Check edge | O(1)   | O(deg) | O(E)      |
| Traversal  | O(V²)  | O(V+E) | greedy    |

- Graphs usually **sparse → adjacency list**
- Floyd–Warshall wants matrix

</details>

<br>
<hr>
<br>

## 🐦‍🔥 **PART 2 - ALGORITHMS**

<br>
<a id="searching"></a>
<details>
<summary><b>🔍 SEARCHING ALGORITHMS</b></summary>

### 🔥 Linear Search - O(n)

Check every element one by one.

```cpp
for (int i = 0; i < n; i++)
  if (arr[i] == key) return i;
return -1;
```

### 🔥 Binary Search - O(log n)

Only on **sorted array**. Check the middle & **discard half** each step.

```
Search key = 7 in [1, 3, 5, 7, 9, 11] (n = 6)
mid = 3 → arr[3] = 7 ✅ found at once (best case)
```

```cpp
int binarySearch(int a[], int l, int r, int key){
  while (l <= r){
    int mid = l + (r - l) / 2;
    if (a[mid] == key) return mid;
    if (a[mid] < key) l = mid + 1;
    else r = mid - 1;
  }
  return -1;
}
```

### 🔥 First / Last Occurrence (BS on range)

```cpp
// First occurrence
int firstOcc(int a[], int n, int key){
  int l = 0, r = n-1, ans = -1;
  while (l <= r){
    int mid = (l + r) / 2;
    if (a[mid] == key){ ans = mid; r = mid - 1; }
    else if (a[mid] < key) l = mid + 1;
    else r = mid - 1;
  }
  return ans;
}
// Last → move l = mid + 1 when found
```

### 🔥 Binary Search on Answer (Monotonic Predicate)

When we can `check(mid)` - pick bigger / smaller answer:

```cpp
int best = 0, l = 0, r = 1e6;
while (l <= r){
  int mid = (l + r) / 2;
  if (f(mid)){ best = mid; l = mid + 1; }
  else r = mid - 1;
}
// Example: sqrt-like, book allocation, minimum cut capacity
```

### 🎯 Applications

- Searching in sorted array
- Finding square root / division without `sqrt`
- "Binary Search on answer" problems - fixed split points

</details>

<a id="recursion"></a>

<details>
<summary><b>🔄 RECURSION &amp; BACKTRACKING</b></summary>

### 🔥 What is Recursion?

A function calling **itself** to solve a smaller instance of the same problem, until a **base case** stops it.

### 🔥 Factorial - `n!`

```
fact(5) = 5 × fact(4)
        = 5 × 4 × fact(3) ... = 120
```

```cpp
int fact(int n){
  if (n <= 1) return 1;         // base case
  return n * fact(n - 1);       // recursive case
}
```

### 🔥 Fibonacci - without memo (⚠ exponential)

```cpp
int fib(int n){
  if (n <= 1) return n;
  return fib(n-1) + fib(n-2);   // duplicates recomputed → DP needed (see DP section)
}
```

### 🔥 Two ingredients of recursion

1. **Base case** - stop condition
2. **Recursive call** - smaller sub-problem

### 🔥 Call Stack

```
fact(3)
├─ fact(2)
│  ├─ fact(1) → 1
│  └─ 2 * 1 = 2
└─ 3 * 2 = 6
```

### 🤺 Backtracking (Systematic Recursion)

Try all candidates; **undo** at dead end - e.g. N-Queens, Sudoku, subset generation.

**N-Queens** - place N queens on N×N board, no two attack each other.

```cpp
int cnt = 0, N;
bool col[20], d1[20], d2[20];

void solve(int row){
  if (row == N){ cnt++; return; }
  for (int c = 0; c < N; c++){
    if (col[c] || d1[row+c] || d2[row-c+N-1]) continue;
    col[c] = d1[row+c] = d2[row-c+N-1] = true;
    solve(row + 1);
    col[c] = d1[row+c] = d2[row-c+N-1] = false;   // BACKTRACK
  }
}
```

> 💡 Diagonals have constant `row + col` (\) and `row - col` (/) → use arrays to check O(1).

</details>

<a id="two-pointers"></a>

<details>
<summary><b>🧮 TWO POINTERS &amp; SLIDING WINDOW</b></summary>

### 🔥 Two Pointers - sorted pair sum

Input sorted array, find pair summing to target:

```cpp
bool pairSum(vector<int>& a, int target){
  int l = 0, r = a.size() - 1;
  while (l < r){
    int sum = a[l] + a[r];
    if (sum == target) return true;
    else if (sum < target) l++;
    else r--;
  }
  return false;
}
// [1, 2, 3, 4, 6], target 8 → l=0,r=5: 1+6=7<8 l++
//   l=1: 2+6=8 ✅
```

### 🔥 Sliding Window - Fixed Size K

Max sum of every subarray of size k - slide the window:

```cpp
int maxSubarrayK(vector<int>& a, int k){
  int sum = 0;
  for (int i = 0; i < k; i++) sum += a[i];
  int best = sum;
  for (int i = k; i < a.size(); i++){
    sum += a[i] - a[i-k];      // slide: add new, remove old
    best = max(best, sum);
  }
  return best;
}
// [2,1,5,1,3,2] k=3 → 9 (window 5,1,3)
```

### 🔥 Sliding Window - Variable (Longest substring no repeat)

```cpp
int longestUnique(string s){
  unordered_set<char> st;
  int l = 0, ans = 0;
  for (int r = 0; r < s.size(); r++){
    while (st.count(s[r])) st.erase(s[l++]);
    st.insert(s[r]);
    ans = max(ans, r - l + 1);
  }
  return ans;
}
// "abcabcbb" → 3 ("abc")
```

### 🎯 When to use

- Sorted array → two pointers
- Contiguous subarray / substring → sliding window
- Window can grow & shrink → variable window

</details>

<a id="prefix"></a>

<details>
<summary><b>➕ PREFIX SUM &amp; DIFFERENCE ARRAY</b></summary>

### 🔥 Prefix Sum

Pre-compute array so that **range sum** becomes O(1):

```
arr = [2, 4, 6, 3]
pre = [2, 6, 12, 15]
sum(1, 3) = pre[3] - pre[0] = 15 - 2 = 13  ✓ (4+6+3)
```

```cpp
vector<int> pre(n);
pre[0] = arr[0];
for (int i = 1; i < n; i++)
  pre[i] = pre[i-1] + arr[i];

int rangeSum(int l, int r){
  return pre[r] - (l ? pre[l-1] : 0);
}
```

### 🔥 Difference Array

Perform **many additions** on a range in O(n):

```
Add 5 to [1, 3], add 3 to [2, 4]:
diff[1] += 5;  diff[4] -= 5;
diff[2] += 3;  diff[5] -= 3;
```

```cpp
vector<int> diff(n+1, 0);
// per operation:
diff[l] += x;  diff[r+1] -= x;
// final array
for (int i = 0; i < n; i++)
  arr[i] = (i ? arr[i-1] : 0) + diff[i];
```

### 🎯 Applications

- Range sum queries - static
- Subarray sum equals K - prefix + hashmap
- Sweep-line range cover problems
- Count of prefix sums in range

</details>

<a id="greedy"></a>

<details>
<summary><b>📈 GREEDY ALGORITHM</b></summary>

### 🔥 What is Greedy ?

Make the **best local choice** at each step → hope for globally optimum solution.

> ⚠️ Greedy is NOT always optimal - only correct when the choice at each step can't worse the final result (exchange argument / proof needed).

### 🔥 Example 1 - Activity Selection

The **maximum number** of non-overlapping activities.

Greedy: **sort by end time**, pick the earliest finishing, then next compatible.

```
Intervals: (1,4) (3,5) (0,6) (5,7) (6,9) (8,10)
Sorted by end → pick (1,4) → (5,7) → (8,10) = 3 ✓ optimal
```

```cpp
struct Activity { int start, end; };
sort(acts.begin(), acts.end(), [](Activity& a, Activity& b){ return a.end < b.end; });
int count = 1, lastEnd = acts[0].end;
for (int i = 1; i < acts.size(); i++)
  if (acts[i].start >= lastEnd){
    count++;
    lastEnd = acts[i].end;
  }
```

### 🔥 Example 2 - Fractional Knapsack

Item values vs weight - take highest **value/weight** ratio, cut last item (fraction allowed):

```
Items: (w, v) = (10, 60) (20, 100) (30, 120)  capacity = 50
Ratio = 6, 5, 4 → take all 1,2 (30kg, 160) then fraction 20/30 of 3 → +80 → 240
```

### 🎯 Applications

- Job scheduling, Huffman coding (min freq first)
- Coin change (only canonical coins → greedy optimal)
- Dijkstra & Prim are greedy on graphs
- Minimum number of jumps

</details>

<a id="kadane"></a>

<details>
<summary><b>📌 KADANE'S ALGORITHM - MAX SUBARRAY SUM</b></summary>

> **Idea**: if the running sum becomes negative, adding it to future elements will only decrease the max - so reset it to 0 and start anew.
> 🔸 keep adding every element to `sum`
> 🔸 update `maxSum = max(maxSum, sum)`
> 🔸 if `sum < 0` → `sum = 0`

```cpp
vector<int> a = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
int sum = 0, maxSum = INT_MIN;
for (int x : a){
  sum += x;
  maxSum = max(maxSum, sum);
  if (sum < 0) sum = 0;
}
cout << maxSum << endl;   // 6 → subarray [4, -1, 2, 1]
```

**Complexity:** O(n) time, O(1) space

### 🔥 Variant - Max circular subarray

Max(circular) = max(normal, totalSum - minSubarraySum)

</details>

<a id="dp"></a>

<details>
<summary><b>🧠 DYNAMIC PROGRAMMING (DP)</b></summary>

### 🔥 What is Dynamic Programming ?

Breaking a problem into **overlapping subproblems** and storing the solution to each subproblem, **reuse** instead of recompute → huge speed-up.

### 🔥 When to use DP?

- Problem can be broken into subproblems
- **Overlapping subproblems** → same small problem computed many times
- **Optimal substructure** → best solution from optimal sub-solutions

```
Fibonacci:  F(5) = F(4) + F(3)
           F(4) = F(3) + F(2)  → F(3) computed twice (once per) - wasted!
```

### 🔥 Techniques

**1) Top-Down (Memoization) - recursion + storage**

```cpp
vector<int> memo(1000, -1);
int fib(int n){
  if (n <= 1) return n;
  if (memo[n] != -1) return memo[n];   // already computed?
  return memo[n] = fib(n-1) + fib(n-2); // compute & store
}
```

**2) Bottom-Up (Tabulation) - iterative array**

```cpp
int fib(int n){
  vector<int> dp(n+1);
  dp[0] = 0; dp[1] = 1;
  for (int i = 2; i <= n; i++)
    dp[i] = dp[i-1] + dp[i-2];
  return dp[n];
}
```

> Tabulation → also memory-optimizable: only last 2 needed → O(1) space.

### 🔥 Classic DP - 0/1 Knapsack

> Items {weight, value}; each **once**; max value with capacity W.

```
Weight  Value:  (3, 40), (2, 30), (4, 50)   → W = 5 → max = 70 (items 2+1)
```

```cpp
vector<vector<int>> dp(n+1, vector<int>(W+1, 0));
for (int i = 1; i <= n; i++)
  for (int w = 0; w <= W; w++){
    int skip = dp[i-1][w];
    int take = (weight <= w) ? value[i-1] + dp[i-1][w - weight[i-1]] : 0;
    dp[i][w] = max(skip, take);
  }
// answer = dp[n][W]
```

### 🔥 Classic - Longest Common Subsequence (LCS)

> "ABCBDAB" vs "BDCAB" → LCS = "BCDB"…Length 4 (any LCS)

```cpp
int lcs(string s1, string s2){
  int n = s1.size(), m = s2.size();
  vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (s1[i-1] == s2[j-1])
        dp[i][j] = dp[i-1][j-1] + 1;
      else
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
  return dp[n][m];
}
```

### 🔥 Longest Increasing Subsequence (LIS) - O(n²)

```cpp
vector<int> dp(n, 1);   // 1 = only itself
for (int i = 1; i < n; i++)
  for (int j = 0; j < i; j++)
    if (arr[j] < arr[i])
      dp[i] = max(dp[i], dp[j] + 1);
// answer = max(dp) - O(n²)
// [10, 9, 2, 5, 3, 7, 101] → 4 (2,3,7,101)
```

### 🔥 DP vs Greedy

- Greedy - one local decision, no look-back → not always optimal
- DP - considers both take/skip → always optimal

### 🎯 Common DP patterns

| Pattern    | Example                                 |
| ---------- | --------------------------------------- |
| 1D DP      | Fibonacci, Climbing stairs, Coin change |
| 2D DP      | LCS, Edit Distance, Knapsack            |
| Grid DP    | Unique Paths, Min path sum              |
| Tree DP    | Diameter, max independent set           |
| Bitmask DP | TSP, subset problems                    |

</details>

<a id="graph-algos"></a>

<details>
<summary><b>🌐 GRAPH ALGORITHMS</b></summary>

### 🔥 Breadth First Search (BFS) - queue, level order

> Visit all neighbors, then neighbors of neighbors...

```cpp
void bfs(int src, vector<vector<int>>& g, vector<bool>& vis){
  queue<int> q;
  q.push(src); vis[src] = true;
  while (!q.empty()){
    int u = q.front(); q.pop();
    cout << u << " ";
    for (int v : g[u])
      if (!vis[v]){
        vis[v] = true;
        q.push(v);
      }
  }
}
```

- Finds **shortest path** in unweighted graph (levels)
- Graph : connected components, bipartite check

### 🔥 Depth First Search (DFS) - recursion / stack

```cpp
void dfs(int u, vector<vector<int>>& g, vector<bool>& vis){
  vis[u] = true;
  cout << u << " ";
  for (int v : g[u])
    if (!vis[v]) dfs(v, g, vis);
}
```

> 📝 Recursion uses implicit stack internally.

### 🔥 Topological Sort - DAG only

Ordering where every edge `u → v` has u **before** v. Only for Directed **Acyclic** Graph.

**Kahn's algorithm (BFS + indegree)**

```cpp
// find indegree of each node (how many incoming edges)
queue<int> q;
for (int i = 0; i < n; i++)
  if (indegree[i] == 0) q.push(i);

vector<int> topo;
while (!q.empty()){
  int u = q.front(); q.pop();
  topo.push_back(u);
  for (int v : g[u]){
    if (--indegree[v] == 0)
      q.push(v);
  }
}
// if topo.size() != n → there was a cycle
```

**DFS method** - finish each node, then push reversed.

### 🔥 Shortest Path - Dijkstra (weighted, no neg)

```cpp
using PII = pair<int, int>;
vector<int> dijkstra(int src, vector<vector<PII>>& g){
  int n = g.size();
  vector<int> dist(n, INT_MAX);
  dist[src] = 0;
  priority_queue<PII, vector<PII>, greater<PII>> pq;
  pq.push({0, src});
  while (!pq.empty()){
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;
    for (auto [v, w] : g[u])
      if (dist[v] > dist[u] + w){
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
      }
  }
  return dist;
}
```

- O((V+E) log V) - priority queue

### 🔥 Bellman-Ford (negative weights, detects −ve cycle)

Relax all E edges `V-1` times:

```
relax: if dist[v] > dist[u] + w → update
E × (V-1) → O(V·E); extra relaxation detects negative cycle
```

### 🔥 Floyd–Warshall (all pairs) O(V³)

```cpp
for (int k = 0; k < V; k++)
  for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++)
      dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
```

### 🔥 Minimum Spanning Tree (MST) - Kruskal & Prim

**Kruskal** - sort all edges by weight, add smallest that doesn't make a cycle (needs DSU).

**Prim** - start from a vertex, keep adding the smallest edge apart.

Both O(E log E).

### 🔥 Disjoint Set Union (DSU) - with path compression

```cpp
vector<int> parent;

int find(int a){
  return parent[a] == a ? a : parent[a] = find(parent[a]); // path compression
}

void union(int a, int b){
  a = find(a); b = find(b);
  if (a == b) return;
  parent[b] = a;            // could use rank/size join
}
```

Applications: connected components, cycle detection, Kruskal.

</details>

<a id="string"></a>

<details>
<summary><b>🔤 STRING ALGORITHMS</b></summary>

### 🔥 Palindrome Check

```cpp
bool isPalindrome(string s){
  int l = 0, r = s.size() - 1;
  while (l < r)
    if (s[l++] != s[r--]) return false;
  return true;
}
// "racecar" → true
```

### 🔥 Counting / Frequency - O(n)

```cpp
int freq[26] = {};
for (char c : s) freq[c - 'a']++;
```

- Anagrams: s1 and s2 → same frequencies ✓

### 🔥 Pattern Search - Naive O(n·m)

### 🔥 KMP - O(n+m) using LPS (longest proper prefix-suffix)

```
Pattern: "ABABC"   LPS: [0,0,1,2,0]
On mismatch → jump to lps[key] instead of restarting
```

```cpp
vector<int> buildLPS(string p){
  int m = p.size();
  vector<int> lps(m);
  for (int len = 0, i = 1; i < m;){
    if (p[i] == p[len]) lps[i++] = ++len;
    else if (len) len = lps[len-1];
    else lps[i++] = 0;
  }
  return lps;
}
```

### 🔥 Rabin-Karp (hashing) - avg O(n+m)

Hash of pattern & every substring; compare only on hash match:

### 🎯 Applications

- Palindromic substrings (Manacher's O(n))
- Distinct substrings with suffix automaton/trie
- Pattern search in text editor - problem input files

</details>

<a id="math"></a>

<details>
<summary><b>🧮 NUMBER THEORY &amp; MATH</b></summary>

### 🔥 GCD - Euclid's algorithm

```cpp
int gcd(int a, int b){
  return b == 0 ? a : gcd(b, a % b);
}
// gcd(48, 18) → gcd(18, 12) → gcd(12, 6) → 6
```

### 🔥 LCM

```
lcm(a, b) = (a / gcd(a, b)) * b
```

### 🔥 Prime Test - O(√n)

```cpp
bool isPrime(int n){
  if (n < 2) return false;
  for (int i = 2; i * i <= n; i++)
    if (n % i == 0) return false;
  return true;
}
```

### 🔥 Sieve of Eratosthenes - all primes ≤ n in O(n log log n)

```cpp
vector<bool> sieve(int n){
  vector<bool> prime(n+1, true);
  prime[0] = prime[1] = false;
  for (int p = 2; p * p <= n; p++)
    if (prime[p])
      for (int m = p * p; m <= n; m += p)
        prime[m] = false;
  return prime;
}
```

### 🔥 Modular Fast Power - `(a^b) % mod` in O(log b)

```cpp
long long modPow(long long a, long long b, long long mod){
  long long res = 1;
  while (b){
    if (b & 1) res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}
// 2^10 = 1024
```

### 🔥 Fast Multiplication (doubling)

`n * 7 = (n << 3) - n`

### 🎯 applications

- Counting problems - prime factorization
- Geometry - gcd/lcm, lattice
- Hash functions - big prime bases
</details>

<a id="bitmanip"></a>

<details>

<summary><b> 🔥 BIT MANIPULATION</b></summary>

### 🔥 What is Bit Manipulation?

Working directly on **bits of integers** using bitwise operators - extremely fast (O(1) hardware ops), saves memory, huge interview topic.

### 🔥 Bitwise Operators

| Op   | Name        | Rule                      | Example (5 & 3)        |
| ---- | ----------- | ------------------------- | ---------------------- |
| `&`  | AND         | 1 only if both 1          | `101 & 011 = 001 = 1`  |
| `\|` | OR          | 1 if any 1                | `101 \| 011 = 111 = 7` |
| `^`  | XOR         | 1 if **differ**           | `101 ^ 011 = 110 = 6`  |
| `~`  | NOT         | flip all                  | `~5 = -6` (2's comp.)  |
| `<<` | Left shift  | multiply by 2<sup>k</sup> | `5 << 1 = 10`          |
| `>>` | Right shift | divide by 2               | `10 >> 1 = 5`          |

### 🔥 Powers of Two

```
1<<0=1, 1<<1=2, 1<<2=4, 1<<3=8, 1<<4=16, ...
One left shift by k = multiply by 2^k
```

### 🔥 THE TRICKS

#### 1. Check even / odd

```cpp
n & 1      // 1 → odd, 0 → even
```

#### 2. Check kth bit

```cpp
(n >> k) & 1;  // n = 11 (1011), k = 1
// (n >> k) & 1 = 0101 & 1 = 1
```

#### 3. Set kth bit

```cpp
n | (1 << k);
```

#### 4. Clear kth bit

```cpp
n & ~(1 << k);
```

#### 5. Toggle kth bit

```cpp
n ^ (1 << k);
```

#### 6. Power of 2 check

```cpp
n > 0 && (n & (n - 1)) == 0;
```

#### 7. Counting set bits - Kernighan

```cpp
int cnt = 0;
while (n){
  n &= n - 1;   // removes the last set bit
  cnt++;
}
// builtin: __builtin_popcount(n)
```

#### 8. Isolate lowest set bit

```cpp
n & -n;
// e.g. 12 (00001100) & -12 (11110100) → 4 (00000100)
```

#### 9. Remove lowest set bit

```cpp
n & (n-1);   // 12 → 8
```

#### 10. XOR swap (no temp)

```cpp
a ^= b; b ^= a; a ^= b;  // Provided &a, &b are different
```

#### 11. Find missing number (1..n)

```cpp
int xr = 0;
for (int i = 1; i <= n; i++) xr ^= i;
for (int x : arr) xr ^= x;
return xr;      // the missing one
```

#### 12. Find single number (everyone appears twice)

```cpp
int xr = 0;
for (int x : arr) xr ^= x;   // pairs cancel → remaining
```

#### 13. Two unique numbers - split by rightmost set of XOR

```
xor = a ^ b   → find rightmost set bit → or what makes them differ →
split array into two groups by that bit, XOR each
```

#### 14. Count flips to convert a→b

```cpp
__builtin_popcount(a ^ b);
```

#### 15. Multiply / divide by 2

```cpp
n << 1,  n >> 1;
```

### 🔥 XOR Properties - the GEM

| Property      | Result              |
| ------------- | ------------------- |
| a ^ a = 0     | cancels with itself |
| a ^ 0 = a     | identity            |
| a ^ b = b ^ a | commutative         |
| a ^ b ^ a = b | remove-duplicate    |

### 🔥 Generate All Subsets Using Bitmask

A set of `n` elements has `2ⁿ` subsets. Use each bit of `mask` to represent whether an element is included.

```cpp
for (int mask = 0; mask < (1 << n); mask++) {
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            // include element i
        }
    }
}
```

**Time:** `O(n × 2ⁿ)`

- `bit i = 1` → include `element[i]`
- `bit i = 0` → exclude `element[i]`
- `1 << n` = `2ⁿ` → generates all subsets

### 🎯 Practice problems

| #   | Problem          | Trick         |
| --- | ---------------- | ------------- |
| 136 | Single Number    | XOR           |
| 191 | Hamming weight   | popcount      |
| 231 | Power of Two     | n&(n-1)       |
| 461 | Hamming Distance | popcount(a^b) |
| 260 | Single num III   | group XOR     |
| 78  | Subsets          | bitmask       |

</details>

<a id="sorting"></a>

<details >
<summary><b>🃏 SORTING ALGORITHMS</b></summary>

### 🔥 Complexity Summary Sheet

| Sort      | Avg      | Worst    | Space   | Stable |
| --------- | -------- | -------- | ------- | ------ |
| Bubble    | O(n²)    | O(n²)    | O(1)    | ✅     |
| Selection | O(n²)    | O(n²)    | O(1)    | ❌     |
| Insertion | O(n²)    | O(n²)    | O(1)    | ✅     |
| Merge     | O(nlogn) | O(nlogn) | O(n)    | ✅     |
| Quick     | O(nlogn) | O(n²)    | O(logn) | ❌     |
| Heap      | O(nlogn) | O(nlogn) | O(1)    | ❌     |
| Counting  | O(n+k)   | O(n+k)   | O(k)    | ✅     |
| Radix     | O(k·n)   | O(k·n)   | O(n+k)  | ✅     |

### 🫧 Bubble Sort - compare adjacent, swap

```cpp
for (int i = 0; i < n; i++)
  for (int j = 0; j < n - i - 1; j++)
    if (arr[j] > arr[j+1])
      swap(arr[j], arr[j+1]);   // bubble largest to end
```

### Selection Sort - pick minimum to right position

```cpp
for (int i = 0; i < n-1; i++){
  int minIdx = i;
  for (int j = i+1; j < n; j++)
    if (arr[j] < arr[minIdx]) minIdx = j;
  swap(arr[i], arr[minIdx]);
}
```

### Insertion Sort - insert into sorted part

```cpp
for (int i = 1; i < n; i++){
  int key = arr[i], j = i-1;
  while (j >= 0 && arr[j] > key){
    arr[j+1] = arr[j];
    j--;
  }
  arr[j+1] = key;
}
```

### Merge Sort - divide & conquer (stable)

```cpp
void merge(int arr[], int l, int m, int r){
  int n1 = m-l+1, n2 = r-m;
  int L[n1], R[n2];
  for (int i = 0; i < n1; i++) L[i] = arr[l+i];
  for (int j = 0; j < n2; j++) R[j] = arr[m+1+j];
  int i=0, j=0, k=l;
  while (i<n1 && j<n2){
    if (L[i] <= R[j]) arr[k++] = L[i++];
    else arr[k++] = R[j++];
  }
  while (i<n1) arr[k++] = L[i++];
  while (j<n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r){
  if (l >= r) return;
  int mid = l + (r-l)/2;
  mergeSort(arr, l, mid);
  mergeSort(arr, mid+1, r);
  merge(arr, l, mid, r);
}
```

### Quick Sort - pivot partition

```cpp
int partition(int arr[], int low, int high){
  int pivot = arr[high];
  int i = low-1;
  for (int j = low; j < high; j++){
    if (arr[j] < pivot){
      i++;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i+1], arr[high]);
  return i+1;
}

void quickSort(int arr[], int low, int high){
  if (low < high){
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi-1);
    quickSort(arr, pi+1, high);
  }
}
```

### Heap Sort - max-heap + extract

```cpp
void heapify(vector<int>& a, int n, int i){
  int big = i, l = 2*i+1, r = 2*i+2;
  if (l < n && a[l] > a[big]) big = l;
  if (r < n && a[r] > a[big]) big = r;
  if (big != i){
    swap(a[i], a[big]);
    heapify(a, n, big);
  }
}

void heapSort(vector<int>& a){
  int n = a.size();
  for (int i = n/2-1; i >= 0; i--) heapify(a, n, i);
  for (int i = n-1; i > 0; i--){
    swap(a[0], a[i]);
    heapify(a, i, 0);
  }
}
```

### Counting Sort - 0..k range

```cpp
vector<int> count(k+1, 0);
for (int x : arr) count[x]++;
int idx = 0;
for (int i = 0; i <= k; i++)
  while (count[i]--) arr[idx++] = i;
```

### Radix Sort - digit by digit with stable counting

```cpp
// for each digit exp = 1, 10, 100 ...
// counting sort on (arr[i]/exp) % 10, repeat
```

### 📝 When to use which

- n small → insertion (fast & stable)
- large & memory-ok → merge
- n large, in-place → heap sort
- integer range small → counting/radix

</details>

<a id="advanced"></a>

<details>
<summary><b>🎯 ADVANCED - SEGMENT TREE &amp; FENWICK</b></summary>

### 🔥 When you need them?

**Point update + range query** (sum, max, gcd) many times → each O(log n) instead of O(n).

### 🔥 Segment Tree (concept)

Array is stored in a tree - leaves = elements, parents = function of children.

```
    16            [1..4]
   /   \
  /     \
[1..2]  [3..4]
 1  3    5  7    → sum tree
```

```cpp
class SegTree {
  vector<int> tree;
 public:
  SegTree(vector<int>& a){
    tree.resize(4 * a.size());
    build(a, 1, 0, a.size()-1);
  }
  void build(vector<int>& a, int node, int l, int r){
    if (l == r){ tree[node] = a[l]; return; }
    int mid = (l+r)/2;
    build(a, node*2, l, mid);
    build(a, node*2+1, mid+1, r);
    tree[node] = tree[node*2] + tree[node*2+1];
  }
  int query(int node, int l, int r, int ql, int qr){
    if (qr < l || r < ql) return 0;          // no overlap
    if (ql <= l && r <= qr) return tree[node]; // full overlap
    int mid = (l+r)/2;
    return query(node*2, l, mid, ql, qr)
         + query(node*2+1, mid+1, r, ql, qr);
  }
  void update(int node, int l, int r, int idx, int val){
    if (l == r){ tree[node] = val; return; }
    int mid = (l+r)/2;
    if (idx <= mid) update(node*2, l, mid, idx, val);
    else update(node*2+1, mid+1, r, idx, val);
    tree[node] = tree[node*2] + tree[node*2+1];
  }
};
```

### 🔥 Fenwick (Fenwick/BIT) - simplest for sum

```cpp
class Fenwick {                       // 1-indexed internally
  vector<int> bit;
  int n;
 public:
  Fenwick(int sz){ n = sz; bit.assign(n + 1, 0); }
  void add(int idx, int val){
    for (int i = idx; i <= n; i += i & -i)
      bit[i] += val;
  }
  long long sum(int idx){
    long long s = 0;
    for (int i = idx; i > 0; i -= i & -i)
      s += bit[i];
    return s;
  }
};
```

> Root trick: `idx & -idx` → lowest set bit - moves up (add) / down (sum) the tree.

### 🎯 Applications

- Range sum with point updates (net: like DP)
- Count of smaller numbers to right (merge-fenwick)
- 2D BIT for grids

---

**Ready for the next milestone? More topics (AVL detail, Trie, LCA, flows). Ask → I'll expand any topic.**

</details>

<br>
<hr>

> 📝 **NOTE to self** : This file is a living document - edit freely, but keep the accordion layout + the 🔥 heading style.

</div>
</div>
