// LeetCode 155 - Min Stack (Medium)
// A stack that supports push, pop, top AND getMin, all in O(1).
//
// Problem: after pop() removes the current minimum, the NEW minimum is unknown unless
// we remembered it. So every entry stores the minimum of the stack AS IT WAS when that
// entry was pushed. Then popping simply reveals the previous minimum.
//
//   push -2 -> (-2, min -2)
//   push  0 -> ( 0, min -2)
//   push -3 -> (-3, min -3)    getMin() = -3
//   pop     -> top is ( 0, min -2)   getMin() = -2
//
// Every operation O(1). Space O(n) (one extra int per element).
// Like the LeetCode version, top/pop/getMin assume the stack is not empty.
#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
using namespace std;

class MinStack {
private:
    // first = the value, second = smallest value in the stack up to and including this entry
    stack<pair<int, int>> entries;

public:
    void push(int value) {
        int smallestSoFar = value;
        if (!entries.empty()) smallestSoFar = min(value, entries.top().second);
        entries.push({value, smallestSoFar});
    }

    void pop() { entries.pop(); }

    int top() const { return entries.top().first; }

    int getMin() const { return entries.top().second; }

    bool empty() const { return entries.empty(); }
};

int main() {
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << "getMin = " << minStack.getMin() << endl;       // -3
    minStack.pop();
    cout << "top = " << minStack.top() << endl;             // 0
    cout << "getMin = " << minStack.getMin() << endl;       // -2

    // duplicates of the minimum are handled too: popping one copy keeps the other
    MinStack duplicates;
    duplicates.push(5);
    duplicates.push(1);
    duplicates.push(1);
    duplicates.pop();
    cout << "getMin after popping one of two 1s = " << duplicates.getMin() << endl;   // 1
    return 0;
}
