/**
 * @file test_graphs.cpp
 * @brief Unit tests for Graph: BFS, DFS, topological sort, Dijkstra.
 */

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

#include "data_structures/graphs/graph.hpp"

// ─── BFS Tests ────────────────────────────────────────────────────────────────

TEST(GraphTest, BFSOrder) {
    Graph<int> g(false);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    auto order = g.bfs(0);
    // 0 must come first
    EXPECT_EQ(order[0], 0);
    // All 4 vertices visited
    EXPECT_EQ(order.size(), 4u);
}

TEST(GraphTest, BFSDistances) {
    Graph<int> g(false);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    auto dist = g.bfs_distances(0);
    EXPECT_EQ(dist[0], 0);
    EXPECT_EQ(dist[1], 1);
    EXPECT_EQ(dist[2], 2);
    EXPECT_EQ(dist[3], 3);
}

// ─── DFS Tests ────────────────────────────────────────────────────────────────

TEST(GraphTest, DFSVisitsAll) {
    Graph<int> g(false);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    auto order = g.dfs(0);
    EXPECT_EQ(order.size(), 4u);
    // All vertices must appear
    for (int v : {0, 1, 2, 3}) {
        EXPECT_NE(std::find(order.begin(), order.end(), v), order.end());
    }
}

// ─── Cycle Detection ──────────────────────────────────────────────────────────

TEST(GraphTest, UndirectedNoCycle) {
    Graph<int> g(false);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    EXPECT_FALSE(g.has_cycle_undirected());
}

TEST(GraphTest, UndirectedHasCycle) {
    Graph<int> g(false);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    EXPECT_TRUE(g.has_cycle_undirected());
}

TEST(GraphTest, DirectedNoCycle) {
    Graph<int> g(true);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    EXPECT_FALSE(g.has_cycle_directed());
}

TEST(GraphTest, DirectedHasCycle) {
    Graph<int> g(true);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    EXPECT_TRUE(g.has_cycle_directed());
}

// ─── Topological Sort ─────────────────────────────────────────────────────────

TEST(GraphTest, TopologicalSortDAG) {
    Graph<int> g(true);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 3);
    auto order = g.topological_sort();
    EXPECT_EQ(order.size(), 4u);
    // 0 must come before 1 and 2; both before 3
    auto pos = [&](int v) {
        return std::find(order.begin(), order.end(), v) - order.begin();
    };
    EXPECT_LT(pos(0), pos(1));
    EXPECT_LT(pos(0), pos(2));
    EXPECT_LT(pos(1), pos(3));
    EXPECT_LT(pos(2), pos(3));
}

TEST(GraphTest, TopologicalSortCycleReturnsEmpty) {
    Graph<int> g(true);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    auto order = g.topological_sort();
    EXPECT_TRUE(order.empty());
}

// ─── Connected Components ─────────────────────────────────────────────────────

TEST(GraphTest, ConnectedComponents) {
    Graph<int> g(false);
    g.add_edge(0, 1);
    g.add_edge(2, 3);
    g.add_vertex(4);
    EXPECT_EQ(g.connected_components(), 3);
}

// ─── Dijkstra ─────────────────────────────────────────────────────────────────

TEST(GraphTest, DijkstraSimple) {
    Graph<int> g(true);
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 1);
    g.add_edge(2, 1, 2);
    g.add_edge(1, 3, 1);
    auto dist = g.dijkstra(0);
    EXPECT_EQ(dist[0], 0);
    EXPECT_EQ(dist[1], 3);  // 0→2→1
    EXPECT_EQ(dist[2], 1);
    EXPECT_EQ(dist[3], 4);  // 0→2→1→3
}
