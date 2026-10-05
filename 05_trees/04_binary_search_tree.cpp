// Binary Search Tree: for every node, left subtree < node < right subtree.
// Average O(log n) for insert/search/delete; O(n) if the tree degenerates into a line.
// Inorder traversal of a BST gives sorted order.
#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    // base case: empty spot -> create the node here.
    TreeNode* insertHelper(TreeNode* node, int value) {
        if (node == nullptr) return new TreeNode(value);
        if (value < node->data) node->left = insertHelper(node->left, value);
        else if (value > node->data) node->right = insertHelper(node->right, value);
        // equal values are ignored (no duplicates)
        return node;
    }

    bool searchHelper(TreeNode* node, int value) const {
        if (node == nullptr) return false;              // base case: not found
        if (value == node->data) return true;
        if (value < node->data) return searchHelper(node->left, value);
        return searchHelper(node->right, value);
    }

    TreeNode* findMinNode(TreeNode* node) const {
        while (node->left != nullptr) node = node->left;   // leftmost = smallest
        return node;
    }

    // Delete has 3 cases:
    //  1) no left child  -> replace node by its right child (covers leaf too)
    //  2) no right child -> replace node by its left child
    //  3) two children   -> copy the inorder successor (min of right subtree) here,
    //                       then delete that successor from the right subtree
    TreeNode* removeHelper(TreeNode* node, int value) {
        if (node == nullptr) return nullptr;            // base case: not found
        if (value < node->data) {
            node->left = removeHelper(node->left, value);
        } else if (value > node->data) {
            node->right = removeHelper(node->right, value);
        } else {
            if (node->left == nullptr) {
                TreeNode* rightChild = node->right;
                delete node;
                return rightChild;
            }
            if (node->right == nullptr) {
                TreeNode* leftChild = node->left;
                delete node;
                return leftChild;
            }
            TreeNode* successor = findMinNode(node->right);
            node->data = successor->data;
            node->right = removeHelper(node->right, successor->data);
        }
        return node;
    }

    void inorderHelper(TreeNode* node) const {
        if (node == nullptr) return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }

    int heightHelper(TreeNode* node) const {
        if (node == nullptr) return 0;
        return 1 + max(heightHelper(node->left), heightHelper(node->right));
    }

    void freeHelper(TreeNode* node) {
        if (node == nullptr) return;
        freeHelper(node->left);
        freeHelper(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { freeHelper(root); }

    void insert(int value) { root = insertHelper(root, value); }
    bool search(int value) const { return searchHelper(root, value); }
    void remove(int value) { root = removeHelper(root, value); }
    int height() const { return heightHelper(root); }

    int minValue() const { return root ? findMinNode(root)->data : -1; }
    int maxValue() const {
        if (root == nullptr) return -1;
        TreeNode* node = root;
        while (node->right != nullptr) node = node->right;   // rightmost = largest
        return node->data;
    }

    void printInorder() const { inorderHelper(root); cout << endl; }
};

int main() {
    BST tree;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int value : values) tree.insert(value);

    tree.printInorder();                                     // 20 30 40 50 60 70 80
    cout << "Search 60: " << tree.search(60) << endl;        // 1
    cout << "Search 65: " << tree.search(65) << endl;        // 0
    cout << "Min: " << tree.minValue() << ", Max: " << tree.maxValue() << endl;  // 20, 80
    cout << "Height: " << tree.height() << endl;             // 3

    tree.remove(20);   // leaf
    tree.remove(30);   // one child (40)
    tree.remove(50);   // two children (root)
    tree.printInorder();                                     // 40 60 70 80
    return 0;
}
