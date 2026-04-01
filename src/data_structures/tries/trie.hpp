#pragma once

#include <array>
#include <string>
#include <vector>

/**
 * @file trie.hpp
 * @brief Trie (prefix tree) for string storage and lookup.
 *
 * Each node stores an array of 26 child pointers (lowercase a–z).
 * @complexity
 *   Insert:  O(m) — m = string length
 *   Search:  O(m)
 *   Prefix:  O(m)
 *   Space:   O(n * m) — n = number of words
 */

struct TrieNode {
    std::array<TrieNode*, 26> children{};
    bool is_end = false;
    int  pass   = 0;   // number of words passing through this node

    TrieNode() { children.fill(nullptr); }
    ~TrieNode() {
        for (auto* child : children) delete child;
    }
};

class Trie {
 public:
  Trie() : root_(new TrieNode()) {}
  ~Trie() { delete root_; }

  /**
   * @brief Insert a word.
   * @complexity O(m)
   */
  void insert(const std::string& word) {
    TrieNode* cur = root_;
    ++cur->pass;
    for (char c : word) {
      int idx = c - 'a';
      if (!cur->children[idx]) cur->children[idx] = new TrieNode();
      cur = cur->children[idx];
      ++cur->pass;
    }
    cur->is_end = true;
  }

  /**
   * @brief Returns true if word exists exactly.
   * @complexity O(m)
   */
  bool search(const std::string& word) const {
    const TrieNode* node = traverse(word);
    return node && node->is_end;
  }

  /**
   * @brief Returns true if any word has the given prefix.
   * @complexity O(m)
   */
  bool starts_with(const std::string& prefix) const {
    return traverse(prefix) != nullptr;
  }

  /**
   * @brief Count words with given prefix.
   * @complexity O(m)
   */
  int count_prefix(const std::string& prefix) const {
    const TrieNode* node = traverse(prefix);
    return node ? node->pass : 0;
  }

  /**
   * @brief Delete a word. No-op if not found.
   * @complexity O(m)
   */
  void erase(const std::string& word) {
    if (!search(word)) return;
    erase_helper(root_, word, 0);
  }

  /**
   * @brief Return all words with a given prefix.
   * @complexity O(n * m) in worst case
   */
  std::vector<std::string> autocomplete(const std::string& prefix) const {
    const TrieNode* node = traverse(prefix);
    std::vector<std::string> results;
    if (!node) return results;
    collect(node, prefix, results);
    return results;
  }

  /**
   * @brief Search with '.' wildcard (matches any character).
   * Used in LeetCode "Design Add and Search Words Data Structure" (#211).
   * @complexity O(26^m) worst case
   */
  bool search_with_wildcard(const std::string& word) const {
    return wildcard_helper(root_, word, 0);
  }

 private:
  const TrieNode* traverse(const std::string& s) const {
    const TrieNode* cur = root_;
    for (char c : s) {
      int idx = c - 'a';
      if (!cur->children[idx]) return nullptr;
      cur = cur->children[idx];
    }
    return cur;
  }

  bool erase_helper(TrieNode* node, const std::string& word, int depth) {
    if (!node) return false;
    if (depth == static_cast<int>(word.size())) {
      node->is_end = false;
    } else {
      int idx = word[depth] - 'a';
      if (erase_helper(node->children[idx], word, depth + 1)) {
        delete node->children[idx];
        node->children[idx] = nullptr;
      }
    }
    // Can delete this node if it's not end and has no children
    if (node == root_) return false;
    if (!node->is_end) {
      for (auto* child : node->children)
        if (child) return false;
      return true;  // signal parent to delete this node
    }
    return false;
  }

  void collect(const TrieNode* node, const std::string& current,
               std::vector<std::string>& results) const {
    if (node->is_end) results.push_back(current);
    for (int i = 0; i < 26; ++i) {
      if (node->children[i])
        collect(node->children[i], current + static_cast<char>('a' + i), results);
    }
  }

  bool wildcard_helper(const TrieNode* node, const std::string& word, int idx) const {
    if (!node) return false;
    if (idx == static_cast<int>(word.size())) return node->is_end;
    char c = word[idx];
    if (c != '.') {
      return wildcard_helper(node->children[c - 'a'], word, idx + 1);
    }
    for (auto* child : node->children)
      if (wildcard_helper(child, word, idx + 1)) return true;
    return false;
  }

  TrieNode* root_;
};
