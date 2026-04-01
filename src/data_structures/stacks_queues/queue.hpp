#pragma once

#include <deque>
#include <stdexcept>
#include <unordered_map>
#include <vector>

/**
 * @file queue.hpp
 * @brief Queue (FIFO) and Deque implementations.
 */

// ─── Queue (circular buffer) ──────────────────────────────────────────────────

/**
 * @brief FIFO Queue implemented as a circular buffer (ring buffer).
 *
 * Provides O(1) amortized enqueue and O(1) dequeue without element shifting.
 *
 * @tparam T Element type.
 */
template <typename T>
class Queue {
 public:
  explicit Queue(std::size_t initial_capacity = 8)
      : data_(initial_capacity), head_(0), tail_(0), size_(0) {}

  /**
   * @brief Add element to the back.
   * @complexity O(1) amortized
   */
  void enqueue(const T& value) {
    if (size_ == data_.size()) grow();
    data_[tail_] = value;
    tail_ = (tail_ + 1) % data_.size();
    ++size_;
  }

  /**
   * @brief Remove and return element from the front.
   * @throws std::underflow_error if empty.
   * @complexity O(1)
   */
  T dequeue() {
    if (empty()) throw std::underflow_error("Queue::dequeue — queue is empty");
    T val = data_[head_];
    head_ = (head_ + 1) % data_.size();
    --size_;
    return val;
  }

  /**
   * @brief Return element at the front without removing it.
   * @throws std::underflow_error if empty.
   */
  const T& front() const {
    if (empty()) throw std::underflow_error("Queue::front — queue is empty");
    return data_[head_];
  }

  T& front() {
    if (empty()) throw std::underflow_error("Queue::front — queue is empty");
    return data_[head_];
  }

  bool        empty() const noexcept { return size_ == 0; }
  std::size_t size()  const noexcept { return size_; }

 private:
  void grow() {
    std::vector<T> new_data(data_.size() * 2);
    for (std::size_t i = 0; i < size_; ++i)
      new_data[i] = data_[(head_ + i) % data_.size()];
    head_   = 0;
    tail_   = size_;
    data_   = std::move(new_data);
  }

  std::vector<T> data_;
  std::size_t    head_;
  std::size_t    tail_;
  std::size_t    size_;
};

// ─── Queue using Two Stacks ───────────────────────────────────────────────────

#include "stack.hpp"

/**
 * @brief FIFO Queue implemented with two stacks.
 *
 * Classic interview question: "Implement a queue using two stacks."
 * Amortized O(1) enqueue and dequeue.
 *
 * @tparam T Element type.
 */
template <typename T>
class QueueWithTwoStacks {
 public:
  /**
   * @brief Enqueue — always push to inbox stack.
   * @complexity O(1)
   */
  void enqueue(const T& value) { inbox_.push(value); }

  /**
   * @brief Dequeue — if outbox is empty, transfer all from inbox.
   * @complexity O(1) amortized — each element is moved at most once.
   */
  T dequeue() {
    if (empty()) throw std::underflow_error("QueueWithTwoStacks::dequeue — empty");
    if (outbox_.empty()) {
      while (!inbox_.empty()) {
        outbox_.push(inbox_.top());
        inbox_.pop();
      }
    }
    T val = outbox_.top();
    outbox_.pop();
    return val;
  }

  const T& front() {
    if (outbox_.empty()) {
      while (!inbox_.empty()) {
        outbox_.push(inbox_.top());
        inbox_.pop();
      }
    }
    return outbox_.top();
  }

  bool        empty() const noexcept { return inbox_.empty() && outbox_.empty(); }
  std::size_t size()  const noexcept { return inbox_.size() + outbox_.size(); }

 private:
  Stack<T> inbox_;
  Stack<T> outbox_;
};

// ─── Monotonic Queue (Deque) ──────────────────────────────────────────────────

/**
 * @brief Monotonic deque for sliding window maximum/minimum.
 *
 * Used in "Sliding Window Maximum" (LeetCode #239).
 * Stores indices; values are compared via a comparator.
 *
 * @tparam T    Element type.
 * @tparam Comp Comparator: std::greater<T> for max-queue, std::less<T> for min.
 */
template <typename T, typename Comp = std::greater<T>>
class MonotonicQueue {
 public:
  /**
   * @brief Add element at index i. Removes elements from back that violate monotonicity.
   */
  void push(int idx, const T& val) {
    while (!dq_.empty() && comp_(val, values_[dq_.back()])) dq_.pop_back();
    dq_.push_back(idx);
    values_[idx] = val;
  }

  /**
   * @brief Remove front if it's the element at index i (outside window).
   */
  void pop_if_front(int idx) {
    if (!dq_.empty() && dq_.front() == idx) dq_.pop_front();
  }

  /**
   * @brief Return the optimal element (max or min depending on Comp).
   */
  const T& front_val() const { return values_.at(dq_.front()); }

  bool empty() const noexcept { return dq_.empty(); }

 private:
  std::deque<int>          dq_;
  std::unordered_map<int, T> values_;
  Comp comp_;
};
