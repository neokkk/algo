#include "../util.c"

void merge_sort(int *arr, int left, int right);

void run_merge()
{
    int arr[] = {4, 1, 9, 3, 9, 4, 7, 6};

    printf("[merge sort]\n");

    merge_sort(arr, 0, 7);

    print(arr, 8);
}

void merge(int *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = j = 0;
    k = l;

    while (i < n1 && j < n2)
        arr[k++] = L[i] <= R[j] ? L[i++] : R[j++];

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void merge_sort(int *arr, int left, int right)
{
    int mid;

    if (left >= right) return;

    mid = (left + right) / 2;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}