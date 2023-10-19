#include <stdio.h>
#include <stdlib.h>

void print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void heap_up(int *arr, int idx)
{
    int parent_idx, tmp;

    if (idx <= 0) return;

    parent_idx = (idx - 1) / 2;

    if (arr[idx] < arr[parent_idx]) {
        tmp = arr[idx];
        arr[idx] = arr[parent_idx];
        arr[parent_idx] = tmp;
        heap_up(arr, parent_idx);
    }
}

void heap_down(int *arr, int size, int idx)
{
    int left_idx, right_idx, child_idx, tmp;

    left_idx = idx * 2 + 1;
    right_idx = left_idx + 1;

    if (size <= 1 || left_idx >= size) return;
    if (right_idx >= size) child_idx = left_idx;
    else child_idx = arr[left_idx] < arr[right_idx] ? left_idx : right_idx;

    if (arr[idx] > arr[child_idx]) {
        tmp = arr[idx];
        arr[idx] = arr[child_idx];
        arr[child_idx] = tmp;
        heap_down(arr, size, child_idx);
    }
}

int *heap_sort(int *arr, int size)
{
    int i;
    int *_arr = (int *)malloc(sizeof(int) * size);
    int *sorted = (int *)malloc(sizeof(int) * size);

    for (i = 0; i < size; i++) {
        _arr[i] = arr[i];
        heap_up(_arr, i);
    }

    for (i = 0; i < size; i++) {
        sorted[i] = _arr[0];
        _arr[0] = _arr[size - 1 - i];
        heap_down(_arr, size - i, 0);
    }

    free(_arr);

    return sorted;
}
