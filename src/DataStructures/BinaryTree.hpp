#pragma once

#include <cstdint>
#include <vector>

namespace _bst_impl {

/**
 * @brief Binary Tree Node template.
 *
 * @details Stores a value and pointers to left and right childs.
 *
 * @tparam T Type of the stored value.
 */
template <typename T>
class BinaryTreeNode {
 public:
  /**
   * @brief Construct a new BinaryTreeNode object.
   *
   */
  BinaryTreeNode() : m_Left{nullptr}, m_Right{nullptr}, m_Value{} {}

  /**
   * @brief Construct a new BinaryTreeNode object.
   *
   * @param value Value to store in the node.
   */
  explicit BinaryTreeNode(const T& value)
      : m_Value{value}, m_Left{nullptr}, m_Right{nullptr} {}

  /**
   * @brief Destroy the BinaryTreeNode object.
   *
   */
  ~BinaryTreeNode() = default;

  /**
   * @brief Set the pointer to right child.
   *
   * @param node Pointer to right child node.
   */
  void setRight(BinaryTreeNode* node) { m_Right = node; }

  /**
   * @brief Set the pointer to left child.
   *
   * @param node Pointer to left child node.
   */
  void setLeft(BinaryTreeNode* node) { m_Left = node; }

  /**
   * @brief Set the value stored in the node.
   *
   * @param value Value to store.
   */
  void setValue(const T& value) { m_Value = value; }

  /**
   * @brief Get the pointer to right child node.
   *
   * @return `BinaryTreeNode*` Pointer to right child node.
   */
  BinaryTreeNode* getRight() const { return m_Right; }

  /**
   * @brief Get the pointer to left child node.
   *
   * @return `BinaryTreeNode*` Pointer to left child node.
   */
  BinaryTreeNode* getLeft() const { return m_Left; }

  /**
   * @brief Get the value stored in the node.
   *
   * @return `T&` Value reference.
   */
  T& getValue() { return m_Value; }

  /**
   * @brief Get the value stored in the node.
   *
   * @return `const T&` Const value reference.
   */
  const T& getValue() const { return m_Value; }

 private:
  T m_Value;
  BinaryTreeNode* m_Left;
  BinaryTreeNode* m_Right;
};
}  // namespace _bst_impl

/**
 * @brief Template for binary search tree container.
 *
 * @details Binary search tree implemented with linked nodes. The binary search
 * tree always inserts new node with value smaller than current node in the
 * left. It allows for checking if an item is present in `O(log n)` time. This
 * binary search tree class contains simple rebalancing implementation that
 * takes `O(n)` time and extra `O(n)` space.
 *
 * Example usage:
 * @code
 * BinarySearchTree<int> bst;
 * bst.insert(1);
 * bst.insert(2);
 * bst.insert(3);
 * bst.inOrder(); // == std::vector<int>{1, 2, 3}
 * @endcode
 *
 *
 * @tparam T Type of stored items.
 */
template <typename T>
class BinarySearchTree {
 public:
  /**
   * @brief Type used for indexing and size definition.
   *
   */
  typedef uint32_t size_type;

  /**
   * @brief Construct a new BinarySearchTree object.
   *
   */
  BinarySearchTree() : m_Root{nullptr}, m_Size{0} {}

  /**
   * @brief Construct a new BinarySearchTree object.
   *
   * @details Inserts provided values to the tree.
   *
   * @param values Vector of values to insert.
   */
  explicit BinarySearchTree(const std::vector<T>& values)
      : m_Root{nullptr}, m_Size{0} {
    for (const auto& value : values) {
      insert(value);
    }
  }

  /**
   * @brief Destroy the BinarySearchTree object.
   *
   */
  ~BinarySearchTree() { deleteTree(); }

  /**
   * @brief Insert value to the tree.
   *
   * @details Should take `O(log n)` time.
   *
   * @param value Value to insert.
   */
  void insert(const T& value) {
    m_Root = insert(value, m_Root);
    ++m_Size;
  }

  /**
   * @brief Remove value from the tree.
   *
   * @param value Value to remove.
   */
  void remove(const T& value);

