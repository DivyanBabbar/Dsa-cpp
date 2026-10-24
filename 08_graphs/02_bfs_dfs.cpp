// Graph traversals on an adjacency list (undirected graph).
//
// BFS (breadth-first): visit all vertices at distance 1, then distance 2, ... uses a QUEUE.
//   Because it explores level by level, it gives the shortest path in an UNWEIGHTED graph.
// DFS (depth-first): go as deep as possible, then backtrack. Uses recursion (or a STACK).
//
// Time O(V + E), space O(V) for the visited array and the queue/stack.
// A "visited" array is essential: graphs can have cycles, so without it we would loop forever.
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

void addEdge(vector<vector<int>>& adjacency, int a, int b) {
    adjacency[a].push_back(b);
    adjacency[b].push_back(a);
}

// ---------- BFS ----------
vector<int> bfs(const vector<vector<int>>& adjacency, int startVertex) {
    vector<int> visitOrder;
    vector<bool> visited(adjacency.size(), false);
    queue<int> toVisit;

    visited[startVertex] = true;      // mark when we ENQUEUE, so a vertex is never queued twice
    toVisit.push(startVertex);

    while (!toVisit.empty()) {
        int current = toVisit.front();
        toVisit.pop();
        visitOrder.push_back(current);
        for (int neighbor : adjacency[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                toVisit.push(neighbor);
            }
        }
    }
    return visitOrder;
}

// BFS also gives the fewest-edges distance from startVertex to every vertex (-1 = unreachable).
vector<int> bfsDistances(const vector<vector<int>>& adjacency, int startVertex) {
    vector<int> distance(adjacency.size(), -1);
    queue<int> toVisit;

    distance[startVertex] = 0;
    toVisit.push(startVertex);

    while (!toVisit.empty()) {
        int current = toVisit.front();
        toVisit.pop();
        for (int neighbor : adjacency[current]) {
            if (distance[neighbor] == -1) {                     // -1 doubles as "not visited yet"
                distance[neighbor] = distance[current] + 1;
                toVisit.push(neighbor);
            }
        }
    }
    return distance;
}

// ---------- DFS (recursive) ----------
// Marks `current` visited, records it, then recurses into every unvisited neighbour.
// Base case: when every neighbour is already visited the loop does nothing and the call returns.
void dfsVisit(const vector<vector<int>>& adjacency, int current,
              vector<bool>& visited, vector<int>& visitOrder) {
    visited[current] = true;
    visitOrder.push_back(current);
    for (int neighbor : adjacency[current]) {
        if (!visited[neighbor]) dfsVisit(adjacency, neighbor, visited, visitOrder);
    }
}

vector<int> dfsRecursive(const vector<vector<int>>& adjacency, int startVertex) {
    vector<int> visitOrder;
    vector<bool> visited(adjacency.size(), false);
    dfsVisit(adjacency, startVertex, visited, visitOrder);
    return visitOrder;
}

// ---------- DFS (iterative, explicit stack) ----------
vector<int> dfsIterative(const vector<vector<int>>& adjacency, int startVertex) {
    vector<int> visitOrder;
    vector<bool> visited(adjacency.size(), false);
    stack<int> toVisit;
    toVisit.push(startVertex);

    while (!toVisit.empty()) {
        int current = toVisit.top();
        toVisit.pop();
        if (visited[current]) continue;           // may be pushed several times, visit only once
        visited[current] = true;
        visitOrder.push_back(current);
        // push in reverse so the FIRST neighbour is popped first (same order as the recursive version)
        for (int index = static_cast<int>(adjacency[current].size()) - 1; index >= 0; index--) {
            int neighbor = adjacency[current][index];
            if (!visited[neighbor]) toVisit.push(neighbor);
        }
    }
    return visitOrder;
}

// A connected component is a group of vertices that can all reach each other.
// Start a DFS from every vertex not yet visited; each fresh start is one new component.
int countConnectedComponents(const vector<vector<int>>& adjacency) {
    vector<bool> visited(adjacency.size(), false);
    vector<int> ignoredOrder;
    int components = 0;
    for (int vertex = 0; vertex < static_cast<int>(adjacency.size()); vertex++) {
        if (!visited[vertex]) {
            dfsVisit(adjacency, vertex, visited, ignoredOrder);
            components++;
        }
    }
    return components;
}

void printVector(const vector<int>& values) {
    for (int value : values) cout << value << " ";
    cout << endl;
}

int main() {
    // 0 - 1        5 - 6
    // |   |
    // 2 - 3 - 4
    vector<vector<int>> adjacency(7);
    addEdge(adjacency, 0, 1);
    addEdge(adjacency, 0, 2);
    addEdge(adjacency, 1, 3);
    addEdge(adjacency, 2, 3);
    addEdge(adjacency, 3, 4);
    addEdge(adjacency, 5, 6);

    cout << "BFS from 0:           "; printVector(bfs(adjacency, 0));            // 0 1 2 3 4
    cout << "BFS distances from 0: "; printVector(bfsDistances(adjacency, 0));   // 0 1 1 2 3 -1 -1
    cout << "DFS recursive from 0: "; printVector(dfsRecursive(adjacency, 0));   // 0 1 3 2 4
    cout << "DFS iterative from 0: "; printVector(dfsIterative(adjacency, 0));   // 0 1 3 2 4
    cout << "Connected components: " << countConnectedComponents(adjacency) << endl;   // 2
    return 0;
}
