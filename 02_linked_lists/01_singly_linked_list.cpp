// Singly linked list: each node points only to the next node.
// head -> [10|*] -> [20|*] -> [30|null]
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;
    int size;

public:
    SinglyLinkedList() : head(nullptr), size(0) {}

    ~SinglyLinkedList() {
        while (head != nullptr) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
        }
    }

    // O(1)
    void insertAtHead(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size++;
    }

    // O(n): must walk to the last node
    void insertAtTail(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) current = current->next;
            current->next = newNode;
        }
        size++;
    }

    // position 0 = head. Walk to the node BEFORE the position, then relink.
    bool insertAtPosition(int position, int value) {
        if (position < 0 || position > size) return false;
        if (position == 0) { insertAtHead(value); return true; }
        Node* previous = head;
        for (int i = 0; i < position - 1; i++) previous = previous->next;
        Node* newNode = new Node(value);
        newNode->next = previous->next;
        previous->next = newNode;
        size++;
        return true;
    }

    bool deleteByValue(int value) {
        if (head == nullptr) return false;
        if (head->data == value) {             // deleting the head
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            size--;
            return true;
        }
        Node* previous = head;
        while (previous->next != nullptr && previous->next->data != value) {
            previous = previous->next;
        }
        if (previous->next == nullptr) return false;  // not found
        Node* toDelete = previous->next;
        previous->next = toDelete->next;       // bypass the node
        delete toDelete;
        size--;
        return true;
    }

    bool search(int value) const {
        for (Node* current = head; current != nullptr; current = current->next) {
            if (current->data == value) return true;
        }
        return false;
    }

    // Reverse by flipping each next pointer. O(n), O(1) space.
    void reverse() {
        Node* previous = nullptr;
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;  // save
            current->next = previous;        // flip
            previous = current;              // advance previous
            current = nextNode;              // advance current
        }
        head = previous;
    }

    void print() const {
        for (Node* current = head; current != nullptr; current = current->next) {
            cout << current->data << " -> ";
        }
        cout << "null" << endl;
    }
};

int main() {
    SinglyLinkedList list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtHead(5);
    list.insertAtPosition(2, 15);
    list.print();                        // 5 -> 10 -> 15 -> 20 -> null
    list.deleteByValue(10);
    list.print();                        // 5 -> 15 -> 20 -> null
    list.reverse();
    list.print();                        // 20 -> 15 -> 5 -> null
    cout << "Has 15? " << list.search(15) << endl;  // 1
    return 0;
}
