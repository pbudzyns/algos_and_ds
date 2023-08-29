#include <gtest/gtest.h>

#include "DataStructures/Heap.hpp"

TEST(HeapTest, CreateEmptyHeap) {
  Heap<int> heap;
  ASSERT_EQ(heap.size(), 0);
  ASSERT_TRUE(heap.empty());
}

TEST(HeapTest, InsertElements) {
  Heap<int> heap;
  ASSERT_EQ(heap.size(), 0);
  heap.insert(1);
  heap.insert(2);
  heap.insert(3);
  heap.insert(4);
  ASSERT_EQ(heap.size(), 4);
}

TEST(HeapTest, GetPeek) {
  Heap<int> heap;
  heap.insert(1);
  heap.insert(2);
  heap.insert(3);
  heap.insert(4);
  ASSERT_EQ(heap.peek(), 1);
}

TEST(HeapTest, InsertPutsMinOnPeek) {
  Heap<int> heap;
  heap.insert(4);
  ASSERT_EQ(heap.peek(), 4);
  heap.insert(3);
  ASSERT_EQ(heap.peek(), 3);
  heap.insert(5);
  ASSERT_EQ(heap.peek(), 3);
  heap.insert(-1);
  ASSERT_EQ(heap.peek(), -1);
  heap.insert(0);
  ASSERT_EQ(heap.peek(), -1);
}

TEST(HeapTest, PopItem) {
  Heap<int> heap;
  heap.insert(4);
  heap.insert(3);
  heap.insert(2);
  heap.insert(1);
  ASSERT_EQ(heap.size(), 4);
  heap.pop();
  ASSERT_EQ(heap.size(), 3);
  heap.pop();
  ASSERT_EQ(heap.size(), 2);
  heap.pop();
  ASSERT_EQ(heap.size(), 1);
  heap.pop();
  ASSERT_EQ(heap.size(), 0);
}

TEST(HeapTest, PopItemPreservesMinPeek) {
  Heap<int> heap;
  heap.insert(4);
  heap.insert(3);
  heap.insert(2);
  heap.insert(1);
  ASSERT_EQ(heap.peek(), 1);
  heap.pop();
  ASSERT_EQ(heap.peek(), 2);
  heap.pop();
  ASSERT_EQ(heap.peek(), 3);
  heap.pop();
  ASSERT_EQ(heap.peek(), 4);
}

TEST(HeapTest, PeekEmptyHeap) {
  Heap<int> heap;

  EXPECT_THROW(
      {
        try {
          heap.peek();
        } catch (const std::out_of_range& e) {
          ASSERT_STREQ("Heap is empty!", e.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST(HeapTest, PopEmptyHeap) {
  Heap<int> heap;

  EXPECT_THROW(
      {
        try {
          heap.pop();
        } catch (const std::out_of_range& e) {
          ASSERT_STREQ("Heap is empty!", e.what());
          throw;
        }
      },
      std::out_of_range);
}
