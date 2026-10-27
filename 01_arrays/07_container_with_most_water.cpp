// LeetCode 11 - Container With Most Water (Medium)
// heights[i] is a vertical line at x = i. Pick two lines; together with the x-axis they form a
// container. Find the largest amount of water one container can hold.
//   area = (distance between the lines) * (the SHORTER of the two heights)
//   {1,8,6,2,5,4,8,3,7}  ->  49   (lines at index 1 and 8: width 7, height min(8,7) = 7)
//
// Brute force tries every pair: O(n^2).
// Two pointers: start with the widest container (first and last line) and move inward.
//   The water level is limited by the SHORTER line, so moving the TALLER line inward can only
//   make things worse (smaller width, height still capped by the same short line).
//   So we always move the pointer at the shorter line, hoping to find a taller one.
//
// Time O(n), space O(1).
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int maxWaterArea(const vector<int>& heights) {
    int left = 0;
    int right = static_cast<int>(heights.size()) - 1;
    int bestArea = 0;

    while (left < right) {
        int width = right - left;
        int waterHeight = min(heights[left], heights[right]);
        bestArea = max(bestArea, width * waterHeight);

        if (heights[left] < heights[right]) left++;     // left line is the limit, try a taller one
        else right--;                                   // right line is the limit (or equal), move it
    }
    return bestArea;
}

int main() {
    cout << maxWaterArea({1, 8, 6, 2, 5, 4, 8, 3, 7}) << endl;      // 49
    cout << maxWaterArea({1, 1}) << endl;                           // 1
    cout << maxWaterArea({4, 3, 2, 1, 4}) << endl;                  // 16  (index 0 and 4: width 4 * height 4)
    return 0;
}
