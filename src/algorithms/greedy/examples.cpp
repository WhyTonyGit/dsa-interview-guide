/**
 * @file examples.cpp
 * @brief Greedy algorithm examples.
 *
 * Greedy: make the locally optimal choice at each step.
 * Works when greedy choice property holds + optimal substructure.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

// ─── Jump Game ────────────────────────────────────────────────────────────────

// Can you reach the last index from position 0?
bool canJump(const std::vector<int>& nums) {
    int max_reach = 0;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        if (i > max_reach) return false;
        max_reach = std::max(max_reach, i + nums[i]);
    }
    return true;
}

// Minimum number of jumps to reach last index
int jump(const std::vector<int>& nums) {
    int jumps = 0, cur_end = 0, farthest = 0;
    for (int i = 0; i < static_cast<int>(nums.size()) - 1; ++i) {
        farthest = std::max(farthest, i + nums[i]);
        if (i == cur_end) {
            ++jumps;
            cur_end = farthest;
        }
    }
    return jumps;
}

// ─── Non-overlapping Intervals ────────────────────────────────────────────────

// Minimum number of intervals to remove so none overlap (sort by end time)
int eraseOverlapIntervals(std::vector<std::vector<int>> intervals) {
    if (intervals.empty()) return 0;
    std::sort(intervals.begin(), intervals.end(),
              [](const auto& a, const auto& b){ return a[1] < b[1]; });
    int count = 0, last_end = intervals[0][1];
    for (int i = 1; i < static_cast<int>(intervals.size()); ++i) {
        if (intervals[i][0] < last_end) ++count;   // overlap — remove
        else last_end = intervals[i][1];             // keep
    }
    return count;
}

// ─── Task Scheduler ───────────────────────────────────────────────────────────

int leastInterval(const std::vector<char>& tasks, int n) {
    std::vector<int> freq(26, 0);
    for (char t : tasks) ++freq[t - 'A'];
    std::sort(freq.rbegin(), freq.rend());
    int max_freq = freq[0];
    int max_count = std::count(freq.begin(), freq.end(), max_freq);
    return std::max(static_cast<int>(tasks.size()),
                    (max_freq - 1) * (n + 1) + max_count);
}

int main() {
    std::cout << "\n=== Jump Game ===\n";
    std::cout << "canJump([2,3,1,1,4]) = " << (canJump({2,3,1,1,4}) ? "true" : "false")
              << "  (expected true)\n";
    std::cout << "canJump([3,2,1,0,4]) = " << (canJump({3,2,1,0,4}) ? "true" : "false")
              << "  (expected false)\n";

    std::cout << "\n=== Minimum Jumps ===\n";
    std::cout << "jump([2,3,1,1,4]) = " << jump({2,3,1,1,4}) << "  (expected 2)\n";

    std::cout << "\n=== Non-overlapping Intervals ===\n";
    std::vector<std::vector<int>> ivs = {{1,2},{2,3},{3,4},{1,3}};
    std::cout << "eraseOverlapIntervals = " << eraseOverlapIntervals(ivs) << "  (expected 1)\n";

    std::cout << "\n=== Task Scheduler ===\n";
    std::vector<char> tasks = {'A','A','A','B','B','B'};
    std::cout << "leastInterval(n=2) = " << leastInterval(tasks, 2) << "  (expected 8)\n";

    return 0;
}
