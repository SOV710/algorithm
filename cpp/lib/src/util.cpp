//
// Created by chris on 24-12-9.
//

#include "util.hpp"
#include <iostream>

void swap(int *i, int *j) {
  int temp = *i;
  *i = *j;
  *j = temp;
}

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d", arr[i]);
    if (i < size - 1)
      printf(" "); // 数字间有空格
  }
  printf("\n"); // 换行
}

void printTree(const std::string &prefix, Node *node, bool isLeft) {
  if (node == nullptr)
    return;
  else {
    std::cout << prefix;
    std::cout << (isLeft ? "├──" : "└──");
    std::cout << node->key << std::endl;

    printTree(prefix + (isLeft ? "│   " : "    "), node->left, true);
    printTree(prefix + (isLeft ? "│   " : "    "), node->right, false);
  }
}
