// Code from Mark Allen Weiss textbook
// Modified by: Abrar Mahi

#ifndef SORT_H
#define SORT_H

/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first.
 */
#include <vector>
#include <functional>
#include <iostream>
using namespace std;

/**
 * Simple insertion sort.
 */

//adding new typename and comparator param
template <typename Comparable, typename Comparator>
void insertionSort(vector<Comparable> &a, Comparator less_than)
{
    for (int p = 1; p < a.size(); ++p)
    {
        Comparable tmp = std::move(a[p]);

        int j;
        //including less than function in the iteration
        for (j = p; j > 0 && less_than(tmp, a[j - 1]); --j)
            a[j] = std::move(a[j - 1]);
        a[j] = std::move(tmp);
    }
}

/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
//adding new typename and comparator param
template <typename Comparable, typename Comparator>
void insertionSort(vector<Comparable> &a, int left, int right, Comparator less_than)
{
    for (int p = left + 1; p <= right; ++p)
    {
        Comparable tmp = std::move(a[p]);
        int j;

        //including less than function in the iteration
        for (j = p; j > left && less_than(tmp, a[j - 1]); --j)
            a[j] = std::move(a[j - 1]);
        a[j] = std::move(tmp);
    }
}

/**
 * Shellsort, using Shell's (poor) increments.
 */
//adding new typename and comparator param
template <typename Comparable>
void shellsort(vector<Comparable> &a)
{
    for (int gap = a.size() / 2; gap > 0; gap /= 2)
        for (int i = gap; i < a.size(); ++i)
        {
            Comparable tmp = std::move(a[i]);
            int j = i;

            for (; j >= gap && tmp < a[j - gap]; j -= gap)
                a[j] = std::move(a[j - gap]);
            a[j] = std::move(tmp);
        }
}

/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild(int i)
{
    return 2 * i + 1;
}

/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
//adding new typename and comparator param
template <typename Comparable, typename Comparator>
void percDown(vector<Comparable> &a, int i, int n, Comparator less_than)
{
    int child;
    Comparable tmp;

    for (tmp = std::move(a[i]); leftChild(i) < n; i = child)
    {
        child = leftChild(i);
        //checking if the value in the vecotr at location child is less than the next value
        if (child != n - 1 && less_than(a[child], a[child + 1]))
        {
            ++child;
        }
        //checking to see if the child value is greater than the temp
        if (less_than(tmp, a[child]))
        {
            a[i] = std::move(a[child]);
        }
        else
        {
            break;
        }
    }
    a[i] = std::move(tmp);
}

/**
 * Standard heapsort.
 */
//adding new typename and comparator param
template <typename Comparable, typename Comparator>
void HeapSort(vector<Comparable> &a, Comparator less_than)
{
    for (int i = a.size() / 2 - 1; i >= 0; --i) /* buildHeap */
        percDown(a, i, a.size(), less_than);
    for (int j = a.size() - 1; j > 0; --j)
    {
        std::swap(a[0], a[j]); /* deleteMax */
        percDown(a, 0, j, less_than);
    }
}

/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
//adding new typename and comparator param
template <typename Comparable, typename Comparator>
void merge(vector<Comparable> &a, vector<Comparable> &tmpArray,
           int leftPos, int rightPos, int rightEnd, Comparator less_than)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while (leftPos <= leftEnd && rightPos <= rightEnd)
        if (less_than(a[leftPos], a[rightPos]))
            tmpArray[tmpPos++] = std::move(a[leftPos++]);
        else
            tmpArray[tmpPos++] = std::move(a[rightPos++]);

    while (leftPos <= leftEnd)
        tmpArray[tmpPos++] = std::move(a[leftPos++]);

    while (rightPos <= rightEnd)
        tmpArray[tmpPos++] = std::move(a[rightPos++]);

    for (int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = std::move(tmpArray[rightEnd]);
}

/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
//adding new typename and comparator param
template <typename Comparable, typename Comparator>
void mergeSort(vector<Comparable> &a,
               vector<Comparable> &tmpArray, int left, int right, Comparator less_than)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        mergeSort(a, tmpArray, left, center, less_than);
        mergeSort(a, tmpArray, center + 1, right, less_than);
        merge(a, tmpArray, left, center + 1, right, less_than);
    }
}

/**
 * Mergesort algorithm (driver).
 */
//adding new typename and comparator param
template <typename Comparable, typename Comparator>
void MergeSort(vector<Comparable> &a, Comparator less_than)
{
    vector<Comparable> tmpArray(a.size());

    mergeSort(a, tmpArray, 0, a.size() - 1, less_than);
}

