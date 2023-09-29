#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *left, *right, *parent;
};

struct st {
    unsigned int count;
    struct node *root;
};

struct node *rotate(struct node *node)
{
    struct node *parent, *tmp;

    if (node == NULL || node->parent == NULL) return NULL;

    parent = node->parent;
    tmp = node->right;
    parent->left = tmp;
    node->right = parent;

    return node;
}

struct node *create_node(int value)
{
    struct node *node;

    node = (struct node *)malloc(sizeof(struct node));
    node->value = value;
    node->left = node->right = node->parent = NULL;

    return node;
}

void destroy_node(struct node *node)
{
    free(node);
}

void print(struct st *st)
{
    int i = 0;
    struct node **buf, *current;

    buf = (struct node *)malloc(sizeof(struct node) * st->count);
    buf[0] = st->root;

    while (i < st->count) {
        current = buf[i];
        printf("%d ", current->value);

        if (current->left != NULL)
            buf[++i] = current->left;

        if (current->right != NULL)
            buf[++i] = current->right;
    }

    free(buf);
}

void run_splay()
{
    struct st st;
    struct node *a, *b, *c, *d, *e;

    a = create_node(6);
    b = create_node(3);
    c = create_node(8);
    d = create_node(1);
    e = create_node(4);

    a->left = b;
    a->right = c;
    a->left->left = d;
    a->left->right = e;
    b->parent = a;
    c->parent = a;
    d->parent = b;
    e->parent = b;
    st.root = a;
    st.count = 5;

    print(&st);

    destroy_node(a);
    destroy_node(b);
    destroy_node(c);
    destroy_node(d);
    destroy_node(e);
}