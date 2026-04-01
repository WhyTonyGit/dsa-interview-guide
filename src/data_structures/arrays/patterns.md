# Array Interview Patterns

## Pattern 1: Two Pointers

**When to use:** Sorted array, find pair with target sum, remove duplicates, reverse.

**Approach:** Place one pointer at start, one at end (or both at start moving at different speeds). Move inward based on comparison.

**Complexity:** O(n) time, O(1) space

### Example: Two Sum II (sorted array)
```
Input: [2, 7, 11, 15], target = 9
Output: [0, 1]  (indices)
```

```cpp
std::vector<int> twoSum(std::vector<int>& nums, int target) {
    int lo = 0, hi = static_cast<int>(nums.size()) - 1;
    while (lo < hi) {
        int sum = nums[lo] + nums[hi];
        if (sum == target) return {lo, hi};
        else if (sum < target) ++lo;
        else --hi;
    }
    return {};
}
```

### Example: Remove Duplicates in-place
```cpp
int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    int slow = 0;
    for (int fast = 1; fast < (int)nums.size(); ++fast) {
        if (nums[fast] != nums[slow]) nums[++slow] = nums[fast];
    }
    return slow + 1;
}
```

---

## Pattern 2: Sliding Window

**When to use:** Contiguous subarray/substring problems — max sum, longest substring, smallest window containing a set of characters.

**Approach:** Expand right boundary; shrink left when constraint is violated. Track state in a hash map or counter.

**Complexity:** O(n) time, O(k) space where k = window state size

### Example: Maximum Sum Subarray of size K
```cpp
int maxSumSubarrayK(const std::vector<int>& nums, int k) {
    int window_sum = 0, max_sum = INT_MIN;
    for (int i = 0; i < (int)nums.size(); ++i) {
        window_sum += nums[i];
        if (i >= k - 1) {
            max_sum = std::max(max_sum, window_sum);
            window_sum -= nums[i - k + 1];
        }
    }
    return max_sum;
}
```

### Example: Longest Substring Without Repeating Characters
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

---

## Pattern 3: Prefix Sum

**When to use:** Range sum queries, count subarrays with a target sum, equilibrium index.

**Approach:** Build a prefix array where `prefix[i] = sum of nums[0..i-1]`. Range sum [l, r] = `prefix[r+1] - prefix[l]`.

**Complexity:** O(n) build, O(1) query; O(n) space

### Example: Subarray Sum Equals K (count)
```cpp
int subarraySum(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> prefix_count;
    prefix_count[0] = 1;  // empty prefix
    int count = 0, prefix_sum = 0;
    for (int x : nums) {
        prefix_sum += x;
        count += prefix_count[prefix_sum - k];
        ++prefix_count[prefix_sum];
    }
    return count;
}
```

---

## Pattern 4: Sorting + Greedy Scan

**When to use:** Merge intervals, meeting rooms, minimum platforms, overlapping ranges.

**Approach:** Sort by start time. Then do a single pass, maintaining current state (latest end time, active intervals).

**Complexity:** O(n log n) sort + O(n) scan

### Example: Merge Intervals
```cpp
std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
    std::sort(intervals.begin(), intervals.end());
    std::vector<std::vector<int>> result;
    for (const auto& iv : intervals) {
        if (!result.empty() && iv[0] <= result.back()[1])
            result.back()[1] = std::max(result.back()[1], iv[1]);
        else
            result.push_back(iv);
    }
    return result;
}
```

---

## Pattern 5: Kadane's Algorithm (Max Subarray)

**When to use:** Maximum subarray sum (contiguous), maximum product subarray.

**Approach:** Track current sum and global max. Reset current sum when it goes negative.

**Complexity:** O(n) time, O(1) space

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

---

## Pattern 6: Binary Search on Sorted Array

**When to use:** Any sorted array lookup — find target, find first/last occurrence, search in rotated array.

**Standard template:**
```cpp
int lo = 0, hi = (int)nums.size() - 1;
while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (nums[mid] == target) return mid;
    else if (nums[mid] < target) lo = mid + 1;
    else hi = mid - 1;
}
return -1;
```

### Example: Search in Rotated Sorted Array
```cpp
int search(const std::vector<int>& nums, int target) {
    int lo = 0, hi = (int)nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;
        // Left half is sorted
        if (nums[lo] <= nums[mid]) {
            if (nums[lo] <= target && target < nums[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else {  // Right half is sorted
            if (nums[mid] < target && target <= nums[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return -1;
}
```

---

## Pattern 7: Hash Map for O(1) Lookup

**When to use:** Two Sum (unsorted), group anagrams, find duplicate, check subset.

### Example: Two Sum (unsorted)
```cpp
std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen;  // value → index
    for (int i = 0; i < (int)nums.size(); ++i) {
        int complement = target - nums[i];
        if (seen.count(complement)) return {seen[complement], i};
        seen[nums[i]] = i;
    }
    return {};
}
```

---

## Common Interview Questions

| Question | Pattern | Difficulty |
|----------|---------|------------|
| Two Sum | Hash Map | Easy |
| Best Time to Buy and Sell Stock | Sliding Window / Greedy | Easy |
| Maximum Subarray (Kadane) | DP / Greedy | Easy |
| Product of Array Except Self | Prefix/Suffix | Medium |
| Merge Intervals | Sorting + Scan | Medium |
| Find Minimum in Rotated Array | Binary Search | Medium |
| Trapping Rain Water | Two Pointers / Stack | Hard |
| Maximum Product Subarray | Kadane variant | Medium |
| Subarray Sum Equals K | Prefix Sum + Hash | Medium |
| Sliding Window Maximum | Monotonic Deque | Hard |
