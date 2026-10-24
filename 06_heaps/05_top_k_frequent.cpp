// LeetCode 347 - Top K Frequent Elements (Medium)
// Return the k values that appear most often.
//   {1,1,1,2,2,3}, k = 2  ->  1 2
//
// Idea:
//   1. Count how often each value appears (hash map).
//   2. Keep a MIN-heap that holds at most k (frequency, value) pairs.
//      The heap's top is the weakest of the current top k. When the heap grows to k+1,
//      pop the top: the least frequent one is thrown away.
//   3. What is left in the heap are the k most frequent values.
//
// Time O(n log k), space O(n). Better than sorting all frequencies (O(n log n)) when k is small.
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

vector<int> topKFrequent(const vector<int>& numbers, int k) {
    unordered_map<int, int> frequency;
    for (int number : numbers) frequency[number]++;

    // pair = (frequency, value). greater<> makes priority_queue a MIN-heap on frequency;
    // equal frequencies fall back to the value, so the result is the same every run.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    for (const pair<const int, int>& entry : frequency) {
        minHeap.push({entry.second, entry.first});
        if (static_cast<int>(minHeap.size()) > k) minHeap.pop();     // drop the least frequent
    }

    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    reverse(result.begin(), result.end());          // heap gave least frequent first, flip it
    return result;
}

void printVector(const vector<int>& values) {
    for (int value : values) cout << value << " ";
    cout << endl;
}

int main() {
    printVector(topKFrequent({1, 1, 1, 2, 2, 3}, 2));                   // 1 2
    printVector(topKFrequent({4, 4, 4, 6, 6, 7, 7, 7, 7, 9}, 2));       // 7 4
    printVector(topKFrequent({5}, 1));                                  // 5
    return 0;
}
