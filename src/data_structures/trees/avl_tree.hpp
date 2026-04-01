#pragma once

#include <algorithm>
#include <cstddef>

/**
 * @file avl_tree.hpp
 * @brief Self-balancing AVL Tree.
 *
 * An AVL tree maintains the invariant that for every node N,
 * |height(N.left) - height(N.right)| <= 1.
 *
 * This guarantees O(log n) worst-case for all operations.
 *
 * @tparam T Key type. Must support operator< and operator==.
 */
template <typename T>
class AVLTree {
 public:
  struct Node {
    T     val;
    Node* left;
    Node* right;
    int   height;

    explicit Node(T v)
        : val(v), left(nullptr), right(nullptr), height(1) {}
  };

  AVLTree() : root_(nullptr), size_(0) {}

  ~AVLTree() { clear(root_); }

  // ─── Public Interface ────────────────────────────────────────────────────

  /**
   * @brief Insert a value. Duplicates are ignored.
   * @complexity O(log n)
   */
  void insert(const T& val) {
    bool inserted = false;
    root_ = insert_helper(root_, val, inserted);
    if (inserted) ++size_;
  }

  /**
   * @brief Remove a value. No-op if not present.
   * @complexity O(log n)
   */
  void remove(const T& val) {
    bool removed = false;
    root_ = remove_helper(root_, val, removed);
    if (removed) --size_;
  }

  /**
   * @brief Check membership.
   * @complexity O(log n)
   */
  bool contains(const T& val) const {
    Node* cur = root_;
    while (cur) {
      if (val == cur->val) return true;
      cur = val < cur->val ? cur->left : cur->right;
    }
    return false;
  }

  bool        empty() const noexcept { return size_ == 0; }
  std::size_t size()  const noexcept { return size_; }
  Node*       root()  const noexcept { return root_; }

  int tree_height() const { return node_height(root_); }

 private:
  // ─── Height helpers ──────────────────────────────────────────────────────

  int node_height(Node* n) const { return n ? n->height : 0; }

  int balance_factor(Node* n) const {
    return n ? node_height(n->left) - node_height(n->right) : 0;
  }

  void update_height(Node* n) {
    if (n)
      n->height = 1 + std::max(node_height(n->left), node_height(n->right));
  }

  // ─── Rotations ───────────────────────────────────────────────────────────

  /**
   * @brief Right rotation around y:
   *        y              x
   *       / \            / \
   *      x   C    →     A   y
   *     / \                / \
   *    A   B              B   C
   */
  Node* rotate_right(Node* y) {
    Node* x  = y->left;
    Node* B  = x->right;
    x->right = y;
    y->left  = B;
    update_height(y);
    update_height(x);
    return x;
  }

  /**
   * @brief Left rotation around x:
   *      x                y
   *     / \              / \
   *    A   y      →     x   C
   *       / \          / \
   *      B   C        A   B
   */
  Node* rotate_left(Node* x) {
    Node* y  = x->right;
    Node* B  = y->left;
    y->left  = x;
    x->right = B;
    update_height(x);
    update_height(y);
    return y;
  }

  /**
   * @brief Rebalance node if |bf| > 1.
   */
  Node* rebalance(Node* n) {
    update_height(n);
    int bf = balance_factor(n);

    // Left heavy
    if (bf > 1) {
      if (balance_factor(n->left) < 0)       // Left-Right case
        n->left = rotate_left(n->left);
      return rotate_right(n);                 // Left-Left case
    }
    // Right heavy
    if (bf < -1) {
      if (balance_factor(n->right) > 0)      // Right-Left case
        n->right = rotate_right(n->right);
      return rotate_left(n);                  // Right-Right case
    }
    return n;
  }

  // ─── Insert / Remove ─────────────────────────────────────────────────────

  Node* insert_helper(Node* n, const T& val, bool& inserted) {
    if (!n) { inserted = true; return new Node(val); }
    if (val < n->val)      n->left  = insert_helper(n->left,  val, inserted);
    else if (val > n->val) n->right = insert_helper(n->right, val, inserted);
    return rebalance(n);
  }

  Node* find_min(Node* n) const {
    while (n->left) n = n->left;
    return n;
  }

  Node* remove_helper(Node* n, const T& val, bool& removed) {
    if (!n) return nullptr;
    if (val < n->val) {
      n->left  = remove_helper(n->left,  val, removed);
    } else if (val > n->val) {
      n->right = remove_helper(n->right, val, removed);
    } else {
      removed = true;
      if (!n->left || !n->right) {
        Node* child = n->left ? n->left : n->right;
        delete n;
        return child;
      }
      Node* successor = find_min(n->right);
      n->val = successor->val;
      bool dummy = false;
      n->right = remove_helper(n->right, successor->val, dummy);
    }
    return rebalance(n);
  }

  void clear(Node* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
  }

  Node*       root_;
  std::size_t size_;
};