  /**
   * @brief Rebalance the tree.
   *
   * @details Uses naive approach to rebalance the tree. Retrieves all values
   * from the tree using in order traversal and inserts them in a way that
   * creates balanced tree. Takes `O(n)` time and `O(n)` extra space.
   */
  void rebalance();

  /**
   * @brief Check if tree contains a value.
   *
   * @param value Value to check.
   * @return `true` If tree contains the value.
   * @return `false` If tree does not contain the value.
   */
  bool contains(const T& value) const;

  /**
   * @brief Performs in order traversal and returns vector of values.
   *
   * @details Visit nodes recursively in left-root-right manner.
   *
   * @return `std::vector<T>` Vector of values ordered in-order.
   */
  std::vector<T> inOrder();

  /**
   * @brief Performs in pre traversal and returns vector of values.
   *
   * @details Visit nodes recursively in root-left-right manner.
   *
   * @return `std::vector<T>` Vector of values ordered pre-order.
   */
  std::vector<T> preOrder();

  /**
   * @brief Performs in post traversal and returns vector of values.
   *
   * @details Visit nodes recursively in left-right-root manner.
   *
   * @return `std::vector<T>` Vector of values ordered post-order.
   */
  std::vector<T> postOrder();

  /**
   * @brief Get the size of the tree.
   *
   * @return `size_type` Number of items in the tree.
   */
  size_type getSize() { return m_Size; }

  /**
   * @brief Get the root node.
   *
   * @return `const _bst_impl::BinaryTreeNode<T>*` Const pointer to the root
   * node.
   */
  const _bst_impl::BinaryTreeNode<T>* getRoot() const { return m_Root; }

 private:
  size_type m_Size;
  _bst_impl::BinaryTreeNode<T>* m_Root;

  _bst_impl::BinaryTreeNode<T>* insert(const T& value,
                                       _bst_impl::BinaryTreeNode<T>* node);

  bool contains(const T& value, _bst_impl::BinaryTreeNode<T>* node) const;

  void inOrder(std::vector<T>* values, _bst_impl::BinaryTreeNode<T>* node);
  void preOrder(std::vector<T>* values, _bst_impl::BinaryTreeNode<T>* node);
  void postOrder(std::vector<T>* values, _bst_impl::BinaryTreeNode<T>* node);

  void deleteTree();
  void deleteNode(_bst_impl::BinaryTreeNode<T>* node);

  _bst_impl::BinaryTreeNode<T>* fromSortedArray(const T* array, int start,
                                                int end);
};

// ------ Binary Search Tree Implementation -------

using _bst_impl::BinaryTreeNode;

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
bool BinarySearchTree<T>::contains(const T& value) const {
  return contains(value, m_Root);
}

template <typename T>
bool BinarySearchTree<T>::contains(const T& value,
                                   BinaryTreeNode<T>* node) const {
  if (!node) {
    return false;
  }

  if (node->getValue() == value) {
    return true;
  }

  if (node->getValue() > value) {
    return contains(value, node->getLeft());
  } else {
    return contains(value, node->getRight());
  }
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

template <typename T>
void BinarySearchTree<T>::rebalance() {
  if (m_Size == 0) {
    return;
  }
  std::vector<T> sortedValues{inOrder()};
  BinaryTreeNode<T>* balancedTree{
      fromSortedArray(sortedValues.data(), 0, sortedValues.size() - 1)};

  deleteTree();
  m_Root = balancedTree;
}

template <typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::fromSortedArray(const T* array,
                                                        int start, int end) {
  if (start > end) {
    return nullptr;
  }

  int mid{(start + end) / 2};
  BinaryTreeNode<T>* node = new BinaryTreeNode<T>(array[mid]);
  node->setLeft(fromSortedArray(array, start, mid - 1));
  node->setRight(fromSortedArray(array, mid + 1, end));
  return node;
}

template <typename T>
void BinarySearchTree<T>::deleteTree() {
  deleteNode(m_Root);
}

template <typename T>
void BinarySearchTree<T>::deleteNode(BinaryTreeNode<T>* node) {
  if (!node) {
    return;
  }
  deleteNode(node->getLeft());
  deleteNode(node->getRight());
  delete node;
}
