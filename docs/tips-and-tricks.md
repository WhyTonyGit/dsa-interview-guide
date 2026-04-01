# Interview Tips & Tricks

## The UMPIRE Framework

A structured approach to solving any coding problem:

| Letter | Meaning | What to do |
|--------|---------|------------|
| **U** | Understand | Restate the problem, ask clarifying questions |
| **M** | Match | Identify the pattern / data structure |
| **P** | Plan | Outline the algorithm before coding |
| **I** | Implement | Write clean, commented code |
| **R** | Review | Trace through with examples |
| **E** | Evaluate | State time and space complexity |

---

## Clarifying Questions to Always Ask

Before writing a single line of code:

```
1. "What is the range of input values?" (overflow risk?)
2. "Can the input be empty or null?"
3. "Are there duplicate values?"
4. "Is the array sorted?"
5. "What should I return if there's no solution?"
6. "Do I need to handle negative numbers?"
7. "What are the constraints on n?" (guides O(n²) vs O(n log n))
```

---

## Pattern Recognition Cheat Sheet

When you see this → think this:

| Problem keywords | Likely pattern |
|-----------------|----------------|
| "Find pair that sums to X" | Two Pointers / Hash Table |
| "Subarray / substring" | Sliding Window |
| "Sorted array, find position" | Binary Search |
| "Top K / K largest / K smallest" | Heap (priority_queue) |
| "Tree path / traversal" | DFS (recursive) |
| "Level by level / shortest path" | BFS |
| "Count paths / combinations" | Dynamic Programming |
| "Make choices at each step" | Greedy or Backtracking |
| "Connected components" | Union-Find or BFS/DFS |
| "String prefix search" | Trie |
| "Parentheses matching" | Stack |
| "Next greater element" | Monotonic Stack |
| "Repeated subproblem" | Memoization / DP |
| "All permutations / subsets" | Backtracking |
| "Intervals overlap" | Sort + Sweep |

---

## How to Communicate During Coding

### Starting out

```
"Let me make sure I understand the problem correctly. We have [restate].
The input is [type/range], and we need to return [output].
A few questions: [ask 2–3 clarifying questions]."
```

### Proposing your approach

```
"A brute force approach would be to [X], giving O(n²) time.
We can optimize this by [insight], reducing it to O(n log n).
Let me code up the optimized solution."
```

### While coding

```
"I'm initializing a hash map to track [what].
This loop processes each element once — that's O(n).
I'm handling the edge case where [...]."
```

### After coding

```
"Let me trace through the example: input [X], ...
Now let me check edge cases: empty input, single element, all duplicates.
The time complexity is O(n) because [reason].
The space complexity is O(n) for the hash map.
We could optimize space to O(1) by [approach], but at the cost of O(n²) time."
```

---

## When You're Stuck

1. **State what you know**: "I know I need to track [X] efficiently..."
2. **Start with brute force**: "A naive O(n²) solution would be..."
3. **Think aloud about optimizations**: "The bottleneck is [X]. Can I use a different data structure?"
4. **Ask for a hint gracefully**: "I'm thinking about [approach] but I'm not sure if that's right — any direction?"
5. **Don't panic-code**: Clean code with a suboptimal algorithm beats messy code with the right algorithm

---

## Red Flags (What NOT to Do)

- Jumping straight to code without discussing the approach
- Not asking about edge cases
- Writing code silently without explaining
- Changing approach without explaining why
- Ignoring the interviewer's hints
- Using `using namespace std;` in production code (acceptable in interviews with warning)
- Not cleaning up after yourself (memory leaks, dangling pointers)
- Claiming O(1) for a hash table without mentioning worst case

---

## Useful Phrases

| Situation | What to say |
|-----------|------------|
| Starting clarification | "Before I start coding, let me ask a few questions..." |
| Stating approach | "My plan is to use [X] because [reason]..." |
| Spotting edge case | "One thing to be careful about is when [edge case]..." |
| Complexity analysis | "This runs in O(n log n) because we sort once and..." |
| Acknowledging a hint | "Good point — that means I should use [X] instead of [Y]..." |
| Asking for direction | "I'm between two approaches: [A] or [B]. Which would you prefer?" |
| Finishing up | "This solution handles [cases]. The tradeoff vs an O(1)-space approach is..." |

---

## Practice Strategy

### Daily routine (1–2 hours)

1. Solve 1–2 problems on LeetCode (timed: 30 min each)
2. If stuck after 15 min → look at hints, not solution
3. After solving → read top solutions to learn optimal approaches
4. Write down the pattern/insight you missed

### Problem selection

- Start with problems tagged by the company you're targeting
- Focus on Medium difficulty (80% of real interviews)
- Revisit problems you got wrong after 3–7 days
- Track patterns, not specific problems

### Mock interviews

- Practice on paper or whiteboard, not just IDE
- Verbalize everything as you code
- Use Pramp or interviewing.io for realistic practice
- Time yourself strictly (45 minutes per problem)

---

## Interview Day Checklist

- [ ] Read the problem twice before writing anything
- [ ] Restate the problem in your own words
- [ ] Ask 2–3 clarifying questions
- [ ] Write out 1–2 examples manually
- [ ] State brute force complexity first
- [ ] Explain your optimized approach before coding
- [ ] Code cleanly with meaningful variable names
- [ ] Walk through your code with the example
- [ ] Check edge cases: empty, null, single, duplicates, negatives
- [ ] State final time and space complexity
- [ ] Ask if there's anything you missed
