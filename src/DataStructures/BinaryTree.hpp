#pragma once

#include <cstdint>
#include <vector>

template <typename T>
class BinaryTreeNode {
 public:
  BinaryTreeNode() : m_Left{nullptr}, m_Right{nullptr} {}
  explicit BinaryTreeNode(const T& value)
      : m_Value{value}, m_Left{nullptr}, m_Right{nullptr} {}
  ~BinaryTreeNode() = default;

  void setRight(BinaryTreeNode* node) { m_Right = node; }
  void setLeft(BinaryTreeNode* node) { m_Left = node; }
  void setValue(const T& value) { m_Value = value; }

  BinaryTreeNode* getRight() const { return m_Right; }
  BinaryTreeNode* getLeft() const { return m_Left; }
  const T& getValue() const { return m_Value; }

 private:
  T m_Value;
  BinaryTreeNode* m_Left;
  BinaryTreeNode* m_Right;
};

template <typename T>
class BinarySearchTree {
 public:
  BinarySearchTree() : m_Root{nullptr}, m_Size{0} {}
  explicit BinarySearchTree(const std::vector<T>& values)
      : m_Root{nullptr}, m_Size{0} {
    for (const auto& value : values) {
      insert(value);
    }
  };
  ~BinarySearchTree() = default;

  void insert(const T& value) {
    m_Root = insert(value, m_Root);
    ++m_Size;
  }
  void remove(const T& value);

  std::vector<T> inOrder();
  std::vector<T> preOrder();
  std::vector<T> postOrder();

  const BinaryTreeNode<T>* getRoot() const { return m_Root; }
  uint32_t getSize() { return m_Size; }

 private:
  uint32_t m_Size;
  BinaryTreeNode<T>* m_Root;

  BinaryTreeNode<T>* insert(const T& value, BinaryTreeNode<T>* node);

  void inOrder(std::vector<T>* values, BinaryTreeNode<T>* node);
  void preOrder(std::vector<T>* values, BinaryTreeNode<T>* node);
  void postOrder(std::vector<T>* values, BinaryTreeNode<T>* node);

  void rebalance();
};

template <typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::insert(const T& value,
                                               BinaryTreeNode<T>* node) {
  if (!node) {
    return new BinaryTreeNode<T>(value);
  }

  if (node->getValue() > value) {
    node->setLeft(insert(value, node->getLeft()));
  } else {
    node->setRight(insert(value, node->getRight()));
  }

  return node;
}

template <typename T>
std::vector<T> BinarySearchTree<T>::inOrder() {
  std::vector<T> values;
  inOrder(&values, m_Root);
  return values;
}

template <typename T>
std::vector<T> BinarySearchTree<T>::preOrder() {
  std::vector<T> values;
  preOrder(&values, m_Root);
  return values;
}

template <typename T>
std::vector<T> BinarySearchTree<T>::postOrder() {
  std::vector<T> values;
  postOrder(&values, m_Root);
  return values;
}

template <typename T>
void BinarySearchTree<T>::inOrder(std::vector<T>* values,
                                  BinaryTreeNode<T>* node) {
  if (!node) {
    return;
  }
  inOrder(values, node->getLeft());
  values->push_back(node->getValue());
  inOrder(values, node->getRight());
}

template <typename T>
void BinarySearchTree<T>::preOrder(std::vector<T>* values,
                                   BinaryTreeNode<T>* node) {
  if (!node) {
    return;
  }
  values->push_back(node->getValue());
  preOrder(values, node->getLeft());
  preOrder(values, node->getRight());
}

template <typename T>
void BinarySearchTree<T>::postOrder(std::vector<T>* values,
                                    BinaryTreeNode<T>* node) {
  if (!node) {
    return;
  }
  postOrder(values, node->getLeft());
  postOrder(values, node->getRight());
  values->push_back(node->getValue());
}
