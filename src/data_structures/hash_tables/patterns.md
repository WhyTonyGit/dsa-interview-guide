# Hash Table Interview Patterns

## Pattern 1: Frequency Counting

```cpp
// Count character frequencies
std::unordered_map<char, int> charFrequency(const std::string& s) {
    std::unordered_map<char, int> freq;
    for (char c : s) freq[c]++;
    return freq;
}

// Group Anagrams
std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> groups;
    for (const auto& s : strs) {
        std::string key = s;
        std::sort(key.begin(), key.end());
        groups[key].push_back(s);
    }
    std::vector<std::vector<std::string>> result;
    for (auto& [k, v] : groups) result.push_back(std::move(v));
    return result;
}

// Top K Frequent Elements
std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;
    // Bucket sort by frequency
    std::vector<std::vector<int>> buckets(nums.size() + 1);
    for (auto& [num, count] : freq) buckets[count].push_back(num);
    std::vector<int> result;
    for (int i = buckets.size() - 1; i >= 0 && (int)result.size() < k; --i)
        for (int x : buckets[i]) { result.push_back(x); if ((int)result.size() == k) break; }
    return result;
}
```

## Pattern 2: Two Sum / Complement Lookup

```cpp
// Two Sum — classic O(n) solution
std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen;  // value -> index
    for (int i = 0; i < (int)nums.size(); ++i) {
        int complement = target - nums[i];
        if (seen.count(complement)) return {seen[complement], i};
        seen[nums[i]] = i;
    }
    return {};
}

// Four Sum count (A[i] + B[j] + C[k] + D[l] == 0)
int fourSumCount(const std::vector<int>& A, const std::vector<int>& B,
                 const std::vector<int>& C, const std::vector<int>& D) {
    std::unordered_map<int, int> ab_sums;
    for (int a : A) for (int b : B) ab_sums[a + b]++;
    int count = 0;
    for (int c : C) for (int d : D) {
        auto it = ab_sums.find(-(c + d));
        if (it != ab_sums.end()) count += it->second;
    }
    return count;
}
```

## Pattern 3: Sliding Window with Hash Map

```cpp
// Minimum Window Substring
std::string minWindow(const std::string& s, const std::string& t) {
    std::unordered_map<char, int> need, window;
    for (char c : t) need[c]++;
    int have = 0, required = need.size();
    int min_len = INT_MAX, min_start = 0;
    int left = 0;
    for (int right = 0; right < (int)s.size(); ++right) {
        char c = s[right];
        window[c]++;
        if (need.count(c) && window[c] == need[c]) ++have;
        while (have == required) {
            if (right - left + 1 < min_len) {
                min_len = right - left + 1;
                min_start = left;
            }
            char lc = s[left++];
            window[lc]--;
            if (need.count(lc) && window[lc] < need[lc]) --have;
        }
    }
    return min_len == INT_MAX ? "" : s.substr(min_start, min_len);
}
```

## Pattern 4: Longest Consecutive Sequence

```cpp
// O(n) using hash set
int longestConsecutive(const std::vector<int>& nums) {
    std::unordered_set<int> num_set(nums.begin(), nums.end());
    int best = 0;
    for (int num : num_set) {
        if (!num_set.count(num - 1)) {  // start of a sequence
            int cur = num, length = 1;
            while (num_set.count(cur + 1)) { ++cur; ++length; }
            best = std::max(best, length);
        }
    }
    return best;
}
```

## Pattern 5: LRU Cache Design

```cpp
// O(1) get and put using doubly-linked list + hash map
class LRUCache {
    int capacity;
    std::list<std::pair<int,int>> lst;  // (key, value), front = most recent
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

## Common Interview Questions

| Question | Key Insight | Difficulty |
|----------|-------------|------------|
| Two Sum | Complement in hash map | Easy |
| Contains Duplicate | Hash set membership | Easy |
| Valid Anagram | Sort or freq count | Easy |
| Group Anagrams | Sorted key → hash map | Medium |
| Top K Frequent | Freq map + bucket sort | Medium |
| Minimum Window Substring | Sliding window + freq | Hard |
| Longest Consecutive Sequence | Hash set + sequence start | Medium |
| LRU Cache | List + hash map | Medium |
| Subarray Sum Equals K | Prefix sum + hash map | Medium |
