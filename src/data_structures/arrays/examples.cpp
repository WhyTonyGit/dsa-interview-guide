/**
 * @file examples.cpp
 * @brief Runnable examples demonstrating DynamicArray and common array patterns.
 *
 * Compile & run:
 *   cd build && cmake .. && make examples_arrays && ./examples_arrays
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "data_structures/arrays/array.hpp"

// ─── Helpers ──────────────────────────────────────────────────────────────────

template <typename T>
void print(const std::string& label, const DynamicArray<T>& arr) {
    std::cout << label << ": [";
    for (std::size_t i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << (i + 1 < arr.size() ? ", " : "");
    std::cout << "]\n";
}

template <typename T>
void print(const std::string& label, const std::vector<T>& v) {
    std::cout << label << ": [";
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << (i + 1 < v.size() ? ", " : "");
    std::cout << "]\n";
}

// ─── 1. DynamicArray basics ───────────────────────────────────────────────────

void demo_dynamic_array() {
    std::cout << "\n=== DynamicArray Basics ===\n";

    DynamicArray<int> arr = {10, 20, 30, 40, 50};
    print("Initial", arr);

    arr.push_back(60);
    print("After push_back(60)", arr);

    arr.insert(2, 25);   // insert 25 at index 2
    print("After insert(2, 25)", arr);

    arr.erase(0);        // remove element at index 0
    print("After erase(0)", arr);

    arr.pop_back();
    print("After pop_back()", arr);

    std::cout << "Size: " << arr.size() << ", Capacity: " << arr.capacity() << "\n";
    std::cout << "Front: " << arr.front() << ", Back: " << arr.back() << "\n";
    std::cout << "Element at index 1: " << arr.at(1) << "\n";

    arr.sort();
    print("After sort()", arr);

    arr.reverse();
    print("After reverse()", arr);

    // Copy semantics
    DynamicArray<int> copy = arr;
    copy[0] = 999;
    print("Original after modifying copy", arr);  // should be unchanged
}

// ─── 2. Two Sum (unsorted) ────────────────────────────────────────────────────

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        int complement = target - nums[i];
        auto it = seen.find(complement);
        if (it != seen.end()) return {it->second, i};
        seen[nums[i]] = i;
    }
    return {};
}

// ─── 3. Maximum Subarray (Kadane's Algorithm) ─────────────────────────────────

int maxSubArray(const std::vector<int>& nums) {
    int current = nums[0], best = nums[0];
    for (int i = 1; i < static_cast<int>(nums.size()); ++i) {
        current = std::max(nums[i], current + nums[i]);
        best    = std::max(best, current);
    }
    return best;
}

// ─── 4. Merge Intervals ───────────────────────────────────────────────────────

std::vector<std::vector<int>> mergeIntervals(std::vector<std::vector<int>> intervals) {
    std::sort(intervals.begin(), intervals.end());
    std::vector<std::vector<int>> result;
    for (const auto& iv : intervals) {
        if (!result.empty() && iv[0] <= result.back()[1])
            result.back()[1] = std::max(result.back()[1], iv[1]);
        else
            result.push_back(iv);
    }
    return result;
}

// ─── 5. Longest Substring Without Repeating Characters ───────────────────────

int lengthOfLongestSubstring(const std::string& s) {
    std::unordered_map<char, int> last_seen;
    int max_len = 0, left = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        auto it = last_seen.find(s[right]);
        if (it != last_seen.end() && it->second >= left)
            left = it->second + 1;
        last_seen[s[right]] = right;
        max_len = std::max(max_len, right - left + 1);
    }
    return max_len;
}

// ─── 6. Product of Array Except Self ─────────────────────────────────────────

std::vector<int> productExceptSelf(const std::vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    std::vector<int> result(n, 1);
    // Forward pass: result[i] = product of all elements to the left
    for (int i = 1; i < n; ++i)
        result[i] = result[i - 1] * nums[i - 1];
    // Backward pass: multiply by product of all elements to the right
    int right_product = 1;
    for (int i = n - 1; i >= 0; --i) {
        result[i] *= right_product;
        right_product *= nums[i];
    }
    return result;
}

// ─── 7. Trapping Rain Water ───────────────────────────────────────────────────

int trap(const std::vector<int>& height) {
    int lo = 0, hi = static_cast<int>(height.size()) - 1;
    int left_max = 0, right_max = 0, water = 0;
    while (lo < hi) {
        if (height[lo] < height[hi]) {
            if (height[lo] >= left_max) left_max = height[lo];
            else water += left_max - height[lo];
            ++lo;
        } else {
            if (height[hi] >= right_max) right_max = height[hi];
            else water += right_max - height[hi];
            --hi;
        }
    }
    return water;
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main() {
    // ── DynamicArray demo ──
    demo_dynamic_array();

    // ── Two Sum ──
    std::cout << "\n=== Two Sum ===\n";
    std::vector<int> nums1 = {2, 7, 11, 15};
    auto res = twoSum(nums1, 9);
    std::cout << "twoSum([2,7,11,15], 9) = [" << res[0] << ", " << res[1] << "]\n";

    // ── Max Subarray ──
    std::cout << "\n=== Maximum Subarray (Kadane) ===\n";
    std::vector<int> nums2 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "maxSubArray = " << maxSubArray(nums2) << "  (expected 6)\n";

    // ── Merge Intervals ──
    std::cout << "\n=== Merge Intervals ===\n";
    std::vector<std::vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    auto merged = mergeIntervals(intervals);
    std::cout << "Merged: ";
    for (const auto& iv : merged)
        std::cout << "[" << iv[0] << "," << iv[1] << "] ";
    std::cout << "  (expected [1,6] [8,10] [15,18])\n";

    // ── Longest Substring ──
    std::cout << "\n=== Longest Substring Without Repeating ===\n";
    std::cout << "\"abcabcbb\" -> " << lengthOfLongestSubstring("abcabcbb")
              << "  (expected 3)\n";
    std::cout << "\"pwwkew\"   -> " << lengthOfLongestSubstring("pwwkew")
              << "  (expected 3)\n";

    // ── Product Except Self ──
    std::cout << "\n=== Product of Array Except Self ===\n";
    std::vector<int> nums3 = {1, 2, 3, 4};
    print("productExceptSelf([1,2,3,4])", productExceptSelf(nums3));

    // ── Trapping Rain Water ──
    std::cout << "\n=== Trapping Rain Water ===\n";
    std::vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    std::cout << "trap = " << trap(height) << "  (expected 6)\n";

    return 0;
}
