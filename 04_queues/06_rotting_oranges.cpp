// LeetCode 994 - Rotting Oranges (Medium)
// Grid cells: 0 = empty, 1 = fresh orange, 2 = rotten orange.
// Every minute, each fresh orange that is next to (up/down/left/right) a rotten one becomes rotten.
// Return the minutes until no fresh orange is left, or -1 if some can never rot.
//
// Idea: multi-source BFS with a QUEUE.
//   Put ALL rotten oranges in the queue at time 0. Each "round" of the queue (one level of BFS)
//   is one minute: every orange in the queue infects its fresh neighbours, which join the queue.
//   Count the fresh oranges first; if any remain when the queue runs out, they were unreachable.
//
// Time O(rows * columns), space O(rows * columns).
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int orangesRotting(vector<vector<int>> grid) {      // by value: we change the grid, caller's copy stays intact
    int rowCount = static_cast<int>(grid.size());
    int columnCount = static_cast<int>(grid[0].size());

    queue<pair<int, int>> rotten;                   // (row, column) of every rotten orange to process
    int freshCount = 0;
    for (int row = 0; row < rowCount; row++) {
        for (int column = 0; column < columnCount; column++) {
            if (grid[row][column] == 2) rotten.push({row, column});
            else if (grid[row][column] == 1) freshCount++;
        }
    }

    int rowOffsets[4] = {-1, 1, 0, 0};              // up, down, left, right
    int columnOffsets[4] = {0, 0, -1, 1};
    int minutes = 0;

    while (!rotten.empty() && freshCount > 0) {
        int roundSize = static_cast<int>(rotten.size());    // everything currently queued rots neighbours this minute
        for (int processed = 0; processed < roundSize; processed++) {
            pair<int, int> cell = rotten.front();
            rotten.pop();
            for (int direction = 0; direction < 4; direction++) {
                int nextRow = cell.first + rowOffsets[direction];
                int nextColumn = cell.second + columnOffsets[direction];
                bool insideGrid = nextRow >= 0 && nextRow < rowCount && nextColumn >= 0 && nextColumn < columnCount;
                if (insideGrid && grid[nextRow][nextColumn] == 1) {
                    grid[nextRow][nextColumn] = 2;          // becomes rotten
                    freshCount--;
                    rotten.push({nextRow, nextColumn});     // will infect ITS neighbours next minute
                }
            }
        }
        minutes++;
    }
    return freshCount == 0 ? minutes : -1;
}

int main() {
    cout << orangesRotting({{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}) << endl;   // 4
    cout << orangesRotting({{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}) << endl;   // -1 (bottom-left orange is cut off)
    cout << orangesRotting({{0, 2}}) << endl;                            // 0  (nothing fresh to rot)
    return 0;
}
