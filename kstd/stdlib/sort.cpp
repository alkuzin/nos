/**
 * The Null Operating System (NOS).
 * Copyright (C) 2024  Alexander (@alkuzin).
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <kernel/kstd/cstdlib.hpp>
#include <kernel/kstd/cstring.hpp>
#include <kernel/kstd/cmath.hpp>


namespace kernel {
namespace kstd {

/**
 * @brief Swaps the contents of two memory regions of a given size.
 * 
 * @param [in] p1 - given pointer to the start of the first memory block to swap.
 * @param [in] p2 - given pointer to the start of the second memory block to swap.
 * @param [in] size - given size of the memory blocks to swap, in bytes.
 */
static inline void __swap(void *p1, void *p2, usize size) noexcept
{
    char temp[size];

    memcpy(temp, p1, size);
    memcpy(p1, p2, size);
    memcpy(p2, temp, size);
}

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
static void __quick_sort(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *)) noexcept
{
    char  pivot[size];
    char  temp[size];

    if (nmemb <= 1)
        return;
    
    memcpy(pivot, static_cast<char*>(base) + (nmemb / 2) * size, size);

    usize i = 0;
    usize j = nmemb - 1;

    while (i <= j) {

        while (cmp(static_cast<char*>(base) + i * size, pivot) < 0)
            i++;

        while (cmp(static_cast<char*>(base) + j * size, pivot) > 0)
            j--;

        if (i <= j) {
            memcpy(temp, static_cast<char*>(base) + i * size, size);
            memcpy(static_cast<char*>(base) + i * size, static_cast<char*>(base) + j * size, size);
            memcpy(static_cast<char*>(base) + j * size, temp, size);

            i++;
            j--;
        }
    }

    if (j > 0)
        __quick_sort(base, j + 1, size, cmp);

    if (i < nmemb)
        __quick_sort(static_cast<char*>(base) + i * size, nmemb - i, size, cmp);
}

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
static void __heapify(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *), usize i) noexcept
{
    usize largest, left, right;
    char  *arr = static_cast<char*>(base);

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
static void __heap_sort(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *)) noexcept
{
    char *arr = static_cast<char*>(base);

    for (usize i = nmemb / 2 - 1; i < nmemb; i--)
        __heapify(arr, nmemb, size, cmp, i);

    for (usize i = nmemb - 1; i > 0; i--) {
        __swap(arr, arr + i * size, size);
        __heapify(arr, i, size, cmp, 0);
    }
}

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
static void __insertion_sort(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *)) noexcept
{
    char   tmp[size];
    usize  i, j;

    for (i = 1; i < nmemb; i++) {
        memcpy(tmp, static_cast<char*>(base) + i * size, size);
        
        for (j = i; j > 0 && cmp(static_cast<char*>(base) + (j - 1) * size, tmp) > 0; j--)
            memcpy(static_cast<char*>(base) + j * size, static_cast<char*>(base) + (j - 1) * size, size);
        
        memcpy(static_cast<char*>(base) + j * size, tmp, size);
    }
}

/**
 * @brief Count sort algorithm.
 * 
 * This function sorts an array @a arr with @a nmemb elements.
 * 
 * @param [in] arr - given array of integers to sort.
 * @param [in] nmemb - given number of elements in the sequence.
 * @param [in] exp - given digit position to sort by.
 */
static void __count_sort(s32 *arr, s32 nmemb, s32 exp) noexcept
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

/**
 * @brief Radix sort algorithm.
 * 
 * This function sorts an array @a arr with @a nmemb elements.
 * 
 * @param [in] arr - given array of integers to sort.
 * @param [in] nmemb - given number of elements in the sequence.
 */
static void __radix_sort(s32 *arr, s32 nmemb) noexcept
{
    s32 max = arr[0];
    
    for (s32 i = 1; i < nmemb; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    for (s32 exp = 1; max / exp > 0; exp *= 10)
        __count_sort(arr, nmemb, exp);
}

void qsort(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *)) noexcept
{
    if (size == sizeof(s32))
        __radix_sort(static_cast<s32*>(base), nmemb);
    else {
        auto depth_limit = 2 * log(size);
        
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

} // namespace kstd
} // namespace kernel