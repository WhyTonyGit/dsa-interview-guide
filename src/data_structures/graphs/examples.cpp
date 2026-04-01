/**
 * @file examples.cpp
 * @brief Graph traversals, BFS, DFS, Dijkstra, topological sort examples.
 */

#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#include "data_structures/graphs/graph.hpp"

void demo_undirected_graph() {
    std::cout << "\n=== Undirected Graph — BFS & DFS ===\n";
    Graph<int> g(false);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 5);

    auto bfs = g.bfs(0);
    std::cout << "BFS from 0: [";
    for (std::size_t i = 0; i < bfs.size(); ++i)
        std::cout << bfs[i] << (i+1 < bfs.size() ? "," : "");
    std::cout << "]\n";

    auto dfs = g.dfs(0);
    std::cout << "DFS from 0: [";
    for (std::size_t i = 0; i < dfs.size(); ++i)
        std::cout << dfs[i] << (i+1 < dfs.size() ? "," : "");
    std::cout << "]\n";

    auto dist = g.bfs_distances(0);
    std::cout << "Distances from 0: 0→" << dist[0] << " 3→" << dist[3] << " 5→" << dist[5] << "\n";
    std::cout << "Connected components: " << g.connected_components() << "\n";
}

void demo_directed_graph() {
    std::cout << "\n=== Directed Graph — Topological Sort ===\n";
    // Courses: 0 requires no prereq, 1 requires 0, 2 requires 0, 3 requires 1+2
    Graph<int> g(true);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 3);

    auto topo = g.topological_sort();
    std::cout << "Topological order: [";
    for (std::size_t i = 0; i < topo.size(); ++i)
        std::cout << topo[i] << (i+1 < topo.size() ? "," : "");
    std::cout << "]  (0 must come before 1,2; both before 3)\n";
    std::cout << "Has cycle: " << (g.has_cycle_directed() ? "true" : "false")
              << "  (expected false)\n";
}

void demo_dijkstra() {
    std::cout << "\n=== Dijkstra Shortest Path ===\n";
    Graph<int> g(true);
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 1);
    g.add_edge(2, 1, 2);
    g.add_edge(1, 3, 1);
    g.add_edge(2, 3, 5);

    auto dist = g.dijkstra(0);
    std::cout << "Shortest path from 0:\n";
    std::cout << "  0→0: " << dist[0] << "\n";
    std::cout << "  0→1: " << dist[1] << "  (expected 3: 0→2→1)\n";
    std::cout << "  0→2: " << dist[2] << "  (expected 1)\n";
    std::cout << "  0→3: " << dist[3] << "  (expected 4: 0→2→1→3)\n";
}

// Number of Islands (grid DFS)
int numIslands(std::vector<std::vector<char>> grid) {
    if (grid.empty()) return 0;
    int rows = grid.size(), cols = grid[0].size(), count = 0;
    std::function<void(int, int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') return;
        grid[r][c] = '0';
        dfs(r+1,c); dfs(r-1,c); dfs(r,c+1); dfs(r,c-1);
    };
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (grid[r][c] == '1') { dfs(r, c); ++count; }
    return count;
}

void demo_number_of_islands() {
    std::cout << "\n=== Number of Islands ===\n";
    std::vector<std::vector<char>> grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    std::cout << "numIslands = " << numIslands(grid) << "  (expected 3)\n";
}

int main() {
    demo_undirected_graph();
    demo_directed_graph();
    demo_dijkstra();
    demo_number_of_islands();
    return 0;
}
