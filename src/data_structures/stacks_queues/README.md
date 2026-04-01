# Stacks & Queues

**Stack** — LIFO (Last In, First Out). Like a stack of plates — you add and remove from the top.

**Queue** — FIFO (First In, First Out). Like a waiting line — you add to the back and remove from the front.

Both are abstract data types that can be implemented with arrays or linked lists.

## Operations & Complexity

### Stack

| Operation | Time | Notes |
|-----------|------|-------|
| push | O(1) | |
| pop | O(1) | |
| top / peek | O(1) | |
| isEmpty | O(1) | |

### Queue

| Operation | Time | Notes |
|-----------|------|-------|
| enqueue | O(1) amortized | Circular buffer or linked list |
| dequeue | O(1) | |
| front / peek | O(1) | |
| isEmpty | O(1) | |

## ✅ When to Use

**Stack:**
- Matching brackets / parentheses
- Undo/redo operations
- DFS traversal (iterative)
- Evaluating expressions
- Monotonic stack for "next greater element"

**Queue:**
- BFS traversal
- Level-order tree traversal
- Task scheduling (FIFO)
- Sliding window problems (deque)

## ❌ When NOT to Use

- Need random access → `std::vector`
- Need to search for arbitrary elements → hash map

## 📊 Interview Frequency

- **80%** of coding interviews involve stacks or queues
- Common in **Easy to Medium** problems
- Every BFS question uses a queue

## C++ STL Equivalents

```cpp
#include <stack>
#include <queue>
#include <deque>

// Stack
std::stack<int> s;
s.push(1);           // push
s.top();             // peek
s.pop();             // remove top

// Queue
std::queue<int> q;
q.push(1);           // enqueue
q.front();           // peek
q.pop();             // dequeue

// Deque (double-ended)
std::deque<int> d;
d.push_front(1);
d.push_back(2);
d.pop_front();
d.pop_back();
d[0];                // O(1) random access

// Priority queue (heap — max by default)
std::priority_queue<int> pq;
pq.push(3); pq.push(1); pq.push(5);
pq.top();    // 5
pq.pop();    // removes 5
```

## Key Interview Patterns

| Pattern | Data Structure | Problems |
|---------|---------------|---------|
| Bracket matching | Stack | Valid Parentheses |
| Next greater element | Monotonic Stack | Daily Temperatures |
| BFS level-order | Queue | Binary Tree Level Order |
| Min in O(1) | Stack + auxiliary stack | Min Stack |
| Sliding window max | Deque (monotonic) | Sliding Window Maximum |
| Queue from two stacks | Two Stacks | Implement Queue using Stacks |

See [patterns.md](patterns.md) for implementations.
