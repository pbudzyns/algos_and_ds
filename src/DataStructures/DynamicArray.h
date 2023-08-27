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
  void insert(T element) { m_Data[m_Size++] = element; }

  const T& operator[](size_type index) const { return m_Data[index]; }
  T& get(size_type index) { return m_Data[index]; }

  inline size_type size() const { return m_Size; }
  inline size_type capacity() const { return m_Capacity; }

 private:
  T* m_Data;
  size_type m_Size;
  size_type m_Capacity;
};
