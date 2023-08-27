#include <gtest/gtest.h>

#include "DynamicArray.h"

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
