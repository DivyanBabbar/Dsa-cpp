// Binary search: only works on a SORTED array. O(log n).
// Each step discards half of the remaining range.
#include <iostream>
using namespace std;

int binarySearchIterative(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;  // avoids overflow of (low + high)
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;   // target is in right half
        else high = mid - 1;                          // target is in left half
    }
    return -1;
}

// Recursive: base case = empty range (low > high); returns -1.
int binarySearchRecursive(int arr[], int low, int high, int target) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) return binarySearchRecursive(arr, mid + 1, high, target);
    return binarySearchRecursive(arr, low, mid - 1, target);
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56};
    int size = 8;
    cout << "Iterative, 23: " << binarySearchIterative(arr, size, 23) << endl;        // 5
    cout << "Recursive, 56: " << binarySearchRecursive(arr, 0, size - 1, 56) << endl; // 7
    cout << "Missing, 7: " << binarySearchIterative(arr, size, 7) << endl;            // -1
    return 0;
}
