# Hard Interview Questions (with C++ Solutions)

---

## 1. Serialize and Deserialize Binary Tree

**Problem:** Design an algorithm to serialize a binary tree to string and deserialize back.

**Solution:** Preorder DFS with null markers.

```cpp
class Codec {
public:
    std::string serialize(TreeNode* root) {
        if (!root) return "null,";
        return std::to_string(root->val) + "," +
               serialize(root->left) + serialize(root->right);
    }

    TreeNode* deserialize(const std::string& data) {
        std::istringstream ss(data);
        return deserialize_helper(ss);
    }
private:
    TreeNode* deserialize_helper(std::istringstream& ss) {
        std::string token;
        std::getline(ss, token, ',');
        if (token == "null") return nullptr;
        TreeNode* node = new TreeNode(std::stoi(token));
        node->left  = deserialize_helper(ss);
        node->right = deserialize_helper(ss);
        return node;
    }
};
```

**Complexity:** Time O(n), Space O(n)

**Key Insight:** Preorder uniquely determines tree structure when null nodes are encoded.

---

## 2. Trapping Rain Water

**Problem:** Given elevation map, calculate total water that can be trapped.

**Example:** `[0,1,0,2,1,0,1,3,2,1,2,1]` → `6`

**Solution:** Two pointers. At each position, water = min(max_left, max_right) - height.

```cpp
int trap(const std::vector<int>& height) {
    int lo = 0, hi = (int)height.size() - 1;
    int left_max = 0, right_max = 0, water = 0;
    while (lo < hi) {
        if (height[lo] < height[hi]) {
            if (height[lo] >= left_max) left_max = height[lo];
            else water += left_max - height[lo];
            ++lo;
        } else {
            if (height[hi] >= right_max) right_max = height[hi];
            else water += right_max - height[hi];
            --hi;
        }
    }
    return water;
}
```

**Complexity:** Time O(n), Space O(1)

---

## 3. Median of Two Sorted Arrays

**Problem:** Find the median of two sorted arrays in O(log(m+n)) time.

**Solution:** Binary search on the shorter array to find the correct partition.

```cpp
double findMedianSortedArrays(const std::vector<int>& nums1,
                               const std::vector<int>& nums2) {
    const auto& A = nums1.size() <= nums2.size() ? nums1 : nums2;
    const auto& B = nums1.size() <= nums2.size() ? nums2 : nums1;
    int m = A.size(), n = B.size();
    int lo = 0, hi = m;
    while (lo <= hi) {
        int i = (lo + hi) / 2;
        int j = (m + n + 1) / 2 - i;
        int maxLeftA  = (i == 0)   ? INT_MIN : A[i-1];
        int minRightA = (i == m)   ? INT_MAX : A[i];
        int maxLeftB  = (j == 0)   ? INT_MIN : B[j-1];
        int minRightB = (j == n)   ? INT_MAX : B[j];
        if (maxLeftA <= minRightB && maxLeftB <= minRightA) {
            if ((m + n) % 2 == 1)
                return std::max(maxLeftA, maxLeftB);
            return (std::max(maxLeftA, maxLeftB) + std::min(minRightA, minRightB)) / 2.0;
        } else if (maxLeftA > minRightB) hi = i - 1;
        else lo = i + 1;
    }
    return 0.0;
}
```

**Complexity:** Time O(log(min(m,n))), Space O(1)

---

## 4. Word Ladder (Shortest Transformation Sequence)

**Problem:** Given beginWord, endWord, and wordList, find the length of the shortest transformation sequence where each step changes exactly one letter.

**Solution:** BFS. Use the word list as a set; erase visited words to prevent cycles.

```cpp
int ladderLength(const std::string& begin, const std::string& end,
                 std::vector<std::string>& wordList) {
    std::unordered_set<std::string> word_set(wordList.begin(), wordList.end());
    if (!word_set.count(end)) return 0;
    std::queue<std::string> q;
    q.push(begin);
    int steps = 1;
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; ++i) {
            std::string word = q.front(); q.pop();
            if (word == end) return steps;
            for (int j = 0; j < (int)word.size(); ++j) {
                char orig = word[j];
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == orig) continue;
                    word[j] = c;
                    if (word_set.count(word)) {
                        q.push(word);
                        word_set.erase(word);
                    }
                }
                word[j] = orig;
            }
        }
        ++steps;
    }
    return 0;
}
```

**Complexity:** Time O(n × L × 26), Space O(n × L) where n = words, L = word length

---

## 5. Find Median from Data Stream

**Problem:** Design a class that supports adding numbers and finding the running median.

**Solution:** Max-heap for lower half + min-heap for upper half.

```cpp
class MedianFinder {
    std::priority_queue<int> lower;  // max-heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> upper;  // min-heap
public:
    void addNum(int num) {
        lower.push(num);
        upper.push(lower.top()); lower.pop();
        if (lower.size() < upper.size()) {
            lower.push(upper.top()); upper.pop();
        }
    }
    double findMedian() {
        if (lower.size() > upper.size()) return lower.top();
        return (lower.top() + upper.top()) / 2.0;
    }
};
```

**Complexity:** addNum O(log n), findMedian O(1), Space O(n)

---

## 6. Largest Rectangle in Histogram

**Problem:** Find the largest rectangle that can be formed in a histogram.

**Example:** `[2,1,5,6,2,3]` → `10` (rectangle of height 5, width 2)

**Solution:** Monotonic stack — for each bar, find the nearest smaller bars on left and right.

```cpp
int largestRectangleArea(const std::vector<int>& heights) {
    std::stack<int> stk;
    int max_area = 0;
    std::vector<int> h(heights.begin(), heights.end());
    h.push_back(0);  // sentinel to flush remaining bars
    for (int i = 0; i < (int)h.size(); ++i) {
        while (!stk.empty() && h[stk.top()] > h[i]) {
            int height = h[stk.top()]; stk.pop();
            int width = stk.empty() ? i : i - stk.top() - 1;
            max_area = std::max(max_area, height * width);
        }
        stk.push(i);
    }
    return max_area;
}
```

**Complexity:** Time O(n), Space O(n)

---

## 7. Regular Expression Matching

**Problem:** Implement regex matching with `.` (any char) and `*` (zero or more of preceding).

**Solution:** 2D DP where `dp[i][j]` = does `s[0..i-1]` match `p[0..j-1]`?

```cpp
bool isMatch(const std::string& s, const std::string& p) {
    int m = s.size(), n = p.size();
    std::vector<std::vector<bool>> dp(m+1, std::vector<bool>(n+1, false));
    dp[0][0] = true;
    for (int j = 2; j <= n; j += 2)
        if (p[j-1] == '*') dp[0][j] = dp[0][j-2];
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (p[j-1] == '*') {
                dp[i][j] = dp[i][j-2] ||  // zero occurrences
                   ((p[j-2] == '.' || p[j-2] == s[i-1]) && dp[i-1][j]);
            } else {
                dp[i][j] = dp[i-1][j-1] &&
                            (p[j-1] == '.' || p[j-1] == s[i-1]);
            }
        }
    }
    return dp[m][n];
}
```

**Complexity:** Time O(m×n), Space O(m×n)
