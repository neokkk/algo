#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define non_allocate_mem() do { \
  perror("fail to allocate memory"); \
  exit(1); \
} while(0)

struct node {
  bool is_leaf;
  int max_key_count, current_key_count;
  int *keys;
  struct node **ptrs;
};

struct bt {
  int count, t; // minimum degree, t >= 2
  struct node *root;
};

struct bt *create_bt(int t);
struct node *create_node(struct bt *bt);
struct node *find_node(struct node *node, int key, struct node **parent);
bool insert_key(struct bt *bt, int key);
void split_node(struct bt *bt, struct node *node, struct node *parent);
void print_bt(struct node *node, int level);

void run_bt()
{
  struct bt *bt;

  bt = create_bt(3);
  assert(bt->t == 3);
  assert(bt->root->max_key_count == 5);
  assert(bt->root->current_key_count == 0);

  assert(insert_key(bt, 1) == true);
  assert(insert_key(bt, 1) == false);
  assert(insert_key(bt, 2) == true);

  insert_key(bt, 33);
  insert_key(bt, 11);
  insert_key(bt, 6);
  insert_key(bt, 52);
  insert_key(bt, 47);
  insert_key(bt, 74);
  insert_key(bt, 25);
  insert_key(bt, 39);
  insert_key(bt, 16);
  insert_key(bt, 10);
  insert_key(bt, 23);

  print_bt(bt->root, 0);
}

struct bt *create_bt(int t)
{
  struct bt *bt;

  bt = (struct bt *)malloc(sizeof(struct bt));
  if (bt == NULL) {
    non_allocate_mem();
  }
  bt->t = t;
  bt->count = 0;
  bt->root = create_node(bt);

  return bt;
}

struct node *create_node(struct bt *bt)
{
  struct node *node;

  node = (struct node *)malloc(sizeof(struct node));
  if (node == NULL)
    non_allocate_mem();
  node->max_key_count = bt->t * 2 - 1;
  node->current_key_count = 0;
  node->is_leaf = true;
  node->keys = (int *)malloc(sizeof(int) * node->max_key_count);
  if (node->keys == NULL)
    non_allocate_mem();
  node->ptrs = (struct node **)malloc(sizeof(struct node *) * (node->max_key_count + 1));
  if (node->ptrs == NULL)
    non_allocate_mem();
  bt->count += 1;

  for (int i = 0; i < bt->t + 1; i++)
    node->ptrs[i] = NULL;

  return node;
}

bool is_full(struct node *node)
{
  return node->current_key_count == node->max_key_count;
}

bool is_lack(struct node *node)
{
  return node->current_key_count < (node->max_key_count + 1) / 2;
}

struct node *find_node(struct node *node, int key, struct node **parent)
{
  struct node *current;
  int i = 0;

  current = node;

  while (current != NULL) {
    while (i < current->current_key_count && key >= current->keys[i]) {
      i++;
    }
    if (current->is_leaf) break;

    *parent = current;
    current = current->ptrs[i];
  }

  return current;
}

bool insert_key(struct bt *bt, int key)
{
  struct node *current, *parent = NULL;
  int i = 0;

  current = find_node(bt->root, key, &parent);

  if (current == NULL) return false;

  if (current->current_key_count == 0) {
    current->keys[0] = key;
    current->current_key_count++;
    return true;
  }

  if (is_full(current)) {
//    printf("is_full. key: %d\n", key);
    split_node(bt, current, parent);
    current = find_node(bt->root, key, &parent);
  }

  for (i = current->current_key_count; i > 0 && key < current->keys[i - 1]; i--) {
    current->keys[i] = current->keys[i - 1];
  }

  if (current->keys[i - 1] == key) return false;

  current->keys[i] = key;
  current->current_key_count++;

  return true;
}

void balance_node(struct node *parent, int idx)
{

}

