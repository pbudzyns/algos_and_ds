#include <gtest/gtest.h>

#include "DataStructures/Heap.hpp"

TEST(HeapTest, CreateEmptyHeap) {
  Heap<int> heap;
  ASSERT_EQ(heap.size(), 0);
  ASSERT_TRUE(heap.empty());
}

TEST(HeapTest, InsertElements) {
  Heap<int> heap;
  int n = 1000;
  for (int i{n}; i > 0; --i) {
    ASSERT_EQ(heap.size(), n - i);
    heap.insert(i);
    ASSERT_EQ(heap.peek(), i);
  }
}

TEST(HeapTest, PopElements) {
  Heap<int> heap;
  int n = 1000;
  for (int i{0}; i < n; ++i) {
    heap.insert(i);
  }
  for (int i{0}; i < n; ++i) {
    ASSERT_EQ(heap.size(), n - i);
    ASSERT_EQ(heap.peek(), i);
    heap.pop();
  }
  ASSERT_TRUE(heap.empty());
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
  ASSERT_TRUE(heap.empty());
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

TEST(HeapTest, CustomCompareFunction) {
  Heap<int> maxHeap([](int a, int b) { return a > b; });
  maxHeap.insert(1);
  ASSERT_EQ(maxHeap.peek(), 1);
  maxHeap.insert(3);
  ASSERT_EQ(maxHeap.peek(), 3);
  maxHeap.insert(2);
  ASSERT_EQ(maxHeap.peek(), 3);
  maxHeap.insert(5);
  ASSERT_EQ(maxHeap.peek(), 5);
  maxHeap.pop();
  ASSERT_EQ(maxHeap.peek(), 3);
  maxHeap.pop();
  ASSERT_EQ(maxHeap.peek(), 2);
  maxHeap.pop();
  ASSERT_EQ(maxHeap.peek(), 1);
  maxHeap.pop();
  ASSERT_TRUE(maxHeap.empty());
}
