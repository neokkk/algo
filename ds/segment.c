#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct st {
  int h;
  int *input, *buf;
};

struct st *create_st(int *input, int size);
int init(struct st *st, int start, int end, int node);
int sum(struct st *st, int start, int end, int node, int left, int right);
void update(struct st *st, int start, int end, int node, int idx, int diff);
void print(struct st *st, int end, int node, int level);
void destroy_st(struct st *st);

void run_st()
{
  struct st *st;
  int arr[] = {1, 9, 3, 8, 4, 5, 5, 9, 10, 3, 4, 5};

  st = create_st(arr, 12);
  assert(init(st, 0, 11, 0) == 66);

  assert(sum(st, 0, 11, 0, 0, 11) == 66);
  assert(sum(st, 0, 11, 0, 3, 8) == 41);

  update(st, 0, 11, 0, 5, 1);
  assert(sum(st, 0, 11, 0, 3, 8) == 67);
  print(st, (1 << (st->h + 1)) - 1, 0, 1);

  destroy_st(st);
}

struct st *create_st(int *input, int size)
{
  struct st *st;

  st = (struct st *)malloc(sizeof(struct st));
  st->h = (int)ceil(log2(size));
  st->input = input;
  st->buf = (int *)calloc(1 << (st->h + 1), sizeof(int));

  return st;
}

int init(struct st *st, int start, int end, int node)
{
  int mid;

  if (start == end) return st->buf[node] = st->input[start];

  mid = (start + end) / 2;

  return st->buf[node] = init(st, start, mid, node * 2 + 1) + init(st, mid + 1, end, node * 2 + 2);
}

int sum(struct st *st, int start, int end, int node, int left, int right)
{
  int mid;

  if (left > end || right < start) return 0;
  if (left <= start && end <= right) return st->buf[node];

  mid = (start + end) / 2;

  return sum(st, start, mid, node * 2 + 1, left, right) + sum(st, mid + 1, end, node * 2 + 2, left, right);
}

void update(struct st *st, int start, int end, int node, int idx, int diff)
{
  int mid;

  if (idx < start || idx > end) return;

  st->buf[node] += diff;

  if (start != end) {
    mid = (start + end) / 2;

    update(st, start, mid, node * 2 + 1, idx, value);
    update(st, mid + 1, end, node * 2 + 2, idx, value);
  }
}

void print(struct st *st, int end, int node, int level)
{
  if (end < node) return;

  printf("[level %d] %d \n", level, st->buf[node]);

  print(st, end, node * 2 + 1, level + 1);
  print(st, end, node * 2 + 2, level + 1);
}

void destroy_st(struct st *st)
{
  free(st->buf);
  free(st);
}