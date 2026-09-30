// Tree traversals WITHOUT recursion: we manage the stack ourselves.
#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Inorder: go as far left as possible, visit, then move to the right child.
void inorderIterative(TreeNode* root) {
    stack<TreeNode*> path;
    TreeNode* current = root;
    while (current != nullptr || !path.empty()) {
        while (current != nullptr) {       // dive left, remembering the path
            path.push(current);
            current = current->left;
        }
        current = path.top();
        path.pop();
        cout << current->data << " ";      // visit
        current = current->right;          // then the right subtree
    }
}

// Preorder: pop, visit, push RIGHT first so LEFT is popped first.
void preorderIterative(TreeNode* root) {
    if (root == nullptr) return;
    stack<TreeNode*> pending;
    pending.push(root);
    while (!pending.empty()) {
        TreeNode* node = pending.top();
        pending.pop();
        cout << node->data << " ";
        if (node->right != nullptr) pending.push(node->right);
        if (node->left != nullptr) pending.push(node->left);
    }
}

// Postorder with two stacks: produce Root-Right-Left, then reverse it to Left-Right-Root.
void postorderIterative(TreeNode* root) {
    if (root == nullptr) return;
    stack<TreeNode*> pending;
    stack<TreeNode*> reversed;
    pending.push(root);
    while (!pending.empty()) {
        TreeNode* node = pending.top();
        pending.pop();
        reversed.push(node);
        if (node->left != nullptr) pending.push(node->left);
        if (node->right != nullptr) pending.push(node->right);
    }
    while (!reversed.empty()) {
        cout << reversed.top()->data << " ";
        reversed.pop();
    }
}

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

    cout << "Inorder:   "; inorderIterative(root);   cout << endl;   // 4 2 5 1 3 6
    cout << "Preorder:  "; preorderIterative(root);  cout << endl;   // 1 2 4 5 3 6
    cout << "Postorder: "; postorderIterative(root); cout << endl;   // 4 5 2 6 3 1

    freeTree(root);
    return 0;
}
