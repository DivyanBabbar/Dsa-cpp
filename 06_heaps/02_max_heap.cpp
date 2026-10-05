// Max-heap: every parent >= its children. The largest element is at index 0.
// Same array layout and logic as the min-heap with comparisons flipped.
#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] <= heap[parent]) break;
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void siftDown(int index) {
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;
            if (left < size && heap[left] > heap[largest]) largest = left;
            if (right < size && heap[right] > heap[largest]) largest = right;
            if (largest == index) break;
            swap(heap[index], heap[largest]);
            index = largest;
        }
    }

public:
    bool isEmpty() const { return heap.empty(); }

    void insert(int value) {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }

    int peekMax() const {
        if (heap.empty()) { cout << "Heap empty" << endl; return -1; }
        return heap[0];
    }

    int extractMax() {
        if (heap.empty()) { cout << "Heap empty" << endl; return -1; }
        int maxValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) siftDown(0);
        return maxValue;
    }
};

int main() {
    MaxHeap heap;
    for (int value : {10, 40, 30, 50, 20}) heap.insert(value);
    cout << "Max: " << heap.peekMax() << endl;            // 50
    while (!heap.isEmpty()) cout << heap.extractMax() << " ";   // 50 40 30 20 10
    cout << endl;
    return 0;
}
