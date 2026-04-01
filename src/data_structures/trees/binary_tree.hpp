#pragma once

#include <algorithm>
#include <functional>
#include <optional>
#include <queue>
#include <stack>
#include <vector>

/**
 * @file binary_tree.hpp
 * @brief Binary tree node definition and traversal algorithms.
 *
 * The TreeNode struct matches the LeetCode interview format.
 * Traversal functions are provided both as recursive and iterative versions.
 */

// ─── Node ─────────────────────────────────────────────────────────────────────

/**
 * @brief Standard binary tree node used in interview problems.
 *
 * @tparam T Value type.
 */
template <typename T>
struct TreeNode {
    T         val;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(T v)
        : val(v), left(nullptr), right(nullptr) {}
    TreeNode(T v, TreeNode* l, TreeNode* r)
        : val(v), left(l), right(r) {}
};

// ─── BinaryTree ───────────────────────────────────────────────────────────────

/**
 * @brief Utility class providing traversals and common tree algorithms.
 *
 * Owns the root node; destructor deletes all nodes.
 *
 * @tparam T Value type.
 */
template <typename T>
class BinaryTree {
 public:
  using Node = TreeNode<T>;

  BinaryTree() : root_(nullptr) {}

  ~BinaryTree() { deleteTree(root_); }

  Node* root() const { return root_; }
  void  set_root(Node* r) { root_ = r; }

  // ─── Traversals ────────────────────────────────────────────────────────

  /**
   * @brief Inorder traversal (left → root → right). Produces sorted output for BST.
   * @complexity O(n) time, O(h) space (recursion stack, h = height)
   */
  std::vector<T> inorder() const {
    std::vector<T> result;
    inorder_helper(root_, result);
    return result;
  }

  /**
   * @brief Inorder traversal — iterative (Morris traversal optional).
   * @complexity O(n) time, O(h) space (explicit stack)
   */
  std::vector<T> inorder_iterative() const {
    std::vector<T> result;
    std::stack<Node*> stk;
    Node* cur = root_;
    while (cur || !stk.empty()) {
      while (cur) { stk.push(cur); cur = cur->left; }
      cur = stk.top(); stk.pop();
      result.push_back(cur->val);
      cur = cur->right;
    }
    return result;
  }

  /**
   * @brief Preorder traversal (root → left → right).
   * @complexity O(n) time, O(h) space
   */
  std::vector<T> preorder() const {
    std::vector<T> result;
    preorder_helper(root_, result);
    return result;
  }

  /**
   * @brief Postorder traversal (left → right → root).
   * @complexity O(n) time, O(h) space
   */
  std::vector<T> postorder() const {
    std::vector<T> result;
    postorder_helper(root_, result);
    return result;
  }

  /**
   * @brief Level-order (BFS) traversal.
   * @return Vector of vectors, one per level.
   * @complexity O(n) time, O(w) space (w = max width)
   */
  std::vector<std::vector<T>> level_order() const {
    std::vector<std::vector<T>> result;
    if (!root_) return result;
    std::queue<Node*> q;
    q.push(root_);
    while (!q.empty()) {
      int level_size = static_cast<int>(q.size());
      result.push_back({});
      for (int i = 0; i < level_size; ++i) {
        Node* node = q.front(); q.pop();
        result.back().push_back(node->val);
        if (node->left)  q.push(node->left);
        if (node->right) q.push(node->right);
      }
    }
    return result;
  }

  // ─── Properties ────────────────────────────────────────────────────────

  /**
   * @brief Compute tree height (0 for single node, -1 for empty).
   * @complexity O(n)
   */
  int height() const { return height_helper(root_); }

  /**
   * @brief Count total number of nodes.
   * @complexity O(n)
   */
  int size() const { return size_helper(root_); }

  /**
   * @brief Check if tree is balanced (heights differ by at most 1 at every node).
   * @complexity O(n)
   */
  bool is_balanced() const {
    return check_balanced(root_) != -1;
  }

