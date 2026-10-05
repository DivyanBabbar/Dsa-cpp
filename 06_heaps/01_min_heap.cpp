// Min-heap: a complete binary tree stored in an ARRAY where every parent <= its children.
// The smallest element is always at index 0.
// For index i:  parent = (i-1)/2,  left child = 2i+1,  right child = 2i+2
//
// insert:     add at the end, then sift UP while smaller than parent.   O(log n)
// extractMin: move last element to the root, then sift DOWN.            O(log n)
#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
private:
    vector<int> heap;

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] >= heap[parent]) break;       // heap property holds
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void siftDown(int index) {
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;
            if (left < size && heap[left] < heap[smallest]) smallest = left;
            if (right < size && heap[right] < heap[smallest]) smallest = right;
            if (smallest == index) break;                 // already in place
            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:
    bool isEmpty() const { return heap.empty(); }
    int size() const { return heap.size(); }

    void insert(int value) {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }

    int peekMin() const {
        if (heap.empty()) { cout << "Heap empty" << endl; return -1; }
        return heap[0];
    }

    int extractMin() {
        if (heap.empty()) { cout << "Heap empty" << endl; return -1; }
        int minValue = heap[0];
        heap[0] = heap.back();       // move last to root
        heap.pop_back();
        if (!heap.empty()) siftDown(0);
        return minValue;
    }

    void print() const {
        for (int value : heap) cout << value << " ";
        cout << endl;
    }
};

int main() {
    MinHeap heap;
    for (int value : {50, 30, 40, 10, 20, 60}) heap.insert(value);
    heap.print();                                         // 10 20 40 50 30 60
    cout << "Min: " << heap.peekMin() << endl;            // 10
    while (!heap.isEmpty()) cout << heap.extractMin() << " ";   // 10 20 30 40 50 60
    cout << endl;
    return 0;
}
