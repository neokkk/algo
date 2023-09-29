#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * 0: black
 * 1: red
*/
struct node {
    bool color;
    int value;
    struct node *left, *right, *parent;
};

struct rbt {
    unsigned int count;
    struct node *root;
};


struct rbt *create_rbt();
struct node *create_node(int value);
bool insert_node(struct rbt *rbt, int value);
void destroy_node(struct node *node);
void destroy_rbt(struct rbt *rbt);
void fixup(struct node *node);
void print(struct rbt *rbt);

void run_rbt()
{
    struct rbt *rbt;

    rbt = create_rbt();

    insert_node(rbt, 12);
    insert_node(rbt, 7);
    insert_node(rbt, 23);
    insert_node(rbt, 10);
    insert_node(rbt, 3);

    print(rbt);

    destroy_rbt(rbt);
}

struct rbt *create_rbt()
{
    struct rbt *rbt;

    rbt = (struct rbt *)malloc(sizeof(struct rbt));
    rbt->root = NULL;
    rbt->count = 0;

    return rbt;
}

struct node *create_node(int value)
{
    struct node *node;

    node = (struct node *)malloc(sizeof(struct node));
    node->value = value;
    node->color = 1;
    node->left = node->right = node->parent = NULL;

    return node;
}

struct node *find_node(struct node *node, int value)
{
    if (node == NULL) return NULL;
    if (value == node->value) return node;
    if (value < node->value) return find_node(node->left, value);
    if (value > node->value) return find_node(node->right, value);
}

struct node *find_prev(struct node *node)
{
    struct node *current, *prev = NULL;

    current = node->left;

    while (current != NULL) {
        prev = current;
        current = current->right;
    }

    return prev;
}

bool insert_node(struct rbt *rbt, int value)
{
    struct node *child, *current;

    child = create_node(value);

    if (rbt->root == NULL) {
        child->color = 0;
        rbt->root = child;
    } else {
        current = rbt->root;

        while (1) {
            if (value == current->value) return false;
            if (value < current->value) {
                if (current->left == NULL) {
                    current->left = child;
                    child->parent = current;
                    break;
                } else {
                    current = current->left;
                    continue;
                }
            }
            if (value > current->value) {
                if (current->right == NULL) {
                    current->right = child;
                    child->parent = current;
                    break;
                } else {
                    current = current->right;
                    continue;
                }
            }
        }

        fixup(child);
    }

    rbt->count++;
    return true;
}

bool remove_node(struct rbt *rbt, int value)
{
    struct node *parent, *child, *current, *prev;

    current = rbt->root;

    while (current != NULL && current->value != value) {
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) return false;

    if (current->left == NULL || current->right == NULL) {
        child = current->left ? current->left : current->right;

        parent = current->parent;

        if (parent == NULL) {
            rbt->root = child;
        } else if (current == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    } else {
        prev = find_prev(current);
        current->value = prev->value;
        remove_node(rbt, prev->value);
    }

    rbt->count--;
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

void destroy_rbt(struct rbt *rbt)
{
    destroy_node(rbt->root);
    free(rbt);
}

struct node *get_sibling(struct node *node)
{
    struct node *parent;

    if (node == NULL || node->parent == NULL) return NULL;

    parent = node->parent;

    if (node == parent->left) return parent->right;
    if (node == parent->right) return parent->left;
    return NULL;
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

void restructure(struct node *node)
{
    struct node *parent, *grand;

    if (node == NULL || node->parent == NULL || node->parent->parent == NULL) return;

    parent = node->parent;
    grand = parent->parent;

    if (parent == grand->left && node == parent->right) {
        grand->left = left_rotate(node);
        node->parent = grand;
    } else if (parent == grand->right && node == parent->left) {
        grand->right = right_rotate(node);
        node->parent = grand;
        left_rotate(node);
    }

    parent = node->parent;

    if (node == parent->left) {
        right_rotate(node);
    } else if (node == parent->right) {
        left_rotate(node);
    }

    node->color = 0;
    node->left->color = 1;
    node->right->color = 1;
}

void recolor(struct node *node)
{
    struct node *parent, *uncle, *grand;

    if (node == NULL || node->parent == NULL || node->parent->parent == NULL) return;

    parent = node->parent;
    grand = parent->parent;
    uncle = get_sibling(parent);

    parent->color = 0;

    if (uncle != NULL) uncle->color = 0;
    if (grand->parent == NULL) { // root
        grand->color = 0;
    } else {
        grand->color = 1;
        fixup(grand);
    }
}

void fixup(struct node *node)
{
    struct node *uncle;

    if (node->parent == NULL) return;
    if (node->color == 1 && node->parent->color == 1) {
        uncle = get_sibling(node->parent);

        if (uncle == NULL) { // root
            node->parent->color = 0;
        } else {
            if (uncle->color == 0) {
                restructure(node);
            } else if (uncle->color == 1) {
                recolor(node);
            }
        }
    }
}

void print(struct rbt *rbt)
{
    struct node **queue, *current;
    int head = 0, tail = 0;

    current = rbt->root;

    if (current == NULL) return;

    queue = (struct node **)malloc(sizeof(struct node *) * rbt->count);
    queue[head] = current;

    while (tail < rbt->count) {
        current = queue[tail++];

    if (current->left)
        queue[++head] = current->left;

    if (current->right)
        queue[++head] = current->right;
    }

    for (int i = 0; i < rbt->count; i++)
        printf("%d(%s) ", queue[i]->value, queue[i]->color == 0 ? "black" : "red");
    printf("\n");
}