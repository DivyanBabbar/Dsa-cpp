// Classic problems solved with a hash map / hash set (STL unordered_map / unordered_set).
// The trade: spend O(n) extra memory to turn a nested O(n^2) loop into one O(n) pass.
//   1. Two sum                    O(n) time, O(n) space
//   2. First non-repeating char   O(n)
//   3. Subarray sum equals k      O(n)  (prefix sum + hash map)
//   4. Longest consecutive run    O(n)  (hash set)
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// 1. Find two indices whose values add up to target.
// For each number we ask: "have I already seen (target - number)?"
vector<int> twoSum(const vector<int>& numbers, int target) {
    unordered_map<int, int> valueToIndex;           // value -> index where we saw it
    for (int index = 0; index < static_cast<int>(numbers.size()); index++) {
        int needed = target - numbers[index];
        auto found = valueToIndex.find(needed);
        if (found != valueToIndex.end()) return {found->second, index};
        valueToIndex[numbers[index]] = index;       // store AFTER checking so we never pair with ourselves
    }
    return {-1, -1};
}

// 2. Index of the first character that appears exactly once, or -1.
int firstNonRepeatingChar(const string& text) {
    unordered_map<char, int> frequency;
    for (char letter : text) frequency[letter]++;                       // pass 1: count
    for (int index = 0; index < static_cast<int>(text.size()); index++) {
        if (frequency[text[index]] == 1) return index;                  // pass 2: first with count 1
    }
    return -1;
}

// 3. Count the contiguous subarrays whose sum is exactly k.
// If prefixSum(j) - prefixSum(i) == k then the subarray (i, j] sums to k,
// so at each j we count how many earlier prefix sums equal prefixSum(j) - k.
int subarraySumEqualsK(const vector<int>& numbers, int k) {
    unordered_map<int, int> prefixSumCount;
    prefixSumCount[0] = 1;                          // the empty prefix, lets subarrays start at index 0
    int runningSum = 0;
    int matchingSubarrays = 0;
    for (int number : numbers) {
        runningSum += number;
        auto found = prefixSumCount.find(runningSum - k);
        if (found != prefixSumCount.end()) matchingSubarrays += found->second;
        prefixSumCount[runningSum]++;
    }
    return matchingSubarrays;
}

// 4. Length of the longest run of consecutive integers (order in the array does not matter).
// Only start counting from a number whose predecessor is missing, so each run is walked once.
int longestConsecutiveRun(const vector<int>& numbers) {
    unordered_set<int> numberSet(numbers.begin(), numbers.end());
    int longest = 0;
    for (int number : numberSet) {
        if (numberSet.count(number - 1) > 0) continue;          // not the start of a run
        int currentNumber = number;
        int currentLength = 1;
        while (numberSet.count(currentNumber + 1) > 0) {
            currentNumber++;
            currentLength++;
        }
        if (currentLength > longest) longest = currentLength;
    }
    return longest;
}

int main() {
    vector<int> twoSumResult = twoSum({2, 7, 11, 15}, 9);
    cout << "twoSum indices: " << twoSumResult[0] << " " << twoSumResult[1] << endl;   // 0 1

    cout << "firstNonRepeatingChar(\"leetcode\") = " << firstNonRepeatingChar("leetcode") << endl;   // 0 ('l')
    cout << "firstNonRepeatingChar(\"aabb\") = " << firstNonRepeatingChar("aabb") << endl;           // -1

    cout << "subarraySumEqualsK({1,1,1}, 2) = " << subarraySumEqualsK({1, 1, 1}, 2) << endl;         // 2
    cout << "subarraySumEqualsK({3,4,7,2,-3,1,4,2}, 7) = "
         << subarraySumEqualsK({3, 4, 7, 2, -3, 1, 4, 2}, 7) << endl;                                // 4

    cout << "longestConsecutiveRun({100,4,200,1,3,2}) = "
         << longestConsecutiveRun({100, 4, 200, 1, 3, 2}) << endl;                                   // 4 (1,2,3,4)
    return 0;
}
