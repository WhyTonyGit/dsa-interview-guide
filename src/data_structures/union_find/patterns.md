# Union-Find Interview Patterns

## Pattern 1: Number of Connected Components

```cpp
int countComponents(int n, const std::vector<std::vector<int>>& edges) {
    UnionFind uf(n);
    for (const auto& e : edges) uf.unite(e[0], e[1]);
    return uf.num_components();
}
```

## Pattern 2: Detect Cycle in Undirected Graph

```cpp
bool hasCycle(int n, const std::vector<std::vector<int>>& edges) {
    UnionFind uf(n);
    for (const auto& e : edges) {
        if (!uf.unite(e[0], e[1])) return true;  // already connected = cycle
    }
    return false;
}
```

## Pattern 3: Kruskal's Minimum Spanning Tree

```cpp
// edges = {weight, u, v}
int minSpanningTree(int n, std::vector<std::tuple<int,int,int>> edges) {
    std::sort(edges.begin(), edges.end());  // sort by weight
    UnionFind uf(n);
    int total_weight = 0;
    for (auto [w, u, v] : edges) {
        if (uf.unite(u, v)) total_weight += w;  // include edge
    }
    return total_weight;
}
```

## Pattern 4: Number of Islands II (Dynamic)

```cpp
// Add land cells one by one, query connected islands count after each
std::vector<int> numIslands2(int m, int n,
                              const std::vector<std::vector<int>>& positions) {
    UnionFind uf(m * n);
    std::vector<bool> is_land(m * n, false);
    std::vector<int> result;
    int islands = 0;
    const int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

    for (const auto& pos : positions) {
        int r = pos[0], c = pos[1];
        int cell = r * n + c;
        if (!is_land[cell]) {
            is_land[cell] = true;
            ++islands;
            for (const auto& d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                int ncell = nr * n + nc;
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && is_land[ncell]) {
                    if (uf.unite(cell, ncell)) --islands;
                }
            }
        }
        result.push_back(islands);
    }
    return result;
}
```

## Pattern 5: Redundant Connection (find the edge that creates a cycle)

```cpp
std::vector<int> findRedundantConnection(const std::vector<std::vector<int>>& edges) {
    int n = edges.size();
    UnionFind uf(n + 1);
    for (const auto& e : edges) {
        if (!uf.unite(e[0], e[1])) return e;  // this edge creates a cycle
    }
    return {};
}
```

## Common Interview Questions

| Question | Technique | Difficulty |
|----------|-----------|------------|
| Number of Connected Components | Union-Find | Medium |
| Redundant Connection | Cycle detection | Medium |
| Number of Islands II | Dynamic union-find | Hard |
| Friend Circles | Union-Find | Medium |
| Graph Valid Tree | n-1 edges + connected | Medium |
| Accounts Merge | Union by email | Medium |
| Minimum Spanning Tree | Kruskal's | Medium |