  /**
   * @brief Check if tree is a valid BST.
   * @complexity O(n)
   */
  bool is_valid_bst() const {
    return is_bst_helper(root_, std::nullopt, std::nullopt);
  }

  /**
   * @brief Maximum depth (same as height + 1 for non-empty tree).
   * @complexity O(n)
   */
  int max_depth() const {
    if (!root_) return 0;
    return height_helper(root_) + 1;
  }

  /**
   * @brief Diameter = longest path between any two nodes (may not pass through root).
   * @complexity O(n)
   */
  int diameter() const {
    int diam = 0;
    diameter_helper(root_, diam);
    return diam;
  }

  /**
   * @brief Lowest Common Ancestor of nodes with values a and b.
   * @complexity O(n)
   */
  Node* lca(Node* root, const T& a, const T& b) const {
    if (!root) return nullptr;
    if (root->val == a || root->val == b) return root;
    Node* left  = lca(root->left,  a, b);
    Node* right = lca(root->right, a, b);
    if (left && right) return root;  // a and b on different sides
    return left ? left : right;
  }

  // ─── Construction ──────────────────────────────────────────────────────

  /**
   * @brief Build tree from level-order input (LeetCode format, -1 = null).
   * @complexity O(n)
   */
  static Node* from_level_order(const std::vector<std::optional<T>>& vals) {
    if (vals.empty() || !vals[0]) return nullptr;
    Node* root = new Node(*vals[0]);
    std::queue<Node*> q;
    q.push(root);
    std::size_t i = 1;
    while (!q.empty() && i < vals.size()) {
      Node* node = q.front(); q.pop();
      if (i < vals.size() && vals[i]) {
        node->left = new Node(*vals[i]);
        q.push(node->left);
      }
      ++i;
      if (i < vals.size() && vals[i]) {
        node->right = new Node(*vals[i]);
        q.push(node->right);
      }
      ++i;
    }
    return root;
  }

 private:
  // ─── Helpers ───────────────────────────────────────────────────────────

  void inorder_helper(Node* node, std::vector<T>& result) const {
    if (!node) return;
    inorder_helper(node->left, result);
    result.push_back(node->val);
    inorder_helper(node->right, result);
  }

  void preorder_helper(Node* node, std::vector<T>& result) const {
    if (!node) return;
    result.push_back(node->val);
    preorder_helper(node->left, result);
    preorder_helper(node->right, result);
  }

  void postorder_helper(Node* node, std::vector<T>& result) const {
    if (!node) return;
    postorder_helper(node->left, result);
    postorder_helper(node->right, result);
    result.push_back(node->val);
  }

  int height_helper(Node* node) const {
    if (!node) return -1;
    return 1 + std::max(height_helper(node->left), height_helper(node->right));
  }

  int size_helper(Node* node) const {
    if (!node) return 0;
    return 1 + size_helper(node->left) + size_helper(node->right);
  }

  // Returns height or -1 if unbalanced
  int check_balanced(Node* node) const {
    if (!node) return 0;
    int left = check_balanced(node->left);
    if (left == -1) return -1;
    int right = check_balanced(node->right);
    if (right == -1) return -1;
    if (std::abs(left - right) > 1) return -1;
    return 1 + std::max(left, right);
  }

  bool is_bst_helper(Node* node,
                     std::optional<T> min_val,
                     std::optional<T> max_val) const {
    if (!node) return true;
    if (min_val && node->val <= *min_val) return false;
    if (max_val && node->val >= *max_val) return false;
    return is_bst_helper(node->left, min_val, node->val) &&
           is_bst_helper(node->right, node->val, max_val);
  }

  int diameter_helper(Node* node, int& diam) const {
    if (!node) return 0;
    int left  = diameter_helper(node->left, diam);
    int right = diameter_helper(node->right, diam);
    diam = std::max(diam, left + right);
    return 1 + std::max(left, right);
  }

  void deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }

  Node* root_;
};
