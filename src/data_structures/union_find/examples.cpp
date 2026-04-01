/**
 * @file examples.cpp
 * @brief Union-Find examples: connected components, cycles, MST.
 */

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include "data_structures/union_find/union_find.hpp"

void demo_basic() {
    std::cout << "\n=== Union-Find Basics ===\n";
    UnionFind uf(6);
    std::cout << "Initial components: " << uf.num_components() << "  (expected 6)\n";

    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(3, 4);

    std::cout << "After unite(0,1), unite(1,2), unite(3,4):\n";
    std::cout << "  Components: " << uf.num_components() << "  (expected 3)\n";
    std::cout << "  connected(0,2): " << (uf.connected(0,2) ? "true" : "false") << "\n";
    std::cout << "  connected(0,3): " << (uf.connected(0,3) ? "true" : "false") << "\n";
    std::cout << "  component_size(0): " << uf.component_size(0) << "  (expected 3)\n";
}

int countComponents(int n, const std::vector<std::vector<int>>& edges) {
    UnionFind uf(n);
    for (const auto& e : edges) uf.unite(e[0], e[1]);
    return uf.num_components();
}

std::vector<int> findRedundantConnection(const std::vector<std::vector<int>>& edges) {
    int n = static_cast<int>(edges.size());
    UnionFind uf(n + 1);
    for (const auto& e : edges)
        if (!uf.unite(e[0], e[1])) return e;
    return {};
}

int kruskal(int n, std::vector<std::tuple<int,int,int>> edges) {
    std::sort(edges.begin(), edges.end());
    UnionFind uf(n);
    int total = 0, used = 0;
    for (auto [w, u, v] : edges) {
        if (uf.unite(u, v)) { total += w; ++used; }
        if (used == n - 1) break;
    }
    return total;
}

int main() {
    demo_basic();

    std::cout << "\n=== Connected Components ===\n";
    std::vector<std::vector<int>> edges = {{0,1},{1,2},{3,4}};
    std::cout << "Components (n=5): " << countComponents(5, edges) << "  (expected 2)\n";

    std::cout << "\n=== Redundant Connection ===\n";
    std::vector<std::vector<int>> cycle_edges = {{1,2},{1,3},{2,3}};
    auto redundant = findRedundantConnection(cycle_edges);
    std::cout << "Redundant edge: [" << redundant[0] << "," << redundant[1] << "]"
              << "  (expected [2,3])\n";

    std::cout << "\n=== Kruskal MST ===\n";
    // 4 vertices, edges: (0,1,w1), (1,2,w2), ...
    std::vector<std::tuple<int,int,int>> mst_edges = {
        {1, 0, 1}, {2, 1, 2}, {3, 0, 2}, {4, 1, 3}, {5, 2, 3}
    };
    std::cout << "MST weight (4 nodes): " << kruskal(4, mst_edges)
              << "  (expected 6: edges 1+2+3)\n";

    return 0;
}
