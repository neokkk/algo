#ifndef __QUEUE__
#define __QUEUE__

#include <assert.h>
#include "../util.c"

struct queue {
    int *buf;
    int size;
    int count;
    int front;
    int rear;
};

struct queue *create_queue(int size);
bool enqueue(struct queue *queue, int value);
int dequeue(struct queue *queue);
void destroy_queue(struct queue *queue);

void run_queue()
{
    struct queue *queue;

    queue = create_queue(4);
    assert(enqueue(queue, 3) == true);
    enqueue(queue, 4);
    enqueue(queue, 6);
    enqueue(queue, 8);
    assert(enqueue(queue, 1) == false);
    assert(dequeue(queue) == 3);
    assert(dequeue(queue) == 4);
    assert(dequeue(queue) == 6);
    assert(dequeue(queue) == 8);
    assert(dequeue(queue) == -1);
    destroy_queue(queue);
}

struct queue *create_queue(int size)
{
    struct queue *queue;

    queue = (struct queue *)malloc(sizeof(struct queue));
    queue->buf = (int *)malloc(sizeof(int) * size);
    queue->size = size;
    queue->count = 0;
    queue->front = 0;
    queue->rear = 0;

    return queue;
}

bool is_empty(struct queue *queue)
{
    return queue->count == 0;
}

bool is_full(struct queue *queue)
{
    return queue->count == queue->size;
}

bool enqueue(struct queue *queue, int value)
{
    if (is_full(queue)) return false;

    queue->buf[queue->front] = value;
    queue->front = (queue->front + 1) % queue->size;
    queue->count += 1;

    return true;
}

int dequeue(struct queue *queue)
{
    int result;

    if (is_empty(queue)) return -1;

    result = queue->buf[queue->rear];
    queue->rear = (queue->rear + 1) % queue->size;
    queue->count -= 1;

    return result;
}

void destroy_queue(struct queue *queue)
{
    free(queue->buf);
    free(queue);
}

#endif