#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <vector>

#include "Algorithms/Sorting.hpp"

const int MIN_VAL{-5000};
const int N_VAL{10000};

std::vector<int> getRandomOrderedNumbers(int start, int n) {
  static std::random_device rd;
  static std::mt19937 g(rd());
  std::vector<int> numbers(n);
  std::iota(numbers.begin(), numbers.end(), start);
  std::shuffle(numbers.begin(), numbers.end(), g);
  return numbers;
}

TEST(SortingTest, TestBubbleSort) {
  int start{MIN_VAL};
  int n{N_VAL};
  std::vector<int> numbers{getRandomOrderedNumbers(start, n)};

  sort::bubbleSort(numbers.data(), n);

  for (int i{0}; i < n; ++i) {
    ASSERT_EQ(numbers[i], i + start);
  }
}

TEST(SortingTest, TestSelectionSort) {
  int start{MIN_VAL};
  int n{N_VAL};
  std::vector<int> numbers{getRandomOrderedNumbers(start, n)};

  sort::selectionSort(numbers.data(), n);

  for (int i{0}; i < n; ++i) {
    ASSERT_EQ(numbers[i], i + start);
  }
}

TEST(SortingTest, TestMergeSort) {
  int start{MIN_VAL};
  int n{N_VAL};
  std::vector<int> numbers{getRandomOrderedNumbers(start, n)};

  sort::mergeSort(numbers.data(), n);

  for (int i{0}; i < n; ++i) {
    ASSERT_EQ(numbers[i], i + start);
  }
}

TEST(SortingTest, TestQuickSort) {
  int start{MIN_VAL};
  int n{N_VAL};
  std::vector<int> numbers{getRandomOrderedNumbers(start, n)};

  sort::quickSort(numbers.data(), n);

  for (int i{0}; i < n; ++i) {
    ASSERT_EQ(numbers[i], i + start);
  }
}

TEST(SortingTest, HeapSort) {
  int start{MIN_VAL};
  int n{N_VAL};
  std::vector<int> numbers{getRandomOrderedNumbers(start, n)};

  sort::heapSort(numbers.data(), n);

  for (int i{0}; i < n; ++i) {
    ASSERT_EQ(numbers[i], i + start);
  }
}
