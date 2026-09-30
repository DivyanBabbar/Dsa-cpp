// Classic linked list interview problems on a plain singly linked list.
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

Node* buildList(const vector<int>& values) {
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int value : values) {
        Node* newNode = new Node(value);
        if (head == nullptr) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }
    return head;
}

void printList(Node* head) {
    for (Node* current = head; current != nullptr; current = current->next) cout << current->data << " ";
    cout << endl;
}

void freeList(Node* head) {
    while (head != nullptr) { Node* next = head->next; delete head; head = next; }
}

// Middle node: slow moves 1 step, fast moves 2. When fast ends, slow is in the middle.
Node* findMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Floyd's cycle detection: if there is a cycle, fast eventually catches slow.
bool hasCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// Merge two sorted lists by always taking the smaller front node.
Node* mergeSorted(Node* first, Node* second) {
    Node dummy(0);                 // placeholder to avoid special-casing the head
    Node* tail = &dummy;
    while (first != nullptr && second != nullptr) {
        if (first->data <= second->data) { tail->next = first; first = first->next; }
        else { tail->next = second; second = second->next; }
        tail = tail->next;
    }
    tail->next = (first != nullptr) ? first : second;  // attach the leftover
    return dummy.next;
}

// Remove the n-th node from the end: move `lead` n steps ahead, then move both.
Node* removeNthFromEnd(Node* head, int n) {
    Node dummy(0);
    dummy.next = head;
    Node* lead = &dummy;
    Node* lag = &dummy;
    for (int i = 0; i < n; i++) lead = lead->next;
    while (lead->next != nullptr) { lead = lead->next; lag = lag->next; }
    Node* toDelete = lag->next;    // lag is the node just BEFORE the target
    lag->next = toDelete->next;
    delete toDelete;
    return dummy.next;
}

int main() {
    Node* list = buildList({1, 2, 3, 4, 5});
    cout << "Middle: " << findMiddle(list)->data << endl;   // 3
    cout << "Cycle? " << hasCycle(list) << endl;            // 0

    list = removeNthFromEnd(list, 2);                       // removes 4
    printList(list);                                        // 1 2 3 5

    Node* a = buildList({1, 4, 7});
    Node* b = buildList({2, 3, 8, 9});
    Node* merged = mergeSorted(a, b);
    printList(merged);                                      // 1 2 3 4 7 8 9

    // Make a cycle on purpose: last node points back to the second node.
    Node* cyclic = buildList({1, 2, 3, 4});
    cyclic->next->next->next->next = cyclic->next;
    cout << "Cycle? " << hasCycle(cyclic) << endl;          // 1
    cyclic->next->next->next->next = nullptr;               // break it so we can free safely

    freeList(list); freeList(merged); freeList(cyclic);
    return 0;
}
