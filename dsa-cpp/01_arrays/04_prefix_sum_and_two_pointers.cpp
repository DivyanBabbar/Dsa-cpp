// Two very common array techniques.
// 1) Prefix sum: precompute running totals so any range sum is O(1).
// 2) Two pointers: on a sorted array, find a pair with a given sum in O(n).
#include <iostream>
using namespace std;

int main() {
    // ---- Prefix sum ----
    int arr[] = {3, 1, 4, 1, 5, 9};
    int size = 6;
    int prefix[7];          // prefix[i] = sum of arr[0..i-1]
    prefix[0] = 0;
    for (int i = 0; i < size; i++) prefix[i + 1] = prefix[i] + arr[i];

    int left = 1, right = 4;  // sum of arr[1..4]
    cout << "Sum arr[1..4] = " << prefix[right + 1] - prefix[left] << endl;  // 1+4+1+5 = 11

    // ---- Two pointers (array must be sorted) ----
    int sorted[] = {1, 2, 4, 7, 11, 15};
    int n = 6, target = 15;
    int i = 0, j = n - 1;
    bool found = false;
    while (i < j) {
        int sum = sorted[i] + sorted[j];
        if (sum == target) {
            cout << "Pair: " << sorted[i] << " + " << sorted[j] << endl;  // 4 + 11
            found = true;
            break;
        } else if (sum < target) i++;   // need a bigger sum
        else j--;                        // need a smaller sum
    }
    if (!found) cout << "No pair" << endl;
    return 0;
}
