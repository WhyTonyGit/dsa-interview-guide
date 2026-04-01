#pragma once

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <utility>

/**
 * @file array.hpp
 * @brief Dynamic array implementation (analogous to std::vector).
 *
 * Demonstrates the core ideas behind a growable array:
 * - Amortized O(1) push_back via doubling strategy
 * - O(1) random access
 * - RAII memory management
 */

/**
 * @brief A dynamic (resizable) array container with value semantics.
 *
 * @tparam T Element type. Must be copy-constructible and move-constructible.
 *
 * Invariants:
 *   size_    <= capacity_
 *   data_    points to a valid allocation of capacity_ elements (or nullptr if capacity_ == 0)
 */
template <typename T>
class DynamicArray {
 public:
  // ─── Types ────────────────────────────────────────────────────────────────
  using value_type      = T;
  using size_type       = std::size_t;
  using reference       = T&;
  using const_reference = const T&;
  using pointer         = T*;
  using const_pointer   = const T*;

  // ─── Iterators ────────────────────────────────────────────────────────────
  using iterator       = pointer;
  using const_iterator = const_pointer;

  // ─── Constructors / Destructor ────────────────────────────────────────────

  /**
   * @brief Default constructor — creates an empty array.
   * @complexity O(1)
   */
  DynamicArray() : data_(nullptr), size_(0), capacity_(0) {}

  /**
   * @brief Construct with initial size, default-initialised elements.
   * @complexity O(n)
   */
  explicit DynamicArray(size_type n)
      : data_(n ? new T[n]{} : nullptr), size_(n), capacity_(n) {}

  /**
   * @brief Construct with n copies of value.
   * @complexity O(n)
   */
  DynamicArray(size_type n, const T& value) : DynamicArray(n) {
    std::fill(data_, data_ + size_, value);
  }

  /**
   * @brief Construct from initializer list.
   * @complexity O(n)
   */
  DynamicArray(std::initializer_list<T> ilist)
      : data_(ilist.size() ? new T[ilist.size()] : nullptr),
        size_(ilist.size()),
        capacity_(ilist.size()) {
    std::copy(ilist.begin(), ilist.end(), data_);
  }

  /**
   * @brief Copy constructor — deep copy.
   * @complexity O(n)
   */
  DynamicArray(const DynamicArray& other)
      : data_(other.size_ ? new T[other.size_] : nullptr),
        size_(other.size_),
        capacity_(other.size_) {
    std::copy(other.data_, other.data_ + other.size_, data_);
  }

