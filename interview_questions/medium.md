# Medium Interview Questions (with C++ Solutions)

---

## 1. LRU Cache

**Problem:** Design a data structure supporting `get(key)` and `put(key, value)` in O(1). Evict the least recently used when capacity is exceeded.

**Solution:** Doubly-linked list (for O(1) insert/delete) + hash map (for O(1) lookup).

```cpp
class LRUCache {
    int capacity;
    std::list<std::pair<int,int>> lst;  // (key, value), front = MRU
    std::unordered_map<int, std::list<std::pair<int,int>>::iterator> map;
public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        if (!map.count(key)) return -1;
        lst.splice(lst.begin(), lst, map[key]);  // move to front
        return map[key]->second;
    }

    void put(int key, int value) {
        if (map.count(key)) lst.erase(map[key]);
        else if ((int)lst.size() == capacity) {
            map.erase(lst.back().first);
            lst.pop_back();
        }
        lst.push_front({key, value});
        map[key] = lst.begin();
    }
};
```

**Complexity:** Time O(1) for both, Space O(capacity)

---

## 2. Number of Islands

**Problem:** Given a 2D grid of '1's and '0's, count the number of islands (connected groups of '1's).

**Solution:** DFS flood-fill — mark visited cells as '0'.

```cpp
int numIslands(std::vector<std::vector<char>>& grid) {
    int rows = grid.size(), cols = grid[0].size(), count = 0;
    std::function<void(int,int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') return;
        grid[r][c] = '0';
        dfs(r+1,c); dfs(r-1,c); dfs(r,c+1); dfs(r,c-1);
    };
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (grid[r][c] == '1') { dfs(r,c); ++count; }
    return count;
}
```

**Complexity:** Time O(m×n), Space O(m×n) (recursion stack)

---

## 3. Course Schedule (Cycle Detection in DAG)

**Problem:** n courses, prerequisites as pairs [a,b] means "a requires b". Can you finish all courses?

**Solution:** Topological sort (Kahn's BFS). If all courses are processed, no cycle exists.

```cpp
bool canFinish(int n, const std::vector<std::vector<int>>& prereqs) {
    std::vector<std::vector<int>> adj(n);
    std::vector<int> in_degree(n, 0);
    for (const auto& p : prereqs) { adj[p[1]].push_back(p[0]); ++in_degree[p[0]]; }
    std::queue<int> q;
    for (int i = 0; i < n; ++i) if (in_degree[i] == 0) q.push(i);
    int done = 0;
    while (!q.empty()) {
        int cur = q.front(); q.pop(); ++done;
        for (int nbr : adj[cur]) if (--in_degree[nbr] == 0) q.push(nbr);
    }
    return done == n;
}
```

**Complexity:** Time O(V+E), Space O(V+E)

---

## 4. Product of Array Except Self

**Problem:** Return array where `output[i]` = product of all elements except `nums[i]`. No division allowed.

**Solution:** Forward pass (left products) + backward pass (right products).

```cpp
std::vector<int> productExceptSelf(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n, 1);
    for (int i = 1; i < n; ++i)     result[i] = result[i-1] * nums[i-1];
    int right = 1;
    for (int i = n-1; i >= 0; --i) { result[i] *= right; right *= nums[i]; }
    return result;
}
```

**Complexity:** Time O(n), Space O(1) (output array not counted)

---

## 5. Longest Substring Without Repeating Characters

**Problem:** Find the length of the longest substring without repeating characters.

**Solution:** Sliding window with a hash map tracking last seen position.

```cpp
int lengthOfLongestSubstring(const std::string& s) {
    std::unordered_map<char, int> last_seen;
    int max_len = 0, left = 0;
    for (int right = 0; right < (int)s.size(); ++right) {
        if (last_seen.count(s[right]) && last_seen[s[right]] >= left)
            left = last_seen[s[right]] + 1;
        last_seen[s[right]] = right;
        max_len = std::max(max_len, right - left + 1);
    }
    return max_len;
}
```

**Complexity:** Time O(n), Space O(min(n, alphabet_size))

---

## 6. Binary Tree Level Order Traversal

**Problem:** Return values of nodes level by level.

**Solution:** BFS with queue, process one level at a time.

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
```

**Complexity:** Time O(n), Space O(n)

---

## 7. Merge Intervals

**Problem:** Merge all overlapping intervals.

**Example:** `[[1,3],[2,6],[8,10],[15,18]]` → `[[1,6],[8,10],[15,18]]`

**Solution:** Sort by start, then greedily merge.

```cpp
std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
    std::sort(intervals.begin(), intervals.end());
    std::vector<std::vector<int>> result;
    for (const auto& iv : intervals) {
        if (!result.empty() && iv[0] <= result.back()[1])
            result.back()[1] = std::max(result.back()[1], iv[1]);
        else result.push_back(iv);
    }
    return result;
}
```

**Complexity:** Time O(n log n), Space O(n)

---

## 8. Coin Change

**Problem:** Minimum coins to make amount. Return -1 if impossible.

**Solution:** Bottom-up DP.

```cpp
int coinChange(const std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i)
        for (int coin : coins)
            if (coin <= i) dp[i] = std::min(dp[i], dp[i-coin] + 1);
    return dp[amount] > amount ? -1 : dp[amount];
}
```

**Complexity:** Time O(amount × coins), Space O(amount)
