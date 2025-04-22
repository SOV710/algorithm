//
// Created by chris on 24-12-9.
//

#pragma once
#include <concepts>
#include <memory>

template <typename Key>
concept KeyComparble = std::totally_ordered<Key>;

template <KeyComparble Key> struct BSTNode {
  using key_type = Key;
  using node_ptr = std::unique_ptr<BSTNode>;

  key_type key;
  node_ptr left{nullptr};
  node_ptr right{nullptr};
  BSTNode *parent{nullptr};
  int height{1};

  explicit BSTNode(const key_type &k) noexcept : key(k) {}

  BSTNode(const BSTNode &) = delete;
  BSTNode &operator=(const BSTNode &) = delete;
  BSTNode(BSTNode &&) noexcept = default;
  BSTNode &operator=(BSTNode &&) noexcept = default;

  ~BSTNode() = default;
};

struct RBTNode {
  int key;
  int height;
  RBTNode *left;
  RBTNode *right;
  RBTNode *parent;

  enum { RED, BLACK } color;

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
