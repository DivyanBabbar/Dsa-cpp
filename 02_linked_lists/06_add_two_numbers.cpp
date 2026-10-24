// LeetCode 2 - Add Two Numbers (Medium)
// Two numbers are stored as linked lists, one digit per node, LEAST significant digit first.
//   342 is 2 -> 4 -> 3        465 is 5 -> 6 -> 4
//   342 + 465 = 807           result: 7 -> 0 -> 8
//
// Idea: add column by column exactly like on paper. The lists already start at the ones digit,
// so we just walk both lists together, carrying 1 to the next column when a sum reaches 10.
// A dummy head node avoids a special case for the first node of the result.
//
// Time O(max(m, n)), space O(max(m, n)) for the result list.
#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int digit;
    ListNode* next;
    ListNode(int value) : digit(value), next(nullptr) {}
};

ListNode* addTwoNumbers(ListNode* firstList, ListNode* secondList) {
    ListNode dummyHead(0);                  // result starts at dummyHead.next
    ListNode* tail = &dummyHead;
    int carry = 0;

    // keep going while any list has digits left OR a carry is still waiting
    while (firstList != nullptr || secondList != nullptr || carry != 0) {
        int columnSum = carry;
        if (firstList != nullptr) {
            columnSum += firstList->digit;
            firstList = firstList->next;
        }
        if (secondList != nullptr) {
            columnSum += secondList->digit;
            secondList = secondList->next;
        }

        carry = columnSum / 10;                         // 0 or 1
        tail->next = new ListNode(columnSum % 10);      // digit that stays in this column
        tail = tail->next;
    }
    return dummyHead.next;
}

ListNode* buildList(const vector<int>& digits) {
    ListNode dummyHead(0);
    ListNode* tail = &dummyHead;
    for (int digit : digits) {
        tail->next = new ListNode(digit);
        tail = tail->next;
    }
    return dummyHead.next;
}

void printList(ListNode* head) {
    for (ListNode* current = head; current != nullptr; current = current->next) {
        cout << current->digit;
        if (current->next != nullptr) cout << " -> ";
    }
    cout << endl;
}

void freeList(ListNode* head) {
    while (head != nullptr) {
        ListNode* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

int main() {
    ListNode* first = buildList({2, 4, 3});         // 342
    ListNode* second = buildList({5, 6, 4});        // 465
    ListNode* sum = addTwoNumbers(first, second);
    printList(sum);                                 // 7 -> 0 -> 8   (807)
    freeList(first); freeList(second); freeList(sum);

    // carry runs past the end of both lists: 9999 + 1 = 10000
    first = buildList({9, 9, 9, 9});
    second = buildList({1});
    sum = addTwoNumbers(first, second);
    printList(sum);                                 // 0 -> 0 -> 0 -> 0 -> 1   (10000)
    freeList(first); freeList(second); freeList(sum);
    return 0;
}
