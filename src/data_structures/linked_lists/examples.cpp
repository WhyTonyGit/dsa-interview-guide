/**
 * @file examples.cpp
 * @brief Runnable examples for linked list operations and interview patterns.
 *
 * Compile & run:
 *   cd build && make examples_linked_lists && ./examples_linked_lists
 */

#include <iostream>
#include <string>
#include <vector>

#include "data_structures/linked_lists/linked_list.hpp"

// ─── Helpers ──────────────────────────────────────────────────────────────────

// Build a singly-linked list from a vector (caller owns the nodes)
SLLNode<int>* build(const std::vector<int>& vals) {
    if (vals.empty()) return nullptr;
    SLLNode<int>* head = new SLLNode<int>(vals[0]);
    SLLNode<int>* cur  = head;
    for (std::size_t i = 1; i < vals.size(); ++i) {
        cur->next = new SLLNode<int>(vals[i]);
        cur = cur->next;
    }
    return head;
}

void printSLL(const std::string& label, SLLNode<int>* head) {
    std::cout << label << ": ";
    while (head) {
        std::cout << head->val;
        if (head->next) std::cout << " -> ";
        head = head->next;
    }
    std::cout << "\n";
}

void freeSLL(SLLNode<int>* head) {
    while (head) {
        SLLNode<int>* next = head->next;
        delete head;
        head = next;
    }
}

// ─── 1. DoublyLinkedList demo ─────────────────────────────────────────────────

void demo_doubly_linked_list() {
    std::cout << "\n=== DoublyLinkedList Basics ===\n";

    DoublyLinkedList<int> list = {10, 20, 30, 40, 50};
    list.print();

    list.push_front(5);
    list.push_back(60);
    std::cout << "After push_front(5) + push_back(60): ";
    list.print();

    std::cout << "Front: " << list.front() << ", Back: " << list.back() << "\n";

    list.pop_front();
    list.pop_back();
    std::cout << "After pop_front() + pop_back(): ";
    list.print();

    list.remove(30);
    std::cout << "After remove(30): ";
    list.print();

    std::cout << "Size: " << list.size() << "\n";

    list.reverse();
    std::cout << "After reverse(): ";
    list.print();

    // Copy
    DoublyLinkedList<int> copy = list;
    copy.push_front(0);
    std::cout << "Original unchanged after modifying copy: ";
    list.print();
}

// ─── 2. Reverse singly-linked list ───────────────────────────────────────────

void demo_reverse() {
    std::cout << "\n=== Reverse Linked List ===\n";
    SLLNode<int>* head = build({1, 2, 3, 4, 5});
    printSLL("Original", head);

    head = SinglyLinkedListAlgorithms<int>::reverse(head);
    printSLL("Reversed", head);

    freeSLL(head);
}

// ─── 3. Detect cycle ─────────────────────────────────────────────────────────

void demo_cycle_detection() {
    std::cout << "\n=== Cycle Detection ===\n";

    // List with no cycle: 1 -> 2 -> 3 -> nullptr
    SLLNode<int>* no_cycle = build({1, 2, 3});
    std::cout << "No cycle: " << (SinglyLinkedListAlgorithms<int>::has_cycle(no_cycle) ? "true" : "false")
              << "  (expected false)\n";
    freeSLL(no_cycle);

    // List with cycle: 1 -> 2 -> 3 -> 2 (cycle)
    SLLNode<int>* n1 = new SLLNode<int>(1);
    SLLNode<int>* n2 = new SLLNode<int>(2);
    SLLNode<int>* n3 = new SLLNode<int>(3);
    n1->next = n2; n2->next = n3; n3->next = n2;  // create cycle
    std::cout << "Has cycle: " << (SinglyLinkedListAlgorithms<int>::has_cycle(n1) ? "true" : "false")
              << "  (expected true)\n";
    // Break cycle before freeing
    n3->next = nullptr;
    freeSLL(n1);
}

// ─── 4. Find middle ───────────────────────────────────────────────────────────

void demo_find_middle() {
    std::cout << "\n=== Find Middle ===\n";
    SLLNode<int>* odd = build({1, 2, 3, 4, 5});
    SLLNode<int>* mid = SinglyLinkedListAlgorithms<int>::find_middle(odd);
    std::cout << "Middle of [1,2,3,4,5]: " << mid->val << "  (expected 3)\n";
    freeSLL(odd);

    SLLNode<int>* even = build({1, 2, 3, 4});
    mid = SinglyLinkedListAlgorithms<int>::find_middle(even);
    std::cout << "Middle of [1,2,3,4]: " << mid->val << "  (expected 3 — second middle)\n";
    freeSLL(even);
}

// ─── 5. Merge two sorted lists ────────────────────────────────────────────────

void demo_merge_sorted() {
    std::cout << "\n=== Merge Two Sorted Lists ===\n";
    SLLNode<int>* l1 = build({1, 3, 5, 7});
    SLLNode<int>* l2 = build({2, 4, 6, 8});
    printSLL("L1", l1);
    printSLL("L2", l2);
    SLLNode<int>* merged = SinglyLinkedListAlgorithms<int>::merge_sorted(l1, l2);
    printSLL("Merged", merged);
    freeSLL(merged);
}

// ─── 6. LRU Cache (doubly-linked list + hash map) ────────────────────────────

#include <unordered_map>

class LRUCache {
 public:
    explicit LRUCache(int capacity) : capacity_(capacity) {}

    int get(int key) {
        auto it = map_.find(key);
        if (it == map_.end()) return -1;
        // Move to front (most recently used)
        list_.remove(it->second);
        list_.push_front(it->second);
        // Update map to point to new front
        map_[key] = list_.front();
        // Re-find node value  (simplified: store key-value pair)
        return it->second;
    }

    void put(int key, int value) {
        auto it = map_.find(key);
        if (it != map_.end()) {
            list_.remove(it->second);
        } else if (static_cast<int>(list_.size()) == capacity_) {
            // Evict least recently used (back of list)
            int lru_key = list_.back();
            list_.pop_back();
            map_.erase(lru_key);
        }
        list_.push_front(value);
        map_[key] = value;
    }

 private:
    int capacity_;
    DoublyLinkedList<int> list_;
    std::unordered_map<int, int> map_;
};

void demo_lru_cache() {
    std::cout << "\n=== LRU Cache ===\n";
    LRUCache cache(3);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    std::cout << "get(1) = " << cache.get(1) << "  (expected 10)\n";
    cache.put(4, 40);  // evicts key 2 (least recently used)
    std::cout << "get(2) = " << cache.get(2) << "  (expected -1, evicted)\n";
    std::cout << "get(3) = " << cache.get(3) << "  (expected 30)\n";
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main() {
    demo_doubly_linked_list();
    demo_reverse();
    demo_cycle_detection();
    demo_find_middle();
    demo_merge_sorted();
    demo_lru_cache();

    return 0;
}
