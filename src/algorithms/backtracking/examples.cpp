/**
 * @file examples.cpp
 * @brief Backtracking algorithm examples.
 *
 * Backtracking = DFS + pruning. Build a candidate solution step by step;
 * abandon (backtrack) when you determine the current path cannot lead to a valid solution.
 *
 * Template:
 *   void backtrack(state, choices) {
 *       if (base case) { add result; return; }
 *       for choice in choices:
 *           make choice
 *           backtrack(new state, remaining choices)
 *           undo choice   ← KEY: restore state
 *   }
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// ─── Permutations ─────────────────────────────────────────────────────────────

std::vector<std::vector<int>> permute(std::vector<int> nums) {
    std::vector<std::vector<int>> result;
    std::sort(nums.begin(), nums.end());
    do {
        result.push_back(nums);
    } while (std::next_permutation(nums.begin(), nums.end()));
    return result;
}

// Manual backtracking version
void permuteHelper(std::vector<int>& nums, int start,
                   std::vector<std::vector<int>>& result) {
    if (start == static_cast<int>(nums.size())) { result.push_back(nums); return; }
    for (int i = start; i < static_cast<int>(nums.size()); ++i) {
        std::swap(nums[start], nums[i]);
        permuteHelper(nums, start + 1, result);
        std::swap(nums[start], nums[i]);  // ← backtrack
    }
}

// ─── Subsets ──────────────────────────────────────────────────────────────────

std::vector<std::vector<int>> subsets(std::vector<int> nums) {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    std::function<void(int)> bt = [&](int start) {
        result.push_back(current);
        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            current.push_back(nums[i]);
            bt(i + 1);
            current.pop_back();  // ← backtrack
        }
    };
    bt(0);
    return result;
}

// ─── Combination Sum ──────────────────────────────────────────────────────────

std::vector<std::vector<int>>
combinationSum(std::vector<int> candidates, int target) {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    std::sort(candidates.begin(), candidates.end());
    std::function<void(int, int)> bt = [&](int start, int remaining) {
        if (remaining == 0) { result.push_back(current); return; }
        for (int i = start; i < static_cast<int>(candidates.size()); ++i) {
            if (candidates[i] > remaining) break;  // pruning
            current.push_back(candidates[i]);
            bt(i, remaining - candidates[i]);  // can reuse same element
            current.pop_back();
        }
    };
    bt(0, target);
    return result;
}

// ─── N-Queens ─────────────────────────────────────────────────────────────────

int totalNQueens(int n) {
    int count = 0;
    std::vector<int> col(n, 0), diag1(2*n, 0), diag2(2*n, 0);
    std::function<void(int)> bt = [&](int row) {
        if (row == n) { ++count; return; }
        for (int c = 0; c < n; ++c) {
            if (col[c] || diag1[row-c+n] || diag2[row+c]) continue;
            col[c] = diag1[row-c+n] = diag2[row+c] = 1;
            bt(row + 1);
            col[c] = diag1[row-c+n] = diag2[row+c] = 0;
        }
    };
    bt(0);
    return count;
}

// ─── Word Search ──────────────────────────────────────────────────────────────

bool wordSearch(std::vector<std::vector<char>>& board, const std::string& word) {
    int rows = board.size(), cols = board[0].size();
    std::function<bool(int,int,int)> dfs = [&](int r, int c, int idx) -> bool {
        if (idx == static_cast<int>(word.size())) return true;
        if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != word[idx])
            return false;
        char saved = board[r][c];
        board[r][c] = '#';  // mark visited
        bool found = dfs(r+1,c,idx+1) || dfs(r-1,c,idx+1) ||
                     dfs(r,c+1,idx+1) || dfs(r,c-1,idx+1);
        board[r][c] = saved;  // ← backtrack
        return found;
    };
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (dfs(r, c, 0)) return true;
    return false;
}

int main() {
    std::cout << "\n=== Permutations of [1,2,3] ===\n";
    auto perms = subsets({1,2,3});
    // Use permute for demo
    std::vector<int> p = {1,2,3};
    std::vector<std::vector<int>> perm_result;
    permuteHelper(p, 0, perm_result);
    std::cout << "Count: " << perm_result.size() << "  (expected 6)\n";

    std::cout << "\n=== Subsets of [1,2,3] ===\n";
    auto ss = subsets({1,2,3});
    std::cout << "Count: " << ss.size() << "  (expected 8: 2^3)\n";

    std::cout << "\n=== Combination Sum (target=7, candidates=[2,3,6,7]) ===\n";
    auto combs = combinationSum({2,3,6,7}, 7);
    std::cout << "Count: " << combs.size() << "  (expected 2: [7] and [2,2,3])\n";

    std::cout << "\n=== N-Queens (n=4) ===\n";
    std::cout << "Solutions: " << totalNQueens(4) << "  (expected 2)\n";

    std::cout << "\n=== Word Search ===\n";
    std::vector<std::vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    std::cout << "\"ABCCED\": " << (wordSearch(board, "ABCCED") ? "found" : "not found")
              << "  (expected found)\n";
    std::cout << "\"ABCB\":   " << (wordSearch(board, "ABCB") ? "found" : "not found")
              << "  (expected not found)\n";

    return 0;
}
