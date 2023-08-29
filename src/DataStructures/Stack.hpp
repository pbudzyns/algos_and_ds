#pragma once

#include "DataStructures/DynamicArray.hpp"

/**
 * @brief Template for stack container.
 *
 * @details Stack implementation using DynamicArray as an underlying container.
 * Stacks allows to push an item to the top, access and remove top item in
 * constant time `O(1)`.
 *
 * Example usage:
 * @code
 * Stack<int> stack;
 * stack.insert(1);
 * stack.insert(2);
 * stack.peek(); // == 2
 * stack.pop();
 * stack.peek(); // == 1
 * @endcode
 *
 * @tparam T Type of the stored values.
 */
template <typename T>
class Stack {
 public:
  /**
   * @brief Type used for indexing and size definition.
   *
   */
  typedef typename DynamicArray<T>::size_type size_type;

  /**
   * @brief Construct a new Stack object.
   *
   */
  Stack() = default;

  /**
   * @brief Destroy the Stack object.
   *
   */
  ~Stack() = default;

  /**
   * @brief Push an item to the Stack.
   *
   * @param item Item to be pushed.
   */
  void insert(const T& item) { m_Data.insert(item); }

  /**
   * @brief Removes top item from the Stack.
   *
   */
  void pop() {
    if (empty()) {
      throw std::out_of_range("Stack is empty!");
    }
    m_Data.remove(size() - 1);
  }

  /**
   * @brief Access item from the top of the Stack.
   *
   * @return `T&` Referece to the item on the top.
   */
  T& peek() {
    if (empty()) {
      throw std::out_of_range("Stack is empty!");
    }
    return m_Data[size() - 1];
  }

  /**
   * @brief Get size of the Stack.
   *
   * @return `size_type` Number of items in the stack.
   */
  size_type size() const { return m_Data.size(); }

  /**
   * @brief Check if Stack is empty.
   *
   * @return `true` If stack is empty.
   * @return `false` If stack contains any items.
   */
  bool empty() const { return size() == 0; }

 private:
  DynamicArray<T> m_Data;
};
