//
// Created by chris on 24-12-9.
//

#ifndef NODE_H
#define NODE_H

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    explicit Node(int value) {
        key = value;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        height = 1;
    }

    virtual ~Node() = default;
};

struct RBTNode {
    int key;
    int height;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;

    enum {RED, BLACK} color;

    // Constructor
    explicit RBTNode(int value) {
        key = value;
        height = 1;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = RED;
    }
};

#endif //NODE_H
