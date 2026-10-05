/*
 Binary tree basics: nodes, recursive traversals, level order, height, counts.

 Every recursive tree function below follows the same 4 parts:
   base case      -> node is nullptr
   left subtree   -> recurse on node->left
   right subtree  -> recurse on node->right
   return value   -> combine left result, right result, and this node

            1
          /   \
         2     3
        / \     \
       4   5     6
*/
#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Left, Root, Right
void inorder(TreeNode* node) {
    if (node == nullptr) return;       // base case
    inorder(node->left);               // left subtree
    cout << node->data << " ";         // this node
    inorder(node->right);              // right subtree
}

// Root, Left, Right
void preorder(TreeNode* node) {
    if (node == nullptr) return;
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

// Left, Right, Root
void postorder(TreeNode* node) {
    if (node == nullptr) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

// Level order (BFS): use a queue, visit level by level.
void levelOrder(TreeNode* root) {
    if (root == nullptr) return;
    queue<TreeNode*> pending;
    pending.push(root);
    while (!pending.empty()) {
        TreeNode* node = pending.front();
        pending.pop();
        cout << node->data << " ";
        if (node->left != nullptr) pending.push(node->left);
        if (node->right != nullptr) pending.push(node->right);
    }
}

// Height in nodes along the longest root-to-leaf path (empty tree = 0).
int height(TreeNode* node) {
    if (node == nullptr) return 0;                 // base case
    int leftHeight = height(node->left);           // left subtree
    int rightHeight = height(node->right);         // right subtree
    return 1 + max(leftHeight, rightHeight);       // return value
}

int countNodes(TreeNode* node) {
    if (node == nullptr) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int countLeaves(TreeNode* node) {
    if (node == nullptr) return 0;
    if (node->left == nullptr && node->right == nullptr) return 1;   // leaf
    return countLeaves(node->left) + countLeaves(node->right);
}

// Free memory: children first (postorder), then the node itself.
void freeTree(TreeNode* node) {
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    cout << "Inorder:    "; inorder(root);    cout << endl;   // 4 2 5 1 3 6
    cout << "Preorder:   "; preorder(root);   cout << endl;   // 1 2 4 5 3 6
    cout << "Postorder:  "; postorder(root);  cout << endl;   // 4 5 2 6 3 1
    cout << "Level order:"; cout << " "; levelOrder(root); cout << endl;  // 1 2 3 4 5 6
    cout << "Height: " << height(root) << endl;              // 3
    cout << "Nodes: " << countNodes(root) << endl;           // 6
    cout << "Leaves: " << countLeaves(root) << endl;         // 3

    freeTree(root);
    return 0;
}
