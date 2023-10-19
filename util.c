#ifndef __UTIL__
#define __UTIL__

#include <stdlib.h>
#include <stdio.h>

void swap(int *arr, int a, int b)
{
    int tmp;

    tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

void print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

#endif