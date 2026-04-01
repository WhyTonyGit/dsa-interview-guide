#pragma once

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * @file dp_examples.hpp
 * @brief Classic dynamic programming problems.
 *
 * DP = break a problem into overlapping subproblems, solve each once, cache results.
 *
 * Two approaches:
 *   - Top-down (memoization): recursion + cache
 *   - Bottom-up (tabulation): fill table iteratively
 */

namespace dp {

// ─── 1. Fibonacci (intro to DP) ───────────────────────────────────────────────

/** @brief Fibonacci with bottom-up DP. O(n) time, O(1) space. */
long long fibonacci(int n) {
    if (n <= 1) return n;
    long long prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; ++i) {
        long long cur = prev1 + prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// ─── 2. Climbing Stairs ────────────────────────────────────────────────────────

/** @brief Count ways to climb n stairs taking 1 or 2 steps. O(n), O(1). */
int climbing_stairs(int n) {
    if (n <= 2) return n;
    int a = 1, b = 2;
    for (int i = 3; i <= n; ++i) {
        int c = a + b; a = b; b = c;
    }
    return b;
}

// ─── 3. Coin Change ────────────────────────────────────────────────────────────

/**
 * @brief Minimum coins to make amount. Returns -1 if impossible.
 * @complexity O(amount * coins) time, O(amount) space
 */
int coin_change(const std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i)
        for (int coin : coins)
            if (coin <= i) dp[i] = std::min(dp[i], dp[i - coin] + 1);
    return dp[amount] > amount ? -1 : dp[amount];
}

// ─── 4. Longest Increasing Subsequence (LIS) ─────────────────────────────────

/**
 * @brief Length of longest strictly increasing subsequence.
 * @complexity O(n log n) with patience sorting
 */
int lis(const std::vector<int>& nums) {
    std::vector<int> tails;  // tails[i] = smallest tail of IS with length i+1
    for (int x : nums) {
        auto it = std::lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return static_cast<int>(tails.size());
}

// ─── 5. Longest Common Subsequence (LCS) ─────────────────────────────────────

/**
 * @brief Length of LCS of strings s1 and s2.
 * @complexity O(m*n) time and space
 */
int lcs(const std::string& s1, const std::string& s2) {
    int m = s1.size(), n = s2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            dp[i][j] = (s1[i-1] == s2[j-1]) ? dp[i-1][j-1] + 1
                                              : std::max(dp[i-1][j], dp[i][j-1]);
    return dp[m][n];
}

// ─── 6. 0/1 Knapsack ─────────────────────────────────────────────────────────

/**
 * @brief Maximum value for capacity W given items with weights and values.
 * @complexity O(n * W) time and space
 */
int knapsack(const std::vector<int>& weights, const std::vector<int>& values, int W) {
    int n = weights.size();
    std::vector<int> dp(W + 1, 0);
    for (int i = 0; i < n; ++i)
        for (int w = W; w >= weights[i]; --w)  // traverse backwards for 0/1 knapsack
            dp[w] = std::max(dp[w], dp[w - weights[i]] + values[i]);
    return dp[W];
}

// ─── 7. Edit Distance ─────────────────────────────────────────────────────────

/**
 * @brief Minimum edit distance (Levenshtein) between word1 and word2.
 * Operations: insert, delete, replace (each costs 1).
 * @complexity O(m*n) time and space
 */
int edit_distance(const std::string& word1, const std::string& word2) {
    int m = word1.size(), n = word2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            dp[i][j] = (word1[i-1] == word2[j-1])
                ? dp[i-1][j-1]
                : 1 + std::min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
    return dp[m][n];
}

// ─── 8. Word Break ────────────────────────────────────────────────────────────

/**
 * @brief Can s be segmented into words from wordDict?
 * @complexity O(n^2 * w) time where w = max word length
 */
bool word_break(const std::string& s,
                const std::vector<std::string>& wordDict) {
    std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
    int n = s.size();
    std::vector<bool> dp(n + 1, false);
    dp[0] = true;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < i; ++j)
            if (dp[j] && dict.count(s.substr(j, i - j))) { dp[i] = true; break; }
    return dp[n];
}

// ─── 9. House Robber ─────────────────────────────────────────────────────────

/**
 * @brief Maximum money from non-adjacent houses.
 * @complexity O(n) time, O(1) space
 */
int house_robber(const std::vector<int>& nums) {
    int prev2 = 0, prev1 = 0;
    for (int x : nums) {
        int cur = std::max(prev1, prev2 + x);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// ─── 10. Unique Paths ─────────────────────────────────────────────────────────

/**
 * @brief Count unique paths in m×n grid from top-left to bottom-right.
 * @complexity O(m*n) time and space
 */
int unique_paths(int m, int n) {
    std::vector<int> dp(n, 1);
    for (int i = 1; i < m; ++i)
        for (int j = 1; j < n; ++j)
            dp[j] += dp[j - 1];
    return dp[n - 1];
}

}  // namespace dp
