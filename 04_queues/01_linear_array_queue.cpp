// Queue (FIFO: first in, first out) with a plain array.
// Weakness: once `rear` reaches the end, freed slots at the front are never reused.
// The circular queue (next file) fixes this.
#include <iostream>
using namespace std;

class LinearQueue {
private:
    int* data;
    int capacity;
    int front;   // index of the first element
    int rear;    // index of the last element

public:
    LinearQueue(int cap) : capacity(cap), front(0), rear(-1) { data = new int[capacity]; }
    ~LinearQueue() { delete[] data; }

    bool isEmpty() const { return front > rear; }
    bool isFull() const { return rear == capacity - 1; }

    void enqueue(int value) {
        if (isFull()) { cout << "Queue full" << endl; return; }
        data[++rear] = value;
    }

    int dequeue() {
        if (isEmpty()) { cout << "Queue empty" << endl; return -1; }
        return data[front++];
    }

    int peek() const {
        if (isEmpty()) { cout << "Queue empty" << endl; return -1; }
        return data[front];
    }
};

int main() {
    LinearQueue queue(3);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    cout << "Dequeue: " << queue.dequeue() << endl;  // 1
    queue.enqueue(4);                                // "Queue full" even though a slot is free
    cout << "Front: " << queue.peek() << endl;       // 2
    return 0;
}
