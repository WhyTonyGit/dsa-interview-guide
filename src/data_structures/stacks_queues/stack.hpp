#pragma once

#include <stdexcept>
#include <vector>

/**
 * @file stack.hpp
 * @brief Stack (LIFO) implemented on top of a dynamic array.
 *
 * @tparam T Element type.
 *
 * All operations are O(1) amortized.
 */
template <typename T>
class Stack {
 public:
  Stack() = default;

  /**
   * @brief Push an element onto the top.
   * @complexity O(1) amortized
   */
  void push(const T& value) { data_.push_back(value); }
  void push(T&& value)      { data_.push_back(std::move(value)); }

  /**
   * @brief Remove the top element.
   * @throws std::underflow_error if empty.
   * @complexity O(1)
   */
  void pop() {
    if (empty()) throw std::underflow_error("Stack::pop — stack is empty");
    data_.pop_back();
  }

  /**
   * @brief Return reference to top element.
   * @throws std::underflow_error if empty.
   * @complexity O(1)
   */
  T& top() {
    if (empty()) throw std::underflow_error("Stack::top — stack is empty");
    return data_.back();
  }
  const T& top() const {
    if (empty()) throw std::underflow_error("Stack::top — stack is empty");
    return data_.back();
  }

  bool        empty() const noexcept { return data_.empty(); }
  std::size_t size()  const noexcept { return data_.size(); }
  void        clear() noexcept       { data_.clear(); }

 private:
  std::vector<T> data_;
};

// ─── MinStack ─────────────────────────────────────────────────────────────────

/**
 * @brief Stack that supports O(1) minimum queries.
 *
 * Classic interview problem. Maintains a second stack tracking the
 * running minimum at each push level.
 *
 * @tparam T Element type (must support operator<).
 */
template <typename T>
class MinStack {
 public:
  void push(const T& value) {
    data_.push(value);
    if (min_stack_.empty() || value <= min_stack_.top())
      min_stack_.push(value);
  }

  void pop() {
    if (data_.top() == min_stack_.top()) min_stack_.pop();
    data_.pop();
  }

  T& top() { return data_.top(); }

  /**
   * @brief Return the minimum element currently in the stack.
   * @complexity O(1)
   */
  const T& getMin() const { return min_stack_.top(); }

  bool        empty() const noexcept { return data_.empty(); }
  std::size_t size()  const noexcept { return data_.size(); }

 private:
  Stack<T> data_;
  Stack<T> min_stack_;
};
