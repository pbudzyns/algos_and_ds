#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>

#include "DataStructures/DynamicArray.hpp"

/**
 * @brief Template for heap container.
 *
 * @details Heap implementation using DynamicArray as an underlying container.
 * Heap is a complete binary tree that allows to retrieve minimum (MinHeap) or
 * maximum (MaxHeap) in constant time `O(1)`. Inserting and deleting elements
 * from Heap take `O(log n)` time.
 *
 * Types stored in the Heap should implement compare operators (at least `<` for
 * default implementation).
 *
 * By default this template creates MinHeap. To create MaxHeap provide proper
 * comparison function to the constructor.
 *
 * Example usage:
 * @code
 * Heap<int> heap;
 * heap.insert(2);
 * heap.peek(); // == 2
 * heap.insert(1);
 * heap.peek(); // == 1
 * @endcode
 *
 * @code
 * // Use custom comparator to create MaxHeap.
 * Heap<int> maxHeap([](int a, int b) { return a > b; });
 * maxHeap.insert(1);
 * maxHeap.peek(); // == 1
 * maxHeap.insert(2);
 * maxHeap.peek(); // == 2
 * @endcode
 *
 * @tparam T Type of the stored values.
 */
template <typename T>
class Heap {
 public:
  /**
   * @brief Type used for indexing and size definition.
   *
   */
  typedef typename DynamicArray<T>::size_type size_type;

  /**
   * @brief Construct a new Heap object.
   *
   */
  Heap() = default;

  /**
   * @brief Construct a new Heap object with custom compare function.
   *
   * @details Can be used to create max heap or custom implementations.
   *
   * @param compare Compare function.
   */
  explicit Heap(std::function<bool(const T& a, const T& b)> compare)
      : m_Cmp{compare} {};

  /**
   * @brief Destroy the Heap object.
   *
   */
  ~Heap() = default;

  /**
   * @brief Access item on the top of the Heap.
   *
   * @return `T&` Referece to the item on the top.
   */
  T& peek();

  /**
   * @brief Removes top item from the Heap (minimum by default).
   *
   */
  void pop();

  /**
   * @brief Insert and item to the Heap.
   *
   * @param item Item to be inserted.
   */
  void insert(const T& item);

  /**
   * @brief Check if the Heap is empty.
   *
   * @return `true` If the heap is empty.
   * @return `false` If heap contains any items.
   */
  inline bool empty() const { return m_Data.empty(); }

  /**
   * @brief Get size of the Heap.
   *
   * @return `size_type` Number of items in the heap.
   */
  size_type size() const { return m_Data.size(); }

 private:
  DynamicArray<T> m_Data;

  const std::function<bool(const T& a, const T& b)> m_Cmp{
      [](const T& a, const T& b) { return a < b; }};

  size_type getLeftChild(size_type index) const { return 2 * index + 1; }
  size_type getRightChild(size_type index) const { return 2 * index + 2; }
  size_type getParent(size_type index) const { return (index - 1) / 2; }

  void swap(T* first, T* second);
  void heapify(size_type index);
};

template <typename T>
void Heap<T>::insert(const T& item) {
  m_Data.insert(item);
  size_type idx{m_Data.size() - 1};

  while (idx != 0 && m_Cmp(m_Data[idx], m_Data[getParent(idx)])) {
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
T& Heap<T>::peek() {
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

  if (leftChildIdx < size() &&
      m_Cmp(m_Data[leftChildIdx], m_Data[minNodeIdx])) {
    minNodeIdx = leftChildIdx;
  }
  if (rightChildIdx < size() &&
      m_Cmp(m_Data[rightChildIdx], m_Data[minNodeIdx])) {
    minNodeIdx = rightChildIdx;
  }
  if (minNodeIdx != index) {
    swap(&m_Data[index], &m_Data[minNodeIdx]);
    heapify(minNodeIdx);
  }
}
