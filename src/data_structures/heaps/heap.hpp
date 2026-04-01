#pragma once

#include <functional>
#include <stdexcept>
#include <vector>

/**
 * @file heap.hpp
 * @brief Generic binary heap (min-heap by default).
 *
 * @tparam T    Element type.
 * @tparam Comp Comparator: std::less<T> = min-heap, std::greater<T> = max-heap.
 */
template <typename T, typename Comp = std::less<T>>
class Heap {
 public:
  Heap() = default;

  /**
   * @brief Build heap from existing vector in O(n) — Floyd's algorithm.
   */
  explicit Heap(std::vector<T> data) : data_(std::move(data)) {
    // Start from last non-leaf and sift down each node
    for (int i = static_cast<int>(data_.size()) / 2 - 1; i >= 0; --i)
      sift_down(i);
  }

  // ─── Core operations ─────────────────────────────────────────────────────

  /**
   * @brief Insert an element.
   * @complexity O(log n)
   */
  void push(const T& value) {
    data_.push_back(value);
    sift_up(static_cast<int>(data_.size()) - 1);
  }

  /**
   * @brief Remove the top element (minimum for min-heap, maximum for max-heap).
   * @throws std::underflow_error if empty.
   * @complexity O(log n)
   */
  void pop() {
    if (empty()) throw std::underflow_error("Heap::pop — heap is empty");
    std::swap(data_.front(), data_.back());
    data_.pop_back();
    if (!empty()) sift_down(0);
  }

  /**
   * @brief Return the top element.
   * @throws std::underflow_error if empty.
   * @complexity O(1)
   */
  const T& top() const {
    if (empty()) throw std::underflow_error("Heap::top — heap is empty");
    return data_.front();
  }

  bool        empty() const noexcept { return data_.empty(); }
  std::size_t size()  const noexcept { return data_.size(); }

  /**
   * @brief Return all elements as a sorted vector (destructive).
   * @complexity O(n log n)
   */
  std::vector<T> sort() {
    std::vector<T> result;
    result.reserve(data_.size());
    while (!empty()) {
      result.push_back(top());
      pop();
    }
    return result;
  }

 private:
  // ─── Index helpers ────────────────────────────────────────────────────────

  static int parent(int i)       { return (i - 1) / 2; }
  static int left_child(int i)   { return 2 * i + 1; }
  static int right_child(int i)  { return 2 * i + 2; }

  // ─── Sift operations ──────────────────────────────────────────────────────

  /**
   * @brief Sift element at index i upward until heap property restored.
   */
  void sift_up(int i) {
    Comp comp;
    while (i > 0) {
      int p = parent(i);
      if (comp(data_[i], data_[p])) {
        std::swap(data_[i], data_[p]);
        i = p;
      } else break;
    }
  }

  /**
   * @brief Sift element at index i downward until heap property restored.
   */
  void sift_down(int i) {
    Comp comp;
    int n = static_cast<int>(data_.size());
    while (true) {
      int best = i;
      int lc = left_child(i);
      int rc = right_child(i);
      if (lc < n && comp(data_[lc], data_[best])) best = lc;
      if (rc < n && comp(data_[rc], data_[best])) best = rc;
      if (best == i) break;
      std::swap(data_[i], data_[best]);
      i = best;
    }
  }

  std::vector<T> data_;
};

// Type aliases for convenience
template <typename T>
using MinHeap = Heap<T, std::less<T>>;

template <typename T>
using MaxHeap = Heap<T, std::greater<T>>;

// ─── MedianFinder ─────────────────────────────────────────────────────────────

/**
 * @brief Streaming median using two heaps.
 *
 * Maintains a max-heap for the lower half and a min-heap for the upper half.
 * The median is always at the top of one or both heaps.
 *
 * LeetCode #295 — "Find Median from Data Stream"
 */
class MedianFinder {
 public:
  /**
   * @brief Add a number to the data stream.
   * @complexity O(log n)
   */
  void add_num(int num) {
    lower_.push(num);   // push to max-heap (lower half)
    // Balance: max of lower must be <= min of upper
    upper_.push(lower_.top());
    lower_.pop();
    // Ensure lower_ has same size or one more than upper_
    if (lower_.size() < upper_.size()) {
      lower_.push(upper_.top());
      upper_.pop();
    }
  }

  /**
   * @brief Return the current median.
   * @complexity O(1)
   */
  double find_median() const {
    if (lower_.size() > upper_.size())
      return static_cast<double>(lower_.top());
    return (static_cast<double>(lower_.top()) + upper_.top()) / 2.0;
  }

 private:
  MaxHeap<int> lower_;   // max-heap: lower half of numbers
  MinHeap<int> upper_;   // min-heap: upper half of numbers
};
