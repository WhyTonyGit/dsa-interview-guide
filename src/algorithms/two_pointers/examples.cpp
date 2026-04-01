/**
 * @file examples.cpp
 * @brief Two-pointer and sliding window pattern examples.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// ─── Three Sum ────────────────────────────────────────────────────────────────

std::vector<std::vector<int>> threeSum(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> result;
    for (int i = 0; i < static_cast<int>(nums.size()) - 2; ++i) {
        if (i > 0 && nums[i] == nums[i-1]) continue;  // skip duplicates
        int lo = i + 1, hi = static_cast<int>(nums.size()) - 1;
        while (lo < hi) {
            int sum = nums[i] + nums[lo] + nums[hi];
            if (sum == 0) {
                result.push_back({nums[i], nums[lo], nums[hi]});
                while (lo < hi && nums[lo] == nums[lo+1]) ++lo;
                while (lo < hi && nums[hi] == nums[hi-1]) --hi;
                ++lo; --hi;
            } else if (sum < 0) ++lo;
            else --hi;
        }
    }
    return result;
}

// ─── Container with Most Water ────────────────────────────────────────────────

int maxArea(const std::vector<int>& height) {
    int lo = 0, hi = static_cast<int>(height.size()) - 1, max_water = 0;
    while (lo < hi) {
        max_water = std::max(max_water, std::min(height[lo], height[hi]) * (hi - lo));
        if (height[lo] < height[hi]) ++lo;
        else --hi;
    }
    return max_water;
}

// ─── Minimum Size Subarray Sum ─────────────────────────────────────────────────

int minSubArrayLen(int target, const std::vector<int>& nums) {
    int min_len = INT_MAX, sum = 0, left = 0;
    for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
        sum += nums[right];
        while (sum >= target) {
            min_len = std::min(min_len, right - left + 1);
            sum -= nums[left++];
        }
    }
    return min_len == INT_MAX ? 0 : min_len;
}

// ─── Longest Substring with at Most K Distinct Characters ────────────────────

int lengthOfLongestSubstringKDistinct(const std::string& s, int k) {
    std::unordered_map<char, int> freq;
    int max_len = 0, left = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        ++freq[s[right]];
        while (static_cast<int>(freq.size()) > k) {
            if (--freq[s[left]] == 0) freq.erase(s[left]);
            ++left;
        }
        max_len = std::max(max_len, right - left + 1);
    }
    return max_len;
}

// ─── Sort Colors (Dutch National Flag) ───────────────────────────────────────

void sortColors(std::vector<int>& nums) {
    int lo = 0, mid = 0, hi = static_cast<int>(nums.size()) - 1;
    while (mid <= hi) {
        if (nums[mid] == 0) { std::swap(nums[lo++], nums[mid++]); }
        else if (nums[mid] == 1) { ++mid; }
        else { std::swap(nums[mid], nums[hi--]); }
    }
}

int main() {
    std::cout << "\n=== Three Sum ===\n";
    auto triples = threeSum({-1,0,1,2,-1,-4});
    std::cout << "Count of triples summing to 0: " << triples.size() << "  (expected 2)\n";
    for (const auto& t : triples)
        std::cout << "  [" << t[0] << "," << t[1] << "," << t[2] << "]\n";

    std::cout << "\n=== Container with Most Water ===\n";
    std::cout << "maxArea([1,8,6,2,5,4,8,3,7]) = "
              << maxArea({1,8,6,2,5,4,8,3,7}) << "  (expected 49)\n";

    std::cout << "\n=== Minimum Subarray Length ===\n";
    std::cout << "minSubArrayLen(target=7, [2,3,1,2,4,3]) = "
              << minSubArrayLen(7, {2,3,1,2,4,3}) << "  (expected 2)\n";

    std::cout << "\n=== Longest Substring K Distinct ===\n";
    std::cout << "\"eceba\", k=2: " << lengthOfLongestSubstringKDistinct("eceba", 2)
              << "  (expected 3: 'ece')\n";

    std::cout << "\n=== Sort Colors (Dutch Flag) ===\n";
    std::vector<int> colors = {2,0,2,1,1,0};
    sortColors(colors);
    std::cout << "Sorted: [";
    for (std::size_t i = 0; i < colors.size(); ++i)
        std::cout << colors[i] << (i+1 < colors.size() ? "," : "");
    std::cout << "]  (expected [0,0,1,1,2,2])\n";

    return 0;
}
