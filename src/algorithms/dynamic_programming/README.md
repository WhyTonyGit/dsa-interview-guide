# Dynamic Programming

DP solves problems by breaking them into **overlapping subproblems** and storing results to avoid recomputation. If a problem has:
1. **Optimal substructure** (optimal solution contains optimal subsolutions)
2. **Overlapping subproblems** (same subproblem solved multiple times in recursion)

...then DP applies.

## DP Patterns

| Pattern | Examples |
|---------|---------|
| 1D Linear | Fibonacci, Climbing Stairs, House Robber |
| 2D Grid | Unique Paths, Minimum Path Sum |
| 2-Sequence | LCS, Edit Distance |
| Knapsack | 0/1 Knapsack, Coin Change |
| Interval | Palindromic Substrings, Burst Balloons |
| Tree DP | Binary Tree Maximum Path Sum |
| Bitmask DP | Traveling Salesman, Subsets |

## Framework

```
1. Define state: dp[i] means "answer for subproblem ending at i"
2. Write recurrence: dp[i] = f(dp[i-1], dp[i-2], ...)
3. Base case: dp[0], dp[1]
4. Order: ensure dp[i] is computed before dp[i+1]
5. Answer: usually dp[n] or max(dp)
```

## Top-Down vs Bottom-Up

```cpp
// Top-Down (memoization) — easier to write for complex states
int fib(int n, vector<int>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fib(n-1, memo) + fib(n-2, memo);
}

// Bottom-Up (tabulation) — often more efficient, no recursion overhead
int fib(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) { int c = a+b; a=b; b=c; }
    return b;
}
```

## Interview Frequency

- **95%** at Google, Amazon, Meta — especially Medium/Hard problems
- DP is the most feared topic; mastering it separates good candidates
