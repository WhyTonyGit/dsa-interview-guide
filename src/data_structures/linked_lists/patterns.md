# Linked List Interview Patterns

## Pattern 1: Fast & Slow Pointers (Floyd's Algorithm)

**When to use:** Cycle detection, find middle, find cycle start, check palindrome.

**Approach:** Slow moves 1 step, fast moves 2 steps. They meet if there's a cycle.

```cpp
// Cycle detection
bool hasCycle(ListNode* head) {
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// Find middle (for even length: returns second middle)
ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Find cycle start
ListNode* detectCycleStart(ListNode* head) {
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            ListNode* entry = head;
            while (entry != slow) {
                entry = entry->next;
                slow = slow->next;
            }
            return entry;  // cycle start
        }
    }
    return nullptr;
}
```

---

## Pattern 2: Reverse a Linked List

**Three approaches:** iterative (O(1) space), recursive (O(n) stack), in groups.

```cpp
// Iterative — memorise this
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* cur  = head;
    while (cur) {
        ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur  = next;
    }
    return prev;  // new head
}

// Recursive
ListNode* reverseRecursive(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* new_head = reverseRecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return new_head;
}

// Reverse in groups of K
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* cur = head;
    int count = 0;
    while (cur && count < k) { cur = cur->next; ++count; }
    if (count < k) return head;
    cur = reverseList(head);   // reverse first k nodes
    // head is now tail of reversed group
    // 'cur' is the k+1 th node (start of remaining)
    // Note: for full implementation see examples.cpp
    return cur;
}
```

---

## Pattern 3: Dummy Head Node

**When to use:** Any time the head can change (merge sorted lists, remove nth from end, partition).

```cpp
// Merge two sorted linked lists
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);     // dummy head eliminates special cases
    ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) { tail->next = l1; l1 = l1->next; }
        else                   { tail->next = l2; l2 = l2->next; }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// Remove nth node from end — two-pointer gap
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;
    for (int i = 0; i <= n; ++i) fast = fast->next;
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    ListNode* to_delete = slow->next;
    slow->next = slow->next->next;
    delete to_delete;
    return dummy.next;
}
```

---

## Pattern 4: Check Palindrome

**Approach:** Find middle → reverse second half → compare → restore (optional).

```cpp
bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;
    // 1. Find middle
    ListNode* slow = head, *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    // 2. Reverse second half
    ListNode* second_half = reverseList(slow->next);
    // 3. Compare
    ListNode* p1 = head;
    ListNode* p2 = second_half;
    bool is_palindrome = true;
    while (p2) {
        if (p1->val != p2->val) { is_palindrome = false; break; }
        p1 = p1->next;
        p2 = p2->next;
    }
    // 4. Restore (optional but good practice)
    slow->next = reverseList(second_half);
    return is_palindrome;
}
```

---

## Pattern 5: Intersection of Two Lists

**Approach:** Advance the longer list by the length difference, then walk together.

```cpp
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    ListNode* a = headA;
    ListNode* b = headB;
    // When a reaches end, redirect to headB; same for b → headA
    // They meet at intersection or both reach nullptr simultaneously
    while (a != b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }
    return a;
}
```

---

## Pattern 6: Add Two Numbers (Linked List Representation)

```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* cur = &dummy;
    int carry = 0;
    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) { sum += l1->val; l1 = l1->next; }
        if (l2) { sum += l2->val; l2 = l2->next; }
        carry = sum / 10;
        cur->next = new ListNode(sum % 10);
        cur = cur->next;
    }
    return dummy.next;
}
```

---

## Common Interview Questions

| Question | Pattern | Difficulty |
|----------|---------|------------|
| Reverse Linked List | Three-pointer | Easy |
| Merge Two Sorted Lists | Dummy head | Easy |
| Linked List Cycle | Fast/slow | Easy |
| Remove Nth Node From End | Two-pointer gap | Medium |
| Palindrome Linked List | Find middle + reverse | Easy |
| Add Two Numbers | Carry arithmetic | Medium |
| Reorder List | Find middle + reverse + merge | Medium |
| Copy List with Random Pointer | Hash map / interleave | Medium |
| LRU Cache | Doubly linked list + hash map | Medium |
| Merge K Sorted Lists | Heap / divide & conquer | Hard |
