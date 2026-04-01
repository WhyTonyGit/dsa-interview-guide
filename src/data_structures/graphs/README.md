# Graphs

A graph G = (V, E) is a set of vertices V connected by edges E. Graphs model relationships: road networks, social connections, dependency trees, web links, etc.

## Representations

| Representation | Space | Edge lookup | Neighbor iteration | Best for |
|---------------|-------|-------------|-------------------|---------|
| Adjacency List | O(V+E) | O(degree) | O(degree) | Sparse graphs ✅ |
| Adjacency Matrix | O(V²) | O(1) | O(V) | Dense graphs |
| Edge List | O(E) | O(E) | O(E) | Kruskal's MST |

## Key Algorithms

| Algorithm | Time | Space | Use Case |
|-----------|------|-------|---------|
| BFS | O(V+E) | O(V) | Shortest path (unweighted), level-by-level |
| DFS | O(V+E) | O(V) | Connectivity, cycle detection, topological sort |
| Dijkstra | O((V+E) log V) | O(V) | Shortest path (non-negative weights) |
| Bellman-Ford | O(V·E) | O(V) | Negative edge weights |
| Topological Sort | O(V+E) | O(V) | DAG task ordering |
| Union-Find | O(α(V)) per op | O(V) | Connected components, Kruskal's |

## ✅ When to Use

- Modeling pairwise relationships
- Finding paths, connectivity, distances
- Scheduling with dependencies (topological sort)
- Social networks, web crawling, maps

## ❌ When NOT to Use

- Data is strictly hierarchical (no cross-edges) → use tree
- Relationships are key-value → use hash map

## 📊 Interview Frequency

- **75%** at Google, Meta, Uber, LinkedIn
- Almost always **Medium to Hard** difficulty
- BFS/DFS appear in disguise in many tree/grid problems

## Common Graph Patterns

| Pattern | Algorithm | Examples |
|---------|-----------|---------|
| Shortest unweighted path | BFS | Word Ladder, Rotting Oranges |
| Number of islands | DFS/BFS | Number of Islands |
| Cycle detection | DFS coloring or Union-Find | Course Schedule |
| Topological order | Kahn's BFS | Course Schedule II |
| Shortest weighted path | Dijkstra | Network Delay Time |
| Minimum spanning tree | Kruskal's + Union-Find | Connecting Cities |

See [patterns.md](patterns.md) for implementations.
