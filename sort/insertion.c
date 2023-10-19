#ifndef __INSERTION__
#define __INSERTION__

#include "../util.c"

void insertion_sort(int *arr, int size, int *count);

void run_insertion()
{
    int count = 0;
    int arr[] = {4, 1, 9, 3, 9, 4, 7, 6};

    printf("[insertion sort]\n");

    insertion_sort(arr, 8, &count);

    print(arr, 8);
    printf("count: %d\n", count);
}

void insertion_sort(int *arr, int size, int *count)
{
    int target;

    for (int i = 1; i < size; i++) {
        target = arr[i];
        for (int j = i - 1; j >= 0 && arr[j] > target; j--) {
            arr[j + 1] = arr[j];
            arr[j] = target;
            *count += + 1;
        }
    }
}

#endif