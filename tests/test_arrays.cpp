/**
 * @file test_arrays.cpp
 * @brief Unit tests for DynamicArray and array algorithms.
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

#include "data_structures/arrays/array.hpp"

// ─── Construction ─────────────────────────────────────────────────────────────

TEST(DynamicArrayTest, DefaultConstructor) {
    DynamicArray<int> arr;
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0u);
}

TEST(DynamicArrayTest, InitializerList) {
    DynamicArray<int> arr = {1, 2, 3, 4, 5};
    EXPECT_EQ(arr.size(), 5u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[4], 5);
}

TEST(DynamicArrayTest, SizeConstructor) {
    DynamicArray<int> arr(5);
    EXPECT_EQ(arr.size(), 5u);
    EXPECT_EQ(arr[0], 0);  // default-initialised
}

TEST(DynamicArrayTest, FillConstructor) {
    DynamicArray<int> arr(3, 42);
    for (std::size_t i = 0; i < arr.size(); ++i)
        EXPECT_EQ(arr[i], 42);
}

// ─── Push / Pop ───────────────────────────────────────────────────────────────

TEST(DynamicArrayTest, PushBack) {
    DynamicArray<int> arr;
    for (int i = 0; i < 100; ++i) arr.push_back(i);
    EXPECT_EQ(arr.size(), 100u);
    EXPECT_EQ(arr[99], 99);
}

TEST(DynamicArrayTest, PopBack) {
    DynamicArray<int> arr = {1, 2, 3};
    arr.pop_back();
    EXPECT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr.back(), 2);
}

TEST(DynamicArrayTest, PopBackEmpty) {
    DynamicArray<int> arr;
    EXPECT_THROW(arr.pop_back(), std::underflow_error);
}

// ─── Access ───────────────────────────────────────────────────────────────────

TEST(DynamicArrayTest, AtInBounds) {
    DynamicArray<int> arr = {10, 20, 30};
    EXPECT_EQ(arr.at(1), 20);
}

TEST(DynamicArrayTest, AtOutOfBounds) {
    DynamicArray<int> arr = {10, 20, 30};
    EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST(DynamicArrayTest, FrontBack) {
    DynamicArray<int> arr = {1, 2, 3};
    EXPECT_EQ(arr.front(), 1);
    EXPECT_EQ(arr.back(), 3);
}

// ─── Insert / Erase ───────────────────────────────────────────────────────────

TEST(DynamicArrayTest, Insert) {
    DynamicArray<int> arr = {1, 3, 5};
    arr.insert(1, 2);  // insert 2 at index 1
    EXPECT_EQ(arr.size(), 4u);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(DynamicArrayTest, Erase) {
    DynamicArray<int> arr = {1, 2, 3, 4};
    arr.erase(1);
    EXPECT_EQ(arr.size(), 3u);
    EXPECT_EQ(arr[1], 3);
}

TEST(DynamicArrayTest, EraseOutOfBounds) {
    DynamicArray<int> arr = {1, 2, 3};
    EXPECT_THROW(arr.erase(10), std::out_of_range);
}

// ─── Copy / Move ──────────────────────────────────────────────────────────────

TEST(DynamicArrayTest, CopyConstructor) {
    DynamicArray<int> a = {1, 2, 3};
    DynamicArray<int> b = a;
    b[0] = 99;
    EXPECT_EQ(a[0], 1);  // original unchanged
    EXPECT_EQ(b[0], 99);
}

TEST(DynamicArrayTest, MoveConstructor) {
    DynamicArray<int> a = {1, 2, 3};
    DynamicArray<int> b = std::move(a);
    EXPECT_TRUE(a.empty());
    EXPECT_EQ(b.size(), 3u);
}

// ─── Algorithms ───────────────────────────────────────────────────────────────

TEST(DynamicArrayTest, Sort) {
    DynamicArray<int> arr = {5, 2, 8, 1, 9, 3};
    arr.sort();
    for (std::size_t i = 1; i < arr.size(); ++i)
        EXPECT_LE(arr[i-1], arr[i]);
}

TEST(DynamicArrayTest, Reverse) {
    DynamicArray<int> arr = {1, 2, 3, 4, 5};
    arr.reverse();
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[4], 1);
}

TEST(DynamicArrayTest, Find) {
    DynamicArray<int> arr = {10, 20, 30};
    EXPECT_EQ(arr.find(20), 1u);
    EXPECT_EQ(arr.find(99), DynamicArray<int>::npos);
}

TEST(DynamicArrayTest, Equality) {
    DynamicArray<int> a = {1, 2, 3};
    DynamicArray<int> b = {1, 2, 3};
    DynamicArray<int> c = {1, 2, 4};
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

// ─── Reserve / Shrink ─────────────────────────────────────────────────────────

TEST(DynamicArrayTest, Reserve) {
    DynamicArray<int> arr;
    arr.reserve(100);
    EXPECT_GE(arr.capacity(), 100u);
    EXPECT_EQ(arr.size(), 0u);
}

TEST(DynamicArrayTest, ShrinkToFit) {
    DynamicArray<int> arr = {1, 2, 3};
    arr.reserve(100);
    arr.shrink_to_fit();
    EXPECT_EQ(arr.capacity(), arr.size());
}

// ─── Iterator ─────────────────────────────────────────────────────────────────

TEST(DynamicArrayTest, RangeForLoop) {
    DynamicArray<int> arr = {1, 2, 3, 4, 5};
    int sum = 0;
    for (int x : arr) sum += x;
    EXPECT_EQ(sum, 15);
}
