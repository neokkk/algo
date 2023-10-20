#include <math.h>
#include "../ds/queue.c"
#include "../util.c"

#define BUCKET_SIZE 10

void radix_sort(int *arr, int size);

void run_radix()
{
    int arr[] = {329, 457, 657, 839, 436, 720, 355, 621};

    printf("[radix sort]\n");

    radix_sort(arr, 8);

    print(arr, 8);
}

void radix_sort(int *arr, int size)
{
    int i, idx, max = INT_MIN, max_digit = 0;
    struct queue *bucket[BUCKET_SIZE];

    for (i = 0; i < BUCKET_SIZE; i++)
        bucket[i] = create_queue(BUCKET_SIZE);

    for (i = 0; i < size; i++)
        max = MAX(max, arr[i]);

    while (max > 0) {
        max /= BUCKET_SIZE;
        max_digit++;
    }

    for (int d = 1; d <= pow(10, max_digit); d *= 10) {
        idx = 0;

        for (i = 0; i < size; i++) {
            int num = (arr[i] / d) % 10;
            enqueue(bucket[num], arr[i]);
        }

        for (i = 0; i < BUCKET_SIZE; i++) {
            while (!is_empty(bucket[i])) {
                arr[idx++] = dequeue(bucket[i]);
            }
        }
    }

    for (i = 0; i < BUCKET_SIZE; i++)
        destroy_queue(bucket[i]);
}