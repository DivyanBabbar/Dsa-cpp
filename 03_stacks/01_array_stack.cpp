// Stack (LIFO: last in, first out) using a fixed array.
// `top` is the index of the newest element; -1 means empty.
#include <iostream>
using namespace std;

class ArrayStack {
private:
    int* data;
    int capacity;
    int top;

public:
    ArrayStack(int cap) : capacity(cap), top(-1) { data = new int[capacity]; }
    ~ArrayStack() { delete[] data; }

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == capacity - 1; }

    void push(int value) {
        if (isFull()) { cout << "Stack overflow" << endl; return; }
        data[++top] = value;
    }

    int pop() {
        if (isEmpty()) { cout << "Stack underflow" << endl; return -1; }
        return data[top--];
    }

    int peek() const {
        if (isEmpty()) { cout << "Stack is empty" << endl; return -1; }
        return data[top];
    }
};

int main() {
    ArrayStack stack(3);
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);                                  // overflow
    cout << "Peek: " << stack.peek() << endl;        // 30
    cout << "Pop: " << stack.pop() << endl;          // 30
    cout << "Pop: " << stack.pop() << endl;          // 20
    cout << "Empty? " << stack.isEmpty() << endl;    // 0
    return 0;
}
