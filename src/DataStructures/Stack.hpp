#pragma once

#include "DataStructures/DynamicArray.hpp"

template <typename T>
class Stack {
 public:
  typedef typename DynamicArray<T>::size_type size_type;

  Stack() = default;
  ~Stack() = default;

  void insert(const T& item) { m_Data.insert(item); }

  void pop() {
    if (empty()) {
      throw std::out_of_range("Stack is empty!");
    }
    m_Data.remove(size() - 1);
  }

  T& peek() {
    if (empty()) {
      throw std::out_of_range("Stack is empty!");
    }
    return m_Data[size() - 1];
  }

  size_type size() const { return m_Data.size(); }

  bool empty() const { return size() == 0; }

 private:
  DynamicArray<T> m_Data;
};
