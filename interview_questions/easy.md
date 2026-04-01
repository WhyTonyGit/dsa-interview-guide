# Easy Interview Questions (with C++ Solutions)

---

## 1. Two Sum

**Problem:** Given an array of integers and a target, return indices of two numbers that add up to target.

**Constraints:** `2 <= nums.length <= 10^4`, one exact solution exists.

**Example:**
```
Input:  nums = [2, 7, 11, 15], target = 9
Output: [0, 1]
```

**Solution:**
```cpp
std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen;
    for (int i = 0; i < (int)nums.size(); ++i) {
        int complement = target - nums[i];
        if (seen.count(complement)) return {seen[complement], i};
        seen[nums[i]] = i;
    }
    return {};
}
```

**Complexity:** Time O(n), Space O(n)

**Key Insight:** Store complement in a hash map. When we see `nums[i]`, check if `target - nums[i]` was already seen.

---

## 2. Valid Parentheses

**Problem:** Given a string of `(`, `)`, `{`, `}`, `[`, `]`, determine if it's valid.

**Example:**
```
Input:  "()[]{}"  → true
Input:  "([)]"    → false
```

**Solution:**
```cpp
bool isValid(const std::string& s) {
    std::stack<char> stk;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') { stk.push(c); }
        else {
            if (stk.empty()) return false;
            char top = stk.top(); stk.pop();
            if ((c==')' && top!='(') || (c==']' && top!='[') || (c=='}' && top!='{'))
                return false;
        }
    }
    return stk.empty();
}
```

**Complexity:** Time O(n), Space O(n)

---

## 3. Reverse Linked List

**Problem:** Reverse a singly linked list.

**Example:** `1 → 2 → 3 → 4 → 5` → `5 → 4 → 3 → 2 → 1`

**Solution:**
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr, *cur = head;
    while (cur) {
        ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}
```

**Complexity:** Time O(n), Space O(1)

---

## 4. Maximum Subarray (Kadane's)

**Problem:** Find the contiguous subarray with the largest sum.

**Example:** `[-2,1,-3,4,-1,2,1,-5,4]` → `6` (subarray `[4,-1,2,1]`)

**Solution:**
```cpp
int maxSubArray(const std::vector<int>& nums) {
    int current = nums[0], best = nums[0];
    for (int i = 1; i < (int)nums.size(); ++i) {
        current = std::max(nums[i], current + nums[i]);
        best = std::max(best, current);
    }
    return best;
}
```

**Complexity:** Time O(n), Space O(1)

---

## 5. Climbing Stairs

**Problem:** Count ways to climb n stairs taking 1 or 2 steps at a time.

**Example:** `n=4` → `5` (1+1+1+1, 1+1+2, 1+2+1, 2+1+1, 2+2)

**Solution:**
```cpp
int climbStairs(int n) {
    if (n <= 2) return n;
    int a = 1, b = 2;
    for (int i = 3; i <= n; ++i) { int c = a+b; a=b; b=c; }
    return b;
}
```

**Complexity:** Time O(n), Space O(1)

**Note:** This is Fibonacci! F(n+1) ways to climb n stairs.

---

## 6. Best Time to Buy and Sell Stock

**Problem:** Given prices array, find the maximum profit from one buy+sell (must buy before sell).

**Example:** `[7,1,5,3,6,4]` → `5` (buy day 2 at 1, sell day 5 at 6)

**Solution:**
```cpp
int maxProfit(const std::vector<int>& prices) {
    int min_price = INT_MAX, max_profit = 0;
    for (int price : prices) {
        min_price  = std::min(min_price, price);
        max_profit = std::max(max_profit, price - min_price);
    }
    return max_profit;
}
```

**Complexity:** Time O(n), Space O(1)

---

## 7. Binary Search

**Problem:** Search target in sorted array, return index or -1.

**Solution:**
```cpp
int search(const std::vector<int>& nums, int target) {
    int lo = 0, hi = (int)nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target)  lo = mid + 1;
        else                     hi = mid - 1;
    }
    return -1;
}
```

**Complexity:** Time O(log n), Space O(1)

---

## 8. Contains Duplicate

**Problem:** Return true if any value appears at least twice.

**Solution:**
```cpp
bool containsDuplicate(const std::vector<int>& nums) {
    std::unordered_set<int> seen;
    for (int x : nums) {
        if (!seen.insert(x).second) return true;
    }
    return false;
}
```

**Complexity:** Time O(n), Space O(n)
