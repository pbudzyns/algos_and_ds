#pragma once

#include <cstdint>
#include <memory>
#include <utility>

#include "DataStructures/DynamicArray.hpp"

template <typename T>
class Heap {
 public:
  typedef typename DynamicArray<T>::size_type size_type;
  Heap() = default;
  ~Heap() = default;

  T peek();

  void pop();
  void insert(const T& item);

  inline bool empty() const { return m_Data.empty(); }

  size_type size() const { return m_Data.size(); }

 private:
  DynamicArray<T> m_Data;

  inline size_type getLeftChild(size_type index) const { return 2 * index + 1; }
  inline size_type getRightChild(size_type index) const {
    return 2 * index + 2;
  }
  inline size_type getParent(size_type index) const { return (index - 1) / 2; }

  void swap(T* first, T* second);
  void heapify(size_type index);
};

template <typename T>
void Heap<T>::insert(const T& item) {
  m_Data.insert(item);
  size_type idx{m_Data.size() - 1};

  while (idx != 0 && m_Data[idx] < m_Data[getParent(idx)]) {
    swap(&m_Data[idx], &m_Data[getParent(idx)]);
    idx = getParent(idx);
  }
}

template <typename T>
void Heap<T>::pop() {
  if (empty()) {
    throw std::out_of_range("Heap is empty!");
  }

  m_Data[0] = m_Data[m_Data.size() - 1];
  m_Data.remove(m_Data.size() - 1);

  heapify(0);
}

template <typename T>
T Heap<T>::peek() {
  if (empty()) {
    throw std::out_of_range("Heap is empty!");
  }
  return m_Data[0];
}

template <typename T>
void Heap<T>::swap(T* first, T* second) {
  T tmp = *first;
  *first = *second;
  *second = tmp;
}

template <typename T>
void Heap<T>::heapify(size_type index) {
  size_type leftChildIdx{getLeftChild(index)};
  size_type rightChildIdx{getRightChild(index)};
  size_type minNodeIdx{index};

  if (leftChildIdx < size() && m_Data[leftChildIdx] < m_Data[minNodeIdx]) {
    minNodeIdx = leftChildIdx;
  }
  if (rightChildIdx < size() && m_Data[rightChildIdx] < m_Data[minNodeIdx]) {
    minNodeIdx = rightChildIdx;
  }
  if (minNodeIdx != index) {
    swap(&m_Data[index], &m_Data[minNodeIdx]);
    heapify(minNodeIdx);
  }
}
