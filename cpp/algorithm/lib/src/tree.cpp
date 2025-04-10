//
// Created by chris on 24-12-9.
//

#include "tree.h"
#include "util.h"

namespace TREE {

//-------------------------------------------------------------------------------//
//                              Binary Search Trees //
//-------------------------------------------------------------------------------//

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::BinarySearchTree(std::initializer_list<int> list) {
  root = nullptr;
  for (int key : list) {
    BinarySearchTree::insert(key);
  }
}

BinarySearchTree &BinarySearchTree::operator=(std::initializer_list<int> list) {
  for (int key : list) {
    BinarySearchTree::insert(key);
  }

  return *this;
}

Node *BinarySearchTree::insertNode(Node *node, int key, Node *parent) {
  if (node == nullptr) { // check value, if not exist, create it
    Node *newNode = new Node(key);
    newNode->parent = parent;
    if (!root)
      root = newNode; // maintain the root
    return newNode;
  }

  // recursively search for appropriate place
  if (key < node->key) {
    node->left = insertNode(node->left, key, node);
    node->left->parent = node;
  } else {
    node->right = insertNode(node->right, key, node);
    node->right->parent = node;
  }
  return node; // return parent node, recursively return root
}

Node *BinarySearchTree::searchNode(Node *node, int key) {
  if (node == nullptr || node->key == key) { // check value
    return node;
  }
  if (key < node->key) // search left subtree
    return searchNode(node->left, key);
  else // search right subtree
    return searchNode(node->right, key);
}

void BinarySearchTree::transplant(Node *u, Node *v) { // used to replace u with
                                                      // v
  if (u->parent == nullptr)
    // if u is the root
    this->root = v;
  else if (u == u->parent->left)
    // if u is parent's left child,replace u with v directly
    u->parent->left = v;
  else
    u->parent->right = v;

  if (v != nullptr) { // replace v's parent with u's parent
    v->parent = u->parent;
  }
}

Node *BinarySearchTree::deleteNode(Node *root, Node *node) {
  if (root == nullptr) // nothing to delete
    return root;

  if (node->left == nullptr)
    // cases on node doesn't have left subtrees
    transplant(node, node->right);
  else if (node->right == nullptr)
    // cases on node doesn't have right subtrees
    transplant(node, node->left);
  else {
    // cases on node both have left and right child
    Node *sec = minimumNode(node->right); // successor
    if (sec->parent != node) {
      transplant(sec, sec->right);
      sec->right = node->right;
      sec->right->parent = sec;
    }
    transplant(node, sec);
    sec->left = node->left;
    sec->left->parent = sec;
  }
  return root;
}

Node *BinarySearchTree::minimumNode(Node *node) {
  while (node->left != nullptr)
    node = node->left;
  return node;
}

Node *BinarySearchTree::maximumNode(Node *node) {
  while (node->right != nullptr)
    node = node->right;
  return node;
}

Node *BinarySearchTree::successorNode(Node *node) {
  if (node == nullptr)
    return nullptr;

  if (node->right != nullptr)
    return minimumNode(node->right);

  Node *originNode = node; // prepared for nullptr protection

  Node *parent = node->parent;
  while (parent != nullptr && parent->right == node) {
    node = parent;
    parent = parent->parent;
  }
  if (parent == nullptr) // nullptr protection
    return originNode;
  return parent;
}

Node *BinarySearchTree::rotateLeft(Node *z) {
  Node *y = z->right;
  Node *T2 = y->left;

  // Perform rotation
  y->left = z;
  z->right = T2;

  // Update parents
  y->parent = z->parent;
  z->parent = y;
  if (T2)
    T2->parent = z;

  // Update heights
  updateHeight(z);
  updateHeight(y);

  return y; // y becomes the new root of the subtree
}

Node *BinarySearchTree::rotateRight(Node *z) {
  Node *y = z->left;
  Node *T3 = y->right;

  // Perform rotation
  y->right = z;
  z->left = T3;

  // Update parents
  y->parent = z->parent;
  z->parent = y;
  if (T3)
    T3->parent = z;

  // Update heights
  updateHeight(z);
  updateHeight(y);

  return y; // y becomes the new root of the subtree
}

Node *BinarySearchTree::getRoot() { return root; }

void BinarySearchTree::insert(int key) {
  root = insertNode(root, key, nullptr);
}

Node *BinarySearchTree::search(int key) { return searchNode(root, key); }

void BinarySearchTree::remove(int key) {
  deleteNode(root, searchNode(root, key));
}

Node *BinarySearchTree::minimum() { return minimumNode(root); }

Node *BinarySearchTree::maximum() { return maximumNode(root); }

Node *BinarySearchTree::successor(int key) {
  Node *node = search(key);
  return successorNode(node);
}

void BinarySearchTree::printWithoutPrefix(Node *node) {
  printTree("", node, false);
}

void BinarySearchTree::printWithPrefix(const std::string &string, Node *node) {
  printTree(string, node, false);
}

int BinarySearchTree::getHeight(Node *node) { return node ? node->height : 0; }

int BinarySearchTree::getBalance(Node *node) {
  return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void BinarySearchTree::updateHeight(Node *node) {
  if (!node)
    return;
  node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

//-------------------------------------------------------------------------------//
//                                   AVL Trees //
//-------------------------------------------------------------------------------//

AVLTree::AVLTree() { this->root = nullptr; }

AVLTree::AVLTree(std::initializer_list<int> list) {
  this->root = nullptr;
  for (auto key : list)
    AVLTree::insert(key);
}

AVLTree &AVLTree::operator=(std::initializer_list<int> list) {
  for (auto key : list)
    AVLTree::insert(key);

  return *this;
}

Node *AVLTree::balance(Node *node, int key) {
  int balance = getBalance(node);

  // LL case： left tree is higher. and the insertion point is on the left side
  // of the left subtree
  if (balance > 1 && key < node->left->key) {
    return rotateRight(node);
  }

  // RR case： right subtree is higher, and insertion point is on the right side
  // of the right subtree
  if (balance < -1 && key > node->right->key) {
    return rotateLeft(node);
  }

  // LR case： left subtree is higher, but insertion point is on the right of
  // the left subtree
  if (balance > 1 && key > node->left->key) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  // RL case： right subtree is higher, but insertion point is on the left side
  // of the right subtree
  if (balance < -1 && key < node->right->key) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  // 若无失衡变化，返回当前节点
  return node;
}

Node *AVLTree::insertNode(Node *node, int key, Node *parent) {
  if (node == nullptr) { // check value, if not exist, create it
    Node *newNode = new Node(key);
    newNode->parent = parent;
    if (this->root == nullptr)
      this->root = newNode; // maintain the root
    return newNode;
  }

  // recursively search for appropriate place
  if (key < node->key) {
    node->left = insertNode(node->left, key, node);
    node->left->parent = node;
  } else if (key > node->key) {
    node->right = insertNode(node->right, key, node);
    node->right->parent = node;
  } else
    return node;

  updateHeight(node);

  return balance(node, key);
}

Node *AVLTree::deleteNode(Node *root, Node *node) {
  if (node == nullptr) {
    // Node to be deleted not found, just return root
    return root;
  }

  Node *parent = node->parent; // keep track of the parent for later rebalancing
  Node *rebalanceStart = nullptr; // the node from which we start rebalancing

  // Standard BST Deletion
  if (node->left == nullptr && node->right == nullptr) {
    // No children
    rebalanceStart = node->parent;
    transplant(node, nullptr);
    delete node;
  } else if (node->left == nullptr) {
    // One child (right)
    rebalanceStart = node->right; // after deletion, we will start rebalancing
                                  // from here or its parent
    transplant(node, node->right);
    delete node;
  } else if (node->right == nullptr) {
    // One child (left)
    rebalanceStart = node->left;
    transplant(node, node->left);
    delete node;
  } else {
    // Two children
    Node *sec = minimumNode(node->right); // successor
    // We'll rebalance from successor or its parent after re-linking
    if (sec->parent != node) {
      // If successor is not the direct child of node
      rebalanceStart = sec->parent;
      transplant(sec, sec->right);
      sec->right = node->right;
      if (sec->right)
        sec->right->parent = sec;
    } else {
      // Successor is the direct right child of node
      rebalanceStart = sec; // since we are reattaching sec to node's position
    }
    transplant(node, sec);
    sec->left = node->left;
    if (sec->left)
      sec->left->parent = sec;

    delete node;
  }

  // Now rebalance the tree starting from rebalanceStart and moving upwards
  // If rebalanceStart is nullptr, use parent (this can happen if we deleted the
  // root)
  Node *cur = (rebalanceStart) ? rebalanceStart : parent;

  while (cur != nullptr) {
    updateHeight(cur);
    // Use cur->key as the reference key for balancing
    cur = balance(cur, cur->key);
    if (cur->parent == nullptr) {
      // If this is now the root after balancing, update the class's root
      // pointer
      this->root = cur;
    }
    cur = cur->parent;
  }

  return this->root; // Return the (possibly new) root of this subtree
}

void AVLTree::insert(int key) {
  this->root = insertNode(this->root, key, nullptr);
}

Node *AVLTree::search(int key) { return searchNode(this->root, key); }

void AVLTree::remove(int key) {
  deleteNode(this->root, searchNode(this->root, key));
}

//-------------------------------------------------------------------------------//
//                                Red-Black Trees //
//-------------------------------------------------------------------------------//

/*RedBlackTree::RedBlackTree() {
    root = nullptr;
    NIL = nullptr;
}

RBTNode* RedBlackTree::rotateLeft(RBTNode* z) {
    RBTNode* y = z->right;
    RBTNode* T2 = y->left;

    // Perform rotation
    y->left = z;
    z->right = T2;

    // Update parents
    y->parent = z->parent;
    z->parent = y;
    if (T2) T2->parent = z;

    // Update heights
    updateHeight(z);
    updateHeight(y);

    return y; // y becomes the new root of the subtree
}

RBTNode* RedBlackTree::rotateRight(RBTNode* z) {
    RBTNode* y = z->left;
    RBTNode* T3 = y->right;

    y->right = z;
    z->left = T3;

    y->parent = z->parent;
    z->parent = y;
    if (T3) T3->parent = z;

    updateHeight(z);
    updateHeight(y);

    return y;
}

RBTNode* RedBlackTree::searchNode(RBTNode* node, int key) {
    if (node == nullptr || node->key == key)
        return node;
    if (key < node->key)
        return searchNode(node->left, key);
    return searchNode(node->right, key);
}

void RedBlackTree::transplant(RBTNode* u, RBTNode* v) {

}*/

} // namespace TREE
