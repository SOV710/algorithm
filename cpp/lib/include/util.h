//
// Created by chris on 24-12-9.
//

#ifndef UTIL_H
#define UTIL_H

#include "node.h"

void swap(int* i, int* j);

void printArray(int arr[], int size);
void printTree(const std::string &prefix, Node *node, bool isLeft);

#endif //UTIL_H
