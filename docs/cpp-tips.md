# C++ Interview Tips

## When to Use STL vs Custom Implementation

### Use STL (default choice in interviews)

```cpp
// Almost always prefer STL in interviews — it's faster to write and less error-prone

std::vector<int>           // dynamic array
std::unordered_map<K, V>  // O(1) hash table
std::map<K, V>            // O(log n) sorted map
std::set<T>               // unique sorted elements
std::queue<T>             // FIFO
std::stack<T>             // LIFO
std::priority_queue<T>    // heap (max by default)
std::deque<T>             // double-ended queue
std::string               // always prefer over char*
```

### Write custom implementation when asked explicitly

```
"Implement a linked list from scratch"
"Design a hash map"
"Implement a min-heap"
```

---

## Essential STL Idioms

### Sorting and searching

```cpp
#include <algorithm>

std::vector<int> v = {3, 1, 4, 1, 5, 9};

// Sort ascending
std::sort(v.begin(), v.end());

// Sort descending
std::sort(v.begin(), v.end(), std::greater<int>());

// Sort with custom comparator (e.g., by absolute value)
std::sort(v.begin(), v.end(), [](int a, int b) {
    return std::abs(a) < std::abs(b);
});

// Binary search (requires sorted range)
bool found = std::binary_search(v.begin(), v.end(), 4);

// Lower bound: first position >= val
auto it = std::lower_bound(v.begin(), v.end(), 4);

// Upper bound: first position > val
auto it2 = std::upper_bound(v.begin(), v.end(), 4);

// Min/max element
auto min_it = std::min_element(v.begin(), v.end());
auto max_it = std::max_element(v.begin(), v.end());
```

### Priority Queue (Heap)

```cpp
// Max-heap (default)
std::priority_queue<int> max_heap;
max_heap.push(3); max_heap.push(1); max_heap.push(5);
// top() = 5

// Min-heap
std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

// Custom comparator for pairs (sort by second element, min first)
using P = std::pair<int, int>;
auto cmp = [](const P& a, const P& b) { return a.second > b.second; };
std::priority_queue<P, std::vector<P>, decltype(cmp)> pq(cmp);
```

### Unordered_map pitfalls

```cpp
std::unordered_map<std::string, int> freq;

// ✅ Safe increment (default constructs to 0 if missing)
freq["hello"]++;

// ✅ Check existence before access
if (freq.count("hello") > 0) { /* safe */ }
if (freq.find("hello") != freq.end()) { /* also safe */ }

// ✅ C++17: structured bindings
for (const auto& [key, val] : freq) {
    std::cout << key << ": " << val << "\n";
}

// ❌ Avoid: operator[] creates entry with default value
// if you don't intend to insert
```

### String operations

```cpp
std::string s = "hello world";

// Substring
std::string sub = s.substr(6, 5); // "world"

// Find
size_t pos = s.find("world"); // returns std::string::npos if not found
if (pos != std::string::npos) { /* found */ }

// Split by delimiter (no built-in, use stringstream)
#include <sstream>
std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, delim)) tokens.push_back(token);
    return tokens;
}

// Convert to lowercase
std::transform(s.begin(), s.end(), s.begin(), ::tolower);

// Char checks
std::isalpha('a')  // true
std::isdigit('3')  // true
std::isalnum('a')  // true
```

---

## Memory Management — RAII

### Rule: Never use raw `new`/`delete` in interview code

```cpp
// ❌ Old style — memory leak if exception thrown
Node* node = new Node(5);
// ... (forgot to delete)

// ✅ Smart pointers (C++11+)
#include <memory>

auto node = std::make_unique<Node>(5);  // unique ownership
auto shared = std::make_shared<Node>(5); // shared ownership

// unique_ptr transfers ownership
std::unique_ptr<Node> a = std::make_unique<Node>(5);
std::unique_ptr<Node> b = std::move(a); // a is now nullptr

// In interview implementations, trees/lists often use raw pointers
// for simplicity — just make sure destructor cleans up properly
```

### Tree node destructor example

```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// If you build a tree with raw pointers, you need a cleanup function
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
```

---

## Common C++ Bugs in Interviews

### 1. Integer overflow

```cpp
// ❌ May overflow for large inputs
int mid = (left + right) / 2;

// ✅ Safe
int mid = left + (right - left) / 2;

// ✅ Use long long for large sums
long long sum = static_cast<long long>(a) * b;
```

### 2. Off-by-one in binary search

```cpp
// Classic binary search — memorize this pattern
int binarySearch(const std::vector<int>& arr, int target) {
    int lo = 0, hi = static_cast<int>(arr.size()) - 1;
    while (lo <= hi) {                          // ← note: <=
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
```

### 3. Null pointer dereference

```cpp
// ❌ Crash if node is nullptr
int val = node->val;

// ✅ Guard first
if (node) int val = node->val;
// Or in tree traversal:
void inorder(TreeNode* node) {
    if (!node) return;  // ← always check at start
    inorder(node->left);
    std::cout << node->val;
    inorder(node->right);
}
```

### 4. Iterator invalidation

```cpp
std::vector<int> v = {1, 2, 3, 4};

// ❌ Modifying vector while iterating — UB
for (auto it = v.begin(); it != v.end(); ++it) {
    if (*it == 2) v.erase(it); // invalidates iterator!
}

// ✅ Use erase-remove idiom
v.erase(std::remove(v.begin(), v.end(), 2), v.end());

// ✅ Or iterate with index
for (int i = static_cast<int>(v.size()) - 1; i >= 0; --i) {
    if (v[i] == 2) v.erase(v.begin() + i);
}
```

### 5. Signed/unsigned comparison

```cpp
// ❌ Compiler warning: signed/unsigned comparison
int n = 5;
for (int i = 0; i < v.size(); ++i) { }  // v.size() is size_t (unsigned)

// ✅ Cast explicitly
for (int i = 0; i < static_cast<int>(v.size()); ++i) { }
// Or use range-based for loop
for (const auto& elem : v) { }
```

---

## C++17 Features Useful in Interviews

```cpp
// Structured bindings
auto [key, value] = *map.begin();
auto [min_val, max_val] = std::minmax(a, b);

// if with initializer
if (auto it = m.find(key); it != m.end()) {
    return it->second;
}

// std::optional — great for "value or nothing"
std::optional<int> findFirst(const std::vector<int>& v, int target) {
    for (int x : v) if (x == target) return x;
    return std::nullopt;
}

// Fold expressions, std::string_view (avoid copy), std::variant
```

---

## Interview Code Template

Start every interview problem with this mental checklist:

```cpp
#include <bits/stdc++.h>  // OK in competitive programming, avoid in production
// OR include exactly what you need

class Solution {
public:
    // 1. Read: clarify input types, constraints, edge cases
    // 2. Discuss: brute force O(?) → optimized O(?)
    // 3. Code

    int solve(std::vector<int>& nums, int target) {
        // Edge case first
        if (nums.empty()) return -1;

        // Core logic
        // ...

        return result;
    }
};

// 4. Test with examples
// 5. Walk through edge cases: empty, single element, duplicates, negatives
// 6. State complexity: "Time O(n log n), Space O(n)"
```
