// Three basic O(n^2) sorts: bubble, selection, insertion.
#include <iostream>
using namespace std;

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

// Bubble: repeatedly swap adjacent out-of-order pairs; largest "bubbles" to the end.
void bubbleSort(int arr[], int size) {
    for (int pass = 0; pass < size - 1; pass++) {
        bool swapped = false;
        for (int i = 0; i < size - 1 - pass; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i]; arr[i] = arr[i + 1]; arr[i + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;  // already sorted
    }
}

// Selection: find the minimum of the unsorted part, put it at the front.
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        int temp = arr[i]; arr[i] = arr[minIndex]; arr[minIndex] = temp;
    }
}

// Insertion: take next element, shift bigger ones right, drop it into place.
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int a[] = {64, 25, 12, 22, 11};
    int b[] = {64, 25, 12, 22, 11};
    int c[] = {64, 25, 12, 22, 11};
    bubbleSort(a, 5);    printArray(a, 5);
    selectionSort(b, 5); printArray(b, 5);
    insertionSort(c, 5); printArray(c, 5);   // all: 11 12 22 25 64
    return 0;
}
