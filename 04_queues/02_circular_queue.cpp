// Circular queue: indices wrap around using modulo, so freed slots are reused.
// We track `count` so "full" and "empty" are easy to tell apart.
#include <iostream>
using namespace std;

class CircularQueue {
private:
    int* data;
    int capacity;
    int front;   // index of first element
    int rear;    // index where the NEXT element will be written
    int count;

public:
    CircularQueue(int cap) : capacity(cap), front(0), rear(0), count(0) { data = new int[capacity]; }
    ~CircularQueue() { delete[] data; }

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }

    void enqueue(int value) {
        if (isFull()) { cout << "Queue full" << endl; return; }
        data[rear] = value;
        rear = (rear + 1) % capacity;      // wrap around
        count++;
    }

    int dequeue() {
        if (isEmpty()) { cout << "Queue empty" << endl; return -1; }
        int value = data[front];
        front = (front + 1) % capacity;    // wrap around
        count--;
        return value;
    }

    int peek() const {
        if (isEmpty()) { cout << "Queue empty" << endl; return -1; }
        return data[front];
    }
};

int main() {
    CircularQueue queue(3);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    cout << "Dequeue: " << queue.dequeue() << endl;  // 1
    queue.enqueue(4);                                // works now: rear wrapped to index 0
    cout << "Dequeue: " << queue.dequeue() << endl;  // 2
    cout << "Dequeue: " << queue.dequeue() << endl;  // 3
    cout << "Dequeue: " << queue.dequeue() << endl;  // 4
    queue.dequeue();                                 // empty
    return 0;
}
