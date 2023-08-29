#include <gtest/gtest.h>

#include "DataStructures/Stack.hpp"

TEST(StackTest, CreateEmptyStack) {
  Stack<int> stack;
  ASSERT_EQ(stack.size(), 0);
  ASSERT_TRUE(stack.empty());
}

TEST(StackTest, PeekEmptyStack) {
  Stack<int> stack;

  EXPECT_THROW(
      {
        try {
          stack.peek();
        } catch (const std::out_of_range& e) {
          ASSERT_STREQ("Stack is empty!", e.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST(StackTest, PopEmptyStack) {
  Stack<int> stack;

  EXPECT_THROW(
      {
        try {
          stack.pop();
        } catch (const std::out_of_range& e) {
          ASSERT_STREQ("Stack is empty!", e.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST(StackTest, InsertElements) {
  Stack<int> stack;
  for (int i{1}; i < 1000; ++i) {
    stack.insert(i);
    ASSERT_EQ(stack.size(), i);
    ASSERT_EQ(stack.peek(), i);
  }
}

TEST(StackTest, PopElements) {
  Stack<int> stack;
  for (int i{1}; i < 1000; ++i) {
    stack.insert(i);
  }
  for (int i{999}; i > 0; --i) {
    ASSERT_EQ(stack.peek(), i);
    stack.pop();
  }
  ASSERT_TRUE(stack.empty());
}
