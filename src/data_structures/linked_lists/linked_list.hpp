#pragma once

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility>

/**
 * @file linked_list.hpp
 * @brief Doubly-linked list with a sentinel (dummy) head and tail.
 *
 * Using sentinels eliminates all special-case checks for empty lists and
 * head/tail insertions, making the code cleaner and less error-prone.
 */

// ─── Node ────────────────────────────────────────────────────────────────────

template <typename T>
struct ListNode {
    T        value;
    ListNode* prev;
    ListNode* next;

    explicit ListNode(const T& v, ListNode* p = nullptr, ListNode* n = nullptr)
        : value(v), prev(p), next(n) {}
};

// ─── DoublyLinkedList ─────────────────────────────────────────────────────────

/**
 * @brief Doubly-linked list with O(1) front/back operations.
 *
 * @tparam T Element type. Must be copy-constructible.
 */
template <typename T>
class DoublyLinkedList {
 public:
  using Node = ListNode<T>;

  // ─── Constructors / Destructor ──────────────────────────────────────────

  /**
   * @brief Construct an empty list.
   * @complexity O(1)
   */
  DoublyLinkedList() : size_(0) {
    head_ = new Node(T{});  // sentinel head
    tail_ = new Node(T{});  // sentinel tail
    head_->next = tail_;
    tail_->prev = head_;
  }

  /**
   * @brief Construct from initializer list.
   * @complexity O(n)
   */
  DoublyLinkedList(std::initializer_list<T> ilist) : DoublyLinkedList() {
    for (const T& val : ilist) push_back(val);
  }

  /**
   * @brief Copy constructor.
   * @complexity O(n)
   */
  DoublyLinkedList(const DoublyLinkedList& other) : DoublyLinkedList() {
    for (Node* cur = other.head_->next; cur != other.tail_; cur = cur->next)
      push_back(cur->value);
  }

  /**
   * @brief Move constructor — steals the node chain.
   * @complexity O(1)
   */
  DoublyLinkedList(DoublyLinkedList&& other) noexcept
      : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  /**
   * @brief Unified assignment operator (copy-and-swap).
   */
  DoublyLinkedList& operator=(DoublyLinkedList other) noexcept {
    swap(*this, other);
    return *this;
  }

  /**
   * @brief Destructor — frees all nodes including sentinels.
   * @complexity O(n)
   */
  ~DoublyLinkedList() {
    if (!head_) return;  // moved-from state
    clear();
    delete head_;
    delete tail_;
  }

  // ─── Capacity ──────────────────────────────────────────────────────────

  bool        empty() const noexcept { return size_ == 0; }
  std::size_t size()  const noexcept { return size_; }

  // ─── Element access ────────────────────────────────────────────────────

  /**
   * @brief Returns reference to the first element.
   * @throws std::runtime_error if list is empty.
   */
  T& front() {
    if (empty()) throw std::runtime_error("front() on empty list");
    return head_->next->value;
  }
  const T& front() const {
    if (empty()) throw std::runtime_error("front() on empty list");
    return head_->next->value;
  }

  /**
   * @brief Returns reference to the last element.
   * @throws std::runtime_error if list is empty.
   */
  T& back() {
    if (empty()) throw std::runtime_error("back() on empty list");
    return tail_->prev->value;
  }
  const T& back() const {
    if (empty()) throw std::runtime_error("back() on empty list");
    return tail_->prev->value;
  }

  // ─── Modifiers ─────────────────────────────────────────────────────────

  /**
   * @brief Prepend an element.
   * @complexity O(1)
   */
  void push_front(const T& value) { insert_after(head_, value); }

  /**
   * @brief Append an element.
   * @complexity O(1)
   */
  void push_back(const T& value) { insert_before(tail_, value); }

  /**
   * @brief Remove and return the first element.
   * @throws std::runtime_error if empty.
   * @complexity O(1)
   */
  T pop_front() {
    if (empty()) throw std::runtime_error("pop_front() on empty list");
    T val = head_->next->value;
    remove_node(head_->next);
    return val;
  }

  /**
   * @brief Remove and return the last element.
   * @throws std::runtime_error if empty.
   * @complexity O(1)
   */
  T pop_back() {
    if (empty()) throw std::runtime_error("pop_back() on empty list");
    T val = tail_->prev->value;
    remove_node(tail_->prev);
    return val;
  }

