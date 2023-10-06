#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define non_mem_alloc() do { \
  perror("fail to allocate memory"); \
  exit(1); \
} while (0)

struct mg {
  int row, column;
  int **matrix;
};

struct node {
  int value, to;
  struct node *prev, *next;
};

struct lg {
  int n;
  struct node **list;
};

struct mg *create_mg(int r, int c);
int get_mg_value(struct mg *mg, int r, int c);
bool insert_mg_value(struct mg *mg, int r, int c, int value);
bool remove_mg_value(struct mg *mg, int r, int c);
bool validate_mg_range(struct mg *mg, int r, int c);
void print_mg(struct mg *mg);
void destroy_mg(struct mg *mg);

struct lg *create_lg(int n);
struct node *create_node(int to, int value);
bool insert_lg_value(struct lg *lg, int a, int b, int value);
struct node *get_lg_node(struct lg *lg, int a, int b);
int get_lg_value(struct lg *lg, int a, int b);
bool remove_lg_value(struct lg *lg, int a, int b);
bool validate_lg_range(struct lg *lg, int a, int b);
void print_lg(struct lg *lg);
void destroy_lg(struct lg *lg);

void run_mg()
{
  struct mg *mg;

  mg = create_mg(5, 4);
  insert_mg_value(mg, 1, 0, 5);
  assert(get_mg_value(mg, 1, 0) == 5);
  assert(insert_mg_value(mg, 1, 5, 3) == false);
  insert_mg_value(mg, 1, 3, 4);
  insert_mg_value(mg, 3, 2, 8);
  insert_mg_value(mg, 4, 4, 7);
  assert(remove_mg_value(mg, 1, 2) == false);
  print_mg(mg);
  destroy_mg(mg);
}

void run_lg()
{
  struct lg *lg;

  lg = create_lg(5);
  assert(insert_lg_value(lg, 0, 1, 4) == true);
  insert_lg_value(lg, 2, 2, 5);
  insert_lg_value(lg, 2, 3, 8);
  assert(get_lg_value(lg, 2, 2) == 5);
  insert_lg_value(lg, 2, 1, 6);
  assert(insert_lg_value(lg, 3, 5, 1) == false);
  insert_lg_value(lg, 1, 0, 2);
  assert(insert_lg_value(lg, 1, 0, 2) == false);
  remove_lg_value(lg, 2, 3);
  assert(remove_lg_value(lg, 4, 3) == false);
  print_lg(lg);
  destroy_lg(lg);
}

struct mg *create_mg(int r, int c)
{
  struct mg *mg;

  mg = (struct mg *)malloc(sizeof(struct mg));
  if (mg == NULL) non_mem_alloc();

  mg->row = r;
  mg->column = c;
  mg->matrix = (int **)malloc(sizeof(int *) * r);

  for (int i = 0; i < mg->row; i++) {
    mg->matrix[i] = (int *)calloc(mg->column, sizeof(int));
    if (mg->matrix[i] == NULL) non_mem_alloc();
  }

  return mg;
}

int get_mg_value(struct mg *mg, int r, int c)
{
  if (!validate_mg_range(mg, r, c)) return -1;
  return mg->matrix[r][c];
}

bool insert_mg_value(struct mg *mg, int r, int c, int value)
{
  if (!validate_mg_range(mg, r, c)) return false;
  mg->matrix[r][c] = value;
  return true;
}

bool remove_mg_value(struct mg *mg, int r, int c)
{
  if (!validate_mg_range(mg, r, c)) return false;
  mg->matrix[r][c] = 0;
}

bool validate_mg_range(struct mg *mg, int r, int c)
{
  if (r >= mg->row || c >= mg->column) return false;
  if (r < 0 || c < 0) return false;
  return true;
}

void print_mg(struct mg *mg)
{
  for (int i = 0; i < mg->row; i++) {
    for (int j = 0; j < mg->column; j++) {
      printf("%d ", mg->matrix[i][j]);
    }
    printf("\n");
  }
}

void destroy_mg(struct mg *mg)
{
  for (int i = 0; i < mg->row; i++)
    free(mg->matrix[i]);
  free(mg->matrix);
  free(mg);
}

struct lg *create_lg(int n)
{
  struct lg *lg;

  lg = (struct lg *)malloc(sizeof(struct lg));
  if (lg == NULL) non_mem_alloc();
  lg->n = n;
  lg->list = (struct node **)malloc(sizeof(struct node *) * n);
  if (lg->list == NULL) non_mem_alloc();

  for (int i = 0; i < lg->n; i++)
    lg->list[i] = NULL;

  return lg;
}

struct node *create_node(int to, int value)
{
  struct node *node;

  node = (struct node *)malloc(sizeof(struct node));
  if (node == NULL) non_mem_alloc();
  node->value = value;
  node->to = to;
  node->prev = node->next = NULL;

  return node;
}

bool insert_lg_value(struct lg *lg, int a, int b, int value)
{
  struct node *node, *last;

  if (!validate_lg_range(lg, a, b)) return false;

  node = create_node(b, value);
  last = lg->list[a];

  if (last == NULL) {
    lg->list[a] = node;
  } else {
    if (last->to == b) {
      free(node);
      return false;
    }
    while (last->next != NULL) {
      last = last->next;
    }

    node->prev = last;
    last->next = node;
  }

  return true;
}

struct node *get_lg_node(struct lg *lg, int a, int b)
{
  struct node *node;

  if (!validate_lg_range(lg, a, b)) return NULL;

  node = lg->list[a];
  if (node == NULL) return false;

  while (node->to != b) {
    if (node == NULL) return false;
    node = node->next;
  }

  return node;
}

int get_lg_value(struct lg *lg, int a, int b)
{
  struct node *node;

  node = get_lg_node(lg, a, b);

  if (node == NULL) return -1;

  return node->value;
}

bool remove_lg_value(struct lg *lg, int a, int b)
{
  struct node *node;

  if (!validate_lg_range(lg, a, b)) return false;

  node = lg->list[a];
  if (node == NULL) return false;

  while (node->to != b) {
    if (node == NULL) return false;
    node = node->next;
  }

  node->prev->next = node->next;
  if (node->next != NULL)
    node->next->prev = node->prev;

  free(node);

  return true;
}

bool validate_lg_range(struct lg *lg, int a, int b)
{
  if (a >= lg->n || b >= lg->n) return false;
  if (a < 0 || b < 0) return false;
  return true;
}

void print_lg(struct lg *lg)
{
  struct node *current;

  for (int i = 0; i < lg->n; i++) {
    printf("%d: ", i);
    current = lg->list[i];
    while (current != NULL) {
      printf("-> %d(%d) ", current->to, current->value);
      current = current->next;
    }
    printf("\n");
  }
}

void destroy_lg(struct lg *lg)
{
  struct node *current, *next;

  for (int i = 0; i < lg->n; i++) {
    current = lg->list[i];

    if (current == NULL) continue;

    while (current->next != NULL) {
      next = current->next;
      free(current);
      current = next;
    }
  }

  free(lg->list);
  free(lg);
}