int merge_node(struct node *parent, int idx)
{
  struct node *left, *right;
  int target_key, i;

  left = parent->ptrs[idx];
  right = parent->ptrs[idx + 1];
  target_key = parent->keys[idx];

  for (i = 0; i < right->current_key_count; i++) {
    left->keys[left->current_key_count + i] = right->keys[i];
    left->ptrs[left->current_key_count + 1 + i] = right->ptrs[1 + i];
  }

  left->ptrs[left->current_key_count + 1 + i] = right->ptrs[i];
  left->current_key_count += (right->current_key_count + 1);

  for (i = idx; i < parent->current_key_count - 1; i++) {
    parent->keys[i] = parent->keys[i + 1];
    parent->ptrs[i + 1] = parent->ptrs[i + 2];
  }

  parent->current_key_count--;

  free(right->keys);
  free(right->ptrs);
  free(right);

  return target_key;
}

bool delete_key(struct bt *bt, struct node *node, int key)
{
  struct node *current, *parent = NULL, *left, *right;
  int i, j, successor, target_key;

  if (node->current_key_count == 0) return false;

  current = find_node(node, key, &parent);

  if (current == NULL) return false;

  for (i = 0; i < current->current_key_count && key != current->keys[i]; i++);

  if (current->is_leaf) {
    for (; i < current->current_key_count - 1; i++) {
      current->keys[i] = current->keys[i + 1];
    }
    current->current_key_count--;
  } else {
    left = current->ptrs[i];
    right = current->ptrs[i + 1];
    j = left->current_key_count - 1;

    if (left->current_key_count >= bt->t - 1) {
      successor = left->keys[j];
      current->keys[i] = successor;
      delete_key(bt, left, successor);
    } else {
      if (right->current_key_count >= bt->t - 1) {
        successor = right->keys[0];
        current->keys[i] = successor;
        delete_key(bt, right, successor);
      } else {
        target_key = merge_node(current, i);
        delete_key(bt, current, target_key);
      }
    }
  }

  return true;
}

int get_height(struct bt *bt)
{
  return (int)ceil(log(bt->count) / log(bt->t * 2 - 1));
}

int get_median_key(struct node *node)
{
  return node->keys[(node->current_key_count - 1) / 2];
}

void split_node(struct bt *bt, struct node *node, struct node *parent)
{
  int median_key, i;
  struct node *new_node, *new_root;

  median_key = get_median_key(node);
//  printf("median key: %d\n", median_key);

  new_node = create_node(bt);
  new_node->current_key_count = bt->t - 1;
  new_node->is_leaf = node->is_leaf;

  for (i = 0; i < bt->t - 1; i++) {
    new_node->keys[i] = node->keys[bt->t + i];
    node->keys[bt->t + i] = 0;
    node->current_key_count--;
  }

  if (!node->is_leaf) {
    for (i = 0; i < bt->t - 1; i++) {
      new_node->ptrs[i] = node->ptrs[bt->t + i];
      node->ptrs[bt->t + i] = NULL;
    }
  }

  if (node == bt->root) {
    new_root = create_node(bt);
    new_root->is_leaf = false;
    new_root->keys[0] = median_key;
    new_root->ptrs[0] = node;
    new_root->ptrs[1] = new_node;
    node->keys[i] = 0;
    node->current_key_count--;
    bt->root = new_root;
//    printf("create new root\n");
  } else {
    for (i = parent->current_key_count; i > 0 && median_key < parent->keys[i - 1]; i--) {
      parent->keys[i] = parent->keys[i - 1];
      parent->ptrs[i + 1] = parent->ptrs[i];
    }

    parent->keys[i] = median_key;
    parent->ptrs[i + 1] = new_node;
    parent->current_key_count++;
    node->current_key_count--;
  }
}

void print_bt(struct node *node, int level)
{
  struct node *current;
  int i = 0;

  if (node == NULL) return;

  print_bt(node->ptrs[0], level + 1);
  printf("\nlevel: %d\n", level);

  while (i < node->current_key_count) {
    printf("%d ", node->keys[i]);
    print_bt(node->ptrs[i + 1], level + 1);
    i++;
  }
}