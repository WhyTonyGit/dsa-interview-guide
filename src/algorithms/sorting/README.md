# Sorting Algorithms

## Complexity Summary

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| **Merge Sort** | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| **Heap Sort** | O(n log n) | O(n log n) | O(n log n) | O(1) | No |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Counting Sort | O(n+k) | O(n+k) | O(n+k) | O(k) | Yes |
| Tim Sort (STL) | O(n) | O(n log n) | O(n log n) | O(n) | Yes |

## When to Use Which

| Scenario | Best Choice |
|----------|-------------|
| General purpose | `std::sort` (introsort = quicksort + heapsort) |
| Need stability | `std::stable_sort` (merge sort) |
| Small or nearly sorted | Insertion sort |
| Integer range known and small | Counting sort or Radix sort |
| Memory-constrained in-place | Heap sort |
| External sort (disk) | Merge sort |

## Interview Notes

In C++ interviews:
- **Just use `std::sort`** unless asked to implement
- Know Merge Sort and Quick Sort conceptually
- Understand *why* Quick Sort is faster in practice (better cache, no extra memory)
- Know that `std::sort` is not stable — use `std::stable_sort` if order of equal elements matters

```cpp
std::sort(v.begin(), v.end());                      // ascending
std::sort(v.begin(), v.end(), std::greater<int>()); // descending
std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
    return a.second < b.second;  // sort by second element
});
```
