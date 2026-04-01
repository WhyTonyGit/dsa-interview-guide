#pragma once

#include <functional>
#include <vector>

/**
 * @file searching.hpp
 * @brief Binary search and its variants — the most important search technique.
 *
 * The key insight: binary search applies to ANY monotonic condition,
 * not just sorted arrays. If you can write a predicate f(x) that is
 * false...false...true...true, you can binary search on it.
 */

namespace searching {

// ─── Classic Binary Search ────────────────────────────────────────────────────

/**
 * @brief Find the index of target in a sorted array, or -1 if not found.
 * @complexity O(log n)
 */
template <typename T>
int binary_search(const std::vector<T>& arr, const T& target) {
    int lo = 0, hi = static_cast<int>(arr.size()) - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target)  lo = mid + 1;
        else                    hi = mid - 1;
    }
    return -1;
}

// ─── Lower Bound / Upper Bound ────────────────────────────────────────────────

/**
 * @brief Find the first index i such that arr[i] >= target.
 * Equivalent to std::lower_bound.
 * @complexity O(log n)
 */
template <typename T>
int lower_bound(const std::vector<T>& arr, const T& target) {
    int lo = 0, hi = static_cast<int>(arr.size());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < target) lo = mid + 1;
        else                   hi = mid;
    }
    return lo;  // lo == hi == insertion point
}

/**
 * @brief Find the first index i such that arr[i] > target.
 * Equivalent to std::upper_bound.
 * @complexity O(log n)
 */
template <typename T>
int upper_bound(const std::vector<T>& arr, const T& target) {
    int lo = 0, hi = static_cast<int>(arr.size());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= target) lo = mid + 1;
        else                    hi = mid;
    }
    return lo;
}

/**
 * @brief Count occurrences of target in sorted array.
 * @complexity O(log n)
 */
template <typename T>
int count_occurrences(const std::vector<T>& arr, const T& target) {
    return upper_bound(arr, target) - lower_bound(arr, target);
}

// ─── Search in Rotated Array ──────────────────────────────────────────────────

/**
 * @brief Binary search in a sorted array that has been rotated at an unknown pivot.
 * @complexity O(log n)
 */
int search_rotated(const std::vector<int>& nums, int target) {
    int lo = 0, hi = static_cast<int>(nums.size()) - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;
        // Left half is sorted
        if (nums[lo] <= nums[mid]) {
            if (nums[lo] <= target && target < nums[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else {
            // Right half is sorted
            if (nums[mid] < target && target <= nums[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return -1;
}

// ─── Find Minimum in Rotated Array ───────────────────────────────────────────

/**
 * @brief Find the minimum element in a rotated sorted array.
 * @complexity O(log n)
 */
int find_min_rotated(const std::vector<int>& nums) {
    int lo = 0, hi = static_cast<int>(nums.size()) - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1;  // min is in right half
        else                      hi = mid;       // min is in left half (including mid)
    }
    return nums[lo];
}

// ─── Binary Search on Answer ──────────────────────────────────────────────────

/**
 * @brief Generic binary search on a monotonic predicate.
 *
 * Finds the smallest value x in [lo, hi] such that predicate(x) is true.
 * Assumes: predicate is false for x < answer, true for x >= answer.
 *
 * @param predicate Function int→bool, must be monotonic (false...false...true...)
 * @return Smallest x in [lo, hi] where predicate(x) == true, or hi+1 if none.
 * @complexity O(log(hi-lo) * cost(predicate))
 */
int binary_search_on_answer(int lo, int hi,
                             std::function<bool(int)> predicate) {
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (predicate(mid)) hi = mid;
        else                lo = mid + 1;
    }
    return lo;
}

/**
 * @brief Koko Eating Bananas — classic "binary search on answer" problem.
 * Find the minimum eating speed K such that Koko can eat all bananas in H hours.
 * @complexity O(n log(max_pile))
 */
int min_eating_speed(const std::vector<int>& piles, int h) {
    int lo = 1, hi = *std::max_element(piles.begin(), piles.end());
    auto can_finish = [&](int speed) {
        long long hours = 0;
        for (int pile : piles) hours += (pile + speed - 1) / speed;
        return hours <= h;
    };
    return binary_search_on_answer(lo, hi, can_finish);
}

}  // namespace searching
