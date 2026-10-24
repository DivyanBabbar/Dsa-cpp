// Prim's algorithm: minimum spanning tree (MST), grown from one start vertex.
//
// Idea (greedy): keep a set of vertices already in the tree. Repeatedly take the CHEAPEST edge
// that connects a vertex in the tree to a vertex outside it, and add that new vertex.
// A min-heap (priority queue) hands us the cheapest candidate edge in O(log E).
//
// Kruskal vs Prim: Kruskal sorts ALL edges and merges components (good for sparse graphs).
// Prim grows one tree outward (good for dense graphs). Both give an MST of the same total weight.
//
// Time O(E log V) with a heap and adjacency list. The heap may hold stale entries (edges to a
// vertex that has since joined the tree); we simply skip them when they come out ("lazy" Prim).
// If the graph is not connected, Prim only reaches the start vertex's component.
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

// One entry in the heap: "we can reach `vertex` from `parent` at cost `weight`".
struct Candidate {
    int weight;
    int vertex;
    int parent;       // -1 for the start vertex
    // priority_queue with greater<> gives a MIN-heap; ties broken so the output is deterministic
    bool operator>(const Candidate& other) const {
        if (weight != other.weight) return weight > other.weight;
        if (vertex != other.vertex) return vertex > other.vertex;
        return parent > other.parent;
    }
};

struct MstResult {
    vector<Edge> edges;
    int totalWeight;
    bool reachesAllVertices;
};

// adjacency[a] holds pairs (neighbor, weight)
MstResult primMST(const vector<vector<pair<int, int>>>& adjacency, int startVertex) {
    int vertexCount = static_cast<int>(adjacency.size());
    vector<bool> inTree(vertexCount, false);
    priority_queue<Candidate, vector<Candidate>, greater<Candidate>> candidates;

    MstResult result;
    result.totalWeight = 0;
    int verticesInTree = 0;

    candidates.push({0, startVertex, -1});

    while (!candidates.empty() && verticesInTree < vertexCount) {
        Candidate best = candidates.top();      // cheapest edge leaving the tree
        candidates.pop();

        if (inTree[best.vertex]) continue;      // stale entry: that vertex already joined, skip

        inTree[best.vertex] = true;
        verticesInTree++;
        result.totalWeight += best.weight;
        if (best.parent != -1) result.edges.push_back({best.parent, best.vertex, best.weight});

        // new vertex joined: its edges to outside vertices become candidates
        for (const pair<int, int>& edge : adjacency[best.vertex]) {
            int neighbor = edge.first;
            int weight = edge.second;
            if (!inTree[neighbor]) candidates.push({weight, neighbor, best.vertex});
        }
    }

    result.reachesAllVertices = (verticesInTree == vertexCount);
    return result;
}

void addEdge(vector<vector<pair<int, int>>>& adjacency, int a, int b, int weight) {
    adjacency[a].push_back({b, weight});
    adjacency[b].push_back({a, weight});
}

void printResult(const MstResult& result) {
    for (const Edge& edge : result.edges) {
        cout << edge.from << " - " << edge.to << "  (weight " << edge.weight << ")" << endl;
    }
    cout << "Total weight: " << result.totalWeight << endl;
    if (!result.reachesAllVertices) cout << "Graph is not connected: only the start component was reached" << endl;
}

int main() {
    // Same graph as the Kruskal file, so you can compare the answers.
    vector<vector<pair<int, int>>> adjacency(6);
    addEdge(adjacency, 0, 1, 4);
    addEdge(adjacency, 0, 2, 4);
    addEdge(adjacency, 1, 2, 2);
    addEdge(adjacency, 2, 3, 3);
    addEdge(adjacency, 2, 5, 2);
    addEdge(adjacency, 2, 4, 4);
    addEdge(adjacency, 3, 4, 3);
    addEdge(adjacency, 4, 5, 3);

    printResult(primMST(adjacency, 0));
    // Grows from vertex 0: 0-1 (4), 1-2 (2), 2-5 (2), 2-3 (3), 3-4 (3)
    // 0 - 1  (weight 4)
    // 1 - 2  (weight 2)
    // 2 - 5  (weight 2)
    // 2 - 3  (weight 3)
    // 3 - 4  (weight 3)
    // Total weight: 14   (same total as Kruskal)

    cout << "--- disconnected graph ---" << endl;
    vector<vector<pair<int, int>>> disconnected(4);
    addEdge(disconnected, 0, 1, 5);
    addEdge(disconnected, 2, 3, 1);
    printResult(primMST(disconnected, 0));
    // 0 - 1  (weight 5)
    // Total weight: 5
    // Graph is not connected: only the start component was reached
    return 0;
}
