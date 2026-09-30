// Deque (double-ended queue): insert and remove at BOTH ends in O(1).
// Built on a doubly linked list.
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class Deque {
private:
    Node* front;
    Node* rear;

public:
    Deque() : front(nullptr), rear(nullptr) {}
    ~Deque() { while (!isEmpty()) popFront(); }

    bool isEmpty() const { return front == nullptr; }

    void pushFront(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
    }

    void pushBack(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
    }

    int popFront() {
        if (isEmpty()) { cout << "Deque empty" << endl; return -1; }
        Node* toDelete = front;
        int value = toDelete->data;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        else front->prev = nullptr;
        delete toDelete;
        return value;
    }

    int popBack() {
        if (isEmpty()) { cout << "Deque empty" << endl; return -1; }
        Node* toDelete = rear;
        int value = toDelete->data;
        rear = rear->prev;
        if (rear == nullptr) front = nullptr;
        else rear->next = nullptr;
        delete toDelete;
        return value;
    }

    int peekFront() const { return isEmpty() ? -1 : front->data; }
    int peekBack() const { return isEmpty() ? -1 : rear->data; }
};

int main() {
    Deque deque;
    deque.pushBack(2);
    deque.pushBack(3);
    deque.pushFront(1);
    cout << "Front: " << deque.peekFront() << ", Back: " << deque.peekBack() << endl;  // 1, 3
    cout << "popBack: " << deque.popBack() << endl;    // 3
    cout << "popFront: " << deque.popFront() << endl;  // 1
    cout << "popFront: " << deque.popFront() << endl;  // 2
    deque.popFront();                                  // empty
    return 0;
}
