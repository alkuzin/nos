/* MIT License
 *
 * Copyright (c) 2024 Alexander (@alkuzin)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

#include <nos/string.h>
#include <nos/stdlib.h>
#include <nos/math.h>

/**
 * @brief Swaps the contents of two memory regions of a given size.
 * 
 * @param [in] p1 - given pointer to the start of the first memory block to swap.
 * @param [in] p2 - given pointer to the start of the second memory block to swap.
 * @param [in] size - given size of the memory blocks to swap, in bytes.
 */
static void __swap(void *p1, void *p2, usize size);

/**
 * @brief Quick sort algorithm.
 * 
 * This function sorts an array with @a nmemb elements of size @a size.
 * 
 * @param [in] base - given pointer to the first element of the sequence to sort.
 * @param [in] nmemb - given number of elements in the sequence.
 * @param [in] size - given size of each element in sequence in bytes.
 * @param [in] cmp - given comparison function pointer.
 */
static void __quick_sort(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *));

/**
 * @brief Organizes the elements in the array so that the subtree
 * rooted at index @a i follows the heap property.
 * 
 * @param [in] base - given pointer to the first element of the sequence to sort.
 * @param [in] nmemb - given number of elements in the sequence.
 * @param [in] size - given size of each element in sequence in bytes.
 * @param [in] cmp - given comparison function pointer.
 * @param [in] i - given index of the root node of the subtree to heapify. 
 */
static void __heapify(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *), usize i);

/**
 * @brief Heap sort algorithm.
 * 
 * This function sorts an array with @a nmemb elements of size @a size.
 * 
 * @param [in] base - given pointer to the first element of the sequence to sort.
 * @param [in] nmemb - given number of elements in the sequence.
 * @param [in] size - given size of each element in sequence in bytes.
 * @param [in] cmp - given comparison function pointer.
 */
static void __heap_sort(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *));

/**
 * @brief Insertion sort algorithm.
 * 
 * This function sorts an array with @a nmemb elements of size @a size.
 * 
 * @param [in] base - given pointer to the first element of the sequence to sort.
 * @param [in] nmemb - given number of elements in the sequence.
 * @param [in] size - given size of each element in sequence in bytes.
 * @param [in] cmp - given comparison function pointer.
 */
static void __insertion_sort(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *));

/**
 * @brief Count sort algorithm.
 * 
 * This function sorts an array @a arr with @a nmemb elements.
 * 
 * @param [in] arr - given array of integers to sort.
 * @param [in] nmemb - given number of elements in the sequence.
 * @param [in] exp - given digit position to sort by.
 */
static void __count_sort(s32 *arr, s32 nmemb, s32 exp);

/**
 * @brief Radix sort algorithm.
 * 
 * This function sorts an array @a arr with @a nmemb elements.
 * 
 * @param [in] arr - given array of integers to sort.
 * @param [in] nmemb - given number of elements in the sequence.
 */
static void __radix_sort(s32 *arr, s32 nmemb);


static void __swap(void *p1, void *p2, usize size)
{
    char temp[size];

    memcpy(temp, p1, size);
    memcpy(p1, p2, size);
    memcpy(p2, temp, size);
}

static void __quick_sort(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *))
{
    char  pivot[size];
    char  temp[size];
    usize i, j;

    if (nmemb <= 1)
        return;
    
    memcpy(pivot, (char *)base + (nmemb / 2) * size, size);

    i = 0;
    j = nmemb - 1;

    while (i <= j) {

        while (cmp((char *)base + i * size, pivot) < 0)
            i++;

        while (cmp((char *)base + j * size, pivot) > 0)
            j--;

        if (i <= j) {
            memcpy(temp, (char *)base + i * size, size);
            memcpy((char *)base + i * size, (char *)base + j * size, size);
            memcpy((char *)base + j * size, temp, size);

            i++;
            j--;
        }
    }

    if (j > 0)
        __quick_sort(base, j + 1, size, cmp);

    if (i < nmemb)
        __quick_sort((char *)base + i * size, nmemb - i, size, cmp);
}

static void __heapify(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *), usize i)
{
    usize largest, left, right;
    char  *arr;

    arr     = (char *)base;
    largest = i;
    left    = 2 * i + 1;
    right   = 2 * i + 2;

    if (left < nmemb && cmp(arr + left * size, arr + largest * size) > 0)
        largest = left;

    if (right < nmemb && cmp(arr + right * size, arr + largest * size) > 0)
        largest = right;

    if (largest != i) {
        __swap(arr + i * size, arr + largest * size, size);
        __heapify(arr, nmemb, size, cmp, largest);
    }
}

static void __heap_sort(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *))
{
    char *arr;

    arr = (char *)base;

    for (usize i = nmemb / 2 - 1; i < nmemb; i--)
        __heapify(arr, nmemb, size, cmp, i);

    for (usize i = nmemb - 1; i > 0; i--) {
        __swap(arr, arr + i * size, size);
        __heapify(arr, i, size, cmp, 0);
    }
}

static void __insertion_sort(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *))
{
    char   tmp[size];
    usize  i, j;

    for (i = 1; i < nmemb; i++) {
        memcpy(tmp, (char *)base + i * size, size);
        
        for (j = i; j > 0 && cmp((char *)base + (j - 1) * size, tmp) > 0; j--)
            memcpy((char *)base + j * size, (char *)base + (j - 1) * size, size);
        
        memcpy((char *)base + j * size, tmp, size);
    }
}

static void __count_sort(s32 *arr, s32 nmemb, s32 exp)
{
    s32 count[10] = {0};
    s32 output[nmemb];

    for (s32 i = 0; i < nmemb; i++)
        count[(arr[i] / exp) % 10]++;

    for (s32 i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (s32 i = nmemb - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (s32 i = 0; i < nmemb; i++)
        arr[i] = output[i];
}

static void __radix_sort(s32 *arr, s32 nmemb)
{
    s32 max;

    max = arr[0];
    
    for (s32 i = 1; i < nmemb; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    for (s32 exp = 1; max / exp > 0; exp *= 10)
        __count_sort(arr, nmemb, exp);
}

void qsort(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *))
{
    s32 depth_limit;
    
    if (size == sizeof(s32))
        __radix_sort((s32 *)base, nmemb);
    else {
        depth_limit = 2 * log(size);
        
        if (nmemb <= QSORT_THRESHOLD) {
            __insertion_sort(base, nmemb, size, cmp);
            return;
        }

        if (depth_limit == 0) {
            __heap_sort(base, nmemb, size, cmp);
            return;
        }

        __quick_sort(base, nmemb, size, cmp);
    }
}