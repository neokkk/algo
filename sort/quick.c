#include "../util.c"

void quick_sort(int *arr, int left, int right);

void run_quick()
{
    int arr[] = {4, 1, 9, 3, 9, 4, 7, 6};

    printf("[quick sort]\n");

    quick_sort(arr, 0, 7);

    print(arr, 8);
}

void quick_sort(int *arr, int left, int right)
{
    int pivot = left;
    int L = left + 1, R = right;

    if (left >= right) return;

    while (L <= R) {
        while (L <= right && arr[L] < arr[pivot]) L++;
        while (R >= left && arr[R] > arr[pivot]) R--;

        if (L <= R) {
            swap(arr, L++, R--);
        }
    }

    swap(arr, pivot, R);

    quick_sort(arr, left, R - 1);
    quick_sort(arr, R + 1, right);
}