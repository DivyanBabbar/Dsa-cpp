// Queue using a singly linked list with head (front) and tail (rear) pointers.
// Enqueue at tail, dequeue at head: both O(1), no capacity limit.
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedQueue {
private:
    Node* head;   // front
    Node* tail;   // rear

public:
    LinkedQueue() : head(nullptr), tail(nullptr) {}
    ~LinkedQueue() { while (!isEmpty()) dequeue(); }

    bool isEmpty() const { return head == nullptr; }

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    int dequeue() {
        if (isEmpty()) { cout << "Queue empty" << endl; return -1; }
        Node* toDelete = head;
        int value = toDelete->data;
        head = head->next;
        if (head == nullptr) tail = nullptr;   // queue became empty
        delete toDelete;
        return value;
    }

    int peek() const {
        if (isEmpty()) { cout << "Queue empty" << endl; return -1; }
        return head->data;
    }
};

int main() {
    LinkedQueue queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    cout << "Front: " << queue.peek() << endl;      // 10
    cout << "Dequeue: " << queue.dequeue() << endl; // 10
    cout << "Dequeue: " << queue.dequeue() << endl; // 20
    cout << "Dequeue: " << queue.dequeue() << endl; // 30
    queue.dequeue();                                // empty
    return 0;
}