/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
//adding new typename and comparator param
template <typename Comparable, typename Comparator>
const Comparable &median3(vector<Comparable> &a, int left, int right, Comparator less_than)
{
    int center = (left + right) / 2;
    //including less than functions in conditions to compare values of the vector
    if (less_than(a[center], a[left]))
        std::swap(a[left], a[center]);
    if (less_than(a[right], a[left]))
        std::swap(a[left], a[right]);
    if (less_than(a[right], a[center]))
        std::swap(a[center], a[right]);

    // Place pivot at position right - 1
    std::swap(a[center], a[right - 1]);
    return a[right - 1];
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
//adding new typename and comparator param
template <typename Comparable, typename Comparator>
void quicksort(vector<Comparable> &a, int left, int right, Comparator less_than)
{
    if (left + 10 <= right)
    {
        const Comparable &pivot = median3(a, left, right, less_than);

        // Begin partitioning
        int i = left, j = right - 1;
        for (;;)
        {
            //including less than functions in while loops to compare values of the vector
            while (less_than(a[++i], pivot))
            {
            }
            while (less_than(pivot, a[--j]))
            {
            }
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]); // Restore pivot

        quicksort(a, left, i - 1, less_than);  // Sort small elements
        quicksort(a, i + 1, right, less_than); // Sort large elements
    }
    else // Do an insertion sort on the subarray
        insertionSort(a, left, right, less_than);
}

/**
 * Quicksort algorithm (driver).
 */
//adding new typename and comparator param
template <typename Comparable, typename Comparator>
void QuickSort(vector<Comparable> &a, Comparator less_than)
{
    quicksort(a, 0, a.size() - 1, less_than);
}

/**
 * Internal selection method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * k is the desired rank (1 is minimum) in the entire array.
 */
//adding new typename and comparator param
template <typename Comparable>
void quickSelect(vector<Comparable> &a, int left, int right, int k)
{
    if (left + 10 <= right)
    {
        const Comparable &pivot = median3(a, left, right);

        // Begin partitioning
        int i = left, j = right - 1;
        for (;;)
        {
            while (a[++i] < pivot)
            {
            }
            while (pivot < a[--j])
            {
            }
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]); // Restore pivot

        // Recurse; only this part changes
        if (k <= i)
            quickSelect(a, left, i - 1, k);
        else if (k > i + 1)
            quickSelect(a, i + 1, right, k);
    }
    else // Do an insertion sort on the subarray
        insertionSort(a, left, right);
}

/**
 * Quick selection algorithm.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * k is the desired rank (1 is minimum) in the entire array.
 */
//adding new typename and comparator param
template <typename Comparable>
void quickSelect(vector<Comparable> &a, int k)
{
    quickSelect(a, 0, a.size() - 1, k);
}

template <typename Comparable, typename Comparator>
void SORT(vector<Comparable> &items, Comparator less_than)
{
    if (items.size() > 1)
    {
        vector<Comparable> smaller;
        vector<Comparable> same;
        vector<Comparable> larger;

        auto chosenItem = items[items.size() / 2];

        for (auto &i : items)
        {
            if (less_than(i, chosenItem))
                smaller.push_back(std::move(i));
            else if (less_than(chosenItem, i))
                larger.push_back(std::move(i));
            else
                same.push_back(std::move(i));
        }

        SORT(smaller, less_than); // Recursive call!
        SORT(larger, less_than);  // Recursive call!

        std::move(begin(smaller), end(smaller), begin(items));
        std::move(begin(same), end(same), begin(items) + smaller.size());
        std::move(begin(larger), end(larger), end(items) - larger.size());
    }
}

/*
 * This is the more public version of insertion sort.
 * It requires a pair of iterators and a comparison
 * function object.
 */
//adding new typename and comparator param
template <typename RandomIterator, typename Comparator>
void insertionSort(const RandomIterator &begin,
                   const RandomIterator &end,
                   Comparator lessThan)
{
    if (begin == end)
        return;

    RandomIterator j;

    for (RandomIterator p = begin + 1; p != end; ++p)
    {
        auto tmp = std::move(*p);
        for (j = p; j != begin && lessThan(tmp, *(j - 1)); --j)
            *j = std::move(*(j - 1));
        *j = std::move(tmp);
    }
}

/*
 * The two-parameter version calls the three parameter version, using C++11 decltype
 */
//adding new typename and comparator param
template <typename RandomIterator, typename Comparator>
void insertionSort(const RandomIterator &begin,
                   const RandomIterator &end)
{
    insertionSort(begin, end, less<decltype(*begin)>{});
}

//adding new typename and comparator param
template <typename Comparable, typename Comparator>
void quicksort(vector<Comparable> &a, int left, int right, Comparable &pivot, Comparator less_than)
{
    if (left + 10 <= right)
    {

        // Begin partitioning
        int i = left, j = right - 1;
        for (;;)
        {
            while (less_than(a[++i], pivot))
            {
            }
            while (less_than(pivot, a[--j]))
            {
            }
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]); // Restore pivot

        quicksort(a, left, i - 1, less_than);  // Sort small elements
        quicksort(a, i + 1, right, less_than); // Sort large elements
    }
    else // Do an insertion sort on the subarray
        insertionSort(a, left, right, less_than);
}

template <typename Comparable, typename Comparator>
void QuickSort2(vector<Comparable> &a, Comparator less_than)
{
    int middle = (a.size() / 2) + 1;
    Comparable &pivot = a[middle]; //making the midddle value of vector the pivot
    quicksort(a, 0, a.size() - 1, pivot, less_than);
}

template <typename Comparable, typename Comparator>
void QuickSort3(vector<Comparable> &a, Comparator less_than)
{
    Comparable &pivot = a[0]; //making the pivot the first value of the vector
    quicksort(a, 0, a.size() - 1, pivot, less_than);
}

#endif