# Heap Interview Patterns

## Pattern 1: K Largest / K Smallest Elements

```cpp
// K largest — maintain a min-heap of size K
std::vector<int> kLargest(const std::vector<int>& nums, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    for (int x : nums) {
        min_heap.push(x);
        if ((int)min_heap.size() > k) min_heap.pop();
    }
    std::vector<int> result;
    while (!min_heap.empty()) { result.push_back(min_heap.top()); min_heap.pop(); }
    return result;  // ascending order
}

// Kth largest element
int findKthLargest(const std::vector<int>& nums, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    for (int x : nums) {
        min_heap.push(x);
        if ((int)min_heap.size() > k) min_heap.pop();
    }
    return min_heap.top();
}
```

## Pattern 2: Merge K Sorted Lists

```cpp
// Use min-heap to always pick the smallest current head
struct ListNode { int val; ListNode* next; ListNode(int v) : val(v), next(nullptr) {} };

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)> pq(cmp);
    for (ListNode* l : lists) if (l) pq.push(l);

    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (!pq.empty()) {
        ListNode* node = pq.top(); pq.pop();
        tail->next = node;
        tail = tail->next;
        if (node->next) pq.push(node->next);
    }
    return dummy.next;
}
```

## Pattern 3: Meeting Rooms II (Minimum Conference Rooms)

```cpp
int minMeetingRooms(std::vector<std::vector<int>>& intervals) {
    std::sort(intervals.begin(), intervals.end());
    std::priority_queue<int, std::vector<int>, std::greater<int>> end_times;
    for (const auto& iv : intervals) {
        if (!end_times.empty() && end_times.top() <= iv[0])
            end_times.pop();  // reuse a room
        end_times.push(iv[1]);
    }
    return (int)end_times.size();
}
```

## Pattern 4: Task Scheduler

```cpp
int leastInterval(const std::vector<char>& tasks, int n) {
    std::unordered_map<char, int> freq;
    for (char t : tasks) freq[t]++;
    std::priority_queue<int> max_heap;
    for (auto& [c, f] : freq) max_heap.push(f);
    int time = 0;
    while (!max_heap.empty()) {
        std::vector<int> temp;
        for (int i = 0; i <= n; ++i) {
            if (!max_heap.empty()) { temp.push_back(max_heap.top() - 1); max_heap.pop(); }
        }
        for (int f : temp) if (f > 0) max_heap.push(f);
        time += max_heap.empty() ? (int)temp.size() : n + 1;
    }
    return time;
}
```

## Pattern 5: K Closest Points to Origin

```cpp
std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
    // Max-heap by distance — keeps K smallest
    auto cmp = [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
    };
    std::priority_queue<std::vector<int>,
                        std::vector<std::vector<int>>,
                        decltype(cmp)> pq(cmp);
    for (auto& p : points) {
        pq.push(p);
        if ((int)pq.size() > k) pq.pop();
    }
    std::vector<std::vector<int>> result;
    while (!pq.empty()) { result.push_back(pq.top()); pq.pop(); }
    return result;
}
```

## Common Interview Questions

| Question | Pattern | Difficulty |
|----------|---------|------------|
| Kth Largest Element in Array | Min-heap of size K | Medium |
| Top K Frequent Elements | Min-heap + freq map | Medium |
| K Closest Points to Origin | Max-heap of size K | Medium |
| Find Median from Data Stream | Two heaps | Hard |
| Merge K Sorted Lists | Min-heap | Hard |
| Meeting Rooms II | Min-heap of end times | Medium |
| Task Scheduler | Max-heap with cooldown | Medium |
| Reorganize String | Max-heap greedy | Medium |
