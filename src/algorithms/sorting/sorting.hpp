#pragma once

#include <algorithm>
#include <functional>
#include <vector>

/**
 * @file sorting.hpp
 * @brief Common sorting algorithms for interview preparation.
 *
 * All functions sort in-place (or return sorted copies) and accept a comparator.
 * For interviews, know: QuickSort, MergeSort, HeapSort, and when to use each.
 */

namespace sorting {

// ─── Merge Sort ───────────────────────────────────────────────────────────────

namespace detail {
template <typename T, typename Comp>
void merge(std::vector<T>& arr, int lo, int mid, int hi, Comp comp) {
    std::vector<T> temp(arr.begin() + lo, arr.begin() + hi + 1);
    int i = 0, j = mid - lo + 1, k = lo;
    int left_size = mid - lo + 1;
    int right_size = hi - mid;
    while (i < left_size && j < left_size + right_size) {
        if (!comp(temp[j], temp[i])) arr[k++] = temp[i++];
        else                         arr[k++] = temp[j++];
    }
    while (i < left_size)               arr[k++] = temp[i++];
    while (j < left_size + right_size)  arr[k++] = temp[j++];
}

template <typename T, typename Comp>
void merge_sort_helper(std::vector<T>& arr, int lo, int hi, Comp comp) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    merge_sort_helper(arr, lo, mid, comp);
    merge_sort_helper(arr, mid + 1, hi, comp);
    // Optimization: skip merge if already sorted
    if (!comp(arr[mid + 1], arr[mid])) return;
    merge(arr, lo, mid, hi, comp);
}
}  // namespace detail

/**
 * @brief Merge sort — stable, O(n log n) guaranteed.
 * @complexity O(n log n) time, O(n) space
 */
template <typename T, typename Comp = std::less<T>>
void merge_sort(std::vector<T>& arr, Comp comp = Comp{}) {
    if (arr.size() <= 1) return;
    detail::merge_sort_helper(arr, 0, static_cast<int>(arr.size()) - 1, comp);
}

// ─── Quick Sort ───────────────────────────────────────────────────────────────

namespace detail {
template <typename T, typename Comp>
int partition(std::vector<T>& arr, int lo, int hi, Comp comp) {
    // Median-of-three pivot selection
    int mid = lo + (hi - lo) / 2;
    if (comp(arr[hi], arr[lo]))  std::swap(arr[lo], arr[hi]);
    if (comp(arr[mid], arr[lo])) std::swap(arr[lo], arr[mid]);
    if (comp(arr[hi], arr[mid])) std::swap(arr[mid], arr[hi]);
    // arr[mid] is median; put it as pivot at hi-1
    T pivot = arr[mid];
    std::swap(arr[mid], arr[hi]);
    int i = lo - 1;
    for (int j = lo; j < hi; ++j) {
        if (!comp(pivot, arr[j])) std::swap(arr[++i], arr[j]);
    }
    std::swap(arr[++i], arr[hi]);
    return i;
}

template <typename T, typename Comp>
void quick_sort_helper(std::vector<T>& arr, int lo, int hi, Comp comp) {
    if (lo < hi) {
        int pivot = partition(arr, lo, hi, comp);
        quick_sort_helper(arr, lo, pivot - 1, comp);
        quick_sort_helper(arr, pivot + 1, hi, comp);
    }
}
}  // namespace detail

/**
 * @brief Quick sort — O(n log n) average, O(n²) worst (rare with median-of-3).
 * @complexity O(n log n) average, O(log n) stack space
 */
template <typename T, typename Comp = std::less<T>>
void quick_sort(std::vector<T>& arr, Comp comp = Comp{}) {
    if (arr.size() <= 1) return;
    detail::quick_sort_helper(arr, 0, static_cast<int>(arr.size()) - 1, comp);
}

// ─── Heap Sort ────────────────────────────────────────────────────────────────

namespace detail {
template <typename T, typename Comp>
void sift_down(std::vector<T>& arr, int i, int n, Comp comp) {
    while (true) {
        int best = i, lc = 2*i+1, rc = 2*i+2;
        if (lc < n && comp(arr[best], arr[lc])) best = lc;
        if (rc < n && comp(arr[best], arr[rc])) best = rc;
        if (best == i) break;
        std::swap(arr[i], arr[best]);
        i = best;
    }
}
}  // namespace detail

/**
 * @brief Heap sort — O(n log n), in-place, not stable.
 * @complexity O(n log n) time, O(1) space
 */
template <typename T, typename Comp = std::less<T>>
void heap_sort(std::vector<T>& arr, Comp comp = Comp{}) {
    int n = static_cast<int>(arr.size());
    // Build max-heap
    for (int i = n/2 - 1; i >= 0; --i)
        detail::sift_down(arr, i, n, comp);
    // Extract elements
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        detail::sift_down(arr, 0, i, comp);
    }
}

// ─── Insertion Sort ───────────────────────────────────────────────────────────

/**
 * @brief Insertion sort — O(n²) but excellent for small or nearly-sorted arrays.
 * @complexity O(n²) time, O(1) space, stable
 */
template <typename T, typename Comp = std::less<T>>
void insertion_sort(std::vector<T>& arr, Comp comp = Comp{}) {
    for (int i = 1; i < static_cast<int>(arr.size()); ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && comp(key, arr[j])) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// ─── Counting Sort ────────────────────────────────────────────────────────────

/**
 * @brief Counting sort for non-negative integers in range [0, max_val].
 * @complexity O(n + k) time and space where k = max_val
 */
void counting_sort(std::vector<int>& arr, int max_val) {
    std::vector<int> count(max_val + 1, 0);
    for (int x : arr) ++count[x];
    int idx = 0;
    for (int v = 0; v <= max_val; ++v)
        while (count[v]-- > 0) arr[idx++] = v;
}

}  // namespace sorting
