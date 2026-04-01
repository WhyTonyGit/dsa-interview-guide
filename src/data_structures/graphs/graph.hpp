#pragma once

#include <functional>
#include <limits>
#include <optional>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/**
 * @file graph.hpp
 * @brief Graph represented as adjacency list with BFS, DFS, Dijkstra, and more.
 *
 * @tparam T Vertex type (typically int for interview problems).
 */
template <typename T>
class Graph {
 public:
  /**
   * @brief Construct an empty directed/undirected graph.
   * @param directed If true, edges are one-way (directed).
   */
  explicit Graph(bool directed = false) : directed_(directed) {}

  // ─── Modification ─────────────────────────────────────────────────────────

  /**
   * @brief Add a vertex (no-op if already exists).
   */
  void add_vertex(const T& v) {
    adj_[v];  // default-insert empty list
  }

  /**
   * @brief Add an (optionally weighted) edge from u to v.
   * @complexity O(1) amortized
   */
  void add_edge(const T& u, const T& v, int weight = 1) {
    adj_[u].push_back({v, weight});
    if (!directed_) adj_[v].push_back({u, weight});
    // Ensure v has an entry even if no out-edges
    adj_[v];
  }

  std::size_t vertex_count() const { return adj_.size(); }

  const std::vector<std::pair<T, int>>& neighbors(const T& v) const {
    return adj_.at(v);
  }

  // ─── BFS ──────────────────────────────────────────────────────────────────

  /**
   * @brief BFS from source. Calls visitor for each visited vertex.
   * @return Order in which vertices are visited.
   * @complexity O(V + E)
   */
  std::vector<T> bfs(const T& source) const {
    std::unordered_set<T> visited;
    std::queue<T> q;
    std::vector<T> order;

    q.push(source);
    visited.insert(source);
    while (!q.empty()) {
      T cur = q.front(); q.pop();
      order.push_back(cur);
      for (const auto& [nbr, _w] : adj_.at(cur)) {
        if (!visited.count(nbr)) {
          visited.insert(nbr);
          q.push(nbr);
        }
      }
    }
    return order;
  }

  /**
   * @brief BFS shortest path distances from source (unweighted).
   * @return Map from vertex to distance (-1 = unreachable).
   * @complexity O(V + E)
   */
  std::unordered_map<T, int> bfs_distances(const T& source) const {
    std::unordered_map<T, int> dist;
    for (const auto& [v, _] : adj_) dist[v] = -1;
    dist[source] = 0;
    std::queue<T> q;
    q.push(source);
    while (!q.empty()) {
      T cur = q.front(); q.pop();
      for (const auto& [nbr, _w] : adj_.at(cur)) {
        if (dist[nbr] == -1) {
          dist[nbr] = dist[cur] + 1;
          q.push(nbr);
        }
      }
    }
    return dist;
  }

  // ─── DFS ──────────────────────────────────────────────────────────────────

  /**
   * @brief DFS from source (recursive).
   * @return Order in which vertices are visited.
   * @complexity O(V + E)
   */
  std::vector<T> dfs(const T& source) const {
    std::unordered_set<T> visited;
    std::vector<T> order;
    dfs_helper(source, visited, order);
    return order;
  }

  /**
   * @brief Detect cycle in undirected graph.
   * @complexity O(V + E)
   */
  bool has_cycle_undirected() const {
    std::unordered_set<T> visited;
    for (const auto& [v, _] : adj_) {
      if (!visited.count(v)) {
        if (dfs_cycle_undirected(v, T{}, visited)) return true;
      }
    }
    return false;
  }

  /**
   * @brief Detect cycle in directed graph (coloring method).
   * @complexity O(V + E)
   */
  bool has_cycle_directed() const {
    // 0=white, 1=gray (in stack), 2=black (done)
    std::unordered_map<T, int> color;
    for (const auto& [v, _] : adj_) color[v] = 0;
    for (const auto& [v, _] : adj_) {
      if (color[v] == 0)
        if (dfs_cycle_directed(v, color)) return true;
    }
    return false;
  }

  /**
   * @brief Topological sort (Kahn's algorithm, BFS-based).
   * @return Topological order, or empty vector if cycle exists.
   * @complexity O(V + E)
   */
  std::vector<T> topological_sort() const {
    std::unordered_map<T, int> in_degree;
    for (const auto& [v, _] : adj_) in_degree[v] = 0;
    for (const auto& [v, nbrs] : adj_)
      for (const auto& [nbr, _w] : nbrs) in_degree[nbr]++;

    std::queue<T> q;
    for (const auto& [v, deg] : in_degree)
      if (deg == 0) q.push(v);

    std::vector<T> order;
    while (!q.empty()) {
      T cur = q.front(); q.pop();
      order.push_back(cur);
      for (const auto& [nbr, _w] : adj_.at(cur)) {
        if (--in_degree[nbr] == 0) q.push(nbr);
      }
    }
    return order.size() == adj_.size() ? order : std::vector<T>{};
  }

  /**
   * @brief Connected components count (for undirected graphs).
   * @complexity O(V + E)
   */
  int connected_components() const {
    std::unordered_set<T> visited;
    int count = 0;
    for (const auto& [v, _] : adj_) {
      if (!visited.count(v)) {
        dfs_mark(v, visited);
        ++count;
      }
    }
    return count;
  }

  /**
   * @brief Dijkstra's shortest path from source (non-negative weights).
   * @return Map from vertex to minimum distance (INT_MAX = unreachable).
   * @complexity O((V + E) log V)
   */
  std::unordered_map<T, int> dijkstra(const T& source) const {
    std::unordered_map<T, int> dist;
    for (const auto& [v, _] : adj_) dist[v] = std::numeric_limits<int>::max();
    dist[source] = 0;

    using PII = std::pair<int, T>;
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
      auto [d, u] = pq.top(); pq.pop();
      if (d > dist[u]) continue;  // stale entry
      for (const auto& [v, w] : adj_.at(u)) {
        if (dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
          pq.push({dist[v], v});
        }
      }
    }
    return dist;
  }

 private:
  // ─── Helpers ──────────────────────────────────────────────────────────────

  void dfs_helper(const T& v, std::unordered_set<T>& visited,
                  std::vector<T>& order) const {
    visited.insert(v);
    order.push_back(v);
    for (const auto& [nbr, _w] : adj_.at(v))
      if (!visited.count(nbr)) dfs_helper(nbr, visited, order);
  }

  bool dfs_cycle_undirected(const T& v, const T& parent,
                             std::unordered_set<T>& visited) const {
    visited.insert(v);
    for (const auto& [nbr, _w] : adj_.at(v)) {
      if (!visited.count(nbr)) {
        if (dfs_cycle_undirected(nbr, v, visited)) return true;
      } else if (nbr != parent) {
        return true;
      }
    }
    return false;
  }

  bool dfs_cycle_directed(const T& v,
                           std::unordered_map<T, int>& color) const {
    color[v] = 1;
    for (const auto& [nbr, _w] : adj_.at(v)) {
      if (color[nbr] == 1) return true;
      if (color[nbr] == 0 && dfs_cycle_directed(nbr, color)) return true;
    }
    color[v] = 2;
    return false;
  }

  void dfs_mark(const T& v, std::unordered_set<T>& visited) const {
    visited.insert(v);
    for (const auto& [nbr, _w] : adj_.at(v))
      if (!visited.count(nbr)) dfs_mark(nbr, visited);
  }

  std::unordered_map<T, std::vector<std::pair<T, int>>> adj_;
  bool directed_;
};
