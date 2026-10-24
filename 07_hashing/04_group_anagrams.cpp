// LeetCode 49 - Group Anagrams (Medium)
// Group the words that are anagrams of each other.
//   {"eat","tea","tan","ate","nat","bat"} -> {eat,tea,ate} {tan,nat} {bat}
//
// Idea: two words are anagrams exactly when their letters, sorted, give the same string.
// So the sorted word is a hash key, and every word with that key goes into the same group.
//
// Time O(n * k log k): n words, each of length up to k, sorted once.
// Space O(n * k).
// (Faster key: a 26-slot letter count instead of sorting gives O(n * k).)
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

vector<vector<string>> groupAnagrams(const vector<string>& words) {
    unordered_map<string, int> keyToGroupIndex;     // sorted letters -> position in `groups`
    vector<vector<string>> groups;                  // kept in first-seen order

    for (const string& word : words) {
        string sortedLetters = word;
        sort(sortedLetters.begin(), sortedLetters.end());

        auto found = keyToGroupIndex.find(sortedLetters);
        if (found == keyToGroupIndex.end()) {
            // first word with this key: start a new group
            keyToGroupIndex[sortedLetters] = static_cast<int>(groups.size());
            groups.push_back({word});
        } else {
            groups[found->second].push_back(word);  // key seen before: add to its group
        }
    }
    return groups;
}

void printGroups(const vector<vector<string>>& groups) {
    for (const vector<string>& group : groups) {
        cout << "[ ";
        for (const string& word : group) cout << word << " ";
        cout << "]" << endl;
    }
}

int main() {
    printGroups(groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"}));
    // [ eat tea ate ]
    // [ tan nat ]
    // [ bat ]

    cout << "--- single word ---" << endl;
    printGroups(groupAnagrams({"a"}));
    // [ a ]
    return 0;
}
