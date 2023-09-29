#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
  int value;
  struct node *left, *right;
};

struct bst {
  struct node *root;
  unsigned int count;
};

struct bst *create_bst();
struct node *find_node(struct node *node, int value);
struct node *find_prev(struct node *node);
bool insert_node(struct bst *bst, int value);
bool remove_node(struct bst *bst, int value);
void print(struct bst *bst);
void destroy_bst(struct bst *bst);

void run_bst()
{
    struct bst *bst;
    struct node *node, *prev;

    bst = create_bst();
    assert(insert_node(bst, 5) == true);
    assert(insert_node(bst, 5) == false);
    assert(insert_node(bst, 5) == false);
    assert(bst->count == 1);
    insert_node(bst, 3);
    insert_node(bst, 8);
    insert_node(bst, 1);
    insert_node(bst, 4);
    insert_node(bst, 6);
    insert_node(bst, 10);
    insert_node(bst, 7);
    print(bst);

    assert(remove_node(bst, 9) == false);
    assert(remove_node(bst, 6) == true);
    assert(bst->count == 7);
    print(bst);

    destroy_bst(bst);
}

struct bst *create_bst()
{
    struct bst *bst;

    bst = (struct bst *)malloc(sizeof(struct bst));
    bst->root = NULL;
    bst->count = 0;

    return bst;
}

struct node *find_node(struct node *node, int value)
{
    if (!node) return NULL;
    if (node->value == value) return node;
    if (node->left && (value < node->value)) return find_node(node->left, value);
    if (node->right && (value > node->value)) return find_node(node->right, value);
    return NULL;
}

struct node *find_prev(struct node *node)
{
    struct node *prev = NULL, *current;

    current = node->left;

    while (current != NULL) {
        prev = current;
        current = current->right;
    }

    return prev;
}

struct node *create_node(int value)
{
    struct node *node;

    node = (struct node *)malloc(sizeof(struct node));
    node->value = value;
    node->left = node->right = NULL;

    return node;
}

bool insert_node(struct bst *bst, int value)
{
    struct node *current, *node;

    if (find_node(bst->root, value)) return false;

    node = create_node(value);

    if (!bst->root) {
        bst->root = node;
    } else {
        current = bst->root;

        while (1) {
            if (value < current->value) {
                if (current->left == NULL) {
                    current->left = node;
                    break;
                }
                current = current->left;
                continue;
            }

            if (value > current->value) {
                if (current->right == NULL) {
                    current->right = node;
                    break;
                }
                current = current->right;
                continue;
            }
        }
    }

    bst->count++;
    return true;
}

bool remove_node(struct bst *bst, int value)
{
    struct node *parent = NULL, *child, *current, *prev;

    current = bst->root;

    while (current && current->value != value) {
        parent = current;

        if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL) return false;

    if (current->left == NULL || current->right == NULL) {
        child = current->left ? current->left : current->right;

        if (parent == NULL)
            bst->root = child;
        else if (parent->left == current)
            parent->left = child;
        else
            parent->right = child;

        free(current);
    } else {
        prev = find_prev(current);
        current->value = prev->value;
        remove_node(bst, prev->value);
    }

    bst->count--;
    return true;
}

void destroy_node(struct node *node)
{
    if (!node) return;
    if (node->left) destroy_node(node->left);
    if (node->right) destroy_node(node->right);

    free(node);
    node = NULL;
}

void print(struct bst *bst)
{
    struct node **queue, *current;
    int head = 0, tail = 0;

    current = bst->root;
    queue = (struct node **)malloc(sizeof(struct node*) * bst->count);

    if (current == NULL) return;

    queue[head] = current;

    while (tail < bst->count) {
        current = queue[tail++];

        if (current->left)
        queue[++head] = current->left;

        if (current->right)
        queue[++head] = current->right;
    }

    for (int i = 0; i < bst->count; i++)
        printf("%d ", queue[i]->value);
    printf("\n");
}

void destroy_bst(struct bst *bst)
{
    destroy_node(bst->root);
    free(bst);
}