#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *left, *right, *parent;
};

struct avl {
    unsigned int count;
    struct node *root;
};

struct avl *create_avl();
struct node *create_node(int value);
struct node *find_prev(struct node *node);
struct node *find_node(struct node *node, int value);
bool insert_node(struct avl *avl, int value);
void destroy_node(struct node *node);
void destroy_avl(struct avl *avl);
int get_height(struct node *node);
int check_bf(struct node *node);
struct node *left_rotate(struct node *node);
struct node *right_rotate(struct node *node);
void rebalance(struct avl *avl);
void print(struct avl *avl);

void run_avl()
{
    struct avl *avl;

    avl = create_avl();

    insert_node(avl, 16);
    insert_node(avl, 28);
    insert_node(avl, 9);
    insert_node(avl, 5);
    insert_node(avl, 12);
    insert_node(avl, 2);
    insert_node(avl, 6);

    print(avl);

    destroy_avl(avl);
}

struct avl *create_avl()
{
    struct avl *avl;

    avl = (struct avl *)malloc(sizeof(struct avl));
    avl->count = 0;
    avl->root = NULL;

    return avl;
}

struct node *create_node(int value)
{
    struct node *node;

    node = (struct node *)malloc(sizeof(struct node));
    node->value = value;
    node->left = node->right = node->parent = NULL;

    return node;
}

struct node *find_prev(struct node *node)
{
    struct node *current, *prev;

    current = node->left;

    while (current != NULL) {
        prev = current;
        current = current->right;
    }

    return prev;
}

struct node *find_node(struct node *node, int value)
{
    if (node == NULL) return NULL;
    if (node->value == value) return node;
    if (node->left && value < node->value) return find_node(node->left, value);
    if (node->right && value > node->value) return find_node(node->right, value);
    return NULL;
}

bool insert_node(struct avl *avl, int value)
{
    struct node *child, *current;

    child = create_node(value);

    if (avl->root == NULL) {
        avl->root = child;
    } else {
        current = avl->root;

        while (1) {
            if (value < current->value) {
                if (current->left == NULL) {
                    current->left = child;
                    child->parent = current;
                    break;
                }
                current = current->left;
                continue;
            }

            if (value > current->value) {
                if (current->right == NULL) {
                    current->right = child;
                    child->parent = current;
                    break;
                }
                current = current->right;
                continue;
            }
        }

        rebalance(avl);
    }

    avl->count++;
    return true;
}

void destroy_node(struct node *node)
{
    if (node == NULL) return;

    if (node->parent != NULL) {
        if (node->parent->left == node) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
    }

    destroy_node(node->left);
    destroy_node(node->right);
    free(node);
}

void destroy_avl(struct avl *avl)
{
    if (avl == NULL) return;
    free(avl);
}

int get_height(struct node *node)
{
    int left_height, right_height;

    if (node == NULL) return -1;

    left_height = get_height(node->left);
    right_height = get_height(node->right);

    return left_height > right_height ? left_height + 1 : right_height + 1;
}

int get_bf(struct node *node)
{
    int left_height, right_height;

    left_height = get_height(node->left);
    right_height = get_height(node->right);

    return left_height - right_height;
}

struct node *left_rotate(struct node *node)
{
    struct node *parent, *tmp;

    if (node == NULL || node->parent == NULL) return node;

    parent = node->parent;
    tmp = node->left;
    parent->right = tmp;
    if (tmp != NULL) tmp->parent = parent;
    node->left = parent;
    parent->parent = node;

    return node;
}

struct node *right_rotate(struct node *node)
{
    struct node *parent, *tmp;

    if (node == NULL || node->parent == NULL) return node;

    parent = node->parent;
    tmp = node->right;
    parent->left = tmp;
    if (tmp != NULL) tmp->parent = parent;
    node->right = parent;
    parent->parent = node;

    return node;
}

struct node *ll(struct node *node)
{
    if (node->left == NULL || node->parent == NULL) return NULL;
    return right_rotate(node);
}

struct node *lr(struct node *node)
{
    struct node *parent;

    if (node->right == NULL || node->parent == NULL) return NULL;

    parent = node->parent;
    parent->left = left_rotate(node->right);
    return right_rotate(parent->left);
}

struct node *rl(struct node *node)
{
    struct node *parent;

    if (node->left == NULL || node->parent == NULL) return NULL;

    parent = node->parent;
    parent->right = left_rotate(node->left);
    return right_rotate(parent->right);
}

struct node *rr(struct node *node)
{
    if (node->right == NULL || node->parent == NULL) return NULL;
    return left_rotate(node);
}

void rebalance(struct avl *avl)
{
    int bf;
    struct node *current;

    if (avl->root == NULL) return;

    bf = get_bf(avl->root);

    if (bf > 1) {
        bf = get_bf(avl->root->left);
        if (bf > 0)
            avl->root = ll(avl->root->left);
        else
            avl->root = lr(avl->root->left);
    }
    else if (bf < -1) {
        bf = get_bf(avl->root->right);
        if (bf < 0)
            avl->root = rr(avl->root->right);
        else
            avl->root = rl(avl->root->right);
    }
}

void print(struct avl *avl)
{
    struct node **queue, *current;
    int head = 0, tail = 0;

    current = avl->root;

    if (current == NULL) return;

    queue = (struct node **)malloc(sizeof(struct node *) * avl->count);
    queue[head] = current;

    while (tail < avl->count) {
        current = queue[tail++];

    if (current->left)
        queue[++head] = current->left;

    if (current->right)
        queue[++head] = current->right;
    }

    for (int i = 0; i < avl->count; i++)
        printf("%d ", queue[i]->value);
    printf("\n");
}
