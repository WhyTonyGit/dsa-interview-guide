/**
 * @file examples.cpp
 * @brief Hash table examples and classic interview problems.
 */

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "data_structures/hash_tables/hash_table.hpp"

// ─── 1. Custom HashMap demo ───────────────────────────────────────────────────

void demo_hashmap() {
    std::cout << "\n=== Custom HashMap ===\n";
    HashMap<std::string, int> map;
    map.insert("apple",  5);
    map.insert("banana", 3);
    map.insert("cherry", 8);
    map["date"] = 2;

    std::cout << "apple:  " << map.at("apple")  << "\n";
    std::cout << "banana: " << map.at("banana") << "\n";
    std::cout << "Count 'cherry': " << map.count("cherry") << "\n";
    std::cout << "Count 'grape':  " << map.count("grape")  << "  (0 = not found)\n";

    map.erase("banana");
    std::cout << "After erase 'banana': count = " << map.count("banana") << "\n";
    std::cout << "Size: " << map.size() << "\n";
}

// ─── 2. Group Anagrams ────────────────────────────────────────────────────────

std::vector<std::vector<std::string>>
groupAnagrams(const std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> groups;
    for (const auto& s : strs) {
        std::string key = s;
        std::sort(key.begin(), key.end());
        groups[key].push_back(s);
    }
    std::vector<std::vector<std::string>> result;
    for (auto& [k, v] : groups) result.push_back(std::move(v));
    return result;
}

// ─── 3. Top K Frequent Elements ───────────────────────────────────────────────

std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;
    std::vector<std::vector<int>> buckets(nums.size() + 1);
    for (auto& [num, count] : freq) buckets[count].push_back(num);
    std::vector<int> result;
    for (int i = static_cast<int>(buckets.size()) - 1;
         i >= 0 && static_cast<int>(result.size()) < k; --i) {
        for (int x : buckets[i]) {
            result.push_back(x);
            if (static_cast<int>(result.size()) == k) break;
        }
    }
    return result;
}

// ─── 4. Longest Consecutive Sequence ─────────────────────────────────────────

int longestConsecutive(const std::vector<int>& nums) {
    std::unordered_set<int> num_set(nums.begin(), nums.end());
    int best = 0;
    for (int num : num_set) {
        if (!num_set.count(num - 1)) {
            int cur = num, length = 1;
            while (num_set.count(cur + 1)) { ++cur; ++length; }
            best = std::max(best, length);
        }
    }
    return best;
}

// ─── 5. LRU Cache ────────────────────────────────────────────────────────────

class LRUCache {
 public:
    explicit LRUCache(int cap) : capacity_(cap) {}

    int get(int key) {
        auto it = map_.find(key);
        if (it == map_.end()) return -1;
        list_.splice(list_.begin(), list_, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = map_.find(key);
        if (it != map_.end()) list_.erase(it->second);
        else if (static_cast<int>(list_.size()) == capacity_) {
            map_.erase(list_.back().first);
            list_.pop_back();
        }
        list_.push_front({key, value});
        map_[key] = list_.begin();
    }

 private:
    int capacity_;
    std::list<std::pair<int,int>> list_;
    std::unordered_map<int, std::list<std::pair<int,int>>::iterator> map_;
};

// ─── Main ─────────────────────────────────────────────────────────────────────

int main() {
    demo_hashmap();

    std::cout << "\n=== Group Anagrams ===\n";
    auto groups = groupAnagrams({"eat","tea","tan","ate","nat","bat"});
    std::cout << "Groups: " << groups.size() << "  (expected 3)\n";
    for (const auto& g : groups) {
        std::cout << "  [";
        for (std::size_t i = 0; i < g.size(); ++i)
            std::cout << g[i] << (i+1 < g.size() ? "," : "");
        std::cout << "]\n";
    }

    std::cout << "\n=== Top K Frequent ===\n";
    std::vector<int> nums = {1,1,1,2,2,3};
    auto top = topKFrequent(nums, 2);
    std::cout << "Top 2 frequent in [1,1,1,2,2,3]: [";
    for (std::size_t i = 0; i < top.size(); ++i)
        std::cout << top[i] << (i+1 < top.size() ? "," : "");
    std::cout << "]  (expected [1,2])\n";

    std::cout << "\n=== Longest Consecutive Sequence ===\n";
    std::vector<int> seq = {100,4,200,1,3,2};
    std::cout << "longestConsecutive([100,4,200,1,3,2]) = "
              << longestConsecutive(seq) << "  (expected 4)\n";

    std::cout << "\n=== LRU Cache ===\n";
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    std::cout << "get(1) = " << cache.get(1) << "  (expected 1)\n";
    cache.put(3, 3);  // evicts key 2
    std::cout << "get(2) = " << cache.get(2) << "  (expected -1, evicted)\n";
    cache.put(4, 4);  // evicts key 1
    std::cout << "get(1) = " << cache.get(1) << "  (expected -1, evicted)\n";
    std::cout << "get(3) = " << cache.get(3) << "  (expected 3)\n";
    std::cout << "get(4) = " << cache.get(4) << "  (expected 4)\n";

    return 0;
}
