# Interview Frequency Guide

> Based on analysis of LeetCode, Glassdoor, and community reports from 2021–2024.

## Topic Frequency by Company

### FAANG / Big Tech

| Topic | Google | Meta | Amazon | Apple | Microsoft | Netflix |
|-------|--------|------|--------|-------|-----------|---------|
| Arrays / Strings | ★★★★★ | ★★★★★ | ★★★★★ | ★★★★★ | ★★★★★ | ★★★★★ |
| Hash Tables | ★★★★★ | ★★★★★ | ★★★★★ | ★★★★ | ★★★★★ | ★★★★★ |
| Trees / BST | ★★★★★ | ★★★★★ | ★★★★ | ★★★★★ | ★★★★★ | ★★★★ |
| Dynamic Programming | ★★★★★ | ★★★★ | ★★★★★ | ★★★★ | ★★★★★ | ★★★★ |
| Graphs | ★★★★★ | ★★★★★ | ★★★★ | ★★★★ | ★★★★ | ★★★ |
| Linked Lists | ★★★★ | ★★★★★ | ★★★★ | ★★★★ | ★★★★ | ★★★ |
| Heaps / Priority Queue | ★★★★ | ★★★★ | ★★★★★ | ★★★ | ★★★★ | ★★★★ |
| Binary Search | ★★★★★ | ★★★★ | ★★★★★ | ★★★★ | ★★★★ | ★★★★ |
| Stacks / Queues | ★★★★ | ★★★★ | ★★★★ | ★★★ | ★★★★ | ★★★ |
| Tries | ★★★★ | ★★★ | ★★★ | ★★★ | ★★★ | ★★ |
| Union-Find | ★★★ | ★★★★ | ★★★ | ★★ | ★★★ | ★★ |
| Bit Manipulation | ★★★ | ★★★ | ★★★ | ★★★★ | ★★★ | ★★ |

### Mid-size Tech (Airbnb, Uber, Lyft, Stripe, Dropbox)

| Topic | Frequency |
|-------|-----------|
| Arrays + Hash Tables | 95% of interviews |
| Trees | 75% |
| Graphs | 65% |
| DP | 55% |
| Design (LRU, etc.) | 50% |
| Linked Lists | 45% |

### Startups (Series A–C)

- Heavy focus on practical algorithms (sorting, searching)
- Less emphasis on exotic structures (Trie, Segment Tree)
- More system design questions than at FAANG
- Whiteboard coding less common, take-home more common

---

## Frequency by Interview Round

| Round | What to Expect |
|-------|---------------|
| Phone Screen | Arrays, Strings, basic Hash Tables (Easy–Medium) |
| Technical 1 | Linked Lists, Trees, Stacks/Queues (Medium) |
| Technical 2 | Graphs, DP, or advanced Trees (Medium–Hard) |
| Technical 3 | System design + one algorithm (varies) |
| Onsite | Mix of all topics, emphasis on problem-solving process |

---

## Difficulty Distribution

### What "Easy / Medium / Hard" means in practice

| Level | LeetCode | Real Interview |
|-------|----------|---------------|
| Easy | Straightforward, one concept | Often used as warm-up |
| Medium | 1–2 insights needed | ~80% of technical screens |
| Hard | Multiple insights, optimizations | Senior / Staff roles |

### Most Asked LeetCode Problems (2023–2024)

**Top 20 by company reports:**

1. Two Sum (Arrays + Hash)
2. LRU Cache (Linked List + Hash)
3. Merge K Sorted Lists (Heap)
4. Word Break (DP + Trie)
5. Number of Islands (Graph BFS/DFS)
6. Serialize/Deserialize Binary Tree
7. Find Median from Data Stream (Two Heaps)
8. Trapping Rain Water (Two Pointers / Stack)
9. Course Schedule (Topological Sort)
10. Longest Palindromic Substring (DP / Expand Around Center)
11. Valid Parentheses (Stack)
12. Binary Tree Level Order Traversal (BFS)
13. Clone Graph (DFS/BFS)
14. Meeting Rooms II (Intervals + Heap)
15. Coin Change (DP)
16. Maximum Subarray (Kadane's Algorithm)
17. Climbing Stairs (DP)
18. Reverse Linked List
19. Product of Array Except Self
20. Word Search (Backtracking)

---

## Interview Frequency by Experience Level

### Junior (0–2 years)

| Priority | Topics |
|----------|--------|
| Must Know | Arrays, Strings, Hash Tables, Stacks/Queues |
| Important | Linked Lists, Binary Trees (traversal) |
| Good to Have | Sorting algorithms, basic Recursion |

### Mid-level (2–5 years)

| Priority | Topics |
|----------|--------|
| Must Know | All Junior topics + Graphs (BFS/DFS), BST |
| Important | Heaps, DP (1D), Binary Search variants |
| Good to Have | Tries, Union-Find |

### Senior (5+ years)

| Priority | Topics |
|----------|--------|
| Must Know | All Mid-level topics + Advanced DP, Graph algorithms |
| Important | Tries, Segment Trees, AVL/Red-Black Trees |
| Heavy Focus | System Design, scalability, trade-offs |

---

## Time Allocation in a 45-minute Interview

| Phase | Duration | Notes |
|-------|----------|-------|
| Clarify problem | 3–5 min | Ask constraints, edge cases |
| Discuss approach | 5–7 min | Brute force → optimized |
| Code solution | 20–25 min | Talk while coding |
| Test & debug | 5–7 min | Walk through examples |
| Discuss complexity | 2–3 min | Time and space |
