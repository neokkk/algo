#include "insertion.c"

void shell_sort(int *arr, int size, int *count);

void run_shell()
{
    int count = 0;
    int arr[] = {4, 1, 9, 3, 9, 4, 7, 6};

    printf("[shell sort]\n");

    shell_sort(arr, 8, &count);

    print(arr, 8);
    printf("count: %d\n", count);
}

void shell_sort(int *arr, int size, int *count)
{
    int j, target;

    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            j = i;
            target = arr[i];
            while (j >= gap && target < arr[j - gap]) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = target;
        }
    }

    insertion_sort(arr, size, count);
}