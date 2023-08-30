#include "Algorithms/Sorting.hpp"

void sort::swapElements(int* first, int* second) {
  int tmp = *first;
  *first = *second;
  *second = tmp;
}

void sort::bubbleSort(int* numbers, int n) {
  for (int i{0}; i < n - 1; ++i) {
    for (int j{i + 1}; j < n; ++j) {
      // Swap numbers if i-th is larger than j-th
      if (numbers[i] > numbers[j]) {
        swapElements(&numbers[i], &numbers[j]);
      }
    }
  }
}

void sort::selectionSort(int* numbers, int n) {
  int smallest_idx;
  for (int i{0}; i < n - 1; ++i) {
    smallest_idx = i;
    for (int j{i + 1}; j < n; ++j) {
      // Scan searching for the smallest number.
      if (numbers[smallest_idx] > numbers[j]) {
        smallest_idx = j;
      }
    }
    if (smallest_idx != i) {
      // Insert the value in the correct place.
      swapElements(&numbers[i], &numbers[smallest_idx]);
    }
  }
}

static void mergeSort(int* numbers, int* helper, int low, int high);
static void merge(int* numbers, int* helper, int low, int middle, int high);

void sort::mergeSort(int* numbers, int n) {
  int* helper{new int[n]};
  ::mergeSort(numbers, helper, 0, n - 1);
  delete[] helper;
}

static void mergeSort(int* numbers, int* helper, int low, int high) {
  if (low >= high) {
    return;
  }
  int middle{low + (high - low) / 2};
  mergeSort(numbers, helper, low, middle);
  mergeSort(numbers, helper, middle + 1, high);
  merge(numbers, helper, low, middle, high);
}

static void merge(int* numbers, int* helper, int low, int middle, int high) {
  // Copy content of the array to helper array.
  // Nomally, left and right subarrays would be created. Left of range
  // [low,middle], right of range [middle+1,high]. Helper array allows to skip
  // creating additional arrays in mergeSort functions so the algorithm takes
  // O(n) extra space.
  for (int i{low}; i <= high; ++i) {
    helper[i] = numbers[i];
  }

  int left{low};
  int right{middle + 1};
  int current{low};

  while (left <= middle && right <= high) {
    if (helper[left] <= helper[right]) {
      numbers[current++] = helper[left++];
    } else {
      numbers[current++] = helper[right++];
    }
  }

  // Copy the leftovers from the left side.
  // No need to copy from the right size because it's already there
  // helper content was taken from numbers array at the beginning.
  while (left <= middle) {
    numbers[current++] = helper[left++];
  }
}
