// Kruskal's algorithm: minimum spanning tree (MST) of a weighted, undirected graph.
// An MST connects all V vertices using exactly V-1 edges with the smallest possible total weight.
//
// Idea (greedy):
//   1. Sort all edges by weight, smallest first.
//   2. Take an edge only if it connects two DIFFERENT components (it does not form a cycle).
//   3. Stop when V-1 edges are taken.
// "Are these two vertices already connected?" is answered fast by a Disjoint Set (Union-Find).
//
// Time O(E log E) for the sort. Union-Find with path compression + union by rank is almost O(1) per call.
// If the graph is NOT connected we end up with fewer than V-1 edges (a spanning forest).
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

// Union-Find: each set has one "root" vertex that represents it.
class DisjointSet {
private:
    vector<int> parent;
    vector<int> rankOfRoot;       // rough height of the tree under each root

public:
    DisjointSet(int vertexCount) : parent(vertexCount), rankOfRoot(vertexCount, 0) {
        for (int vertex = 0; vertex < vertexCount; vertex++) parent[vertex] = vertex;   // each alone
    }

    // Follow parents up to the root. Path compression: point every vertex on the way straight at the root.
    int findRoot(int vertex) {
        if (parent[vertex] != vertex) parent[vertex] = findRoot(parent[vertex]);
        return parent[vertex];
    }

    // Merge the sets of a and b. Returns false if they were already in the same set (would form a cycle).
    bool unite(int a, int b) {
        int rootA = findRoot(a);
        int rootB = findRoot(b);
        if (rootA == rootB) return false;

        // attach the shorter tree under the taller one
        if (rankOfRoot[rootA] < rankOfRoot[rootB]) {
            parent[rootA] = rootB;
        } else if (rankOfRoot[rootA] > rankOfRoot[rootB]) {
            parent[rootB] = rootA;
        } else {
            parent[rootB] = rootA;
            rankOfRoot[rootA]++;
        }
        return true;
    }
};

vector<Edge> kruskalMST(int vertexCount, vector<Edge> edges) {
    // sort by weight; ties broken by endpoints so the output is the same every run
    sort(edges.begin(), edges.end(), [](const Edge& first, const Edge& second) {
        if (first.weight != second.weight) return first.weight < second.weight;
        if (first.from != second.from) return first.from < second.from;
        return first.to < second.to;
    });

    DisjointSet components(vertexCount);
    vector<Edge> mstEdges;

    for (const Edge& edge : edges) {
        if (components.unite(edge.from, edge.to)) {            // different components: safe to take
            mstEdges.push_back(edge);
            if (static_cast<int>(mstEdges.size()) == vertexCount - 1) break;   // tree is complete
        }
        // else: from and to are already connected, this edge would create a cycle, skip it
    }
    return mstEdges;
}

void printResult(int vertexCount, const vector<Edge>& mstEdges) {
    int totalWeight = 0;
    for (const Edge& edge : mstEdges) {
        cout << edge.from << " - " << edge.to << "  (weight " << edge.weight << ")" << endl;
        totalWeight += edge.weight;
    }
    cout << "Total weight: " << totalWeight << endl;
    if (static_cast<int>(mstEdges.size()) != vertexCount - 1) {
        cout << "Graph is not connected: this is a spanning forest, not a single tree" << endl;
    }
}

int main() {
    // 6 vertices, 8 edges
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2}, {2, 3, 3},
        {2, 5, 2}, {2, 4, 4}, {3, 4, 3}, {4, 5, 3}
    };
    printResult(6, kruskalMST(6, edges));
    // Sorted: (1-2,2) (2-5,2) (2-3,3) (3-4,3) (4-5,3) (0-1,4) (0-2,4) (2-4,4)
    // 4-5 is skipped (4 and 5 are already connected through 3 and 2), 0-2 and 2-4 are skipped too.
    // 1 - 2  (weight 2)
    // 2 - 5  (weight 2)
    // 2 - 3  (weight 3)
    // 3 - 4  (weight 3)
    // 0 - 1  (weight 4)
    // Total weight: 14

    cout << "--- disconnected graph ---" << endl;
    vector<Edge> disconnectedEdges = {{0, 1, 5}, {2, 3, 1}};
    printResult(4, kruskalMST(4, disconnectedEdges));
    // 2 - 3  (weight 1)
    // 0 - 1  (weight 5)
    // Total weight: 6
    // Graph is not connected: this is a spanning forest, not a single tree
    return 0;
}
