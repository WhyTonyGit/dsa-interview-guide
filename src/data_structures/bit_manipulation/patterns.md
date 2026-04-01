# Bit Manipulation Interview Patterns

## Pattern 1: XOR — Find the Unique/Single Number

```cpp
// Every element appears twice except one — XOR cancels duplicates
int singleNumber(const std::vector<int>& nums) {
    int result = 0;
    for (int x : nums) result ^= x;
    return result;
}

// Every element appears 3 times except one — use bit counting
int singleNumberIII(const std::vector<int>& nums) {
    int ones = 0, twos = 0;
    for (int x : nums) {
        ones = (ones ^ x) & ~twos;
        twos = (twos ^ x) & ~ones;
    }
    return ones;
}
```

## Pattern 2: Count Set Bits (Hamming Weight)

```cpp
// Brian Kernighan's algorithm — O(number of set bits)
int hammingWeight(uint32_t n) {
    int count = 0;
    while (n) { n &= n - 1; ++count; }  // clear lowest set bit each iteration
    return count;
}

// Count bits for all numbers [0, n] using DP
std::vector<int> countBits(int n) {
    std::vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        dp[i] = dp[i >> 1] + (i & 1);  // dp[i] = dp[i/2] + last bit
    return dp;
}
```

## Pattern 3: Subsets via Bitmask

```cpp
// Generate all subsets of nums using bitmask enumeration
std::vector<std::vector<int>> subsets(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<std::vector<int>> result;
    for (int mask = 0; mask < (1 << n); ++mask) {
        std::vector<int> subset;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i)) subset.push_back(nums[i]);
        result.push_back(subset);
    }
    return result;
}
```

## Pattern 4: Missing Number

```cpp
// XOR approach: XOR all indices and values — missing number remains
int missingNumber(const std::vector<int>& nums) {
    int result = nums.size();
    for (int i = 0; i < (int)nums.size(); ++i)
        result ^= i ^ nums[i];
    return result;
}
```

## Pattern 5: Reverse Bits

```cpp
uint32_t reverseBits(uint32_t n) {
    n = ((n & 0xAAAAAAAA) >> 1)  | ((n & 0x55555555) << 1);
    n = ((n & 0xCCCCCCCC) >> 2)  | ((n & 0x33333333) << 2);
    n = ((n & 0xF0F0F0F0) >> 4)  | ((n & 0x0F0F0F0F) << 4);
    n = ((n & 0xFF00FF00) >> 8)  | ((n & 0x00FF00FF) << 8);
    return (n >> 16) | (n << 16);
}
```

## Common Interview Questions

| Question | Technique | Difficulty |
|----------|-----------|------------|
| Single Number | XOR cancellation | Easy |
| Number of 1 Bits | Brian Kernighan | Easy |
| Missing Number | XOR or math | Easy |
| Counting Bits | DP with bit shift | Easy |
| Reverse Bits | Bit swap pairs | Easy |
| Sum of Two Integers (no +) | XOR + carry | Medium |
| Power of Two | `n & (n-1) == 0` | Easy |
| Hamming Distance | XOR + popcount | Easy |
| Maximum XOR of Two Numbers | Binary Trie | Medium |
