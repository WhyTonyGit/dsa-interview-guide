# Tree Interview Patterns

## Pattern 1: DFS Traversals (Recursive Template)

```cpp
// Generic DFS — modify what you do at each step
void dfs(TreeNode* node) {
    if (!node) return;
    // PREORDER: process(node->val) here
    dfs(node->left);
    // INORDER:  process(node->val) here
    dfs(node->right);
    // POSTORDER: process(node->val) here
}

// Maximum depth
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
}

// Check if trees are identical
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    return p->val == q->val &&
           isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
}

// Mirror / invert tree
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    std::swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}
```

## Pattern 2: BFS / Level-Order

```cpp
std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    std::vector<std::vector<int>> result;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        result.push_back({});
        for (int i = 0; i < sz; ++i) {
            TreeNode* node = q.front(); q.pop();
            result.back().push_back(node->val);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return result;
}

// Right side view (last node at each level)
std::vector<int> rightSideView(TreeNode* root) {
    std::vector<int> result;
    if (!root) return result;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; ++i) {
            TreeNode* node = q.front(); q.pop();
            if (i == sz - 1) result.push_back(node->val);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return result;
}
```

## Pattern 3: Path Problems

```cpp
// Path sum — does any root-to-leaf path sum to target?
bool hasPathSum(TreeNode* root, int target) {
    if (!root) return false;
    if (!root->left && !root->right) return root->val == target;
    return hasPathSum(root->left,  target - root->val) ||
           hasPathSum(root->right, target - root->val);
}

// Maximum path sum (path can go through any two nodes)
int maxPathSum(TreeNode* root) {
    int max_sum = INT_MIN;
    std::function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
        if (!node) return 0;
        int left  = std::max(0, dfs(node->left));
        int right = std::max(0, dfs(node->right));
        max_sum = std::max(max_sum, node->val + left + right);
        return node->val + std::max(left, right);
    };
    dfs(root);
    return max_sum;
}
```

## Pattern 4: BST-Specific

```cpp
// Validate BST
bool isValidBST(TreeNode* root, long min_val = LLONG_MIN, long max_val = LLONG_MAX) {
    if (!root) return true;
    if (root->val <= min_val || root->val >= max_val) return false;
    return isValidBST(root->left,  min_val, root->val) &&
           isValidBST(root->right, root->val, max_val);
}

// Kth smallest in BST — inorder traversal
int kthSmallest(TreeNode* root, int k) {
    std::stack<TreeNode*> stk;
    TreeNode* cur = root;
    while (cur || !stk.empty()) {
        while (cur) { stk.push(cur); cur = cur->left; }
        cur = stk.top(); stk.pop();
        if (--k == 0) return cur->val;
        cur = cur->right;
    }
    return -1;
}

// Lowest Common Ancestor (BST property)
TreeNode* lcaBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val) root = root->left;
        else if (p->val > root->val && q->val > root->val) root = root->right;
        else return root;  // split point = LCA
    }
    return nullptr;
}
```

## Pattern 5: Serialize / Deserialize

```cpp
// Preorder serialization with null markers
std::string serialize(TreeNode* root) {
    if (!root) return "null,";
    return std::to_string(root->val) + "," +
           serialize(root->left) + serialize(root->right);
}

TreeNode* deserialize(std::istringstream& ss) {
    std::string token;
    std::getline(ss, token, ',');
    if (token == "null") return nullptr;
    TreeNode* node = new TreeNode(std::stoi(token));
    node->left  = deserialize(ss);
    node->right = deserialize(ss);
    return node;
}
```

## Common Interview Questions

| Question | Key Pattern | Difficulty |
|----------|------------|------------|
| Maximum Depth of Binary Tree | DFS | Easy |
| Invert Binary Tree | DFS postorder | Easy |
| Symmetric Tree | DFS with two pointers | Easy |
| Binary Tree Level Order | BFS | Medium |
| Validate BST | DFS with range | Medium |
| Kth Smallest in BST | Inorder iterative | Medium |
| Lowest Common Ancestor | DFS / BST property | Medium |
| Binary Tree Maximum Path Sum | DFS global max | Hard |
| Serialize/Deserialize Binary Tree | Preorder | Hard |
| Binary Tree Right Side View | BFS | Medium |
