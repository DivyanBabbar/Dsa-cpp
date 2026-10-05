// Heap sort, in place, O(n log n):
//  1) Build a max-heap from the array (heapify from the last parent down to 0) - O(n).
//  2) Repeat: swap root (max) with the last element of the heap, shrink the heap by one,
//     sift the new root down. The array fills from the back in ascending order.
#include <iostream>
using namespace std;

// Sift arr[index] down within the first `heapSize` elements.
void siftDown(int arr[], int heapSize, int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;
        if (left < heapSize && arr[left] > arr[largest]) largest = left;
        if (right < heapSize && arr[right] > arr[largest]) largest = right;
        if (largest == index) break;
        swap(arr[index], arr[largest]);
        index = largest;
    }
}

void heapSort(int arr[], int size) {
    // Step 1: build max-heap. Leaves are already valid heaps, so start at the last parent.
    for (int i = size / 2 - 1; i >= 0; i--) siftDown(arr, size, i);

    // Step 2: extract the max repeatedly.
    for (int end = size - 1; end > 0; end--) {
        swap(arr[0], arr[end]);      // max goes to its final spot
        siftDown(arr, end, 0);       // heap now has `end` elements
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = 6;
    heapSort(arr, size);
    for (int i = 0; i < size; i++) cout << arr[i] << " ";   // 5 6 7 11 12 13
    cout << endl;
    return 0;
}
