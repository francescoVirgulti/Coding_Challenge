// Implementing Red-Black Tree in C++

#include <iostream>
using namespace std;

struct Node_S {
  int data;
  int nSerpente;
  Node_S *parent;
  Node_S *left;
  Node_S *right;
  int color;
};

typedef Node_S *Node_S_Ptr;

class SerpenteRedBlackTree {
   private:
  Node_S_Ptr root;
  Node_S_Ptr TNULL;

  void initializeNULLNode_S(Node_S_Ptr node_S, Node_S_Ptr parent) {
    node_S->data = 0;
    node_S->parent = parent;
    node_S->left = nullptr;
    node_S->right = nullptr;
    node_S->color = 0;
  }

  // Preorder
  void preOrderHelper(Node_S_Ptr node_S) {
    if (node_S != TNULL) {
      cout << node_S->data << " ";
      preOrderHelper(node_S->left);
      preOrderHelper(node_S->right);
    }
  }

  // Inorder
  void inOrderHelper(Node_S_Ptr node_S) {
    if (node_S != TNULL) {
      inOrderHelper(node_S->left);
      cout << node_S->data << " ";
      inOrderHelper(node_S->right);
    }
  }

  // Post order
  void postOrderHelper(Node_S_Ptr node_S) {
    if (node_S != TNULL) {
      postOrderHelper(node_S->left);
      postOrderHelper(node_S->right);
      cout << node_S->data << " ";
    }
  }

  Node_S_Ptr searchTreeHelper(Node_S_Ptr node_S, int key) {
    if (node_S == TNULL || key == node_S->data) {
      return node_S;
    }

    if (key < node_S->data) {
      return searchTreeHelper(node_S->left, key);
    }
    return searchTreeHelper(node_S->right, key);
  }

  // For balancing the tree after deletion
  void deleteFix(Node_S_Ptr x) {
    Node_S_Ptr s;
    while (x != root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            rightRotate(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          leftRotate(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            leftRotate(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }

  void rbTransplant(Node_S_Ptr u, Node_S_Ptr v) {
    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteNode_SHelper(Node_S_Ptr node_S, int key) {
    Node_S_Ptr z = TNULL;
    Node_S_Ptr x, y;
    while (node_S != TNULL) {
      if (node_S->data == key) {
        z = node_S;
      }

      if (node_S->data <= key) {
        node_S = node_S->right;
      } else {
        node_S = node_S->left;
      }
    }

    if (z == TNULL) {
      cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
      x = z->left;
      rbTransplant(z, z->left);
    } else {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == 0) {
      deleteFix(x);
    }
  }

  // For balancing the tree after insertion
  void insertFix(Node_S_Ptr k) {
    Node_S_Ptr u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = 0;
  }

  void printHelper(Node_S_Ptr root, string indent, bool last) {
    if (root != TNULL) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }

      string sColor = root->color ? "RED" : "BLACK";
      cout << root->data << "(" << sColor << ")" << endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

   public:
  SerpenteRedBlackTree() {
    TNULL = new Node_S;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
  }

  void preorder() {
    preOrderHelper(this->root);
  }

  void inorder() {
    inOrderHelper(this->root);
  }

  void postorder() {
    postOrderHelper(this->root);
  }

  Node_S_Ptr searchTree(int k) {
    return searchTreeHelper(this->root, k);
  }

  Node_S_Ptr minimum(Node_S_Ptr node_S) {
    while (node_S->left != TNULL) {
      node_S = node_S->left;
    }
    return node_S;
  }

  Node_S_Ptr maximum(Node_S_Ptr node_S) {
    while (node_S->right != TNULL) {
      node_S = node_S->right;
    }
    return node_S;
  }

  Node_S_Ptr successor(Node_S_Ptr x) {
    if (x->right != TNULL) {
      return minimum(x->right);
    }

    Node_S_Ptr y = x->parent;
    while (y != TNULL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  Node_S_Ptr predecessor(Node_S_Ptr x) {
    if (x->left != TNULL) {
      return maximum(x->left);
    }

    Node_S_Ptr y = x->parent;
    while (y != TNULL && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void leftRotate(Node_S_Ptr x) {
    Node_S_Ptr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(Node_S_Ptr x) {
    Node_S_Ptr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  // Inserting a node_S
  void insert(int key, int n) {
    Node_S_Ptr node_S = new Node_S;
    node_S->parent = nullptr;
    node_S->data = key;
    node_S->nSerpente = n;
    node_S->left = TNULL;
    node_S->right = TNULL;
    node_S->color = 1;

    Node_S_Ptr y = nullptr;
    Node_S_Ptr x = this->root;

    while (x != TNULL) {
      y = x;
      if (node_S->data < x->data) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    node_S->parent = y;
    if (y == nullptr) {
      root = node_S;
    } else if (node_S->data < y->data) {
      y->left = node_S;
    } else {
      y->right = node_S;
    }

    if (node_S->parent == nullptr) {
      node_S->color = 0;
      return;
    }

    if (node_S->parent->parent == nullptr) {
      return;
    }

    insertFix(node_S);
  }

  Node_S_Ptr getRoot() {
    return this->root;
  }

  void deleteNode_S(int data) {
    deleteNode_SHelper(this->root, data);
  }

  void printTree() {
    if (root) {
      printHelper(this->root, "", true);
    }
  }
};

