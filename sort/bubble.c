#include "../util.c"

void bubble_sort(int *arr, int size, int *count);

void run_bubble()
{
    int count = 0;
    int arr[] = {4, 1, 9, 3, 9, 4, 7, 6};

    printf("[bubble sort]\n");

    bubble_sort(arr, 8, &count);

    print(arr, 8);
    printf("count: %d\n", count);
}

void bubble_sort(int *arr, int size, int *count)
{
    int swapped;

    for (int i = 0; i < size - 1; i++) {
        swapped = 0;
        for (int j = 0; j < size - 1 - i; j++) {
            *count++;
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
                swapped = 1;
            }
        }
        if (swapped == 1) break;
    }
}

