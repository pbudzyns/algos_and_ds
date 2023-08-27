#pragma once

#include <cstdint>
#include <string>

using size_type = uint32_t;

template <typename T>
class DynamicArray {
 public:
  DynamicArray() : m_Capacity{0}, m_Size{0}, m_Data{nullptr} {}
  explicit DynamicArray(size_type capacity)
      : m_Size{0}, m_Capacity{capacity}, m_Data{new T[capacity]} {}
  ~DynamicArray() { delete[] m_Data; }

  void insert(T element) {
    if (m_Size == m_Capacity) resize(m_Capacity * 2);
    m_Data[m_Size++] = element;
  }
  void remove(size_type index) {
    if (index >= m_Size) throw std::out_of_range("Index out of range.");

    --m_Size;
    while (index < m_Size) {
      m_Data[index] = m_Data[index + 1];
      ++index;
    }
  }

  // 0 1 2 3 4 5 - size=6
  // 0 1 2       - size=5
  const T& operator[](size_type index) const { return m_Data[index]; }
  T& get(size_type index) { return m_Data[index]; }

  inline size_type size() const { return m_Size; }
  inline size_type capacity() const { return m_Capacity; }

 private:
  T* m_Data;
  size_type m_Size;
  size_type m_Capacity;

  void resize(size_type newCapacity) {
    T* newData = new T[newCapacity];

    memcpy(newData, m_Data, m_Size * sizeof(T));
    delete[] m_Data;
    m_Data = newData;
    m_Capacity = newCapacity;
  }
};
