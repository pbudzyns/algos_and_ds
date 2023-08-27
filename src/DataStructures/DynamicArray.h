#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

using size_type = uint32_t;

template <typename T>
class DynamicArray {
 public:
  DynamicArray() : DynamicArray(2) {}

  explicit DynamicArray(size_type capacity)
      : m_Size{0},
        m_Capacity{capacity},
        m_Data{std::make_unique<T[]>(capacity)} {}

  ~DynamicArray() = default;

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
    if (m_Size < (m_Capacity / 2)) {
      resize(m_Capacity / 2);
    }
  }

  const T& operator[](size_type index) const { return m_Data[index]; }

  T& get(size_type index) { return m_Data[index]; }

  inline size_type size() const { return m_Size; }

  inline size_type capacity() const { return m_Capacity; }

 private:
  std::unique_ptr<T[]> m_Data;
  size_type m_Size;
  size_type m_Capacity;

  void resize(size_type newCapacity) {
    std::unique_ptr<T[]> newData = std::make_unique<T[]>(newCapacity);

    memcpy(newData.get(), m_Data.get(), m_Size * sizeof(T));

    m_Data = std::move(newData);
    m_Capacity = newCapacity;
  }
};
