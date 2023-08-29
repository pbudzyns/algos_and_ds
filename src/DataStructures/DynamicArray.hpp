#pragma once

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <string>
#include <utility>

/**
 * @brief Template for dynamic array container class.
 * @details Dynamic array is a container that dynamically allocates or
 * deallocates memory depending on the number of elements inserted.
 * It allows for access to its elements in constant time `O(1)`. Insert and
 * delete works with `O(n)` complexity.
 *
 * Example usage:
 * @code
 * DynamicArray<int> dynamicArray;
 * dynamicArray.insert(1);
 * int b{dynamicArray[0]};
 * @endcode
 *
 * @tparam T Type of the stored values.
 */
template <typename T>
class DynamicArray {
 public:
  /**
   * @brief Type used for indexing and size definition.
   */
  typedef uint32_t size_type;

  /**
   * @brief Default constructor.
   */
  DynamicArray() : m_Size{0}, m_Capacity{2}, m_Data{std::make_unique<T[]>(2)} {}

  /**
   * @brief Default destructor.
   */
  ~DynamicArray() = default;

  /**
   * @brief Inserts element to the array.
   * @details Allocates additional memory and copy array to new location if
   * size equals capacity.
   * @param element The element to be inserted.
   */
  void insert(T element);

  /**
   * @brief Remove element at an index from the array.
   * @details Reduces container capacity if the container becomes half empty.
   * @param index Index of the element to remove.
   */
  void remove(size_type index);

  /**
   * @brief Access element at given index.
   * @param index Index of the element to access.
   * @return Reference to stored value.
   */
  T& operator[](size_type index) { return get(index); }

  /**
   * @brief Access element at given index.
   * @param index Index of the element to access.
   * @return Const reference to stored value.
   */
  const T& operator[](size_type index) const { return get(index); }

  /**
   * @brief Access element at given index.
   * @param index Index of the element to access.
   * @return Reference to stored value.
   */
  T& get(size_type index);

  /**
   * @brief Access element at given index.
   * @param index Index of the element to access.
   * @return Const reference to stored value.
   */
  const T& get(size_type index) const;

  /**
   * @brief Get number of items in the container.
   * @return Number of stored items.
   */
  inline size_type size() const { return m_Size; }

  /**
   * @brief Get capacity of the container.
   * @return Capacity of the container.
   */
  inline size_type capacity() const { return m_Capacity; }

  /**
   * @brief Test if container is empty.
   * @return `true` if empty.
   */
  inline bool empty() const { return m_Size == 0; }

 private:
  size_type m_Size;
  size_type m_Capacity;
  std::unique_ptr<T[]> m_Data;
  void resize(size_type newCapacity);
};

template <typename T>
void DynamicArray<T>::insert(T element) {
  if (m_Size == m_Capacity) resize(m_Capacity * 2);
  m_Data[m_Size++] = element;
}

template <typename T>
void DynamicArray<T>::remove(size_type index) {
  if (index >= m_Size) throw std::out_of_range("Index out of range!");

  --m_Size;
  while (index < m_Size) {
    m_Data[index] = m_Data[index + 1];
    ++index;
  }
  if (m_Size < (m_Capacity / 2)) {
    resize(m_Capacity / 2);
  }
}

template <typename T>
T& DynamicArray<T>::get(size_type index) {
  return const_cast<T&>(const_cast<const DynamicArray*>(this)->get(index));
}

template <typename T>
const T& DynamicArray<T>::get(size_type index) const {
  if (index >= m_Size) throw std::out_of_range("Index out of range!");

  return m_Data[index];
}

template <typename T>
void DynamicArray<T>::resize(size_type newCapacity) {
  std::unique_ptr<T[]> newData = std::make_unique<T[]>(newCapacity);

  memcpy(newData.get(), m_Data.get(),
         static_cast<std::size_t>(m_Size) * sizeof(T));

  m_Data = std::move(newData);
  m_Capacity = newCapacity;
}
