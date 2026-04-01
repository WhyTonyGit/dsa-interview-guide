/**
 * @file examples.cpp
 * @brief Trie examples: insert, search, autocomplete, wildcard.
 */

#include <iostream>
#include <string>
#include <vector>

#include "data_structures/tries/trie.hpp"

int main() {
    std::cout << "\n=== Trie Demo ===\n";
    Trie trie;
    for (const std::string& w : {"apple", "app", "application", "apt", "banana", "band"})
        trie.insert(w);

    std::cout << "search('apple'):       " << (trie.search("apple")       ? "true" : "false") << "\n";
    std::cout << "search('app'):         " << (trie.search("app")         ? "true" : "false") << "\n";
    std::cout << "search('appl'):        " << (trie.search("appl")        ? "true" : "false") << "\n";
    std::cout << "starts_with('app'):    " << (trie.starts_with("app")    ? "true" : "false") << "\n";
    std::cout << "starts_with('xyz'):    " << (trie.starts_with("xyz")    ? "true" : "false") << "\n";
    std::cout << "count_prefix('app'):   " << trie.count_prefix("app")    << "  (expected 3)\n";
    std::cout << "count_prefix('ban'):   " << trie.count_prefix("ban")    << "  (expected 2)\n";

    std::cout << "\n=== Autocomplete 'app' ===\n";
    auto completions = trie.autocomplete("app");
    for (const auto& w : completions) std::cout << "  " << w << "\n";

    std::cout << "\n=== Wildcard search ===\n";
    std::cout << "search_with_wildcard('a..le'): "
              << (trie.search_with_wildcard("a..le") ? "true" : "false")
              << "  (expected true, matches 'apple')\n";
    std::cout << "search_with_wildcard('b...'): "
              << (trie.search_with_wildcard("b....") ? "true" : "false")
              << "  (expected true, matches 'apple'? no: 'banan'... let's check)\n";

    std::cout << "\n=== Delete ===\n";
    trie.erase("app");
    std::cout << "After erase('app'), search('app'):   " << (trie.search("app")   ? "true" : "false") << "\n";
    std::cout << "After erase('app'), search('apple'): " << (trie.search("apple") ? "true" : "false") << "\n";

    return 0;
}
