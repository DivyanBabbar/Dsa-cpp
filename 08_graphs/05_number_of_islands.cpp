// LeetCode 200 - Number of Islands (Medium)
// A grid of '1' (land) and '0' (water). An island is a group of land cells connected
// up / down / left / right. Count the islands.
//
// Idea: the grid IS a graph (each cell is a vertex, its 4 neighbours are the edges).
// Scan every cell. When we meet unvisited land, that is a NEW island, so count it and run a
// DFS that marks every land cell of that island as visited (flood fill).
//
// Time O(rows * columns): each cell is visited at most once. Space O(rows * columns) for visited
// (and the recursion stack in the worst case, e.g. one huge snake-shaped island).
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Recursive flood fill.
// Base cases (return immediately): outside the grid, water, or already visited.
// Otherwise: mark this cell, then recurse into up, down, left, right. Returns nothing.
void floodFill(const vector<string>& grid, vector<vector<bool>>& visited, int row, int column) {
    int rowCount = static_cast<int>(grid.size());
    int columnCount = static_cast<int>(grid[0].size());

    if (row < 0 || row >= rowCount || column < 0 || column >= columnCount) return;   // outside
    if (grid[row][column] == '0') return;                                            // water
    if (visited[row][column]) return;                                                // seen already

    visited[row][column] = true;
    floodFill(grid, visited, row - 1, column);      // up
    floodFill(grid, visited, row + 1, column);      // down
    floodFill(grid, visited, row, column - 1);      // left
    floodFill(grid, visited, row, column + 1);      // right
}

int numberOfIslands(const vector<string>& grid) {
    if (grid.empty()) return 0;
    int rowCount = static_cast<int>(grid.size());
    int columnCount = static_cast<int>(grid[0].size());
    vector<vector<bool>> visited(rowCount, vector<bool>(columnCount, false));

    int islands = 0;
    for (int row = 0; row < rowCount; row++) {
        for (int column = 0; column < columnCount; column++) {
            if (grid[row][column] == '1' && !visited[row][column]) {
                islands++;                                  // found a new island
                floodFill(grid, visited, row, column);      // mark all of it so we don't count it again
            }
        }
    }
    return islands;
}

int main() {
    vector<string> firstGrid = {
        "11000",
        "11000",
        "00100",
        "00011"
    };
    cout << "Islands: " << numberOfIslands(firstGrid) << endl;       // 3

    vector<string> secondGrid = {
        "11110",
        "11010",
        "11000",
        "00000"
    };
    cout << "Islands: " << numberOfIslands(secondGrid) << endl;      // 1

    vector<string> allWater = {"000", "000"};
    cout << "Islands: " << numberOfIslands(allWater) << endl;        // 0
    return 0;
}
