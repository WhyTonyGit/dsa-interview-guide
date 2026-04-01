/**
 * @file examples.cpp
 * @brief Sorting algorithm demonstrations.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "algorithms/sorting/sorting.hpp"

template <typename T>
void print(const std::string& label, const std::vector<T>& v) {
    std::cout << label << ": [";
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << (i+1 < v.size() ? "," : "");
    std::cout << "]\n";
}

int main() {
    std::vector<int> input = {64, 25, 12, 22, 11, 90, 3, 45};
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());

    auto test = [&](const std::string& name, std::vector<int> arr) {
        std::cout << "\n=== " << name << " ===\n";
        print("Before", arr);
        return arr;
    };

    {
        auto arr = test("Merge Sort", input);
        sorting::merge_sort(arr);
        print("After ", arr);
        assert(arr == expected && "Merge sort failed");
    }
    {
        auto arr = test("Quick Sort", input);
        sorting::quick_sort(arr);
        print("After ", arr);
        assert(arr == expected && "Quick sort failed");
    }
    {
        auto arr = test("Heap Sort", input);
        sorting::heap_sort(arr);
        print("After ", arr);
        assert(arr == expected && "Heap sort failed");
    }
    {
        auto arr = test("Insertion Sort", input);
        sorting::insertion_sort(arr);
        print("After ", arr);
        assert(arr == expected && "Insertion sort failed");
    }
    {
        std::cout << "\n=== Counting Sort ===\n";
        std::vector<int> arr = {4, 2, 2, 8, 3, 3, 1};
        print("Before", arr);
        sorting::counting_sort(arr, 8);
        print("After ", arr);
        assert(std::is_sorted(arr.begin(), arr.end()) && "Counting sort failed");
    }

    // Sorting pairs by second element
    std::cout << "\n=== Sort pairs by frequency (custom comparator) ===\n";
    std::vector<std::pair<std::string,int>> words = {{"cat",3},{"dog",1},{"fish",5},{"ant",2}};
    std::sort(words.begin(), words.end(),
              [](const auto& a, const auto& b){ return a.second > b.second; });
    for (const auto& [w, f] : words) std::cout << w << ":" << f << " ";
    std::cout << "\n";

    std::cout << "\nAll sorting tests passed!\n";
    return 0;
}
