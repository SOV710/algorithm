//
// Created by chris on 24-12-9.
//

#ifndef TREE_H
#define TREE_H

#include "node.hpp"
#include <string>

namespace TREE {

//-------------------------------------------------------------------------------//
//                              Binary Search Trees //
//-------------------------------------------------------------------------------//

template <KeyComparble Key> class BinarySearchTree {
protected:
  using NodeT = BSTNode<Key>;
  NodeT *root;

  virtual NodeT *insertNode(NodeT *node, int key, NodeT *parent);
  NodeT *searchNode(NodeT *node, int key);
  void transplant(NodeT *u, NodeT *v);
  virtual NodeT *deleteNode(NodeT *root, NodeT *node);
  NodeT *minimumNode(NodeT *node);
  NodeT *maximumNode(NodeT *node);
  NodeT *successorNode(NodeT *node);

  NodeT *rotateLeft(NodeT *z);
  NodeT *rotateRight(NodeT *z);

public:
  virtual ~BinarySearchTree() = default;

  // Constructor
  BinarySearchTree();
  BinarySearchTree(std::initializer_list<int> list);
  virtual BinarySearchTree &operator=(std::initializer_list<int> list);

  NodeT *getRoot();
  virtual void insert(int key);
  virtual NodeT *search(int key);
  virtual void remove(int key);
  NodeT *minimum();
  NodeT *maximum();
  NodeT *successor(int key);
  void printWithoutPrefix(NodeT *node);
  void printWithPrefix(const std::string &prefix, NodeT *node);

  int getHeight(NodeT *node);
  int getBalance(NodeT *node);
  void updateHeight(NodeT *node);
};

//-------------------------------------------------------------------------------//
//                                   AVL Trees //
//-------------------------------------------------------------------------------//

template <KeyComparble Key> class AVLTree : public BinarySearchTree {
protected:
  using NodeT = BSTNode<Key>;
  NodeT *balance(NodeT *node, int key);

  NodeT *insertNode(NodeT *node, int key, NodeT *parent) override;
  NodeT *deleteNode(NodeT *root, NodeT *node) override;

public:
  AVLTree();
  AVLTree(std::initializer_list<int> list);
  AVLTree &operator=(std::initializer_list<int> list) override;

  void insert(int key) override;
  NodeT *search(int key) override;
  void remove(int key) override;
};

//-------------------------------------------------------------------------------//
//                                Red-Black Trees //
//-------------------------------------------------------------------------------//

/*class RedBlackTree {
    protected:
    RBTNode* root;
    RBTNode* NIL;

    RBTNode* rotateLeft(RBTNode* z);
    RBTNode* rotateRight(RBTNode* z);

    RBTNode* searchNode(RBTNode* node, int key);
    void transplant(RBTNode* u, RBTNode* v);

    RBTNode* insertNode(RBTNode* node, int key, RBTNode* parent);
    RBTNode* deleteNode(RBTNode* root, RBTNode* node);

    // placing in insert and remove function, keeping RBT properties
    void insertFixup(RBTNode* node);
    void deleteFixup(RBTNode* node, RBTNode* parent);

    RBTNode* minimum(RBTNode* node);
    RBTNode* maximum(RBTNode* node);
    RBTNode* successor(RBTNode* node);

    public:
    // Constructor
    RedBlackTree();
    ~RedBlackTree();

    RBTNode* getRoot();
    RBTNode* search(int key);

    // Override the insert and delete method in Binary search tree
    void insert(int key);
    void remove(int key);

    int getHeight(RBTNode* node);
    int getBalance(RBTNode* node);
    void updateHeight(RBTNode* node);
};*/

} // namespace TREE

#endif // TREE_H
