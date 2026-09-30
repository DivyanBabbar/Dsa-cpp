// Queue built from two stacks.
// inbox receives new elements. outbox serves dequeues.
// When outbox is empty, pour ALL of inbox into it: this reverses the order,
// so the oldest element ends up on top. Amortized O(1) per operation.
#include <iostream>
#include <stack>
using namespace std;

class QueueUsingTwoStacks {
private:
    stack<int> inbox;
    stack<int> outbox;

    void moveInboxToOutbox() {
        if (!outbox.empty()) return;          // only refill when outbox is empty
        while (!inbox.empty()) {
            outbox.push(inbox.top());
            inbox.pop();
        }
    }

public:
    void enqueue(int value) { inbox.push(value); }

    int dequeue() {
        moveInboxToOutbox();
        if (outbox.empty()) { cout << "Queue empty" << endl; return -1; }
        int value = outbox.top();
        outbox.pop();
        return value;
    }

    int peek() {
        moveInboxToOutbox();
        return outbox.empty() ? -1 : outbox.top();
    }
};

int main() {
    QueueUsingTwoStacks queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    cout << "Dequeue: " << queue.dequeue() << endl;  // 1
    queue.enqueue(4);
    cout << "Dequeue: " << queue.dequeue() << endl;  // 2
    cout << "Dequeue: " << queue.dequeue() << endl;  // 3
    cout << "Dequeue: " << queue.dequeue() << endl;  // 4
    return 0;
}
