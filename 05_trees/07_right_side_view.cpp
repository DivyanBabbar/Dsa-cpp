// LeetCode 199 - Binary Tree Right Side View (Medium)
// Imagine standing on the right of the tree: return the value of the node you see at each level,
// from top to bottom.
//
// Example tree (children listed as left, right):
//   1 has children 2 (left) and 3 (right)
//   2 has only a right child 5
//   3 has only a right child 4
// Right side view: 1 3 4
//   level 1 shows 1; level 2 shows 3 (it is right of 2); level 3 shows 4 (it is right of 5).
//
// Two solutions:
//   BFS: go level by level; the LAST node of each level is the visible one.
//   DFS: visit the RIGHT subtree before the left one. The first node reached at a new depth
//        is the rightmost node of that depth.
// Both are O(n) time. BFS uses O(width) space, DFS uses O(height) space.
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int nodeValue) : value(nodeValue), left(nullptr), right(nullptr) {}
};

// ---------- BFS ----------
vector<int> rightSideViewBFS(TreeNode* root) {
    vector<int> view;
    if (root == nullptr) return view;

    queue<TreeNode*> currentLevel;
    currentLevel.push(root);

    while (!currentLevel.empty()) {
        int nodesInLevel = static_cast<int>(currentLevel.size());   // fix the size before pushing children
        for (int position = 0; position < nodesInLevel; position++) {
            TreeNode* current = currentLevel.front();
            currentLevel.pop();
            if (position == nodesInLevel - 1) view.push_back(current->value);   // last in the level = visible
            if (current->left != nullptr) currentLevel.push(current->left);
            if (current->right != nullptr) currentLevel.push(current->right);
        }
    }
    return view;
}

// ---------- DFS (recursive) ----------
// Base case: node is null -> nothing to record, return.
// Record: if view already has `depth` entries, this is the first node seen at this depth
//         (and because we go right first, it is the rightmost one).
// Right subtree: recurse with depth + 1.   Left subtree: recurse with depth + 1.
// Return value: none, results are collected in `view`.
void collectRightFirst(TreeNode* node, int depth, vector<int>& view) {
    if (node == nullptr) return;
    if (depth == static_cast<int>(view.size())) view.push_back(node->value);
    collectRightFirst(node->right, depth + 1, view);
    collectRightFirst(node->left, depth + 1, view);
}

vector<int> rightSideViewDFS(TreeNode* root) {
    vector<int> view;
    collectRightFirst(root, 0, view);
    return view;
}

void freeTree(TreeNode* node) {             // post-order delete: children first, then the node
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

void printVector(const vector<int>& values) {
    for (int value : values) cout << value << " ";
    cout << endl;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(4);

    printVector(rightSideViewBFS(root));        // 1 3 4
    printVector(rightSideViewDFS(root));        // 1 3 4
    freeTree(root);

    // Only left children: nothing hides them, so every node is visible
    TreeNode* leftChain = new TreeNode(1);
    leftChain->left = new TreeNode(2);
    leftChain->left->left = new TreeNode(3);
    printVector(rightSideViewBFS(leftChain));   // 1 2 3
    printVector(rightSideViewDFS(leftChain));   // 1 2 3
    freeTree(leftChain);

    printVector(rightSideViewBFS(nullptr));     // (empty line)
    return 0;
}
