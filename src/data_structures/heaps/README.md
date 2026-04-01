# Heaps (Priority Queues)

A heap is a complete binary tree stored in an array that satisfies the **heap property**: in a min-heap, every parent ≤ its children; in a max-heap, every parent ≥ its children. The root is always the minimum (or maximum).

## Operations & Complexity

| Operation | Time | Notes |
|-----------|------|-------|
| peek (top) | O(1) | Always the min/max |
| push (insert) | O(log n) | Sift up |
| pop (remove top) | O(log n) | Sift down |
| build from array | O(n) | Floyd's algorithm |
| heapsort | O(n log n) | In-place |
| arbitrary search | O(n) | No structural property for arbitrary keys |

## ✅ When to Use

- Need to repeatedly find/remove the minimum or maximum
- K largest/smallest elements
- Merge K sorted lists
- Median of data stream (two heaps)
- Scheduling / task prioritization (Dijkstra)

## ❌ When NOT to Use

- Need arbitrary lookups → hash map
- Need sorted order with all elements → sorting or BST

## 📊 Interview Frequency

- **70%** at Amazon, Google, and others
- Almost always Medium difficulty
- Core of Dijkstra and Prim's algorithms

## C++ STL

```cpp
#include <queue>

// Max-heap (default)
std::priority_queue<int> max_pq;
max_pq.push(3);
max_pq.top();    // 3
max_pq.pop();

// Min-heap
std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;

// Custom comparator (for pairs: sort by second element)
using P = std::pair<int,int>;
auto cmp = [](const P& a, const P& b) { return a.second > b.second; };
std::priority_queue<P, std::vector<P>, decltype(cmp)> pq(cmp);
```

## Key Patterns

| Pattern | Technique | Examples |
|---------|-----------|---------|
| K largest elements | Min-heap of size K | Kth Largest, Top K Frequent |
| K smallest elements | Max-heap of size K | Kth Smallest, Closest K Points |
| Merge K sorted lists | Min-heap of current heads | Merge K Sorted Lists |
| Streaming median | Two heaps (max + min) | Find Median from Data Stream |
| Task scheduling | Max-heap with cooldown | Task Scheduler |
| Shortest path | Min-heap (Dijkstra) | Network Delay Time |

See [patterns.md](patterns.md) for implementations.
