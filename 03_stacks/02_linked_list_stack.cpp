// Stack using a singly linked list. The head IS the top, so push/pop are O(1)
// and there is no fixed capacity.
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedStack {
private:
    Node* topNode;

public:
    LinkedStack() : topNode(nullptr) {}
    ~LinkedStack() { while (!isEmpty()) pop(); }

    bool isEmpty() const { return topNode == nullptr; }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    int pop() {
        if (isEmpty()) { cout << "Stack underflow" << endl; return -1; }
        Node* toDelete = topNode;
        int value = toDelete->data;
        topNode = topNode->next;
        delete toDelete;
        return value;
    }

    int peek() const {
        if (isEmpty()) { cout << "Stack is empty" << endl; return -1; }
        return topNode->data;
    }
};

int main() {
    LinkedStack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    cout << "Peek: " << stack.peek() << endl;   // 3
    cout << "Pop: " << stack.pop() << endl;     // 3
    cout << "Pop: " << stack.pop() << endl;     // 2
    cout << "Pop: " << stack.pop() << endl;     // 1
    stack.pop();                                // underflow
    return 0;
}
