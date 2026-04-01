# Binary Search

Binary search divides the search space in half each iteration, achieving O(log n) performance. It applies not only to sorted arrays but to **any problem with a monotonic structure**.

## Template (memorize this)

```cpp
int lo = 0, hi = n - 1;
while (lo <= hi) {           // ← note: <=
    int mid = lo + (hi - lo) / 2;  // ← avoids overflow
    if (arr[mid] == target) return mid;
    else if (arr[mid] < target) lo = mid + 1;
    else hi = mid - 1;
}
return -1;
```

## Lower Bound (first position >= target)

```cpp
int lo = 0, hi = n;  // hi = n, not n-1
while (lo < hi) {    // ← note: strict <
    int mid = lo + (hi - lo) / 2;
    if (arr[mid] < target) lo = mid + 1;
    else hi = mid;
}
return lo;
```

## Binary Search on Answer

When the problem asks "find the minimum/maximum value X such that condition holds":

```
If condition(X) is false...false...TRUE...true (monotonic), binary search on X.
```

Examples: "minimum eating speed", "minimum capacity to ship packages", "minimum days to bloom flowers"

## Interview Frequency

- **95%** of sorting/array questions benefit from binary search
- Variants appear in **almost every technical interview**

See [examples.cpp](examples.cpp) for working examples.
