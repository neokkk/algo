#ifndef __SELECTION__
#define __SELECTION__

#include "../util.c"

void selection_sort(int *arr, int size, int *count);

void run_selection()
{
    int count = 0;
    int arr[] = {4, 1, 9, 3, 9, 4, 7, 6};

    printf("[selection sort]\n");

    selection_sort(arr, 8, &count);

    print(arr, 8);
    printf("count: %d\n", count);
}

void selection_sort(int *arr, int size, int *count)
{
    int min_idx;

    for (int i = 0; i < size - 1; i++) {
        min_idx = i;
        for (int j = i + 1; j < size; j++) {
            *count++;
            if (arr[min_idx] > arr[j])
                min_idx = j;
        }
        if (min_idx != i)
            swap(arr, i, min_idx);
    }
}

#endif