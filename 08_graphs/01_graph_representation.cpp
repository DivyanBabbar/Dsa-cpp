// Two ways to store a graph with V vertices numbered 0 .. V-1.
//
// Adjacency matrix: a V x V table, matrix[a][b] = 1 if there is an edge a -> b.
//   Space O(V^2).  Edge check O(1).  Listing neighbours O(V).   Good for dense graphs.
// Adjacency list: for every vertex, a list of its neighbours.
//   Space O(V + E). Edge check O(degree). Listing neighbours O(degree). Good for sparse graphs.
//   Most algorithms in this folder use adjacency lists.
//
// Undirected edge a - b is stored in both directions (a -> b and b -> a).
// Directed edge a -> b is stored once.
#include <iostream>
#include <vector>
using namespace std;

class AdjacencyMatrixGraph {
private:
    int vertexCount;
    bool isDirected;
    vector<vector<int>> matrix;

public:
    AdjacencyMatrixGraph(int numberOfVertices, bool directed)
        : vertexCount(numberOfVertices), isDirected(directed),
          matrix(numberOfVertices, vector<int>(numberOfVertices, 0)) {}

    void addEdge(int from, int to) {
        if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
            cout << "Invalid vertex" << endl;
            return;
        }
        matrix[from][to] = 1;
        if (!isDirected) matrix[to][from] = 1;      // undirected: mirror the edge
    }

    bool hasEdge(int from, int to) const { return matrix[from][to] == 1; }   // O(1)

    void print() const {
        for (int row = 0; row < vertexCount; row++) {
            cout << row << ":";
            for (int column = 0; column < vertexCount; column++) cout << " " << matrix[row][column];
            cout << endl;
        }
    }
};

class AdjacencyListGraph {
private:
    int vertexCount;
    bool isDirected;
    vector<vector<int>> neighbors;

public:
    AdjacencyListGraph(int numberOfVertices, bool directed)
        : vertexCount(numberOfVertices), isDirected(directed), neighbors(numberOfVertices) {}

    void addEdge(int from, int to) {
        if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
            cout << "Invalid vertex" << endl;
            return;
        }
        neighbors[from].push_back(to);
        if (!isDirected) neighbors[to].push_back(from);
    }

    bool hasEdge(int from, int to) const {          // O(degree of from)
        for (int neighbor : neighbors[from]) {
            if (neighbor == to) return true;
        }
        return false;
    }

    // undirected: degree. directed: this is the OUT-degree (edges leaving the vertex).
    int degree(int vertex) const { return static_cast<int>(neighbors[vertex].size()); }

    void print() const {
        for (int vertex = 0; vertex < vertexCount; vertex++) {
            cout << vertex << ":";
            for (int neighbor : neighbors[vertex]) cout << " " << neighbor;
            cout << endl;
        }
    }
};

int main() {
    // Undirected graph with 5 vertices and 7 edges
    int edges[7][2] = {{0, 1}, {0, 4}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}};

    AdjacencyMatrixGraph matrixGraph(5, false);
    AdjacencyListGraph listGraph(5, false);
    for (auto& edge : edges) {
        matrixGraph.addEdge(edge[0], edge[1]);
        listGraph.addEdge(edge[0], edge[1]);
    }

    cout << "Adjacency matrix:" << endl;
    matrixGraph.print();
    // 0: 0 1 0 0 1
    // 1: 1 0 1 1 1
    // 2: 0 1 0 1 0
    // 3: 0 1 1 0 1
    // 4: 1 1 0 1 0   (symmetric, because the graph is undirected)

    cout << "Adjacency list:" << endl;
    listGraph.print();
    // 0: 1 4
    // 1: 0 2 3 4
    // 2: 1 3
    // 3: 1 2 4
    // 4: 0 1 3

    cout << "hasEdge(1, 3): " << matrixGraph.hasEdge(1, 3) << " " << listGraph.hasEdge(1, 3) << endl;   // 1 1
    cout << "hasEdge(0, 2): " << matrixGraph.hasEdge(0, 2) << " " << listGraph.hasEdge(0, 2) << endl;   // 0 0
    cout << "degree(1) = " << listGraph.degree(1) << endl;                                              // 4

    // Directed graph: 0 -> 1, 0 -> 2, 1 -> 2 (each edge stored once)
    AdjacencyListGraph directedGraph(3, true);
    directedGraph.addEdge(0, 1);
    directedGraph.addEdge(0, 2);
    directedGraph.addEdge(1, 2);
    cout << "Directed graph:" << endl;
    directedGraph.print();
    // 0: 1 2
    // 1: 2
    // 2:
    cout << "hasEdge(0, 1) = " << directedGraph.hasEdge(0, 1) << ", hasEdge(1, 0) = "
         << directedGraph.hasEdge(1, 0) << endl;                                                         // 1, 0
    return 0;
}
