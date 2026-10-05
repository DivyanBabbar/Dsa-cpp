// Circular singly linked list: the last node points back to the first.
// We store only `tail`. Then tail->next is the head, so both ends are O(1).
//   tail -> [30] -> [10] -> [20] -> (back to [30])
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class CircularSinglyLinkedList {
private:
    Node* tail;
    int size;

public:
    CircularSinglyLinkedList() : tail(nullptr), size(0) {}

    ~CircularSinglyLinkedList() {
        while (tail != nullptr) deleteHead();
    }

    void insertAtHead(int value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            newNode->next = newNode;      // points to itself
            tail = newNode;
        } else {
            newNode->next = tail->next;   // old head
            tail->next = newNode;         // new head
        }
        size++;
    }

    void insertAtTail(int value) {
        insertAtHead(value);              // same linking...
        tail = tail->next;                // ...then move tail to the new node
    }

    void deleteHead() {
        if (tail == nullptr) return;
        Node* head = tail->next;
        if (head == tail) {               // only one node
            tail = nullptr;
        } else {
            tail->next = head->next;
        }
        delete head;
        size--;
    }

    bool deleteByValue(int value) {
        if (tail == nullptr) return false;
        Node* previous = tail;
        Node* current = tail->next;       // head
        do {
            if (current->data == value) {
                if (current == previous) {            // single node
                    tail = nullptr;
                } else {
                    previous->next = current->next;
                    if (current == tail) tail = previous;
                }
                delete current;
                size--;
                return true;
            }
            previous = current;
            current = current->next;
        } while (previous != tail);       // stop after checking the tail node
        return false;
    }

    void print() const {
        if (tail == nullptr) { cout << "(empty)" << endl; return; }
        Node* current = tail->next;
        do {
            cout << current->data << " -> ";
            current = current->next;
        } while (current != tail->next);
        cout << "(back to head)" << endl;
    }
};

int main() {
    CircularSinglyLinkedList list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtHead(5);
    list.print();            // 5 -> 10 -> 20 -> (back to head)
    list.deleteByValue(20);  // delete tail
    list.print();            // 5 -> 10 -> (back to head)
    list.deleteByValue(5);   // delete head
    list.print();            // 10 -> (back to head)
    list.deleteByValue(10);  // delete only node
    list.print();            // (empty)
    return 0;
}
