// Using the STL priority_queue (a heap) + two classic uses.
// By default it is a MAX-heap. For a min-heap use greater<int>.
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// K-th largest: keep a MIN-heap of size k. Its top is the k-th largest seen so far.
int kthLargest(const vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int value : nums) {
        minHeap.push(value);
        if ((int)minHeap.size() > k) minHeap.pop();   // drop the smallest
    }
    return minHeap.top();
}

// Merge k sorted lists: heap holds the current front of each list.
struct Entry {
    int value;
    int listIndex;
    int positionInList;
    bool operator>(const Entry& other) const { return value > other.value; }
};

vector<int> mergeKSorted(const vector<vector<int>>& lists) {
    priority_queue<Entry, vector<Entry>, greater<Entry>> minHeap;
    for (int i = 0; i < (int)lists.size(); i++) {
        if (!lists[i].empty()) minHeap.push({lists[i][0], i, 0});
    }
    vector<int> merged;
    while (!minHeap.empty()) {
        Entry smallest = minHeap.top();
        minHeap.pop();
        merged.push_back(smallest.value);
        int nextPosition = smallest.positionInList + 1;
        if (nextPosition < (int)lists[smallest.listIndex].size()) {
            minHeap.push({lists[smallest.listIndex][nextPosition], smallest.listIndex, nextPosition});
        }
    }
    return merged;
}

int main() {
    priority_queue<int> maxHeap;
    for (int value : {3, 1, 4, 1, 5}) maxHeap.push(value);
    cout << "Max-heap order: ";
    while (!maxHeap.empty()) { cout << maxHeap.top() << " "; maxHeap.pop(); }   // 5 4 3 1 1
    cout << endl;

    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int value : {3, 1, 4, 1, 5}) minHeap.push(value);
    cout << "Min-heap order: ";
    while (!minHeap.empty()) { cout << minHeap.top() << " "; minHeap.pop(); }   // 1 1 3 4 5
    cout << endl;

    cout << "2nd largest of {3,2,1,5,6,4}: " << kthLargest({3, 2, 1, 5, 6, 4}, 2) << endl;  // 5

    vector<int> merged = mergeKSorted({{1, 4, 7}, {2, 5, 8}, {3, 6, 9}});
    for (int value : merged) cout << value << " ";    // 1 2 3 4 5 6 7 8 9
    cout << endl;
    return 0;
}
