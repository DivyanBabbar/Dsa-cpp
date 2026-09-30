// Monotonic stack: for each element, find the next element to its right that is larger.
// The stack holds INDICES whose answer is still unknown (values decreasing).
// Each index is pushed and popped once, so O(n).
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> nextGreaterElement(const vector<int>& nums) {
    int size = nums.size();
    vector<int> result(size, -1);        // -1 = no greater element
    stack<int> pendingIndices;
    for (int i = 0; i < size; i++) {
        while (!pendingIndices.empty() && nums[i] > nums[pendingIndices.top()]) {
            result[pendingIndices.top()] = nums[i];   // nums[i] is the answer for that index
            pendingIndices.pop();
        }
        pendingIndices.push(i);
    }
    return result;
}

int main() {
    vector<int> nums = {4, 5, 2, 25, 7};
    vector<int> answer = nextGreaterElement(nums);
    for (int value : answer) cout << value << " ";    // 5 25 25 -1 -1
    cout << endl;
    return 0;
}
