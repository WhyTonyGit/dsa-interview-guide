/**
 * @file examples.cpp
 * @brief Runnable examples for stacks and queues.
 */

#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <vector>

#include "data_structures/stacks_queues/stack.hpp"
#include "data_structures/stacks_queues/queue.hpp"

void demo_stack() {
    std::cout << "\n=== Stack Demo ===\n";
    Stack<int> s;
    for (int i : {1, 2, 3, 4, 5}) s.push(i);
    std::cout << "Top: " << s.top() << "  (expected 5)\n";
    s.pop();
    std::cout << "After pop, top: " << s.top() << "  (expected 4)\n";
    std::cout << "Size: " << s.size() << "\n";
}

void demo_min_stack() {
    std::cout << "\n=== Min Stack ===\n";
    MinStack<int> ms;
    ms.push(5); ms.push(3); ms.push(7); ms.push(1); ms.push(4);
    std::cout << "Min: " << ms.getMin() << "  (expected 1)\n";
    ms.pop();
    std::cout << "After pop, Min: " << ms.getMin() << "  (expected 1)\n";
    ms.pop();
    std::cout << "After pop, Min: " << ms.getMin() << "  (expected 3)\n";
}

void demo_queue() {
    std::cout << "\n=== Queue Demo ===\n";
    Queue<int> q;
    for (int i : {10, 20, 30, 40}) q.enqueue(i);
    std::cout << "Front: " << q.front() << "  (expected 10)\n";
    std::cout << "Dequeue: " << q.dequeue() << "  (expected 10)\n";
    std::cout << "Front: " << q.front() << "  (expected 20)\n";
    std::cout << "Size: " << q.size() << "\n";
}

void demo_queue_two_stacks() {
    std::cout << "\n=== Queue via Two Stacks ===\n";
    QueueWithTwoStacks<int> q;
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    std::cout << "Dequeue: " << q.dequeue() << "  (expected 1)\n";
    q.enqueue(4);
    std::cout << "Dequeue: " << q.dequeue() << "  (expected 2)\n";
    std::cout << "Dequeue: " << q.dequeue() << "  (expected 3)\n";
    std::cout << "Dequeue: " << q.dequeue() << "  (expected 4)\n";
}

bool isValid(const std::string& s) {
    std::stack<char> stk;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') { stk.push(c); }
        else {
            if (stk.empty()) return false;
            char top = stk.top(); stk.pop();
            if ((c == ')' && top != '(') || (c == ']' && top != '[') || (c == '}' && top != '{'))
                return false;
        }
    }
    return stk.empty();
}

std::vector<int> dailyTemperatures(const std::vector<int>& T) {
    int n = static_cast<int>(T.size());
    std::vector<int> result(n, 0);
    std::stack<int> stk;
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && T[stk.top()] < T[i]) {
            result[stk.top()] = i - stk.top();
            stk.pop();
        }
        stk.push(i);
    }
    return result;
}

std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
    std::deque<int> dq;
    std::vector<int> result;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) result.push_back(nums[dq.front()]);
    }
    return result;
}

int main() {
    demo_stack();
    demo_min_stack();
    demo_queue();
    demo_queue_two_stacks();

    std::cout << "\n=== Valid Parentheses ===\n";
    std::cout << "\"()[]{}\" -> " << (isValid("()[]{}") ? "true" : "false") << "  (expected true)\n";
    std::cout << "\"([)]\"   -> " << (isValid("([)]")   ? "true" : "false") << "  (expected false)\n";

    std::cout << "\n=== Daily Temperatures ===\n";
    std::vector<int> temps = {73,74,75,71,69,72,76,73};
    auto result = dailyTemperatures(temps);
    std::cout << "Result: [";
    for (std::size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << (i+1 < result.size() ? "," : "");
    std::cout << "]  (expected [1,1,4,2,1,1,0,0])\n";

    std::cout << "\n=== Sliding Window Maximum ===\n";
    std::vector<int> nums = {1,3,-1,-3,5,3,6,7};
    auto sw = maxSlidingWindow(nums, 3);
    std::cout << "maxSlidingWindow([1,3,-1,-3,5,3,6,7], k=3): [";
    for (std::size_t i = 0; i < sw.size(); ++i)
        std::cout << sw[i] << (i+1 < sw.size() ? "," : "");
    std::cout << "]  (expected [3,3,5,5,6,7])\n";

    return 0;
}
