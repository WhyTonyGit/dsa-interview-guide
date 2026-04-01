#pragma once

#include <cstdint>
#include <string>
#include <vector>

/**
 * @file bit_ops.hpp
 * @brief Bit manipulation utilities and common interview tricks.
 *
 * All functions operate on 32-bit or 64-bit integers.
 */

namespace bits {

// ─── Basic bit operations ────────────────────────────────────────────────────

/** @brief Get the bit at position pos (0 = LSB). */
inline bool get_bit(int n, int pos) {
    return (n >> pos) & 1;
}

/** @brief Set the bit at position pos. */
inline int set_bit(int n, int pos) {
    return n | (1 << pos);
}

/** @brief Clear the bit at position pos. */
inline int clear_bit(int n, int pos) {
    return n & ~(1 << pos);
}

/** @brief Toggle the bit at position pos. */
inline int toggle_bit(int n, int pos) {
    return n ^ (1 << pos);
}

/** @brief Update bit at position pos to value (0 or 1). */
inline int update_bit(int n, int pos, int value) {
    return (n & ~(1 << pos)) | (value << pos);
}

// ─── Counting bits ───────────────────────────────────────────────────────────

/**
 * @brief Count number of set bits (Hamming weight / popcount).
 * Brian Kernighan's algorithm: O(number of set bits)
 */
inline int count_ones(int n) {
    int count = 0;
    while (n) {
        n &= n - 1;  // clear lowest set bit
        ++count;
    }
    return count;
}

/**
 * @brief Count number of set bits using built-in (fastest).
 * Use in interviews when you want to show you know the tool.
 */
inline int popcount(unsigned int n) {
    return __builtin_popcount(n);  // GCC/Clang intrinsic
}

/**
 * @brief Count bits to flip to convert a to b.
 * @complexity O(number of differing bits)
 */
inline int bits_to_flip(int a, int b) {
    return count_ones(a ^ b);
}

// ─── Powers of two ───────────────────────────────────────────────────────────

/** @brief Returns true if n is a power of 2. */
inline bool is_power_of_two(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

/** @brief Returns the largest power of 2 <= n. */
inline int floor_power_of_two(int n) {
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n - (n >> 1);
}

// ─── Classic tricks ──────────────────────────────────────────────────────────

/** @brief Clear the lowest set bit of n. */
inline int clear_lowest_set_bit(int n) { return n & (n - 1); }

/** @brief Isolate the lowest set bit of n. */
inline int lowest_set_bit(int n) { return n & (-n); }

/**
 * @brief Reverse the bits of a 32-bit integer.
 * @complexity O(log w) where w = word size
 */
inline uint32_t reverse_bits(uint32_t n) {
    n = ((n & 0xAAAAAAAA) >> 1)  | ((n & 0x55555555) << 1);
    n = ((n & 0xCCCCCCCC) >> 2)  | ((n & 0x33333333) << 2);
    n = ((n & 0xF0F0F0F0) >> 4)  | ((n & 0x0F0F0F0F) << 4);
    n = ((n & 0xFF00FF00) >> 8)  | ((n & 0x00FF00FF) << 8);
    n = ((n & 0xFFFF0000) >> 16) | ((n & 0x0000FFFF) << 16);
    return n;
}

/**
 * @brief Swap two integers without a temporary variable.
 */
inline void swap_xor(int& a, int& b) {
    if (&a != &b) {  // guard against self-swap
        a ^= b;
        b ^= a;
        a ^= b;
    }
}

/**
 * @brief Find the single number in an array where every other appears twice.
 * XOR all elements — duplicates cancel out.
 * @complexity O(n) time, O(1) space
 */
inline int single_number(const std::vector<int>& nums) {
    int result = 0;
    for (int x : nums) result ^= x;
    return result;
}

/**
 * @brief Find two numbers that appear once (all others appear twice).
 * @complexity O(n) time, O(1) space
 */
inline std::pair<int,int> single_number_two(const std::vector<int>& nums) {
    int xor_all = 0;
    for (int x : nums) xor_all ^= x;
    // Find the rightmost set bit (differentiates the two unique numbers)
    int diff_bit = xor_all & (-xor_all);
    int a = 0, b = 0;
    for (int x : nums) {
        if (x & diff_bit) a ^= x;
        else              b ^= x;
    }
    return {a, b};
}

/**
 * @brief Convert integer to binary string (8-bit representation).
 */
inline std::string to_binary_string(int n, int bits = 8) {
    std::string result(bits, '0');
    for (int i = bits - 1; i >= 0; --i) {
        result[i] = '0' + (n & 1);
        n >>= 1;
    }
    return result;
}

/**
 * @brief Hamming distance between x and y (number of differing bits).
 */
inline int hamming_distance(int x, int y) {
    return count_ones(x ^ y);
}

/**
 * @brief Generate all subsets of a set represented as bitmask.
 * Useful in bitmask DP.
 * @complexity O(2^n * n)
 */
inline std::vector<std::vector<int>> all_subsets(int n) {
    std::vector<std::vector<int>> result;
    for (int mask = 0; mask < (1 << n); ++mask) {
        std::vector<int> subset;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i)) subset.push_back(i);
        result.push_back(subset);
    }
    return result;
}

}  // namespace bits
