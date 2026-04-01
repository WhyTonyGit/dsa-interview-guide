/**
 * @file test_trees.cpp
 * @brief Unit tests for BST, AVL tree, and binary tree algorithms.
 */

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

#include "data_structures/trees/bst.hpp"
#include "data_structures/trees/avl_tree.hpp"
#include "data_structures/trees/binary_tree.hpp"

// ─── BST Tests ────────────────────────────────────────────────────────────────

TEST(BSTTest, InsertAndContains) {
    BST<int> tree;
    tree.insert(5); tree.insert(3); tree.insert(7);
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_FALSE(tree.contains(4));
}

TEST(BSTTest, SortedOrder) {
    BST<int> tree;
    for (int v : {5, 3, 7, 1, 4, 6, 8}) tree.insert(v);
    auto sorted = tree.sorted_values();
    EXPECT_TRUE(std::is_sorted(sorted.begin(), sorted.end()));
    EXPECT_EQ(sorted.size(), 7u);
}

TEST(BSTTest, MinMax) {
    BST<int> tree;
    for (int v : {5, 3, 7, 1, 9}) tree.insert(v);
    EXPECT_EQ(*tree.minimum(), 1);
    EXPECT_EQ(*tree.maximum(), 9);
}

TEST(BSTTest, EmptyMinMax) {
    BST<int> tree;
    EXPECT_FALSE(tree.minimum().has_value());
    EXPECT_FALSE(tree.maximum().has_value());
}

TEST(BSTTest, Remove) {
    BST<int> tree;
    for (int v : {5, 3, 7, 1, 4}) tree.insert(v);
    tree.remove(3);
    EXPECT_FALSE(tree.contains(3));
    EXPECT_EQ(tree.size(), 4u);
    auto sorted = tree.sorted_values();
    EXPECT_TRUE(std::is_sorted(sorted.begin(), sorted.end()));
}

TEST(BSTTest, RemoveRoot) {
    BST<int> tree;
    tree.insert(5); tree.insert(3); tree.insert(7);
    tree.remove(5);
    EXPECT_FALSE(tree.contains(5));
    EXPECT_EQ(tree.size(), 2u);
}

TEST(BSTTest, KthSmallest) {
    BST<int> tree;
    for (int v : {3, 1, 4, 1, 5, 9, 2, 6}) tree.insert(v);
    EXPECT_EQ(*tree.kth_smallest(1), 1);
    EXPECT_EQ(*tree.kth_smallest(2), 2);
}

TEST(BSTTest, NoDuplicates) {
    BST<int> tree;
    tree.insert(5); tree.insert(5); tree.insert(5);
    EXPECT_EQ(tree.size(), 1u);
}

// ─── AVL Tree Tests ───────────────────────────────────────────────────────────

TEST(AVLTreeTest, InsertMaintainsBalance) {
    AVLTree<int> tree;
    // Insert in sorted order — would degenerate without balancing
    for (int i = 1; i <= 15; ++i) tree.insert(i);
    // A balanced tree of 15 nodes has height 3
    EXPECT_LE(tree.tree_height(), 4);
    EXPECT_EQ(tree.size(), 15u);
}

TEST(AVLTreeTest, ContainsAfterInsert) {
    AVLTree<int> tree;
    for (int v : {5, 3, 7, 1, 4, 6, 8}) tree.insert(v);
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(1));
    EXPECT_FALSE(tree.contains(99));
}

TEST(AVLTreeTest, RemoveMaintainsBalance) {
    AVLTree<int> tree;
    for (int i = 1; i <= 10; ++i) tree.insert(i);
    tree.remove(5);
    EXPECT_FALSE(tree.contains(5));
    EXPECT_EQ(tree.size(), 9u);
    EXPECT_LE(tree.tree_height(), 4);
}

// ─── Binary Tree Tests ────────────────────────────────────────────────────────

TreeNode<int>* buildTree() {
    /*
     *      1
     *     / \
     *    2   3
     *   / \
     *  4   5
     */
    auto* root = new TreeNode<int>(1);
    root->left  = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left->left  = new TreeNode<int>(4);
    root->left->right = new TreeNode<int>(5);
    return root;
}

TEST(BinaryTreeTest, Inorder) {
    BinaryTree<int> tree;
    tree.set_root(buildTree());
    auto result = tree.inorder();
    std::vector<int> expected = {4, 2, 5, 1, 3};
    EXPECT_EQ(result, expected);
}

TEST(BinaryTreeTest, Preorder) {
    BinaryTree<int> tree;
    tree.set_root(buildTree());
    auto result = tree.preorder();
    std::vector<int> expected = {1, 2, 4, 5, 3};
    EXPECT_EQ(result, expected);
}

TEST(BinaryTreeTest, LevelOrder) {
    BinaryTree<int> tree;
    tree.set_root(buildTree());
    auto result = tree.level_order();
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], std::vector<int>({1}));
    EXPECT_EQ(result[1], (std::vector<int>{2, 3}));
    EXPECT_EQ(result[2], (std::vector<int>{4, 5}));
}

TEST(BinaryTreeTest, Height) {
    BinaryTree<int> tree;
    tree.set_root(buildTree());
    EXPECT_EQ(tree.height(), 2);
}

TEST(BinaryTreeTest, Size) {
    BinaryTree<int> tree;
    tree.set_root(buildTree());
    EXPECT_EQ(tree.size(), 5);
}

TEST(BinaryTreeTest, IsBalanced) {
    BinaryTree<int> tree;
    tree.set_root(buildTree());
    EXPECT_TRUE(tree.is_balanced());
}

TEST(BinaryTreeTest, InorderIterative) {
    BinaryTree<int> tree;
    tree.set_root(buildTree());
    EXPECT_EQ(tree.inorder(), tree.inorder_iterative());
}
