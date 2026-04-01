# Arrays

Arrays are contiguous blocks of memory storing elements of the same type. The dynamic array (like `std::vector`) grows automatically by doubling capacity, giving amortized O(1) appends. It is the most frequently tested data structure in technical interviews.

## Operations & Complexity

| Operation | Time | Space | Notes |
|-----------|------|-------|-------|
| Access by index | O(1) | O(1) | Direct memory calculation |
| Search (unsorted) | O(n) | O(1) | Linear scan |
| Search (sorted) | O(log n) | O(1) | Binary search |
| Append (push_back) | O(1)* | O(1)* | *amortized; O(n) on reallocation |
| Insert at position i | O(n) | O(1) | Shifts n-i elements |
| Delete at position i | O(n) | O(1) | Shifts n-i elements |
| Sort | O(n log n) | O(log n) | std::sort uses introsort |
| Reverse | O(n) | O(1) | |

## ✅ When to Use Arrays

- You need **random access** (O(1) by index)
- Data size is known ahead of time
- Cache-friendly iteration over sequential data
- As a building block for other structures (heaps, hash tables)
- Implementing sliding window, two-pointer, or prefix sum techniques

## ❌ When NOT to Use Arrays

- Frequent insertions/deletions in the **middle** → use `std::list` or `std::deque`
- Unknown or highly variable size with many inserts/deletes at arbitrary positions
- Need O(1) search by value → use `std::unordered_set`

## 📊 Interview Frequency

- **95%** of coding interviews involve arrays at some point
- **All major companies**: Google, Meta, Amazon, Apple, Microsoft
- Typically at **Easy to Hard** difficulty

## C++ Specifics

```cpp
// std::vector — the go-to dynamic array
#include <vector>
std::vector<int> v = {1, 2, 3};
v.push_back(4);          // O(1) amortized
v.insert(v.begin(), 0);  // O(n) — avoid in hot paths
v.erase(v.begin() + 1);  // O(n)
std::sort(v.begin(), v.end());  // O(n log n)

// 2D array
std::vector<std::vector<int>> matrix(3, std::vector<int>(3, 0));

// Reserve to avoid reallocations
v.reserve(1000);  // pre-allocate without changing size

// Prefix sums (very common pattern)
std::vector<int> prefix(v.size() + 1, 0);
for (int i = 0; i < (int)v.size(); ++i)
    prefix[i + 1] = prefix[i] + v[i];
// Range sum [l, r]: prefix[r+1] - prefix[l]
```

## Key Techniques

| Technique | Description | Examples |
|-----------|-------------|---------|
| Two Pointers | Left/right or slow/fast pointers | Two Sum, Remove Duplicates |
| Sliding Window | Variable or fixed window over subarray | Max Subarray, Longest Substring |
| Prefix Sum | Precompute cumulative sums | Range Query, Subarray Sum |
| Sorting + Scan | Sort first, then linear scan | Meeting Rooms, Merge Intervals |
| Binary Search | On sorted arrays | Search in Rotated Array |

See [patterns.md](patterns.md) for detailed examples.
