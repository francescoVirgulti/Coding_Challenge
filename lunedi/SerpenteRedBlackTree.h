#ifndef SERPENTEREDBLACKTREE_H
#define SERPENTEREDBLACKTREE_H

#include <iostream>

struct Node_S {
  int data;
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

  void initializeNULLNode_S(Node_S_Ptr node_S, Node_S_Ptr parent);

  void preOrderHelper(Node_S_Ptr node_S);

  void inOrderHelper(Node_S_Ptr node_S);

  void postOrderHelper(Node_S_Ptr node_S);

  Node_S_Ptr searchTreeHelper(Node_S_Ptr node_S, int key);

  void deleteFix(Node_S_Ptr x);

  void rbTransplant(Node_S_Ptr u, Node_S_Ptr v);

  void deleteNode_SHelper(Node_S_Ptr node_S, int key);

  void insertFix(Node_S_Ptr k);

  void printHelper(Node_S_Ptr root, std::string indent, bool last);

public:
  SerpenteRedBlackTree();

  void preorder();

  void inorder();

  void postorder();

  Node_S_Ptr searchTree(int k);

  Node_S_Ptr minimum(Node_S_Ptr node_S);

  Node_S_Ptr maximum(Node_S_Ptr node_S);

  Node_S_Ptr successor(Node_S_Ptr x);

  Node_S_Ptr predecessor(Node_S_Ptr x);

  void leftRotate(Node_S_Ptr x);

  void rightRotate(Node_S_Ptr x);

  void insert(int key);

  Node_S_Ptr getRoot();

  void deleteNode_S(int data);

  void printTree();
};

#endif // SERPENTEREDBLACKTREE_H
