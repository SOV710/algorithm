//
// Created by chris on 24-12-9.
//

#ifndef TREE_H
#define TREE_H

#include <string>
#include "node.h"

namespace TREE {

    //-------------------------------------------------------------------------------//
    //                              Binary Search Trees                              //
    //-------------------------------------------------------------------------------//


    class BinarySearchTree {
    protected:
        Node* root;

        virtual Node* insertNode(Node* node, int key, Node* parent);
        Node* searchNode(Node* node, int key);
        void transplant(Node* u, Node* v);
        virtual Node* deleteNode(Node* root, Node* node);
        Node* minimumNode(Node* node);
        Node* maximumNode(Node* node);
        Node* successorNode(Node* node);

        Node* rotateLeft(Node* z);
        Node* rotateRight(Node* z);

    public:
        virtual ~BinarySearchTree() = default;

        //Constructor
        BinarySearchTree();
        BinarySearchTree(std::initializer_list<int> list);
        virtual BinarySearchTree &operator=(std::initializer_list<int> list);

        Node* getRoot();
        virtual void insert(int key);
        virtual Node* search(int key);
        virtual void remove(int key);
        Node* minimum();
        Node* maximum();
        Node* successor(int key);
        void printWithoutPrefix(Node* node);
        void printWithPrefix(const std::string& prefix, Node* node);

        int getHeight(Node* node);
        int getBalance(Node* node);
        void updateHeight(Node* node);
    };

    //-------------------------------------------------------------------------------//
    //                                   AVL Trees                                   //
    //-------------------------------------------------------------------------------//

    class AVLTree : public BinarySearchTree{
    protected:
        Node* balance(Node* node, int key);

        Node* insertNode(Node* node, int key, Node* parent) override;
        Node* deleteNode(Node* root, Node* node) override;

    public:
        AVLTree();
        AVLTree(std::initializer_list<int> list);
        AVLTree &operator=(std::initializer_list<int> list) override;

        void insert(int key) override;
        Node* search(int key) override;
        void remove(int key) override;
    };


    //-------------------------------------------------------------------------------//
    //                                Red-Black Trees                                //
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

} // TREE

#endif //TREE_H
