#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

template <typename T>
class DynamicArray {
 public:
  typedef uint32_t size_type;

  DynamicArray() : m_Size{0}, m_Capacity{2}, m_Data{std::make_unique<T[]>(2)} {}
  ~DynamicArray() = default;

  void insert(T element);
  void remove(size_type index);

  T& operator[](size_type index) { return get(index); }
  const T& operator[](size_type index) const { return get(index); }

  T& get(size_type index);
  const T& get(size_type index) const;

  inline size_type size() const { return m_Size; }
  inline size_type capacity() const { return m_Capacity; }

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

  memcpy(newData.get(), m_Data.get(), m_Size * sizeof(T));

  m_Data = std::move(newData);
  m_Capacity = newCapacity;
}