  /**
   * @brief Remove the first occurrence of value.
   * @return true if an element was removed.
   * @complexity O(n)
   */
  bool remove(const T& value) {
    for (Node* cur = head_->next; cur != tail_; cur = cur->next) {
      if (cur->value == value) {
        remove_node(cur);
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Remove all elements.
   * @complexity O(n)
   */
  void clear() {
    Node* cur = head_->next;
    while (cur != tail_) {
      Node* next = cur->next;
      delete cur;
      cur = next;
    }
    head_->next = tail_;
    tail_->prev = head_;
    size_ = 0;
  }

  /**
   * @brief Reverse the list in-place.
   * @complexity O(n)
   */
  void reverse() {
    Node* cur = head_;
    while (cur) {
      std::swap(cur->prev, cur->next);
      cur = cur->prev;  // move to what was originally cur->next
    }
    std::swap(head_, tail_);
  }

  /**
   * @brief Search for value. Returns pointer to node or nullptr.
   * @complexity O(n)
   */
  Node* find(const T& value) const {
    for (Node* cur = head_->next; cur != tail_; cur = cur->next)
      if (cur->value == value) return cur;
    return nullptr;
  }

  /**
   * @brief Detect a cycle (Floyd's Tortoise and Hare).
   * @complexity O(n) time, O(1) space
   */
  bool has_cycle() const {
    Node* slow = head_->next;
    Node* fast = head_->next;
    while (fast && fast != tail_ && fast->next && fast->next != tail_) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) return true;
    }
    return false;
  }

  /**
   * @brief Print all elements to stdout.
   * @complexity O(n)
   */
  void print() const {
    std::cout << "[";
    for (Node* cur = head_->next; cur != tail_; cur = cur->next)
      std::cout << cur->value << (cur->next != tail_ ? " <-> " : "");
    std::cout << "]\n";
  }

  friend void swap(DoublyLinkedList& a, DoublyLinkedList& b) noexcept {
    using std::swap;
    swap(a.head_, b.head_);
    swap(a.tail_, b.tail_);
    swap(a.size_, b.size_);
  }

 private:
  // ─── Internal helpers ───────────────────────────────────────────────────

  void insert_after(Node* pos, const T& value) {
    Node* node = new Node(value, pos, pos->next);
    pos->next->prev = node;
    pos->next       = node;
    ++size_;
  }

  void insert_before(Node* pos, const T& value) {
    insert_after(pos->prev, value);
  }

  void remove_node(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    --size_;
  }

  Node*       head_;  // sentinel
  Node*       tail_;  // sentinel
  std::size_t size_;
};

// ─── SinglyLinkedList ─────────────────────────────────────────────────────────

/**
 * @brief Singly-linked list — commonly used in interview questions.
 *
 * This is the "interview-style" node definition that matches LeetCode format.
 *
 * @tparam T Element type.
 */
template <typename T>
struct SLLNode {
    T        val;
    SLLNode* next;
    explicit SLLNode(T v) : val(v), next(nullptr) {}
};

/**
 * @brief Collection of classic singly-linked list algorithms.
 *
 * In interviews you are usually handed a raw SLLNode* — these functions
 * demonstrate canonical implementations.
 */
template <typename T>
struct SinglyLinkedListAlgorithms {
  using Node = SLLNode<T>;

  /**
   * @brief Reverse a singly-linked list iteratively.
   * @complexity O(n) time, O(1) space
   */
  static Node* reverse(Node* head) {
    Node* prev = nullptr;
    Node* cur  = head;
    while (cur) {
      Node* next = cur->next;
      cur->next  = prev;
      prev       = cur;
      cur        = next;
    }
    return prev;
  }

  /**
   * @brief Detect cycle (Floyd's algorithm).
   * @complexity O(n) time, O(1) space
   */
  static bool has_cycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) return true;
    }
    return false;
  }

  /**
   * @brief Find the middle node (slow/fast pointers).
   * For even-length list, returns the second middle.
   * @complexity O(n) time, O(1) space
   */
  static Node* find_middle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow;
  }

  /**
   * @brief Merge two sorted linked lists.
   * @complexity O(n + m) time, O(1) space
   */
  static Node* merge_sorted(Node* l1, Node* l2) {
    Node dummy(T{});
    Node* tail = &dummy;
    while (l1 && l2) {
      if (l1->val <= l2->val) { tail->next = l1; l1 = l1->next; }
      else                    { tail->next = l2; l2 = l2->next; }
      tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
  }

  /**
   * @brief Remove nth node from the end in one pass.
   * @complexity O(n) time, O(1) space
   */
  static Node* remove_nth_from_end(Node* head, int n) {
    Node dummy(T{});
    dummy.next = head;
    Node* fast = &dummy;
    Node* slow = &dummy;
    for (int i = 0; i <= n; ++i) fast = fast->next;
    while (fast) {
      slow = slow->next;
      fast = fast->next;
    }
    Node* to_delete = slow->next;
    slow->next = slow->next->next;
    delete to_delete;
    return dummy.next;
  }
};
