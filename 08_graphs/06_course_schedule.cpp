// LeetCode 207 / 210 - Course Schedule (Medium)
// There are n courses (0 .. n-1). A pair (course, prerequisite) means you must finish
// `prerequisite` BEFORE `course`.
//   207: can you finish all courses?        210: in what order?
//
// This is a DIRECTED graph: edge prerequisite -> course. You can finish everything exactly
// when the graph has NO CYCLE (a cycle means A needs B and B needs A).
//
// Kahn's algorithm (topological sort with BFS):
//   1. Count prerequisites (in-degree) of every course.
//   2. Queue every course with 0 prerequisites: they can be taken right now.
//   3. Take a course from the queue; it "unlocks" the courses that depend on it, so lower their
//      count by 1. Any course that reaches 0 joins the queue.
//   4. If we managed to take all n courses there was no cycle. If some courses never reached 0,
//      they are stuck waiting on each other, so there IS a cycle.
//
// Time O(V + E), space O(V + E).
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

// Returns a valid order to take all courses, or an EMPTY vector if a cycle makes it impossible.
vector<int> courseOrder(int numberOfCourses, const vector<pair<int, int>>& prerequisites) {
    vector<vector<int>> unlocks(numberOfCourses);       // unlocks[a] = courses that need a first
    vector<int> prerequisiteCount(numberOfCourses, 0);

    for (const pair<int, int>& entry : prerequisites) {
        int course = entry.first;
        int prerequisite = entry.second;
        unlocks[prerequisite].push_back(course);
        prerequisiteCount[course]++;
    }

    queue<int> ready;                                   // courses with no remaining prerequisites
    for (int course = 0; course < numberOfCourses; course++) {
        if (prerequisiteCount[course] == 0) ready.push(course);
    }

    vector<int> order;
    while (!ready.empty()) {
        int current = ready.front();
        ready.pop();
        order.push_back(current);
        for (int nextCourse : unlocks[current]) {
            prerequisiteCount[nextCourse]--;            // one prerequisite of nextCourse is now done
            if (prerequisiteCount[nextCourse] == 0) ready.push(nextCourse);
        }
    }

    if (static_cast<int>(order.size()) != numberOfCourses) return {};   // some courses stuck in a cycle
    return order;
}

bool canFinish(int numberOfCourses, const vector<pair<int, int>>& prerequisites) {
    return static_cast<int>(courseOrder(numberOfCourses, prerequisites).size()) == numberOfCourses;
}

void printVector(const vector<int>& values) {
    for (int value : values) cout << value << " ";
    cout << endl;
}

int main() {
    // to take 1 you need 0
    cout << "canFinish(2, {1<-0}): " << canFinish(2, {{1, 0}}) << endl;            // 1 (true)

    // 1 needs 0 AND 0 needs 1: cycle
    cout << "canFinish(2, {1<-0, 0<-1}): " << canFinish(2, {{1, 0}, {0, 1}}) << endl;   // 0 (false)

    // 0 first; then 1 and 2 (both need 0); 3 needs both 1 and 2
    vector<pair<int, int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    cout << "order: ";
    printVector(courseOrder(4, prerequisites));                                    // 0 1 2 3
    return 0;
}
