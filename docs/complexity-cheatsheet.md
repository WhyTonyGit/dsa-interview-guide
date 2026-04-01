# Big-O Complexity Cheatsheet

## Data Structure Operations

| Structure | Access | Search | Insert | Delete | Space |
|-----------|--------|--------|--------|--------|-------|
| Array (dynamic) | O(1) | O(n) | O(1)* | O(n) | O(n) |
| Linked List (singly) | O(n) | O(n) | O(1)† | O(1)† | O(n) |
| Stack | O(n) | O(n) | O(1) | O(1) | O(n) |
| Queue | O(n) | O(n) | O(1) | O(1) | O(n) |
| Hash Table | N/A | O(1)* | O(1)* | O(1)* | O(n) |
| BST (balanced) | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| BST (unbalanced) | O(n) | O(n) | O(n) | O(n) | O(n) |
| AVL Tree | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| Red-Black Tree | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| Binary Heap | O(1)‡ | O(n) | O(log n) | O(log n) | O(n) |
| Trie | N/A | O(m) | O(m) | O(m) | O(n·m) |
| Union-Find | N/A | O(α(n))§ | O(α(n))§ | N/A | O(n) |

> \* = amortized  
> † = with pointer to node  
> ‡ = peek (min or max only)  
> § = inverse Ackermann — effectively O(1)

---

## Sorting Algorithms

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | No |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No |
| Counting Sort | O(n+k) | O(n+k) | O(n+k) | O(k) | Yes |
| Radix Sort | O(nk) | O(nk) | O(nk) | O(n+k) | Yes |
| Tim Sort | O(n) | O(n log n) | O(n log n) | O(n) | Yes |

---

## Graph Algorithms

| Algorithm | Time | Space | Use Case |
|-----------|------|-------|----------|
| BFS | O(V + E) | O(V) | Shortest path (unweighted) |
| DFS | O(V + E) | O(V) | Connectivity, cycles, topological sort |
| Dijkstra | O((V+E) log V) | O(V) | Shortest path (non-negative weights) |
| Bellman-Ford | O(V·E) | O(V) | Shortest path (negative weights) |
| Floyd-Warshall | O(V³) | O(V²) | All-pairs shortest path |
| Prim's MST | O((V+E) log V) | O(V) | Minimum spanning tree |
| Kruskal's MST | O(E log E) | O(V) | Minimum spanning tree |
| Topological Sort | O(V + E) | O(V) | DAG ordering |
| Tarjan's SCC | O(V + E) | O(V) | Strongly connected components |

---

## C++ STL Container Complexity

### `std::vector<T>`

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| `push_back` | O(1) amortized | O(n) on reallocation |
| `pop_back` | O(1) | |
| `operator[]` | O(1) | No bounds check |
| `at()` | O(1) | Bounds-checked |
| `insert(pos, val)` | O(n) | Shifts elements |
| `erase(pos)` | O(n) | Shifts elements |
| `find` (via algorithm) | O(n) | |
| `sort` | O(n log n) | |

### `std::list<T>` (doubly linked list)

| Operation | Complexity |
|-----------|-----------|
| `push_front` / `push_back` | O(1) |
| `pop_front` / `pop_back` | O(1) |
| `insert(iter, val)` | O(1) |
| `erase(iter)` | O(1) |
| Random access | O(n) |

### `std::deque<T>`

| Operation | Complexity |
|-----------|-----------|
| `push_front` / `push_back` | O(1) amortized |
| `operator[]` | O(1) |
| `insert(middle)` | O(n) |

### `std::map<K,V>` / `std::set<T>` (Red-Black Tree)

| Operation | Complexity |
|-----------|-----------|
| `insert` | O(log n) |
| `erase` | O(log n) |
| `find` | O(log n) |
| `lower_bound` | O(log n) |
| Iteration | O(n) |

### `std::unordered_map<K,V>` / `std::unordered_set<T>` (Hash Table)

| Operation | Average | Worst |
|-----------|---------|-------|
| `insert` | O(1) | O(n) |
| `erase` | O(1) | O(n) |
| `find` | O(1) | O(n) |

### `std::priority_queue<T>` (Max-Heap by default)

| Operation | Complexity |
|-----------|-----------|
| `push` | O(log n) |
| `pop` | O(log n) |
| `top` | O(1) |

---

## Space Complexity Quick Reference

| Algorithm / Structure | Space |
|-----------------------|-------|
| Recursive DFS depth | O(h) — tree height |
| BFS queue | O(w) — max tree width |
| DP memoization table | O(n) or O(n²) |
| Merge sort stack | O(log n) |
| Quicksort stack | O(log n) avg, O(n) worst |

---

## Common Recurrences (Master Theorem)

| Recurrence | Example | Result |
|------------|---------|--------|
| T(n) = 2T(n/2) + O(n) | Merge Sort | O(n log n) |
| T(n) = 2T(n/2) + O(1) | Binary Search tree | O(n) |
| T(n) = T(n/2) + O(1) | Binary Search | O(log n) |
| T(n) = T(n-1) + O(1) | Linear recursion | O(n) |
| T(n) = 2T(n-1) + O(1) | Fibonacci (naive) | O(2ⁿ) |
