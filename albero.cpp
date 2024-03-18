#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Position {
public:
    int x;
    int y;

    // Costruttore per inizializzare una posizione con le coordinate fornite
    Position(int x_val, int y_val) : x(x_val), y(y_val) {}
};

class TreeNode {
    public: 
        int value;
        int x; 
        int y;

    TreeNode* left;
    TreeNode* right;

    TreeNode(int value, int x, int y): value(value), x(x), y(y), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    // Funzione di utilità per inserire un nodo nell'albero
    TreeNode* insertNode(TreeNode* root, int value, int x, int y) {
        if (root == nullptr) {
            return new TreeNode(value, x, y);
        }

        if (value < root->value) {
            root->left = insertNode(root->left, value, x, y);
        } else if (value > root->value) {
            root->right = insertNode(root->right, value, x, y);
        }

        return root;
    }

public:

    vector<Position> findMaxPosition() {
        vector<Position> maxPositions;
        int currentMax = INT_MIN;

        if (root == nullptr) {
            return maxPositions;
        }

        stack<TreeNode*> nodeStack;
        TreeNode* current = root;

        while (current != nullptr || !nodeStack.empty()) {
            while (current != nullptr) {
                nodeStack.push(current);
                current = current->right;
            }

            current = nodeStack.top();
            nodeStack.pop();

            if (current->value >= currentMax) {
                maxPositions.push_back(Position(current->x, current->y));
                currentMax = current->value;
            }

            current = current->left;
        }

        return maxPositions;
    }
        
    // Costruttore per inizializzare l'albero
    BinarySearchTree() : root(nullptr) {}

    // Metodo per inserire un nuovo nodo nell'albero
    void insert(int value, int x, int y) {
        root = insertNode(root, value, x, y);
    }
};