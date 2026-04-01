# Stack & Queue Interview Patterns

## Pattern 1: Bracket / Parentheses Matching

```cpp
bool isValid(const std::string& s) {
    std::stack<char> stk;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stk.push(c);
        } else {
            if (stk.empty()) return false;
            char top = stk.top(); stk.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) return false;
        }
    }
    return stk.empty();
}
```

## Pattern 2: Monotonic Stack — Next Greater Element

```cpp
// For each element, find the next element greater than it.
std::vector<int> nextGreaterElement(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n, -1);
    std::stack<int> stk;  // stores indices
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && nums[stk.top()] < nums[i]) {
            result[stk.top()] = nums[i];
            stk.pop();
        }
        stk.push(i);
    }
    return result;
}

// Daily Temperatures variant
std::vector<int> dailyTemperatures(const std::vector<int>& T) {
    int n = T.size();
    std::vector<int> result(n, 0);
    std::stack<int> stk;
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && T[stk.top()] < T[i]) {
            result[stk.top()] = i - stk.top();
            stk.pop();
        }
        stk.push(i);
    }
    return result;
}
```

## Pattern 3: Evaluate Reverse Polish Notation

```cpp
int evalRPN(const std::vector<std::string>& tokens) {
    std::stack<int> stk;
    for (const auto& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = stk.top(); stk.pop();
            int a = stk.top(); stk.pop();
            if (token == "+") stk.push(a + b);
            else if (token == "-") stk.push(a - b);
            else if (token == "*") stk.push(a * b);
            else stk.push(a / b);
        } else {
            stk.push(std::stoi(token));
        }
    }
    return stk.top();
}
```

## Pattern 4: BFS with Queue

```cpp
// Generic BFS template (works for trees and graphs)
void bfs(int start, const std::vector<std::vector<int>>& adj) {
    std::vector<bool> visited(adj.size(), false);
    std::queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        std::cout << node << " ";
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// Level-order traversal of binary tree
std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if (!root) return result;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int level_size = q.size();
        result.push_back({});
        for (int i = 0; i < level_size; ++i) {
            TreeNode* node = q.front(); q.pop();
            result.back().push_back(node->val);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return result;
}
```

## Pattern 5: Sliding Window Maximum (Monotonic Deque)

```cpp
std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
    std::deque<int> dq;  // stores indices, front = max
    std::vector<int> result;
    for (int i = 0; i < (int)nums.size(); ++i) {
        // Remove elements outside window
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        // Remove elements smaller than current (maintain decreasing order)
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) result.push_back(nums[dq.front()]);
    }
    return result;
}
```

## Pattern 6: Implement Stack using Queues / Queue using Stacks

```cpp
// Queue using two stacks (amortized O(1))
class MyQueue {
    std::stack<int> inbox, outbox;
public:
    void push(int x) { inbox.push(x); }
    int pop() {
        if (outbox.empty())
            while (!inbox.empty()) { outbox.push(inbox.top()); inbox.pop(); }
        int val = outbox.top(); outbox.pop();
        return val;
    }
    int peek() {
        if (outbox.empty())
            while (!inbox.empty()) { outbox.push(inbox.top()); inbox.pop(); }
        return outbox.top();
    }
    bool empty() { return inbox.empty() && outbox.empty(); }
};
```

## Common Interview Questions

| Question | Pattern | Difficulty |
|----------|---------|------------|
| Valid Parentheses | Stack matching | Easy |
| Min Stack | Stack + auxiliary | Easy |
| Implement Queue using Stacks | Two stacks | Easy |
| Daily Temperatures | Monotonic stack | Medium |
| Evaluate Reverse Polish Notation | Stack | Medium |
| Sliding Window Maximum | Monotonic deque | Hard |
| Largest Rectangle in Histogram | Monotonic stack | Hard |
| Basic Calculator | Stack + parsing | Hard |
