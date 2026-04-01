/**
 * @file examples.cpp
 * @brief Dynamic programming problem demonstrations.
 */

#include <iostream>
#include <string>
#include <vector>

#include "algorithms/dynamic_programming/dp_examples.hpp"

int main() {
    std::cout << "\n=== Fibonacci ===\n";
    std::cout << "fib(10) = " << dp::fibonacci(10) << "  (expected 55)\n";
    std::cout << "fib(20) = " << dp::fibonacci(20) << "  (expected 6765)\n";

    std::cout << "\n=== Climbing Stairs ===\n";
    std::cout << "stairs(5) = " << dp::climbing_stairs(5) << "  (expected 8)\n";

    std::cout << "\n=== Coin Change ===\n";
    std::vector<int> coins = {1, 5, 11};
    std::cout << "coins([1,5,11], 15) = " << dp::coin_change(coins, 15) << "  (expected 3: 5+5+5)\n";
    std::cout << "coins([2], 3) = "       << dp::coin_change({2}, 3)   << "  (expected -1)\n";

    std::cout << "\n=== LIS ===\n";
    std::vector<int> seq = {10, 9, 2, 5, 3, 7, 101, 18};
    std::cout << "LIS([10,9,2,5,3,7,101,18]) = " << dp::lis(seq) << "  (expected 4: [2,3,7,101])\n";

    std::cout << "\n=== LCS ===\n";
    std::cout << "LCS(\"abcde\",\"ace\") = " << dp::lcs("abcde","ace") << "  (expected 3)\n";

    std::cout << "\n=== Edit Distance ===\n";
    std::cout << "edit(\"horse\",\"ros\") = " << dp::edit_distance("horse","ros") << "  (expected 3)\n";

    std::cout << "\n=== 0/1 Knapsack ===\n";
    std::vector<int> weights = {1, 3, 4, 5};
    std::vector<int> values  = {1, 4, 5, 7};
    std::cout << "knapsack(W=7) = " << dp::knapsack(weights, values, 7) << "  (expected 9)\n";

    std::cout << "\n=== Word Break ===\n";
    std::cout << "wordBreak(\"leetcode\",[\"leet\",\"code\"]) = "
              << (dp::word_break("leetcode", {"leet","code"}) ? "true" : "false")
              << "  (expected true)\n";

    std::cout << "\n=== House Robber ===\n";
    std::vector<int> houses = {2, 7, 9, 3, 1};
    std::cout << "rob([2,7,9,3,1]) = " << dp::house_robber(houses) << "  (expected 12)\n";

    std::cout << "\n=== Unique Paths ===\n";
    std::cout << "uniquePaths(3,7) = " << dp::unique_paths(3,7) << "  (expected 28)\n";

    return 0;
}
