// Circular doubly linked list: head->prev is the tail, tail->next is the head.
// No nulls anywhere in a non-empty list.
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class CircularDoublyLinkedList {
private:
    Node* head;
    int size;

public:
    CircularDoublyLinkedList() : head(nullptr), size(0) {}

    ~CircularDoublyLinkedList() {
        while (size > 0) deleteByValue(head->data);
    }

    void insertAtTail(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            newNode->next = newNode;
            newNode->prev = newNode;
            head = newNode;
        } else {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
        size++;
    }

    void insertAtHead(int value) {
        insertAtTail(value);              // link it in at the back...
        head = head->prev;                // ...then make it the head
    }

    bool deleteByValue(int value) {
        Node* current = head;
        for (int i = 0; i < size; i++) {  // visit each node once
            if (current->data == value) {
                if (size == 1) {
                    head = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    if (current == head) head = current->next;
                }
                delete current;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void printForward() const {
        Node* current = head;
        for (int i = 0; i < size; i++) {
            cout << current->data << " <-> ";
            current = current->next;
        }
        cout << "(circular)" << endl;
    }

    void printBackward() const {
        if (head == nullptr) { cout << "(empty)" << endl; return; }
        Node* current = head->prev;       // tail
        for (int i = 0; i < size; i++) {
            cout << current->data << " <-> ";
            current = current->prev;
        }
        cout << "(circular)" << endl;
    }
};

int main() {
    CircularDoublyLinkedList list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAtHead(5);
    list.printForward();     // 5 <-> 10 <-> 20 <-> 30 <-> (circular)
    list.printBackward();    // 30 <-> 20 <-> 10 <-> 5 <-> (circular)
    list.deleteByValue(5);
    list.deleteByValue(30);
    list.printForward();     // 10 <-> 20 <-> (circular)
    return 0;
}
