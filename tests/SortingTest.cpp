#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <vector>

#include "Algorithms/Sorting.hpp"

std::vector<int> getRandomOrderedNumbers(int start, int n) {
  static std::random_device rd;
  static std::mt19937 g(rd());
  std::vector<int> numbers(n);
  std::iota(numbers.begin(), numbers.end(), start);
  std::shuffle(numbers.begin(), numbers.end(), g);
  return numbers;
}

TEST(SortingTest, TestBubbleSort) {
  int start{-500};
  int n{1000};
  std::vector<int> numbers{getRandomOrderedNumbers(start, n)};

  sort::bubbleSort(numbers.data(), n);

  for (int i{0}; i < n; ++i) {
    ASSERT_EQ(numbers[i], i + start);
  }
}

TEST(SortingTest, TestSelectionSort) {
  int start{-500};
  int n{1000};
  std::vector<int> numbers{getRandomOrderedNumbers(start, n)};

  sort::selectionSort(numbers.data(), n);

  for (int i{0}; i < n; ++i) {
    ASSERT_EQ(numbers[i], i + start);
  }
}

TEST(SortingTest, TestMergeSort) {
  int start{0};
  int n{10};
  std::vector<int> numbers{getRandomOrderedNumbers(start, n)};

  sort::mergeSort(numbers.data(), n);

  for (int i{0}; i < n; ++i) {
    ASSERT_EQ(numbers[i], i + start);
  }
}
