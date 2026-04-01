#pragma once

#include <functional>
#include <optional>
#include <vector>

/**
 * @file bst.hpp
 * @brief Binary Search Tree with standard insert/search/delete.
 *
 * Property: for every node N,
 *   all keys in N->left  < N->key < all keys in N->right
 *
 * @tparam T Key type. Must support operator< and operator==.
 */
template <typename T>
class BST {
 public:
  struct Node {
    T     val;
    Node* left;
    Node* right;
    explicit Node(T v) : val(v), left(nullptr), right(nullptr) {}
  };

  BST() : root_(nullptr), size_(0) {}

  ~BST() { clear(root_); }

  // ─── Modifiers ────────────────────────────────────────────────────────────

  /**
   * @brief Insert a value. Duplicate values are ignored.
   * @complexity O(h) average O(log n) for balanced tree
   */
  void insert(const T& val) {
    bool inserted = false;
    root_ = insert_helper(root_, val, inserted);
    if (inserted) ++size_;
  }

  /**
   * @brief Remove a value. No-op if value not present.
   * @complexity O(h)
   */
  void remove(const T& val) {
    bool removed = false;
    root_ = remove_helper(root_, val, removed);
    if (removed) --size_;
  }

  // ─── Search ───────────────────────────────────────────────────────────────

  /**
   * @brief Returns true if value exists in the tree.
   * @complexity O(h)
   */
  bool contains(const T& val) const {
    return search(root_, val) != nullptr;
  }

  /**
   * @brief Find minimum value.
   * @complexity O(h)
   */
  std::optional<T> minimum() const {
    if (!root_) return std::nullopt;
    return find_min(root_)->val;
  }

  /**
   * @brief Find maximum value.
   * @complexity O(h)
   */
  std::optional<T> maximum() const {
    if (!root_) return std::nullopt;
    Node* cur = root_;
    while (cur->right) cur = cur->right;
    return cur->val;
  }

  /**
   * @brief Inorder traversal produces sorted output.
   * @complexity O(n)
   */
  std::vector<T> sorted_values() const {
    std::vector<T> result;
    inorder(root_, result);
    return result;
  }

  /**
   * @brief Find kth smallest element (1-indexed).
   * @complexity O(h + k)
   */
  std::optional<T> kth_smallest(int k) const {
    int count = 0;
    return kth_helper(root_, k, count);
  }

  // ─── Properties ───────────────────────────────────────────────────────────

  bool        empty() const noexcept { return size_ == 0; }
  std::size_t size()  const noexcept { return size_; }
  Node*       root()  const noexcept { return root_; }

 private:
  // ─── Helpers ──────────────────────────────────────────────────────────────

  Node* insert_helper(Node* node, const T& val, bool& inserted) {
    if (!node) { inserted = true; return new Node(val); }
    if (val < node->val)      node->left  = insert_helper(node->left,  val, inserted);
    else if (val > node->val) node->right = insert_helper(node->right, val, inserted);
    // Equal: duplicate, do nothing
    return node;
  }

  Node* remove_helper(Node* node, const T& val, bool& removed) {
    if (!node) return nullptr;
    if (val < node->val) {
      node->left  = remove_helper(node->left,  val, removed);
    } else if (val > node->val) {
      node->right = remove_helper(node->right, val, removed);
    } else {
      // Found node to delete
      removed = true;
      if (!node->left) {
        Node* right = node->right;
        delete node;
        return right;
      }
      if (!node->right) {
        Node* left = node->left;
        delete node;
        return left;
      }
      // Two children: replace with inorder successor (min of right subtree)
      Node* successor = find_min(node->right);
      node->val   = successor->val;
      bool dummy = false;
      node->right = remove_helper(node->right, successor->val, dummy);
    }
    return node;
  }

  Node* search(Node* node, const T& val) const {
    if (!node) return nullptr;
    if (val == node->val) return node;
    if (val < node->val)  return search(node->left, val);
    return search(node->right, val);
  }

  Node* find_min(Node* node) const {
    while (node->left) node = node->left;
    return node;
  }

  void inorder(Node* node, std::vector<T>& result) const {
    if (!node) return;
    inorder(node->left, result);
    result.push_back(node->val);
    inorder(node->right, result);
  }

  std::optional<T> kth_helper(Node* node, int k, int& count) const {
    if (!node) return std::nullopt;
    auto left = kth_helper(node->left, k, count);
    if (left) return left;
    if (++count == k) return node->val;
    return kth_helper(node->right, k, count);
  }

  void clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

  Node*       root_;
  std::size_t size_;
};
