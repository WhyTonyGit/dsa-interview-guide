/**
 * @file examples.cpp
 * @brief Bit manipulation examples and classic interview problems.
 */

#include <cstdint>
#include <iostream>
#include <vector>

#include "data_structures/bit_manipulation/bit_ops.hpp"

int main() {
    std::cout << "\n=== Basic Bit Operations ===\n";
    int n = 0b1010;  // 10 in binary
    std::cout << "n = " << n << " = " << bits::to_binary_string(n, 4) << "\n";
    std::cout << "get_bit(n, 1) = " << bits::get_bit(n, 1) << "  (expected 1)\n";
    std::cout << "set_bit(n, 0) = " << bits::to_binary_string(bits::set_bit(n, 0), 4) << " = 1011\n";
    std::cout << "clear_bit(n,3)= " << bits::to_binary_string(bits::clear_bit(n, 3), 4) << " = 0010\n";
    std::cout << "toggle_bit(n,2)=" << bits::to_binary_string(bits::toggle_bit(n, 2), 4) << " = 1110\n";

    std::cout << "\n=== Count Bits ===\n";
    std::cout << "count_ones(7) = " << bits::count_ones(7) << "  (expected 3)\n";
    std::cout << "count_ones(255)= " << bits::count_ones(255) << "  (expected 8)\n";
    std::cout << "is_power_of_two(8) = " << bits::is_power_of_two(8) << "\n";
    std::cout << "is_power_of_two(7) = " << bits::is_power_of_two(7) << "\n";

    std::cout << "\n=== XOR: Single Number ===\n";
    std::vector<int> nums = {4, 1, 2, 1, 2};
    std::cout << "single_number([4,1,2,1,2]) = " << bits::single_number(nums)
              << "  (expected 4)\n";

    std::cout << "\n=== Two Unique Numbers ===\n";
    std::vector<int> nums2 = {1,2,1,3,2,5};
    auto [a, b] = bits::single_number_two(nums2);
    std::cout << "Two unique in [1,2,1,3,2,5]: " << a << " and " << b
              << "  (expected 3 and 5)\n";

    std::cout << "\n=== Hamming Distance ===\n";
    std::cout << "hamming_distance(1, 4) = " << bits::hamming_distance(1, 4)
              << "  (1=001, 4=100, differ in 2 bits)\n";

    std::cout << "\n=== Reverse Bits ===\n";
    uint32_t val = 43261596;  // 00000010100101000001111010011100
    std::cout << "reverse_bits(" << val << ") = " << bits::reverse_bits(val)
              << "  (expected 964176192)\n";

    std::cout << "\n=== All Subsets of {0,1,2} ===\n";
    auto subsets = bits::all_subsets(3);
    for (const auto& s : subsets) {
        std::cout << "  {";
        for (std::size_t i = 0; i < s.size(); ++i)
            std::cout << s[i] << (i+1 < s.size() ? "," : "");
        std::cout << "}\n";
    }

    return 0;
}
