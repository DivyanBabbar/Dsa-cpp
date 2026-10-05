// Common binary tree problems. Each recursive function: base case = nullptr,
// then left subtree, right subtree, and a return value built from both.
#include <iostream>
#include <algorithm>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Mirror: swap left and right at every node.
void mirror(TreeNode* node) {
    if (node == nullptr) return;
    swap(node->left, node->right);
    mirror(node->left);
    mirror(node->right);
}

// Two trees are identical if same value at the root and identical left and right subtrees.
bool isSameTree(TreeNode* a, TreeNode* b) {
    if (a == nullptr && b == nullptr) return true;    // both empty
    if (a == nullptr || b == nullptr) return false;   // only one empty
    return a->data == b->data &&
           isSameTree(a->left, b->left) &&
           isSameTree(a->right, b->right);
}

// Diameter = most edges on any path between two nodes.
// At each node the best path THROUGH it is leftHeight + rightHeight.
// `best` keeps the maximum seen; the function returns height so parents can use it.
int diameterHelper(TreeNode* node, int& best) {
    if (node == nullptr) return 0;
    int leftHeight = diameterHelper(node->left, best);
    int rightHeight = diameterHelper(node->right, best);
    best = max(best, leftHeight + rightHeight);
    return 1 + max(leftHeight, rightHeight);
}
int diameter(TreeNode* root) {
    int best = 0;
    diameterHelper(root, best);
    return best;
}

// Balanced: at every node, left and right heights differ by at most 1.
// Returns height, or -1 if any subtree is unbalanced (propagates upward).
int checkBalanced(TreeNode* node) {
    if (node == nullptr) return 0;
    int leftHeight = checkBalanced(node->left);
    if (leftHeight == -1) return -1;
    int rightHeight = checkBalanced(node->right);
    if (rightHeight == -1) return -1;
    if (abs(leftHeight - rightHeight) > 1) return -1;
    return 1 + max(leftHeight, rightHeight);
}
bool isBalanced(TreeNode* root) { return checkBalanced(root) != -1; }

// Does a root-to-leaf path exist whose values add up to target?
bool hasPathSum(TreeNode* node, int target) {
    if (node == nullptr) return false;
    int remaining = target - node->data;
    if (node->left == nullptr && node->right == nullptr) return remaining == 0;  // leaf
    return hasPathSum(node->left, remaining) || hasPathSum(node->right, remaining);
}

// Lowest common ancestor in a general binary tree.
// If p and q are found in different subtrees, the current node is the LCA.
TreeNode* lowestCommonAncestor(TreeNode* node, TreeNode* p, TreeNode* q) {
    if (node == nullptr || node == p || node == q) return node;
    TreeNode* fromLeft = lowestCommonAncestor(node->left, p, q);
    TreeNode* fromRight = lowestCommonAncestor(node->right, p, q);
    if (fromLeft != nullptr && fromRight != nullptr) return node;
    return (fromLeft != nullptr) ? fromLeft : fromRight;
}

void inorder(TreeNode* node) {
    if (node == nullptr) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

void freeTree(TreeNode* node) {
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

TreeNode* buildSample() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    return root;
}

int main() {
    TreeNode* tree = buildSample();
    TreeNode* other = buildSample();

    cout << "Same tree? " << isSameTree(tree, other) << endl;   // 1
    cout << "Diameter: " << diameter(tree) << endl;              // 3 (4-2-1-3)
    cout << "Balanced? " << isBalanced(tree) << endl;            // 1
    cout << "Path sum 7 (1+2+4)? " << hasPathSum(tree, 7) << endl;   // 1
    cout << "Path sum 5? " << hasPathSum(tree, 5) << endl;           // 0

    TreeNode* lca = lowestCommonAncestor(tree, tree->left->left, tree->left->right);
    cout << "LCA of 4 and 5: " << lca->data << endl;             // 2

    mirror(tree);
    cout << "Inorder after mirror: "; inorder(tree); cout << endl;   // 3 1 5 2 4
    cout << "Same tree after mirror? " << isSameTree(tree, other) << endl;  // 0

    freeTree(tree);
    freeTree(other);
    return 0;
}
