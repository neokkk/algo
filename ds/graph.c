#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "disjoint_set.c"

#define BASE 10

#define non_mem_alloc() do { \
    perror("fail to allocate memory"); \
    exit(1); \
} while (0)

struct mg {
    int row, column;
    int **matrix;
};

struct node {
    int from, to, value;
    struct node *prev, *next;
};

struct lg {
    int size;
    struct node **arr;
};

struct mg *create_mg(int r, int c);
int get_mg_value(struct mg *mg, int r, int c);
bool insert_mg_value(struct mg *mg, int r, int c, int value);
bool remove_mg_value(struct mg *mg, int r, int c);
bool validate_mg_range(struct mg *mg, int r, int c);
void print_mg(struct mg *mg);
void destroy_mg(struct mg *mg);

struct lg *create_lg();
struct node *create_node(int from, int to, int value);
bool is_same_node(struct node *a, struct node *b);
struct node *find_lg_node(struct lg *lg, int from);
bool insert_lg_value(struct lg *lg, int from, int to, int value);
struct node *get_lg_node(struct lg *lg, int from, int to);
int get_lg_value(struct lg *lg, int from, int to);
bool remove_lg_value(struct lg *lg, int from, int to);
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

    lg = create_lg();
    insert_lg_value(lg, 0, 1, 4);
    insert_lg_value(lg, 2, 2, 5);
    insert_lg_value(lg, 2, 3, 8);
    assert(get_lg_value(lg, 2, 2) == 5);
    insert_lg_value(lg, 2, 1, 6);
    insert_lg_value(lg, 3, 5, 1);
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
        for (int j = 0; j < mg->column; j++)
            printf("%d ", mg->matrix[i][j]);
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

struct lg *create_lg()
{
    struct lg *lg;

    lg = (struct lg *)malloc(sizeof(struct lg));
    if (lg == NULL) non_mem_alloc();
    lg->size = 0;
    lg->arr = (struct node **)malloc(sizeof(struct node *) * BASE);
    if (lg->arr == NULL) non_mem_alloc();

    return lg;
}

struct node *create_node(int from, int to, int value)
{
    struct node *node;

    node = (struct node *)malloc(sizeof(struct node));
    if (node == NULL) non_mem_alloc();
    node->from = from;
    node->to = to;
    node->value = value;
    node->prev = node->next = NULL;

    return node;
}

bool is_same_node(struct node *a, struct node *b)
{
    if (a->from == b->from && a->to == b->to) return true;
    return false;
}

struct node *find_lg_node(struct lg *lg, int from)
{
    for (int i = 0; i < lg->size; i++) {
        if (lg->arr[i]->from == from) return lg->arr[i];
    }

    return NULL;
}

bool insert_lg_value(struct lg *lg, int from, int to, int value)
{
    struct node *node, *last;

    if (lg->size > 0 && lg->size % BASE == 0) {
        struct node **tmp = realloc(lg->arr, sizeof(struct node *) * (lg->size + BASE));
        if (tmp == NULL) non_mem_alloc();
        lg->arr = tmp;
    }

    node = create_node(from, to, value);
    last = find_lg_node(lg, from);

    if (last != NULL) {
        if (is_same_node(node, last)) return false;
        while (last->next != NULL) {
            last = last->next;
            if (is_same_node(node, last)) return false;
        }
        node->prev = last;
        last->next = node;
    }

    lg->arr[lg->size++] = node;
    return true;
}

struct node *get_lg_node(struct lg *lg, int from, int to)
{
    struct node *node;

    node = find_lg_node(lg, from);
    if (node == NULL) return NULL;

    while (node->to != to) {
        if (node == NULL) return NULL;
        node = node->next;
    }

    return node;
}

int get_lg_value(struct lg *lg, int from, int to)
{
    struct node *node;
    node = get_lg_node(lg, from, to);
    if (node == NULL) return -1;
    return node->value;
}

bool remove_lg_value(struct lg *lg, int from, int to)
{
    struct node *node;

    if (lg->size <= 0) return false;

    node = get_lg_node(lg, from, to);
    if (node == NULL) return false;

    if (node->prev != NULL)
        node->prev->next = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;

    free(node);
    return true;
}

void print_lg(struct lg *lg)
{
    struct node *current;
    struct ds *ds;
    int *ids;
    int size;

    ds = create_ds();

    for (int i = 0; i < lg->size; i++) {
        int from = lg->arr[i]->from;
        make_set(ds, from);
    }

    ids = get_all_ids(ds, &size);
    for (int i = 0; i < size; i++) {
        printf("%d", ids[i]);
        current = find_lg_node(lg, ids[i]);
        while (current != NULL) {
            printf(" -> %d(%d)", current->to, current->value);
            current = current->next;
        }
        printf("\n");
    }

    destroy_ds(ds);
}

void destroy_lg(struct lg *lg)
{
    free(lg->arr);
    free(lg);
}