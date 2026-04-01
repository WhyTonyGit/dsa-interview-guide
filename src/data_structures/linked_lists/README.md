# Linked Lists

A linked list is a sequential structure where each element (node) stores a value and a pointer to the next node. Unlike arrays, elements are not stored contiguously — this allows O(1) insertions and deletions at known positions, but O(n) random access.

## Types

| Type | Pointers per node | Back-insert | Back-delete |
|------|------------------|-------------|-------------|
| Singly-linked | next | O(1)† | O(n) |
| Doubly-linked | prev + next | O(1) | O(1) |
| Circular | wraps around | O(1) | O(1) |

† = with tail pointer

## Operations & Complexity

| Operation | Singly | Doubly | Notes |
|-----------|--------|--------|-------|
| Access by index | O(n) | O(n) | Must traverse from head |
| Search | O(n) | O(n) | Linear scan |
| Insert at head | O(1) | O(1) | |
| Insert at tail | O(1)† | O(1) | With tail pointer |
| Insert at position | O(n) | O(n) | Must find position first |
| Delete at head | O(1) | O(1) | |
| Delete at tail | O(n) | O(1) | Singly needs traversal |
| Delete known node | O(n) | O(1) | Doubly: can remove directly |

## ✅ When to Use

- Need O(1) **insertions/deletions at the front** (e.g., implementing a stack/queue)
- Size changes frequently and unpredictably
- Implementing LRU Cache (doubly-linked list + hash map)
- Representing sequences where you have a pointer to the position

## ❌ When NOT to Use

- Need fast random access → use `std::vector`
- Cache efficiency matters (arrays have better cache locality)
- Memory is tight (each node carries pointer overhead)

## 📊 Interview Frequency

- **85%** of interviews at Google, Meta, Amazon include a linked list question
- Usually at **Easy to Medium** difficulty
- Common in phone screens as "warm-up"

## C++ Implementation Note

In interviews, linked list nodes are usually given as raw structs:

```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```

`std::list<T>` (doubly-linked) is available in STL but rarely used in interviews — interviewers want you to manipulate raw pointers.

## Key Patterns

| Pattern | Technique | Problems |
|---------|-----------|---------|
| Cycle detection | Fast/slow pointers | Linked List Cycle |
| Find middle | Fast/slow pointers | Middle of Linked List |
| Reverse | Three-pointer iterative | Reverse Linked List |
| Merge sorted | Dummy head + two pointers | Merge Two Sorted Lists |
| K-th from end | Two pointers, gap K | Remove Nth From End |
| Palindrome check | Find middle + reverse half | Palindrome Linked List |

See [patterns.md](patterns.md) for detailed implementations.
