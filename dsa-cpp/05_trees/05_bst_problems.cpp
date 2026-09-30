// Common BST problems. Recursive pattern: base case nullptr, left, right, return.
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* node, int value) {
    if (node == nullptr) return new TreeNode(value);
    if (value < node->data) node->left = insert(node->left, value);
    else if (value > node->data) node->right = insert(node->right, value);
    return node;
}

// Valid BST: every node must lie inside an allowed (low, high) range.
// Going left tightens `high`; going right tightens `low`.
// (Checking only parent vs child is a common bug.) Uses long long for INT_MIN/MAX nodes.
bool isValidBST(TreeNode* node, long long low, long long high) {
    if (node == nullptr) return true;
    if (node->data <= low || node->data >= high) return false;
    return isValidBST(node->left, low, node->data) &&
           isValidBST(node->right, node->data, high);
}

// k-th smallest: inorder visits values in sorted order, so count as we go.
void kthSmallestHelper(TreeNode* node, int k, int& visited, int& answer) {
    if (node == nullptr || visited >= k) return;
    kthSmallestHelper(node->left, k, visited, answer);
    visited++;
    if (visited == k) { answer = node->data; return; }
    kthSmallestHelper(node->right, k, visited, answer);
}
int kthSmallest(TreeNode* root, int k) {
    int visited = 0, answer = -1;
    kthSmallestHelper(root, k, visited, answer);
    return answer;
}

// LCA in a BST: walk down. If both values are smaller go left, both larger go right,
// otherwise this node is where they split, so it is the LCA.
TreeNode* lcaBST(TreeNode* root, int a, int b) {
    TreeNode* node = root;
    while (node != nullptr) {
        if (a < node->data && b < node->data) node = node->left;
        else if (a > node->data && b > node->data) node = node->right;
        else return node;
    }
    return nullptr;
}

// Build a height-balanced BST from a sorted array: the middle element becomes the root.
TreeNode* sortedArrayToBST(const vector<int>& sorted, int low, int high) {
    if (low > high) return nullptr;                       // base case
    int mid = low + (high - low) / 2;
    TreeNode* node = new TreeNode(sorted[mid]);
    node->left = sortedArrayToBST(sorted, low, mid - 1);  // left subtree
    node->right = sortedArrayToBST(sorted, mid + 1, high);// right subtree
    return node;
}

// Inorder successor: the smallest value greater than `value`.
int inorderSuccessor(TreeNode* root, int value) {
    TreeNode* candidate = nullptr;
    TreeNode* node = root;
    while (node != nullptr) {
        if (node->data > value) { candidate = node; node = node->left; }
        else node = node->right;
    }
    return candidate ? candidate->data : -1;
}

void preorder(TreeNode* node) {
    if (node == nullptr) return;
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

void freeTree(TreeNode* node) {
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

int main() {
    TreeNode* root = nullptr;
    for (int value : {8, 3, 10, 1, 6, 14, 4, 7, 13}) root = insert(root, value);

    cout << "Valid BST? " << isValidBST(root, LLONG_MIN, LLONG_MAX) << endl;   // 1
    cout << "3rd smallest: " << kthSmallest(root, 3) << endl;                   // 4
    cout << "LCA(4, 7): " << lcaBST(root, 4, 7)->data << endl;                  // 6
    cout << "LCA(1, 13): " << lcaBST(root, 1, 13)->data << endl;                // 8
    cout << "Successor of 8: " << inorderSuccessor(root, 8) << endl;            // 10

    root->left->right->data = 99;    // break the BST property on purpose (99 is in left subtree of 8)
    cout << "Valid after corruption? " << isValidBST(root, LLONG_MIN, LLONG_MAX) << endl;  // 0
    freeTree(root);

    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* balanced = sortedArrayToBST(sorted, 0, sorted.size() - 1);
    cout << "Balanced BST preorder: "; preorder(balanced); cout << endl;        // 4 2 1 3 6 5 7
    freeTree(balanced);
    return 0;
}
