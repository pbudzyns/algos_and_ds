#pragma once

namespace sort {

/**
 * @brief Bubble sort algorithm for an array of integers.
 *
 * @param numbers Pointer to arrray of integers.
 * @param n Number of elements in the array.
 */
void bubbleSort(int* numbers, int n);

/**
 * @brief Selection sort algorithm for an array of integers.
 *
 * @param numbers Pointer to array of integers.
 * @param n Number of elements in the array.
 */
void selectionSort(int* numbers, int n);

/**
 * @brief Merge sort algorithm for an array of integers.
 *
 * @param numbers Pointer to array of integers.
 * @param n Number of elements in the array.
 */
void mergeSort(int* numbers, int n);

/**
 * @brief Quick sort algorithm for an array of integers.
 *
 * @param numbers Pointer to array of integers.
 * @param n Number of elements in the array.
 */
void quickSort(int* numbers, int n);

/**
 * @brief Helper function to swap two elements.
 *
 * @param first Pointer to first element.
 * @param second Pointer to second element.
 */
void swapElements(int* first, int* second);
}  // namespace sort
