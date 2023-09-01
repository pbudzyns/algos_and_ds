#include "Algorithms/Sorting.hpp"

void sort::swapElements(int* first, int* second)
{

    int tmp = *first;
    *first = *second;
    *second = tmp;
}

// ------- Bubble Sort -----------------------------

void sort::bubbleSort(int* numbers, int n)
{
    for (int i{0}; i < n - 1; ++i)
    {
        for (int j{i + 1}; j < n; ++j)
        {
            // Swap numbers if i-th is larger than j-th
            if (numbers[i] > numbers[j])
            {
                swapElements(&numbers[i], &numbers[j]);
            }
        }
    }
}

// ------- Selection Sort -----------------------------

void sort::selectionSort(int* numbers, int n)
{
    int smallest_idx;
    for (int i{0}; i < n - 1; ++i)
    {
        smallest_idx = i;
        for (int j{i + 1}; j < n; ++j)
        {
            // Scan searching for the smallest number.
            if (numbers[smallest_idx] > numbers[j])
            {
                smallest_idx = j;
            }
        }
        if (smallest_idx != i)
        {
            // Insert the value in the correct place.
            swapElements(&numbers[i], &numbers[smallest_idx]);
        }
    }
}

// ------- Merge Sort -----------------------------

static void mergeSort(int* numbers, int* helper, int low, int high);
static void merge(int* numbers, int* helper, int low, int middle, int high);

void sort::mergeSort(int* numbers, int n)
{
    int* helper{new int[n]};
    ::mergeSort(numbers, helper, 0, n - 1);
    delete[] helper;
}

static void mergeSort(int* numbers, int* helper, int low, int high)
{
    if (low >= high)
    {
        return;
    }
    int middle{low + (high - low) / 2};
    mergeSort(numbers, helper, low, middle);
    mergeSort(numbers, helper, middle + 1, high);
    merge(numbers, helper, low, middle, high);
}

static void merge(int* numbers, int* helper, int low, int middle, int high)
{
    // Copy content of the array to helper array.
    // Nomally, left and right subarrays would be created. Left of range
    // [low,middle], right of range [middle+1,high]. Helper array allows to skip
    // creating additional arrays in mergeSort functions so the algorithm takes
    // O(n) extra space.
    for (int i{low}; i <= high; ++i)
    {
        helper[i] = numbers[i];
    }

    int left{low};
    int right{middle + 1};
    int current{low};

    while (left <= middle && right <= high)
    {
        if (helper[left] <= helper[right])
        {
            numbers[current++] = helper[left++];
        }
        else
        {
            numbers[current++] = helper[right++];
        }
    }

    // Copy the leftovers from the left side.
    // No need to copy from the right size because it's already there
    // helper content was taken from numbers array at the beginning.
    while (left <= middle)
    {
        numbers[current++] = helper[left++];
    }
}

// ------- Quick Sort -----------------------------

static void quickSort(int* numbers, int start, int end);
static int partition(int* numbers, int start, int end);

void sort::quickSort(int* numbers, int n)
{
    ::quickSort(numbers, 0, n - 1);
}

void quickSort(int* numbers, int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int pivotIdx{partition(numbers, start, end)};
    quickSort(numbers, start, pivotIdx - 1);
    quickSort(numbers, pivotIdx + 1, end);
}

int partition(int* numbers, int start, int end)
{
    int pivot{numbers[end]};
    int left{start - 1};
    int right{start};
    while (right <= end)
    {
        if (numbers[right] < pivot)
        {
            ++left;
            sort::swapElements(&numbers[left], &numbers[right]);
        }
        ++right;
    }
    ++left;
    sort::swapElements(&numbers[left], &numbers[end]);

    return left;
}

// ------- Heap Sort -----------------------------

static void heapify(int* numbers, int n, int index);

void sort::heapSort(int* numbers, int n)
{
    for (int i{n / 2 - 1}; i >= 0; --i)
    {
        // Heapify subtrees starting from root of the "last" element.
        heapify(numbers, n, i);
    }

    for (int i{n - 1}; i >= 0; --i)
    {
        // Max heap the largest element is the root.
        sort::swapElements(&numbers[0], &numbers[i]);
        // Heapify reduced range of the array.
        heapify(numbers, i, 0);
    }
}

static void heapify(int* numbers, int n, int index)
{
    int largest{index};
    int leftChild{2 * index + 1};
    int rightChild{2 * index + 2};

    if (leftChild < n && numbers[leftChild] > numbers[largest])
    {
        largest = leftChild;
    }
    if (rightChild < n && numbers[rightChild] > numbers[largest])
    {
        largest = rightChild;
    }
    if (largest != index)
    {
        sort::swapElements(&numbers[largest], &numbers[index]);
        heapify(numbers, n, largest);
    }
}
