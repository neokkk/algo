#include "../util.c"

void counting_sort(int *arr, int size);

void run_counting()
{
    int arr[] = {1, 1, 0, 3, 2, 0, 2, 1};

    printf("[counting sort]\n");

    counting_sort(arr, 8);

    print(arr, 8);
}

void counting_sort(int *arr, int size)
{
    int i, max = INT_MIN;

    for (i = 0; i < size; i++)
        max = MAX(max, arr[i]);

    int count[max + 1], sorted[size];

    for (i = 0; i <= max; i++)
        count[i] = 0;

    for (i = 0; i < size; i++)
        count[arr[i]] += 1;

    for (i = 1; i <= max; i++)
        count[i] += count[i - 1];

    for (i = size - 1; i >= 0; i--) {
        sorted[count[arr[i]] - 1] = arr[i];
        count[arr[i]] -= 1;
    }

    for (i = 0; i < size; i++)
        arr[i] = sorted[i];
}