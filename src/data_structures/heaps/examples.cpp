/**
 * @file examples.cpp
 * @brief Heap examples: custom heap, median finder, K-largest, meeting rooms.
 */

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#include "data_structures/heaps/heap.hpp"

void demo_min_heap() {
    std::cout << "\n=== Min Heap ===\n";
    MinHeap<int> h;
    for (int v : {5, 3, 7, 1, 9, 2, 4}) h.push(v);
    std::cout << "Min: " << h.top() << "  (expected 1)\n";
    h.pop();
    std::cout << "After pop, min: " << h.top() << "  (expected 2)\n";
    std::cout << "Size: " << h.size() << "\n";
    auto sorted = h.sort();
    std::cout << "Sorted: [";
    for (std::size_t i = 0; i < sorted.size(); ++i)
        std::cout << sorted[i] << (i+1 < sorted.size() ? "," : "");
    std::cout << "]\n";
}

void demo_max_heap() {
    std::cout << "\n=== Max Heap ===\n";
    MaxHeap<int> h({3, 1, 4, 1, 5, 9, 2, 6});
    std::cout << "Max: " << h.top() << "  (expected 9)\n";
}

void demo_median_finder() {
    std::cout << "\n=== Streaming Median ===\n";
    MedianFinder mf;
    mf.add_num(1);
    mf.add_num(2);
    std::cout << "Median of [1,2]: " << mf.find_median() << "  (expected 1.5)\n";
    mf.add_num(3);
    std::cout << "Median of [1,2,3]: " << mf.find_median() << "  (expected 2.0)\n";
    mf.add_num(5);
    std::cout << "Median of [1,2,3,5]: " << mf.find_median() << "  (expected 2.5)\n";
}

int findKthLargest(const std::vector<int>& nums, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    for (int x : nums) {
        min_heap.push(x);
        if (static_cast<int>(min_heap.size()) > k) min_heap.pop();
    }
    return min_heap.top();
}

int minMeetingRooms(std::vector<std::vector<int>> intervals) {
    std::sort(intervals.begin(), intervals.end());
    std::priority_queue<int, std::vector<int>, std::greater<int>> end_times;
    for (const auto& iv : intervals) {
        if (!end_times.empty() && end_times.top() <= iv[0]) end_times.pop();
        end_times.push(iv[1]);
    }
    return static_cast<int>(end_times.size());
}

int main() {
    demo_min_heap();
    demo_max_heap();
    demo_median_finder();

    std::cout << "\n=== Kth Largest ===\n";
    std::vector<int> nums = {3,2,1,5,6,4};
    std::cout << "2nd largest in [3,2,1,5,6,4]: " << findKthLargest(nums, 2)
              << "  (expected 5)\n";

    std::cout << "\n=== Meeting Rooms II ===\n";
    std::vector<std::vector<int>> meetings = {{0,30},{5,10},{15,20}};
    std::cout << "Min rooms needed: " << minMeetingRooms(meetings)
              << "  (expected 2)\n";

    return 0;
}
