# Hash Tables

A hash table maps keys to values using a hash function to compute an index into a bucket array. Collisions (two keys hashing to the same bucket) are resolved via **separate chaining** (linked list per bucket) or **open addressing** (probe sequence).

**Average-case O(1)** for all major operations — the core reason hash tables appear in 90% of interview solutions.

## Operations & Complexity

| Operation | Average | Worst | Notes |
|-----------|---------|-------|-------|
| Insert | O(1) | O(n) | Worst case: all keys collide |
| Lookup | O(1) | O(n) | |
| Delete | O(1) | O(n) | |
| Space | — | O(n) | |

Load factor α = n/m (n = elements, m = buckets). Rehash when α > 0.75.

## ✅ When to Use

- Need O(1) lookup/insert/delete by key
- Counting frequencies (`freq[x]++`)
- Detecting duplicates
- Caching computed results
- Two Sum and related "complement" problems
- Grouping elements by property

## ❌ When NOT to Use

- Need **sorted order** → use `std::map` (BST, O(log n))
- Need **range queries** → use sorted structure
- Keys are not hashable or equality-comparable
- Memory is extremely tight (hash tables have overhead)

## 📊 Interview Frequency

- **90%** of solutions benefit from a hash table at some point
- Used in problems tagged: Array, String, Two Pointers, Sliding Window
- Virtually all companies ask hash table problems

## C++ STL Equivalents

```cpp
#include <unordered_map>
#include <unordered_set>

// Hash map: O(1) average operations
std::unordered_map<std::string, int> freq;
freq["apple"]++;              // insert / increment
freq.count("apple");          // 1 if exists, 0 if not
freq.find("apple");           // iterator, or .end() if not found
freq.erase("apple");          // O(1) average

// C++17: structured bindings for iteration
for (const auto& [key, val] : freq)
    std::cout << key << ": " << val << "\n";

// Hash set: unique elements, O(1) membership
std::unordered_set<int> seen;
seen.insert(42);
seen.count(42);  // 1 or 0

// Ordered map (Red-Black tree, O(log n))
std::map<std::string, int> ordered_map;
```

## Key Patterns

| Pattern | Example Problems |
|---------|-----------------|
| Frequency count | Top K Frequent, Group Anagrams |
| Existence check | Two Sum, Contains Duplicate |
| Index mapping | Two Sum, LRU Cache |
| Sliding window state | Minimum Window Substring |
| Complement lookup | 3Sum (reduce to 2Sum) |

See [patterns.md](patterns.md) for detailed implementations.
