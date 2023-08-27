#include <gtest/gtest.h>

#include <numeric>
#include <vector>

#include "DynamicArray.h"

template <typename T>
bool compareToVector(const DynamicArray<T>& array, const std::vector<T>& vec) {
  if (array.size() != static_cast<size_type>(vec.size())) return false;

  for (size_type i{0}; i < array.size(); ++i) {
    if (array[i] != vec[static_cast<typename std::vector<T>::size_type>(i)])
      return false;
  }
  return true;
}

TEST(DynamicArrayTest, GetElement) {
  DynamicArray<int> array(2);
  array.insert(1);
  array.insert(2);
  ASSERT_EQ(array.get(0), 1);
  ASSERT_EQ(array.get(1), 2);
}

TEST(DynamicArrayTest, GetElementOperator) {
  DynamicArray<int> array(2);
  array.insert(1);
  array.insert(2);
  ASSERT_EQ(array[0], 1);
  ASSERT_EQ(array[1], 2);
}

TEST(DynamicArrayTest, GetSize) {
  DynamicArray<int> array(2);
  ASSERT_EQ(array.size(), 0);
  array.insert(1);
  ASSERT_EQ(array.size(), 1);
  array.insert(2);
  ASSERT_EQ(array.size(), 2);
}

TEST(DynamicArrayTest, RemoveMiddleElement) {
  DynamicArray<int> array(10);
  std::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i{0}; i < 10; ++i) array.insert(i);
  ASSERT_TRUE(compareToVector(array, vec));
  array.remove(3);
  vec = {0, 1, 2, 4, 5, 6, 7, 8, 9};
  ASSERT_TRUE(compareToVector(array, vec));
}

TEST(DynamicArrayTest, RemoveLastElement) {
  DynamicArray<int> array(10);
  std::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i{0}; i < 10; ++i) array.insert(i);
  ASSERT_TRUE(compareToVector(array, vec));
  array.remove(9);
  vec = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_TRUE(compareToVector(array, vec));
}

TEST(DynamicArrayTest, DynamicResizeUp) {
  DynamicArray<int> array(2);
  ASSERT_EQ(array.capacity(), 2);
  int n{100000};
  for (int i{0}; i < n; ++i) {
    array.insert(i);
  }
  ASSERT_GE(array.capacity(), n);
  std::vector<int> vec(n);
  std::iota(vec.begin(), vec.end(), 0);
  ASSERT_TRUE(compareToVector(array, vec));
}

TEST(DynamicArrayTest, DynamicResizeDown) {
  DynamicArray<int> array;
  int n{1000};
  for (int i{0}; i < n; ++i) {
    array.insert(i);
  }
  ASSERT_GE(array.capacity(), n);
  for (int i{0}; i < n / 2 + 1; ++i) array.remove(1);
  ASSERT_EQ(array.capacity(), 512);
}
