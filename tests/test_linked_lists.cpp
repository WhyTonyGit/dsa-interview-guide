/**
 * @file test_linked_lists.cpp
 * @brief Unit tests for DoublyLinkedList and SinglyLinkedListAlgorithms.
 */

#include <gtest/gtest.h>
#include <stdexcept>

#include "data_structures/linked_lists/linked_list.hpp"

// ─── DoublyLinkedList ─────────────────────────────────────────────────────────

TEST(DoublyLinkedListTest, DefaultEmpty) {
    DoublyLinkedList<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

TEST(DoublyLinkedListTest, PushFrontBack) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.back(), 2);
    EXPECT_EQ(list.size(), 3u);
}

TEST(DoublyLinkedListTest, PopFrontBack) {
    DoublyLinkedList<int> list = {10, 20, 30};
    EXPECT_EQ(list.pop_front(), 10);
    EXPECT_EQ(list.pop_back(), 30);
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.front(), 20);
}

TEST(DoublyLinkedListTest, PopEmptyThrows) {
    DoublyLinkedList<int> list;
    EXPECT_THROW(list.pop_front(), std::runtime_error);
    EXPECT_THROW(list.pop_back(), std::runtime_error);
}

TEST(DoublyLinkedListTest, RemoveExisting) {
    DoublyLinkedList<int> list = {1, 2, 3, 4};
    bool removed = list.remove(3);
    EXPECT_TRUE(removed);
    EXPECT_EQ(list.size(), 3u);
    EXPECT_EQ(list.find(3), nullptr);
}

TEST(DoublyLinkedListTest, RemoveNonExistent) {
    DoublyLinkedList<int> list = {1, 2, 3};
    EXPECT_FALSE(list.remove(99));
    EXPECT_EQ(list.size(), 3u);
}

TEST(DoublyLinkedListTest, Reverse) {
    DoublyLinkedList<int> list = {1, 2, 3, 4, 5};
    list.reverse();
    EXPECT_EQ(list.front(), 5);
    EXPECT_EQ(list.back(), 1);
}

TEST(DoublyLinkedListTest, Clear) {
    DoublyLinkedList<int> list = {1, 2, 3};
    list.clear();
    EXPECT_TRUE(list.empty());
}

TEST(DoublyLinkedListTest, CopySemantics) {
    DoublyLinkedList<int> a = {1, 2, 3};
    DoublyLinkedList<int> b = a;
    b.push_back(4);
    EXPECT_EQ(a.size(), 3u);  // original unchanged
    EXPECT_EQ(b.size(), 4u);
}

TEST(DoublyLinkedListTest, MoveSemantics) {
    DoublyLinkedList<int> a = {1, 2, 3};
    DoublyLinkedList<int> b = std::move(a);
    EXPECT_EQ(b.size(), 3u);
}

// ─── SinglyLinkedListAlgorithms ───────────────────────────────────────────────

using Algo = SinglyLinkedListAlgorithms<int>;
using Node = SLLNode<int>;

Node* buildSLL(const std::vector<int>& vals) {
    if (vals.empty()) return nullptr;
    Node* head = new Node(vals[0]);
    Node* cur = head;
    for (std::size_t i = 1; i < vals.size(); ++i) {
        cur->next = new Node(vals[i]);
        cur = cur->next;
    }
    return head;
}

void freeSLL(Node* head) {
    while (head) { Node* n = head->next; delete head; head = n; }
}

TEST(SinglyLinkedListTest, Reverse) {
    Node* head = buildSLL({1, 2, 3, 4, 5});
    head = Algo::reverse(head);
    EXPECT_EQ(head->val, 5);
    EXPECT_EQ(head->next->val, 4);
    freeSLL(head);
}

TEST(SinglyLinkedListTest, ReverseNull) {
    EXPECT_EQ(Algo::reverse(nullptr), nullptr);
}

TEST(SinglyLinkedListTest, ReverseSingle) {
    Node* n = new Node(42);
    Node* rev = Algo::reverse(n);
    EXPECT_EQ(rev->val, 42);
    EXPECT_EQ(rev->next, nullptr);
    delete rev;
}

TEST(SinglyLinkedListTest, NoCycle) {
    Node* head = buildSLL({1, 2, 3});
    EXPECT_FALSE(Algo::has_cycle(head));
    freeSLL(head);
}

TEST(SinglyLinkedListTest, HasCycle) {
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    n1->next = n2; n2->next = n3; n3->next = n1;
    EXPECT_TRUE(Algo::has_cycle(n1));
    n3->next = nullptr;  // break cycle before delete
    freeSLL(n1);
}

TEST(SinglyLinkedListTest, FindMiddleOdd) {
    Node* head = buildSLL({1, 2, 3, 4, 5});
    Node* mid = Algo::find_middle(head);
    EXPECT_EQ(mid->val, 3);
    freeSLL(head);
}

TEST(SinglyLinkedListTest, FindMiddleEven) {
    Node* head = buildSLL({1, 2, 3, 4});
    Node* mid = Algo::find_middle(head);
    EXPECT_EQ(mid->val, 3);  // second middle
    freeSLL(head);
}

TEST(SinglyLinkedListTest, MergeSorted) {
    Node* l1 = buildSLL({1, 3, 5});
    Node* l2 = buildSLL({2, 4, 6});
    Node* merged = Algo::merge_sorted(l1, l2);
    int expected[] = {1, 2, 3, 4, 5, 6};
    Node* cur = merged;
    for (int v : expected) {
        ASSERT_NE(cur, nullptr);
        EXPECT_EQ(cur->val, v);
        cur = cur->next;
    }
    freeSLL(merged);
}
