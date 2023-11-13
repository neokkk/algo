#ifndef __DISJOINT_SET__
#define __DISJOINT_SET__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BASE 10

#define non_allocate_mem() do { \
    perror("fail to allocate memory"); \
    exit(1); \
} while(0)

struct unit {
    unsigned int id, rank;
    struct unit *parent;
};

struct ds {
    unsigned int size;
    struct unit **sets;
};

struct ds *create_ds();
struct unit *create_unit(unsigned int id);
struct unit *find_unit(struct ds *ds, unsigned int id);
void add_unit(struct ds *ds, struct unit *unit);
bool make_set(struct ds *ds, unsigned int id);
struct unit *unify(struct ds *ds, unsigned int a, unsigned int b);
void destroy_unit(struct unit *unit);
bool has(struct ds *ds, int id);
int *get_all_ids(struct ds *ds, int *size);
void destroy_ds(struct ds *ds);
void print_ds(struct ds *ds);

void run_ds()
{
    struct ds *ds;
    int arr[] = {1, 2, 3, 4, 5};

    ds = create_ds();
    for (int i = 0; i < 5; i++)
        make_set(ds, arr[i]);

    unify(ds, 2, 3);
    unify(ds, 1, 5);

    print_ds(ds);
    destroy_ds(ds);
}

struct ds *create_ds()
{
    struct ds *ds;

    ds = (struct ds *)malloc(sizeof(struct ds));
    if (ds == NULL)
        non_allocate_mem();
    ds->size = 0;
    ds->sets = (struct unit **)malloc(sizeof(struct unit *) * BASE);
    if (ds->sets == NULL) {
        destroy_ds(ds);
        non_allocate_mem();
    }

    return ds;
}

struct unit *create_unit(unsigned int id)
{
    struct unit *unit;

    unit = (struct unit *)malloc(sizeof(struct unit));
    if (unit == NULL)
        non_allocate_mem();
    unit->id = id;
    unit->rank = 0;
    unit->parent = unit;

    return unit;
}

struct unit *find_unit(struct ds *ds, unsigned int id) {
    if (ds->size > 0) {
        for (int i = 0; i < ds->size; i++) {
            if (ds->sets[i]->id == id)
                return ds->sets[i];
        }
    }

    return NULL;
}

void add_unit(struct ds *ds, struct unit *unit)
{
    struct unit **tmp;

    if (ds->size > 0 && ds->size % BASE == 0) {
        tmp = (struct unit **)realloc(ds->sets, sizeof(struct unit *) * (ds->size + BASE));
        if (tmp == NULL) {
            destroy_unit(unit);
            destroy_ds(ds);
            non_allocate_mem();
        }
        ds->sets = tmp;
    }
    ds->sets[ds->size++] = unit;
}

bool make_set(struct ds *ds, unsigned int id)
{
    struct unit *unit;

    if (find_unit(ds, id)) return false;

    unit = create_unit(id);
    add_unit(ds, unit);

    return true;
}

struct unit *find_root(struct unit *unit)
{
    struct unit *current = unit;

    while (current->parent != unit) {
        current = current->parent;
    }

    return current;
}

void swap_ds(struct unit *a, struct unit *b)
{
    struct unit *tmp;

    tmp = a;
    a = b;
    b = tmp;
}

struct unit *unify(struct ds *ds, unsigned int a, unsigned int b)
{
    struct unit *ua, *ub;

    ua = find_unit(ds, a);
    ub = find_unit(ds, b);

    if (ua == NULL || ub == NULL) return NULL;

    ua = find_root(ua);
    ub = find_root(ub);

    if (ua == ub) return NULL; // cycle!
    if (ua->rank < ub->rank) swap_ds(ua, ub);

    ua->rank++;
    ub->parent = ua->parent;

    return ub;
}

bool has(struct ds *ds, int id)
{
    for (int i = 0; i < ds->size; i++) {
        if (ds->sets[i]->id == id) return true;
    }
    return false;
}

int *get_all_ids(struct ds *ds, int *size)
{
    int *arr;
    arr = malloc(sizeof(int) * ds->size);
    for (int i = 0; i < ds->size; i++)
        arr[i] = ds->sets[i]->id;
    *size = ds->size;
    return arr;
}

void destroy_unit(struct unit *unit)
{
    free(unit);
}

void destroy_ds(struct ds *ds)
{
    if (ds->sets != NULL) {
        for (int i = 0; i < ds->size; i++)
            destroy_unit(ds->sets[i]);
        free(ds->sets);
    }
    free(ds);
}

void print_ds(struct ds *ds)
{
    for (int i = 0; i < ds->size; i++) {
        struct unit *current = ds->sets[i];

        printf("%d", ds->sets[i]->id);
        while (current != current->parent) {
            current = current->parent;
            printf(" -> %d", current->id);
        }
        printf("\n");
    }
}

#endif