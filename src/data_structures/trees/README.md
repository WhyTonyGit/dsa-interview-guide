# Trees

A tree is a hierarchical data structure with a root node and child nodes forming a directed acyclic graph. The most common interview tree is the **Binary Tree** (at most 2 children per node) and its variants.

## Types

| Type | Property | Use Case |
|------|----------|---------|
| Binary Tree | At most 2 children | General structure |
| BST | left < root < right | Sorted storage, search |
| AVL Tree | BST + height-balanced | Guaranteed O(log n) ops |
| Red-Black Tree | BST + color balanced | `std::map`, `std::set` |
| Complete Binary Tree | All levels full except last | Heap implementation |

## Operations & Complexity

| Operation | BST (balanced) | BST (worst) | AVL |
|-----------|---------------|-------------|-----|
| Search | O(log n) | O(n) | O(log n) |
| Insert | O(log n) | O(n) | O(log n) |
| Delete | O(log n) | O(n) | O(log n) |
| Min/Max | O(log n) | O(n) | O(log n) |
| Inorder traversal | O(n) | O(n) | O(n) |
| Space | O(n) | O(n) | O(n) |

## ✅ When to Use

- Hierarchical data (file systems, DOM, org charts)
- Need sorted order with efficient inserts/deletes → BST
- Range queries with sorted order
- Prefix-based lookups → Trie

## ❌ When NOT to Use

- Need O(1) lookup → hash table
- Data is not hierarchical
- Memory is very tight

## 📊 Interview Frequency

- **88%** at Google, Meta, Microsoft, Apple
- Tree traversals appear in virtually every interview loop
- DFS/BFS patterns extend directly to graphs

## C++ STL Tree Containers

```cpp
#include <map>    // std::map  — Red-Black tree, O(log n)
#include <set>    // std::set  — Red-Black tree, O(log n)

std::map<int, std::string> m;
m[1] = "one";
m.lower_bound(3);   // first key >= 3
m.upper_bound(3);   // first key >  3

// Tree traversal in interview — always use raw nodes
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};
```

## Key Traversal Patterns

```
         1
        / \
       2   3
      / \
     4   5

Inorder:    [4, 2, 5, 1, 3]   ← sorted for BST
Preorder:   [1, 2, 4, 5, 3]   ← serialize / copy tree
Postorder:  [4, 5, 2, 3, 1]   ← delete tree, evaluate expressions
Level-order:[1, 2, 3, 4, 5]   ← BFS, shortest path
```

See [patterns.md](patterns.md) for complete implementations.
