// Static array basics: traverse, insert, delete, search, reverse, max.
// Arrays have a fixed capacity. "size" = how many slots are actually used.
#include <iostream>
using namespace std;

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

// Insert at index: shift elements from the end toward index one step right. O(n)
int insertAt(int arr[], int size, int capacity, int index, int value) {
    if (size >= capacity || index < 0 || index > size) {
        cout << "Cannot insert" << endl;
        return size;
    }
    for (int i = size; i > index; i--) arr[i] = arr[i - 1];
    arr[index] = value;
    return size + 1;
}

// Delete at index: shift elements after index one step left. O(n)
int deleteAt(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        cout << "Invalid index" << endl;
        return size;
    }
    for (int i = index; i < size - 1; i++) arr[i] = arr[i + 1];
    return size - 1;
}

// Linear search: returns index or -1. O(n)
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// Reverse in place by swapping the two ends and moving inward. O(n)
void reverseArray(int arr[], int size) {
    int left = 0, right = size - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}

int findMax(int arr[], int size) {
    int maxValue = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxValue) maxValue = arr[i];
    }
    return maxValue;
}

int main() {
    const int CAPACITY = 10;
    int arr[CAPACITY] = {5, 2, 9, 1};
    int size = 4;

    printArray(arr, size);                       // 5 2 9 1
    size = insertAt(arr, size, CAPACITY, 2, 7);  // insert 7 at index 2
    printArray(arr, size);                       // 5 2 7 9 1
    size = deleteAt(arr, size, 0);               // delete first element
    printArray(arr, size);                       // 2 7 9 1
    cout << "Index of 9: " << linearSearch(arr, size, 9) << endl;  // 2
    reverseArray(arr, size);
    printArray(arr, size);                       // 1 9 7 2
    cout << "Max: " << findMax(arr, size) << endl;  // 9
    return 0;
}
