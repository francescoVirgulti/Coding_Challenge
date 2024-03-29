// Implementing Red-Black Tree in C++

#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct Node
{
  int data;
  std::string id;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

typedef Node *NodePtr;

class RedBlackTree
{
private:
  NodePtr root;
  NodePtr TNULL;

  void initializeNULLNode(NodePtr node, NodePtr parent)
  {
    node->data = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
  }

  // Preorder
  void preOrderHelper(NodePtr node)
  {
    if (node != TNULL)
    {
      cout << node->data << " ";
      preOrderHelper(node->left);
      preOrderHelper(node->right);
    }
  }

  // Inorder
  void inOrderHelper(NodePtr node)
  {
    if (node != TNULL)
    {
      inOrderHelper(node->left);
      cout << node->data << " ";
      inOrderHelper(node->right);
    }
  }

  // Post order
  void postOrderHelper(NodePtr node)
  {
    if (node != TNULL)
    {
      postOrderHelper(node->left);
      postOrderHelper(node->right);
      cout << node->data << " ";
    }
  }

  NodePtr searchTreeHelper(NodePtr node, int key)
  {
    if (node == TNULL || key == node->data)
    {
      return node;
    }

    if (key < node->data)
    {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  // For balancing the tree after deletion
  void deleteFix(NodePtr x)
  {
    NodePtr s;
    while (x != root && x->color == 0)
    {
      if (x == x->parent->left)
      {
        s = x->parent->right;
        if (s->color == 1)
        {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == 0 && s->right->color == 0)
        {
          s->color = 1;
          x = x->parent;
        }
        else
        {
          if (s->right->color == 0)
          {
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
      }
      else
      {
        s = x->parent->left;
        if (s->color == 1)
        {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 0 && s->right->color == 0)
        {
          s->color = 1;
          x = x->parent;
        }
        else
        {
          if (s->left->color == 0)
          {
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

  void rbTransplant(NodePtr u, NodePtr v)
  {
    if (u->parent == nullptr)
    {
      root = v;
    }
    else if (u == u->parent->left)
    {
      u->parent->left = v;
    }
    else
    {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteNodeHelper(NodePtr node, int key, std::string id)
  {
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL)
    {
      if (node->data == key && !node->id.compare(id))
      {
        z = node;
      }

      if (node->data <= key)
      {
        node = node->right;
      }
      else
      {
        node = node->left;
      }
    }

    if (z == TNULL)
    {
      cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL)
    {
      x = z->right;
      rbTransplant(z, z->right);
    }
    else if (z->right == TNULL)
    {
      x = z->left;
      rbTransplant(z, z->left);
    }
    else
    {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z)
      {
        x->parent = y;
      }
      else
      {
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
    if (y_original_color == 0)
    {
      deleteFix(x);
    }
  }

  // For balancing the tree after insertion
  void insertFix(NodePtr k)
  {
    NodePtr u;
    while (k->parent->color == 1)
    {
      if (k->parent == k->parent->parent->right)
      {
        u = k->parent->parent->left;
        if (u->color == 1)
        {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        }
        else
        {
          if (k == k->parent->left)
          {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      }
      else
      {
        u = k->parent->parent->right;

        if (u->color == 1)
        {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        }
        else
        {
          if (k == k->parent->right)
          {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root)
      {
        break;
      }
    }
    root->color = 0;
  }

  void printHelper(NodePtr root, string indent, bool last)
  {
    if (root != TNULL)
    {
      cout << indent;
      if (last)
      {
        cout << "R----";
        indent += "   ";
      }
      else
      {
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
  RedBlackTree()
  {
    TNULL = new Node;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
  }

  void preorder()
  {
    preOrderHelper(this->root);
  }

  void inorder()
  {
    inOrderHelper(this->root);
  }

  void postorder()
  {
    postOrderHelper(this->root);
  }

  NodePtr searchTree(int k)
  {
    return searchTreeHelper(this->root, k);
  }

  NodePtr minimum(NodePtr node)
  {
    while (node->left != TNULL)
    {
      node = node->left;
    }
    return node;
  }

  NodePtr maximum(NodePtr node)
  {
    while (node->right != TNULL)
    {
      node = node->right;
    }
    return node;
  }

  NodePtr successor(NodePtr x)
  {
    if (x->right != TNULL)
    {
      return minimum(x->right);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->right)
    {
      x = y;
      y = y->parent;
    }
    return y;
  }

  NodePtr predecessor(NodePtr x)
  {
    if (x->left != TNULL)
    {
      return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->left)
    {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void leftRotate(NodePtr x)
  {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL)
    {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
      this->root = y;
    }
    else if (x == x->parent->left)
    {
      x->parent->left = y;
    }
    else
    {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(NodePtr x)
  {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL)
    {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
      this->root = y;
    }
    else if (x == x->parent->right)
    {
      x->parent->right = y;
    }
    else
    {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  // Inserting a node
  void insert(int key, std::string id)
  {
    NodePtr node = new Node;
    node->parent = nullptr;
    node->data = key;
    node->id = id;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL)
    {
      y = x;
      if (node->data < x->data)
      {
        x = x->left;
      }
      else
      {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr)
    {
      root = node;
    }
    else if (node->data < y->data)
    {
      y->left = node;
    }
    else
    {
      y->right = node;
    }

    if (node->parent == nullptr)
    {
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr)
    {
      return;
    }

    insertFix(node);
  }

  NodePtr getRoot()
  {
    return this->root;
  }

  void deleteNode(int data, std::string id)
  {
    deleteNodeHelper(this->root, data, id);
  }

  void printTree()
  {
    if (root)
    {
      printHelper(this->root, "", true);
    }
  }
};

enum Direction
{
  LEFT_TO_RIGHT,
  LEFT_TO_DOWN,
  LEFT_TO_UP,

  UP_TO_RIGHT,
  UP_TO_LEFT,
  UP_TO_DOWN,

  RIGHT_TO_UP,
  RIGHT_TO_LEFT,
  RIGHT_TO_DOWN,

  DOWN_TO_RIGHT,
  DOWN_TO_UP,
  DOWN_TO_LEFT,

  NO_ACTION
};

const std::map<std::string, std::vector<Direction>> tileDirections = {
    {"3", {LEFT_TO_RIGHT}},
    {"5", {DOWN_TO_RIGHT}},
    {"6", {LEFT_TO_DOWN}},
    {"7", {LEFT_TO_RIGHT, LEFT_TO_DOWN, DOWN_TO_RIGHT}},
    {"9", {UP_TO_RIGHT}},
    {"96", {LEFT_TO_DOWN, UP_TO_RIGHT}},
    {"A", {LEFT_TO_UP}},
    {"A5", {LEFT_TO_UP, DOWN_TO_RIGHT}},
    {"B", {LEFT_TO_RIGHT, LEFT_TO_UP, UP_TO_RIGHT}},
    {"C", {UP_TO_DOWN}},
    {"C3", {LEFT_TO_RIGHT, UP_TO_DOWN}},
    {"D", {UP_TO_DOWN, UP_TO_RIGHT, DOWN_TO_RIGHT}},
    {"E", {LEFT_TO_UP, LEFT_TO_DOWN, UP_TO_DOWN}},
    {"F", {LEFT_TO_RIGHT, LEFT_TO_DOWN, LEFT_TO_UP, UP_TO_DOWN, DOWN_TO_RIGHT, UP_TO_RIGHT}},
};

function del_node(std::string id, int costo)
{
  if (LEFT_TO_RIGHT || RIGHT_TO_LEFT)
  {
    L_R.deleteNode(costo, id);
  }
}

RedBlackTree L_R, U_D, L_U, L_D, R_U, R_D;
NodePtr choose(Direction dir)
{
  NodePtr minimo = nullptr;
  switch (dir)
  {
  case LEFT_TO_RIGHT:
  case RIGHT_TO_LEFT:
    minimo = L_R.minimum(L_R.getRoot());
    break;
  case UP_TO_DOWN:
  case DOWN_TO_UP:
    minimo = U_D.minimum(U_D.getRoot());
    break;
  case LEFT_TO_DOWN:
  case DOWN_TO_LEFT:
    minimo = L_D.minimum(L_D.getRoot());
    if (minimo == nullptr)
    {
      minimo = L_R.minimum(L_R.getRoot());
      if (minimo == nullptr)
      {
        U_D.minimum(U_D.getRoot());
      }
    }
    break;
  case LEFT_TO_UP:
  case UP_TO_LEFT:
    minimo = L_U.minimum(L_U.getRoot());
    if (minimo == nullptr)
    {
      minimo = L_R.minimum(L_R.getRoot());
      if (minimo == nullptr)
      {
        U_D.minimum(U_D.getRoot());
      }
      break;
    case UP_TO_RIGHT:
    case RIGHT_TO_UP:
      minimo = R_U.minimum(R_U.getRoot());
      break;
    case RIGHT_TO_DOWN:
    case DOWN_TO_RIGHT:
      minimo = R_D.minimum(R_D.getRoot());
      break;
    default:
      break;
    }
  }

  return minimo;
}
