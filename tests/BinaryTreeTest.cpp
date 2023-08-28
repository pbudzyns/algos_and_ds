#include <gtest/gtest.h>

#include <vector>

#include "DataStructures/BinaryTree.hpp"

// ------ BinaryTreeNode Tests ---------
TEST(BinaryTreeNodeTest, CreateNode) {
  BinaryTreeNode<int> node;
  ASSERT_EQ(node.getLeft(), nullptr);
  ASSERT_EQ(node.getRight(), nullptr);
}

TEST(BinaryTreeNodeTest, NodeSetValue) {
  BinaryTreeNode<int> node(6);
  ASSERT_EQ(node.getValue(), 6);
  node.setValue(42);
  ASSERT_EQ(node.getValue(), 42);
}

TEST(BinaryTreeNodeTest, NodeSetGetChildNodes) {
  BinaryTreeNode<int> node(6);
  ASSERT_EQ(node.getLeft(), nullptr);
  ASSERT_EQ(node.getRight(), nullptr);

  BinaryTreeNode<int> leftChild(3);
  BinaryTreeNode<int> rightChild(10);
  node.setLeft(&leftChild);
  node.setRight(&rightChild);

  ASSERT_EQ(node.getLeft(), &leftChild);
  ASSERT_EQ(node.getRight(), &rightChild);
}

// ------ BinarySearchTree Tests ---------
TEST(BinarySearchTreeTest, CreateEmptyTree) {
  BinarySearchTree<int> tree;
  ASSERT_EQ(tree.getSize(), 0);
  ASSERT_EQ(tree.getRoot(), nullptr);
}

TEST(BinarySearchTreeTest, InsertValues) {
  BinarySearchTree<int> tree;
  ASSERT_EQ(tree.getSize(), 0);
  ASSERT_EQ(tree.getRoot(), nullptr);

  tree.insert(5);
  tree.insert(2);
  tree.insert(6);
  tree.insert(1);

  ASSERT_EQ(tree.getSize(), 4);
  ASSERT_EQ(tree.getRoot()->getValue(), 5);
  ASSERT_EQ(tree.getRoot()->getLeft()->getValue(), 2);
  ASSERT_EQ(tree.getRoot()->getRight()->getValue(), 6);
  ASSERT_EQ(tree.getRoot()->getLeft()->getLeft()->getValue(), 1);
}

TEST(BinarySearchTreeTest, CreateWithVector) {
  std::vector<int> values{5, 4, 3, 1, 2, 6, 7, 0, 9, 8};
  BinarySearchTree<int> tree(values);
  ASSERT_EQ(tree.getSize(), 10);
}

TEST(BinarySearchTreeTest, InOrderTraversal) {
  std::vector<int> values{5, 4, 3, 1, 2, 6, 7, 0, 9, 8};
  BinarySearchTree<int> tree(values);

  std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  ASSERT_EQ(tree.inOrder(), expected);
}

TEST(BinarySearchTreeTest, PreOrderTraversal) {
  std::vector<int> values{5, 4, 3, 1, 2, 6, 7, 0, 9, 8};
  BinarySearchTree<int> tree(values);

  std::vector<int> expected{5, 4, 3, 1, 0, 2, 6, 7, 9, 8};
  ASSERT_EQ(tree.preOrder(), expected);
}

TEST(BinarySearchTreeTest, PostOrderTraversal) {
  std::vector<int> values{5, 4, 3, 1, 2, 6, 7, 0, 9, 8};
  BinarySearchTree<int> tree(values);

  std::vector<int> expected{0, 2, 1, 3, 4, 8, 9, 7, 6, 5};
  ASSERT_EQ(tree.postOrder(), expected);
}
