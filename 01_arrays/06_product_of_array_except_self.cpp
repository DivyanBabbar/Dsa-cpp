// LeetCode 238 - Product of Array Except Self (Medium)
// For every index i, return the product of ALL other elements, WITHOUT using division.
//   {1,2,3,4}  ->  {24,12,8,6}
//
// Idea: answer[i] = (product of everything LEFT of i) * (product of everything RIGHT of i).
//   Pass 1 (left to right): answer[i] holds the product of the elements before i.
//   Pass 2 (right to left): multiply answer[i] by a running product of the elements after i.
// Division would break on zeros, which is why this prefix/suffix method is used.
//
// Time O(n), extra space O(1) (the answer array itself is not counted).
#include <iostream>
#include <vector>
using namespace std;

vector<int> productExceptSelf(const vector<int>& numbers) {
    int count = static_cast<int>(numbers.size());
    vector<int> answer(count, 1);

    // Pass 1: answer[i] = product of numbers[0 .. i-1]
    int productOfLeft = 1;
    for (int index = 0; index < count; index++) {
        answer[index] = productOfLeft;
        productOfLeft *= numbers[index];
    }

    // Pass 2: multiply in the product of numbers[i+1 .. n-1]
    int productOfRight = 1;
    for (int index = count - 1; index >= 0; index--) {
        answer[index] *= productOfRight;
        productOfRight *= numbers[index];
    }
    return answer;
}

void printVector(const vector<int>& values) {
    for (int value : values) cout << value << " ";
    cout << endl;
}

int main() {
    printVector(productExceptSelf({1, 2, 3, 4}));           // 24 12 8 6
    printVector(productExceptSelf({-1, 1, 0, -3, 3}));      // 0 0 9 0 0   (one zero: only that index is non-zero)
    printVector(productExceptSelf({0, 0, 5}));              // 0 0 0       (two zeros: everything is 0)
    return 0;
}
