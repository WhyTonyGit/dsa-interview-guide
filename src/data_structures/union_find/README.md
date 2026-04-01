# Union-Find (Disjoint Set Union)

Union-Find tracks a partition of n elements into disjoint sets. Two key operations — **find** (which set does x belong to?) and **union** (merge two sets) — run in effectively O(1) with path compression and union by rank.

## Operations & Complexity

| Operation | Time | Notes |
|-----------|------|-------|
| find(x) | O(α(n)) | α = inverse Ackermann ≈ O(1) |
| unite(x, y) | O(α(n)) | |
| connected(x, y) | O(α(n)) | |
| component_size | O(α(n)) | |
| num_components | O(1) | |
| Space | O(n) | |

## ✅ When to Use

- Detect cycles in undirected graphs
- Number of connected components
- Minimum Spanning Tree (Kruskal's algorithm)
- "Friend circles" / social network connectivity
- Grid connectivity problems (dynamic)

## ❌ When NOT to Use

- Need to **split** a set (Union-Find is union-only)
- Directed graph connectivity → use DFS/BFS
- Need to list all members of a set efficiently

## 📊 Interview Frequency

- **50%** at Google, Amazon, and others
- Commonly appears as part of graph/MST problems
- Medium difficulty

## C++ Usage

```cpp
UnionFind uf(n);

// Connect nodes
uf.unite(0, 1);
uf.unite(1, 2);

// Check connectivity
uf.connected(0, 2);  // true
uf.connected(0, 3);  // false

// Component info
uf.num_components();      // number of disjoint sets
uf.component_size(0);     // size of 0's component
```

See [patterns.md](patterns.md) for interview applications.
