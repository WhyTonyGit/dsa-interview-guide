#pragma once

#include <numeric>
#include <stdexcept>
#include <vector>

/**
 * @file union_find.hpp
 * @brief Union-Find (Disjoint Set Union) with path compression and union by rank.
 *
 * Supports:
 * - find(x): identify the representative (root) of x's component — O(α(n))
 * - unite(x, y): merge two components — O(α(n))
 * - connected(x, y): check if x and y are in the same component — O(α(n))
 *
 * α(n) = inverse Ackermann function — effectively constant (≤ 4 for n < 10^600)
 */
class UnionFind {
 public:
  /**
   * @brief Initialise n disjoint sets {0}, {1}, ..., {n-1}.
   * @complexity O(n)
   */
  explicit UnionFind(int n)
      : parent_(n), rank_(n, 0), size_(n, 1), components_(n) {
    if (n <= 0) throw std::invalid_argument("UnionFind: n must be positive");
    std::iota(parent_.begin(), parent_.end(), 0);  // parent[i] = i
  }

  /**
   * @brief Find the representative of x's component (with path compression).
   * @complexity O(α(n)) amortized
   */
  int find(int x) {
    validate(x);
    if (parent_[x] != x) parent_[x] = find(parent_[x]);  // path compression
    return parent_[x];
  }

  /**
   * @brief Merge the components containing x and y.
   * @return true if they were in different components (a merge happened).
   * @complexity O(α(n)) amortized
   */
  bool unite(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;  // already connected
    // Union by rank
    if (rank_[rx] < rank_[ry]) std::swap(rx, ry);
    parent_[ry] = rx;
    size_[rx] += size_[ry];
    if (rank_[rx] == rank_[ry]) ++rank_[rx];
    --components_;
    return true;
  }

  /**
   * @brief Returns true if x and y are in the same component.
   * @complexity O(α(n))
   */
  bool connected(int x, int y) { return find(x) == find(y); }

  /**
   * @brief Number of elements in x's component.
   * @complexity O(α(n))
   */
  int component_size(int x) { return size_[find(x)]; }

  /**
   * @brief Total number of disjoint components remaining.
   * @complexity O(1)
   */
  int num_components() const noexcept { return components_; }

  int total_elements() const noexcept { return static_cast<int>(parent_.size()); }

 private:
  void validate(int x) const {
    if (x < 0 || x >= static_cast<int>(parent_.size()))
      throw std::out_of_range("UnionFind: index out of range");
  }

  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> size_;
  int              components_;
};
