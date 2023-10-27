#ifndef __STACK__
#define __STACK__

#include <stdbool.h>
#include <stdlib.h>

struct stack {
    int *buf;
    int size;
    int top;
};

struct stack *create_stack(int size);
bool push(struct stack *stack, int value);
int pop(struct stack *stack);
void destroy_stack(struct stack *stack);

struct stack *create_stack(int size)
{
    struct stack *stack;
    stack = (struct stack *)malloc(sizeof(struct stack));
    stack->size = size;
    stack->buf = (int *)malloc(sizeof(int) * stack->size);
    stack->top = -1;
    return stack;
}

bool is_empty(struct stack *stack)
{
    return stack->top == -1;
}

bool is_full(struct stack *stack)
{
    return stack->top == stack->size - 1;
}

bool push(struct stack *stack, int value)
{
    if (is_full(stack)) return false;
    stack->top += 1;
    stack->buf[stack->top] = value;
    return true;
}

int pop(struct stack *stack)
{
    int result;
    if (is_empty(stack)) return -1;
    result = stack->buf[stack->top];
    stack->top -= 1;
    return result;
}

void destroy_stack(struct stack *stack)
{
    free(stack->buf);
    free(stack);
}

#endif