# Trie Interview Patterns

## Pattern 1: Word Search II (Backtracking + Trie)

```cpp
// Find all words from a dictionary that exist in a 2D board.
// Trie prunes the search space efficiently.
struct TrieNode {
    TrieNode* children[26] = {};
    std::string word;  // non-empty at end of word
};

std::vector<std::string> findWords(std::vector<std::vector<char>>& board,
                                    std::vector<std::string>& words) {
    TrieNode* root = new TrieNode();
    for (const auto& w : words) {
        TrieNode* cur = root;
        for (char c : w) {
            int idx = c - 'a';
            if (!cur->children[idx]) cur->children[idx] = new TrieNode();
            cur = cur->children[idx];
        }
        cur->word = w;
    }

    int rows = board.size(), cols = board[0].size();
    std::vector<std::string> result;

    std::function<void(int, int, TrieNode*)> dfs = [&](int r, int c, TrieNode* node) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) return;
        char ch = board[r][c];
        if (ch == '#' || !node->children[ch - 'a']) return;
        TrieNode* next = node->children[ch - 'a'];
        if (!next->word.empty()) {
            result.push_back(next->word);
            next->word.clear();  // avoid duplicates
        }
        board[r][c] = '#';
        dfs(r+1,c,next); dfs(r-1,c,next); dfs(r,c+1,next); dfs(r,c-1,next);
        board[r][c] = ch;
    };

    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            dfs(r, c, root);
    return result;
}
```

## Pattern 2: Design Add and Search Words (Wildcard)

```cpp
// Uses '.' as wildcard matching any character
bool searchWithWildcard(TrieNode* node, const std::string& word, int idx) {
    if (!node) return false;
    if (idx == (int)word.size()) return node->is_end;
    if (word[idx] == '.') {
        for (auto* child : node->children)
            if (searchWithWildcard(child, word, idx + 1)) return true;
        return false;
    }
    return searchWithWildcard(node->children[word[idx] - 'a'], word, idx + 1);
}
```

## Pattern 3: Maximum XOR of Two Numbers (Bit Trie)

```cpp
// Binary Trie for XOR maximization
struct BitTrie {
    BitTrie* children[2] = {};

    void insert(int num) {
        BitTrie* cur = this;
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (!cur->children[bit]) cur->children[bit] = new BitTrie();
            cur = cur->children[bit];
        }
    }

    int max_xor(int num) {
        BitTrie* cur = this;
        int result = 0;
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;
            int want = 1 - bit;  // we want the opposite bit for maximum XOR
            if (cur->children[want]) { result |= (1 << i); cur = cur->children[want]; }
            else cur = cur->children[bit];
        }
        return result;
    }
};

int findMaximumXOR(const std::vector<int>& nums) {
    BitTrie root;
    for (int num : nums) root.insert(num);
    int max_xor = 0;
    for (int num : nums) max_xor = std::max(max_xor, root.max_xor(num));
    return max_xor;
}
```

## Common Interview Questions

| Question | Technique | Difficulty |
|----------|-----------|------------|
| Implement Trie | Basic trie ops | Medium |
| Add and Search Words | Wildcard DFS | Medium |
| Word Search II | Trie + backtracking | Hard |
| Replace Words (prefix) | Trie traversal | Medium |
| Maximum XOR of Two Numbers | Binary trie | Medium |
| Design Search Autocomplete | Trie + heap | Hard |
