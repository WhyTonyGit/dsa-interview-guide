/**
 * @file examples.cpp
 * @brief Runnable tree examples: BST, AVL, traversals, classic problems.
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "data_structures/trees/binary_tree.hpp"
#include "data_structures/trees/bst.hpp"
#include "data_structures/trees/avl_tree.hpp"

// ─── BST demo ──────────────────────────────────────────────────────────────

void demo_bst() {
    std::cout << "\n=== Binary Search Tree ===\n";
    BST<int> tree;
    for (int v : {5, 3, 7, 1, 4, 6, 8}) tree.insert(v);

    std::cout << "Sorted values: [";
    auto sorted = tree.sorted_values();
    for (std::size_t i = 0; i < sorted.size(); ++i)
        std::cout << sorted[i] << (i+1 < sorted.size() ? "," : "");
    std::cout << "]  (expected [1,3,4,5,6,7,8])\n";

    std::cout << "Min: " << *tree.minimum() << "  Max: " << *tree.maximum() << "\n";
    std::cout << "Contains 4: " << (tree.contains(4) ? "true" : "false") << "\n";
    std::cout << "Contains 9: " << (tree.contains(9) ? "true" : "false") << "\n";
    std::cout << "3rd smallest: " << *tree.kth_smallest(3) << "  (expected 4)\n";

    tree.remove(3);
    std::cout << "After remove(3): [";
    sorted = tree.sorted_values();
    for (std::size_t i = 0; i < sorted.size(); ++i)
        std::cout << sorted[i] << (i+1 < sorted.size() ? "," : "");
    std::cout << "]\n";
}

// ─── AVL demo ─────────────────────────────────────────────────────────────

void demo_avl() {
    std::cout << "\n=== AVL Tree ===\n";
    AVLTree<int> avl;
    // Insert in sorted order — would degenerate to O(n) in plain BST
    for (int v : {1, 2, 3, 4, 5, 6, 7}) avl.insert(v);

    std::cout << "Height after inserting [1..7] in order: "
              << avl.tree_height() << "  (expected 3, balanced)\n";
    std::cout << "Size: " << avl.size() << "\n";
    std::cout << "Contains 5: " << (avl.contains(5) ? "true" : "false") << "\n";
    avl.remove(4);
    std::cout << "Height after remove(4): " << avl.tree_height() << "\n";
}

// ─── Binary Tree traversals ────────────────────────────────────────────────

void demo_traversals() {
    std::cout << "\n=== Binary Tree Traversals ===\n";
    /*
     *        1
     *       / \
     *      2   3
     *     / \   \
     *    4   5   6
     */
    auto* root = new TreeNode<int>(1);
    root->left  = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left->left  = new TreeNode<int>(4);
    root->left->right = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(6);

    BinaryTree<int> tree;
    tree.set_root(root);

    auto inorder = tree.inorder();
    std::cout << "Inorder:    [";
    for (std::size_t i = 0; i < inorder.size(); ++i)
        std::cout << inorder[i] << (i+1 < inorder.size() ? "," : "");
    std::cout << "]  (expected [4,2,5,1,3,6])\n";

    auto preorder = tree.preorder();
    std::cout << "Preorder:   [";
    for (std::size_t i = 0; i < preorder.size(); ++i)
        std::cout << preorder[i] << (i+1 < preorder.size() ? "," : "");
    std::cout << "]  (expected [1,2,4,5,3,6])\n";

    auto level = tree.level_order();
    std::cout << "Level-order: ";
    for (const auto& lvl : level) {
        std::cout << "[";
        for (std::size_t i = 0; i < lvl.size(); ++i)
            std::cout << lvl[i] << (i+1 < lvl.size() ? "," : "");
        std::cout << "] ";
    }
    std::cout << "\n";

    std::cout << "Height: " << tree.height() << "  (expected 2)\n";
    std::cout << "Size:   " << tree.size()   << "  (expected 6)\n";
    std::cout << "Balanced: " << (tree.is_balanced() ? "true" : "false") << "\n";
    std::cout << "Diameter: " << tree.diameter() << "  (expected 4)\n";
}

// ─── Classic problems ─────────────────────────────────────────────────────

// Maximum path sum
int maxPathSum(TreeNode<int>* root) {
    int max_sum = INT_MIN;
    std::function<int(TreeNode<int>*)> dfs = [&](TreeNode<int>* node) -> int {
        if (!node) return 0;
        int left  = std::max(0, dfs(node->left));
        int right = std::max(0, dfs(node->right));
        max_sum = std::max(max_sum, node->val + left + right);
        return node->val + std::max(left, right);
    };
    dfs(root);
    return max_sum;
}

void demo_max_path_sum() {
    std::cout << "\n=== Maximum Path Sum ===\n";
    auto* root = new TreeNode<int>(-10);
    root->left  = new TreeNode<int>(9);
    root->right = new TreeNode<int>(20);
    root->right->left  = new TreeNode<int>(15);
    root->right->right = new TreeNode<int>(7);
    std::cout << "maxPathSum = " << maxPathSum(root) << "  (expected 42)\n";
    // Cleanup
    delete root->right->right;
    delete root->right->left;
    delete root->right;
    delete root->left;
    delete root;
}

// ─── Main ─────────────────────────────────────────────────────────────────

int main() {
    demo_bst();
    demo_avl();
    demo_traversals();
    demo_max_path_sum();
    return 0;
}
