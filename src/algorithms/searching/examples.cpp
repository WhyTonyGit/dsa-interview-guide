/**
 * @file examples.cpp
 * @brief Binary search variants and "binary search on answer" examples.
 */

#include <algorithm>
#include <iostream>
#include <vector>

#include "algorithms/searching/searching.hpp"

int main() {
    std::cout << "\n=== Binary Search ===\n";
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    std::cout << "search(7)  = " << searching::binary_search(arr, 7)  << "  (expected 3)\n";
    std::cout << "search(6)  = " << searching::binary_search(arr, 6)  << "  (expected -1)\n";
    std::cout << "search(15) = " << searching::binary_search(arr, 15) << "  (expected 7)\n";

    std::cout << "\n=== Lower / Upper Bound ===\n";
    std::vector<int> arr2 = {1, 2, 2, 2, 3, 4, 5};
    std::cout << "lower_bound(2) = " << searching::lower_bound(arr2, 2) << "  (expected 1)\n";
    std::cout << "upper_bound(2) = " << searching::upper_bound(arr2, 2) << "  (expected 4)\n";
    std::cout << "count_occ(2)   = " << searching::count_occurrences(arr2, 2) << "  (expected 3)\n";

    std::cout << "\n=== Search in Rotated Array ===\n";
    std::vector<int> rotated = {4, 5, 6, 7, 0, 1, 2};
    std::cout << "search(0) = " << searching::search_rotated(rotated, 0) << "  (expected 4)\n";
    std::cout << "search(3) = " << searching::search_rotated(rotated, 3) << "  (expected -1)\n";

    std::cout << "\n=== Find Min in Rotated Array ===\n";
    std::cout << "min in [3,4,5,1,2] = "
              << searching::find_min_rotated({3,4,5,1,2}) << "  (expected 1)\n";

    std::cout << "\n=== Koko Eating Bananas (Binary Search on Answer) ===\n";
    std::vector<int> piles = {3, 6, 7, 11};
    std::cout << "min speed to eat in 8 hours = "
              << searching::min_eating_speed(piles, 8) << "  (expected 4)\n";

    return 0;
}
