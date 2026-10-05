// Doubly linked list: each node has prev AND next, and we keep a tail pointer.
// null <- [10] <-> [20] <-> [30] -> null
// Insert at tail is O(1) and we can walk backwards.
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
        }
    }

    void insertAtHead(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void insertAtTail(int value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    bool insertAtPosition(int position, int value) {
        if (position < 0 || position > size) return false;
        if (position == 0) { insertAtHead(value); return true; }
        if (position == size) { insertAtTail(value); return true; }
        Node* current = head;
        for (int i = 0; i < position; i++) current = current->next;  // node currently at position
        Node* newNode = new Node(value);
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        size++;
        return true;
    }

    bool deleteByValue(int value) {
        Node* current = head;
        while (current != nullptr && current->data != value) current = current->next;
        if (current == nullptr) return false;

        if (current->prev != nullptr) current->prev->next = current->next;
        else head = current->next;                       // deleting head

        if (current->next != nullptr) current->next->prev = current->prev;
        else tail = current->prev;                       // deleting tail

        delete current;
        size--;
        return true;
    }

    void printForward() const {
        for (Node* current = head; current != nullptr; current = current->next) {
            cout << current->data << " <-> ";
        }
        cout << "null" << endl;
    }

    void printBackward() const {
        for (Node* current = tail; current != nullptr; current = current->prev) {
            cout << current->data << " <-> ";
        }
        cout << "null" << endl;
    }
};

int main() {
    DoublyLinkedList list;
    list.insertAtTail(10);
    list.insertAtTail(30);
    list.insertAtHead(5);
    list.insertAtPosition(2, 20);
    list.printForward();     // 5 <-> 10 <-> 20 <-> 30 <-> null
    list.printBackward();    // 30 <-> 20 <-> 10 <-> 5 <-> null
    list.deleteByValue(5);   // delete head
    list.deleteByValue(30);  // delete tail
    list.printForward();     // 10 <-> 20 <-> null
    return 0;
}
