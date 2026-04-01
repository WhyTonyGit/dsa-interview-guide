# Tries (Prefix Trees)

A trie is a tree where each node represents a character prefix. Words are stored by sharing common prefixes, making prefix lookups extremely efficient.

## Operations & Complexity

| Operation | Time | Space | Notes |
|-----------|------|-------|-------|
| Insert | O(m) | O(m) | m = string length |
| Search (exact) | O(m) | O(1) | |
| Prefix search | O(m) | O(1) | |
| Delete | O(m) | O(1) | |
| Autocomplete | O(m + k) | O(k) | k = results count |

## ✅ When to Use

- Prefix-based search / autocomplete
- Spell checking
- IP routing (longest prefix match)
- Word games (Boggle, Scrabble)
- "Design a search autocomplete system"

## ❌ When NOT to Use

- Exact match only → hash set is faster and simpler
- Memory is constrained (each node uses 26 pointers = 26×8 bytes)
- Keys are not strings with a small alphabet

## 📊 Interview Frequency

- **55%** at Google, Airbnb, and companies building search features
- Usually Medium to Hard difficulty

## C++ Implementation Note

```cpp
// Each trie node stores 26 child pointers (for a-z)
struct TrieNode {
    TrieNode* children[26] = {};
    bool is_end = false;
};

// Index for character c
int idx = c - 'a';
```

For generic alphabets use `unordered_map<char, TrieNode*>` instead of a fixed array.

See [patterns.md](patterns.md) for interview patterns.
