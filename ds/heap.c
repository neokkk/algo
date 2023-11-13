#ifndef __HEAP__
#define __HEAP__

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../util.c"

struct heap {
    unsigned int n;
    int top;
    int *arr;
    /**
     * 0: max heap
     * 1: min heap
     */
    bool flag;
};

struct heap *create_heap(unsigned int n, bool is_min_heap);
bool is_empty(struct heap *heap);
bool is_full(struct heap *heap);
bool insert_item(struct heap *heap, int value);
void heap_up(struct heap *heap, int idx);
void heap_down(struct heap *heap, int idx);
int remove_item(struct heap *heap);
void destroy_heap(struct heap *heap);
void print_heap(struct heap *heap);

void run_heap()
{
    struct heap *heap;

    heap = create_heap(10, true);
    assert(insert_item(heap, 3) == true);
    insert_item(heap, 8);
    insert_item(heap, 7);
    insert_item(heap, 1);
    insert_item(heap, 9);
    insert_item(heap, 4);
    insert_item(heap, 6);
    insert_item(heap, 0);
    insert_item(heap, 2);
    insert_item(heap, 5);
    assert(insert_item(heap, 10) == false);
    print_heap(heap);
    assert(remove_item(heap) == 0);
    assert(remove_item(heap) == 1);
    assert(remove_item(heap) == 2);
    assert(remove_item(heap) == 3);
    assert(remove_item(heap) == 4);
    assert(remove_item(heap) == 5);
    assert(remove_item(heap) == 6);
    assert(remove_item(heap) == 7);
    assert(remove_item(heap) == 8);
    assert(remove_item(heap) == 9);
    destroy_heap(heap);
}

struct heap *create_heap(unsigned int n, bool is_min_heap)
{
    struct heap *heap;

    heap = malloc(sizeof(struct heap));
    heap->n = n;
    heap->top = -1;
    heap->arr = malloc(sizeof(int) * n);
    heap->flag = is_min_heap;

    return heap;
}

bool is_empty(struct heap *heap)
{
    if (heap->top == -1) return true;
    return false;
}

bool is_full(struct heap *heap)
{
    if (heap->top == heap->n - 1) return true;
    return false;
}

bool insert_item(struct heap *heap, int value)
{
    if (is_full(heap)) return false;
    heap->arr[++heap->top] = value;
    heap_up(heap, heap->top);
    return true;
}

void heap_up(struct heap *heap, int idx)
{
    int parent_idx;

    if (idx <= 0) return;

    parent_idx = (idx - 1) / 2;

    if (heap->flag == 0) { // max heap
        if (heap->arr[idx] > heap->arr[parent_idx]) {
            swap(heap->arr, idx, parent_idx);
            heap_up(heap, parent_idx);
        }
    }
    else {
        if (heap->arr[idx] < heap->arr[parent_idx]) {
            swap(heap->arr, idx, parent_idx);
            heap_up(heap, parent_idx);
        }
    }
}

void heap_down(struct heap *heap, int idx)
{
    int left_idx, right_idx, child_idx;

    if (idx >= heap->n) return;

    left_idx = idx * 2 + 1;
    right_idx = idx * 2 + 2;

    if (left_idx <= heap->top) {
        if (right_idx <= heap->top) {
            if (heap->flag == 0)
                child_idx = heap->arr[left_idx] > heap->arr[right_idx] ? left_idx : right_idx;
            else
                child_idx = heap->arr[left_idx] < heap->arr[right_idx] ? left_idx : right_idx;
        }
        else {
            child_idx = left_idx;
        }

        if (heap->flag == 0) {
            if (heap->arr[idx] < heap->arr[child_idx]) {
                swap(heap->arr, idx, child_idx);
                heap_down(heap, child_idx);
            }
        }
        else {
            if (heap->arr[idx] > heap->arr[child_idx]) {
                swap(heap->arr, idx, child_idx);
                heap_down(heap, child_idx);
            }
        }
    }
}

int remove_item(struct heap *heap)
{
    int popped;

    if (is_empty(heap)) return -1;

    popped = heap->arr[0];
    heap->arr[0] = heap->arr[heap->top--];
    heap_down(heap, 0);

    return popped;
}

void destroy_heap(struct heap *heap)
{
    free(heap->arr);
    free(heap);
}

void print_heap(struct heap *heap)
{
    print(heap->arr, heap->top + 1);
}

#endif