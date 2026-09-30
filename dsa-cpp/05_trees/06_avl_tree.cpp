// AVL tree: a self-balancing BST. For every node, |height(left) - height(right)| <= 1.
// After each insert we walk back up and fix any node that becomes unbalanced
// using one of four cases:
//   Left-Left   -> rotate right
//   Right-Right -> rotate left
//   Left-Right  -> rotate left on the left child, then rotate right
//   Right-Left  -> rotate right on the right child, then rotate left
// Guarantees O(log n) insert/search. (Delete is left as an extension.)
#include <iostream>
using namespace std;

struct AVLNode {
    int data;
    int height;     // height of the subtree rooted here (leaf = 1)
    AVLNode* left;
    AVLNode* right;
    AVLNode(int value) : data(value), height(1), left(nullptr), right(nullptr) {}
};

int height(AVLNode* node) { return node ? node->height : 0; }

void updateHeight(AVLNode* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

// balance factor > 1 means left-heavy, < -1 means right-heavy
int balanceFactor(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

/*
     y            x
    / \          / \
   x   C  --->  A   y
  / \              / \
 A   B            B   C
*/
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* middle = x->right;
    x->right = y;
    y->left = middle;
    updateHeight(y);      // y is now lower, update it first
    updateHeight(x);
    return x;             // new root of this subtree
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* middle = y->left;
    y->left = x;
    x->right = middle;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* insert(AVLNode* node, int value) {
    // normal BST insert
    if (node == nullptr) return new AVLNode(value);
    if (value < node->data) node->left = insert(node->left, value);
    else if (value > node->data) node->right = insert(node->right, value);
    else return node;                                   // ignore duplicates

    // update this node and rebalance if needed
    updateHeight(node);
    int balance = balanceFactor(node);

    if (balance > 1 && value < node->left->data) return rotateRight(node);        // Left-Left
    if (balance < -1 && value > node->right->data) return rotateLeft(node);       // Right-Right
    if (balance > 1 && value > node->left->data) {                                // Left-Right
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && value < node->right->data) {                              // Right-Left
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

void inorder(AVLNode* node) {
    if (node == nullptr) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

void preorder(AVLNode* node) {
    if (node == nullptr) return;
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

void freeTree(AVLNode* node) {
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

int main() {
    // Sorted inserts would make a plain BST a straight line (height 7).
    AVLNode* root = nullptr;
    for (int value = 1; value <= 7; value++) root = insert(root, value);

    cout << "Inorder:  "; inorder(root);  cout << endl;   // 1 2 3 4 5 6 7
    cout << "Preorder: "; preorder(root); cout << endl;   // 4 2 1 3 6 5 7
    cout << "Height: " << height(root) << endl;           // 3 (perfectly balanced)

    freeTree(root);
    return 0;
}