  /**
   * @brief Move constructor — steals resources.
   * @complexity O(1)
   */
  DynamicArray(DynamicArray&& other) noexcept
      : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_     = nullptr;
    other.size_     = 0;
    other.capacity_ = 0;
  }

  /**
   * @brief Copy assignment — copy-and-swap idiom.
   * @complexity O(n)
   */
  DynamicArray& operator=(DynamicArray other) noexcept {
    swap(*this, other);
    return *this;
  }

  /**
   * @brief Destructor.
   * @complexity O(1)
   */
  ~DynamicArray() { delete[] data_; }

  // ─── Element access ───────────────────────────────────────────────────────

  /**
   * @brief Unchecked element access.
   * @complexity O(1)
   */
  reference operator[](size_type idx) { return data_[idx]; }
  const_reference operator[](size_type idx) const { return data_[idx]; }

  /**
   * @brief Bounds-checked element access.
   * @throws std::out_of_range if idx >= size_
   * @complexity O(1)
   */
  reference at(size_type idx) {
    if (idx >= size_) throw std::out_of_range("DynamicArray::at — index out of range");
    return data_[idx];
  }
  const_reference at(size_type idx) const {
    if (idx >= size_) throw std::out_of_range("DynamicArray::at — index out of range");
    return data_[idx];
  }

  reference front() { return data_[0]; }
  const_reference front() const { return data_[0]; }
  reference back() { return data_[size_ - 1]; }
  const_reference back() const { return data_[size_ - 1]; }
  pointer data() { return data_; }
  const_pointer data() const { return data_; }

  // ─── Capacity ─────────────────────────────────────────────────────────────

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  size_type capacity() const noexcept { return capacity_; }

  /**
   * @brief Reserve space for at least n elements to avoid future reallocations.
   * @complexity O(n) — copies existing elements to new allocation
   */
  void reserve(size_type n) {
    if (n <= capacity_) return;
    T* new_data = new T[n];
    std::move(data_, data_ + size_, new_data);
    delete[] data_;
    data_     = new_data;
    capacity_ = n;
  }

  /**
   * @brief Shrink internal buffer to fit exactly size_ elements.
   * @complexity O(n)
   */
  void shrink_to_fit() {
    if (size_ == capacity_) return;
    T* new_data = size_ ? new T[size_] : nullptr;
    std::move(data_, data_ + size_, new_data);
    delete[] data_;
    data_     = new_data;
    capacity_ = size_;
  }

  // ─── Modifiers ────────────────────────────────────────────────────────────

  /**
   * @brief Append an element to the end.
   * @complexity O(1) amortized — O(n) when reallocation occurs
   */
  void push_back(const T& value) {
    if (size_ == capacity_) grow();
    data_[size_++] = value;
  }

  void push_back(T&& value) {
    if (size_ == capacity_) grow();
    data_[size_++] = std::move(value);
  }

  /**
   * @brief Construct element in-place at the end.
   * @complexity O(1) amortized
   */
  template <typename... Args>
  reference emplace_back(Args&&... args) {
    if (size_ == capacity_) grow();
    data_[size_] = T(std::forward<Args>(args)...);
    return data_[size_++];
  }

  /**
   * @brief Remove the last element.
   * @complexity O(1)
   */
  void pop_back() {
    if (size_ == 0) throw std::underflow_error("DynamicArray::pop_back — array is empty");
    --size_;
  }

  /**
   * @brief Insert value at position idx, shifting subsequent elements.
   * @complexity O(n)
   */
  void insert(size_type idx, const T& value) {
    if (idx > size_) throw std::out_of_range("DynamicArray::insert — index out of range");
    if (size_ == capacity_) grow();
    std::move_backward(data_ + idx, data_ + size_, data_ + size_ + 1);
    data_[idx] = value;
    ++size_;
  }

  /**
   * @brief Erase element at position idx, shifting subsequent elements.
   * @complexity O(n)
   */
  void erase(size_type idx) {
    if (idx >= size_) throw std::out_of_range("DynamicArray::erase — index out of range");
    std::move(data_ + idx + 1, data_ + size_, data_ + idx);
    --size_;
  }

  /**
   * @brief Remove all elements (does not free memory).
   * @complexity O(1)
   */
  void clear() noexcept { size_ = 0; }

  // ─── Iterators ────────────────────────────────────────────────────────────
  iterator begin() noexcept { return data_; }
  iterator end() noexcept { return data_ + size_; }
  const_iterator begin() const noexcept { return data_; }
  const_iterator end() const noexcept { return data_ + size_; }
  const_iterator cbegin() const noexcept { return data_; }
  const_iterator cend() const noexcept { return data_ + size_; }

  // ─── Utilities ────────────────────────────────────────────────────────────

  /**
   * @brief Reverse elements in-place.
   * @complexity O(n)
   */
  void reverse() { std::reverse(data_, data_ + size_); }

  /**
   * @brief Sort elements ascending.
   * @complexity O(n log n)
   */
  void sort() { std::sort(data_, data_ + size_); }

  /**
   * @brief Linear search. Returns index or npos if not found.
   * @complexity O(n)
   */
  static constexpr size_type npos = static_cast<size_type>(-1);

  size_type find(const T& value) const {
    for (size_type i = 0; i < size_; ++i)
      if (data_[i] == value) return i;
    return npos;
  }

  friend void swap(DynamicArray& a, DynamicArray& b) noexcept {
    using std::swap;
    swap(a.data_, b.data_);
    swap(a.size_, b.size_);
    swap(a.capacity_, b.capacity_);
  }

 private:
  // ─── Internals ────────────────────────────────────────────────────────────

  /**
   * @brief Double the capacity (or set to 1 if currently 0).
   */
  void grow() {
    size_type new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
    reserve(new_cap);
  }

  T*        data_;
  size_type size_;
  size_type capacity_;
};

// ─── Non-member comparison operators ──────────────────────────────────────────

template <typename T>
bool operator==(const DynamicArray<T>& a, const DynamicArray<T>& b) {
  if (a.size() != b.size()) return false;
  return std::equal(a.begin(), a.end(), b.begin());
}

template <typename T>
bool operator!=(const DynamicArray<T>& a, const DynamicArray<T>& b) {
  return !(a == b);
}
