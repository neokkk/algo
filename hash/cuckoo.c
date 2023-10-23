#include "../util.c"
#include "map.c"

struct cuckoo_map {
    struct map *m1;
    struct map *m2;
};

struct cuckoo_map *create_cuckoo_map(struct map *m1, struct map *m2);
void destroy_cuckoo_map(struct cuckoo_map *c);
char search_c(struct cuckoo_map *c, int value);
bool insert_c(struct cuckoo_map *c, int value, int table, int depth);
bool erase_c(struct cuckoo_map *c, int value);
void print_c(struct cuckoo_map *c);

int quadratic_modulo_func(int n)
{
    return (n + 1) * (n + 1) % P;
}

void run_cuckoo()
{
    struct cuckoo_map *c;
    struct map *m1, *m2;
    m1 = create_map(P, modulo_func);
    m2 = create_map(P, quadratic_modulo_func);
    c = create_cuckoo_map(m1, m2);
    assert(insert_c(c, 3, 1, 0) == true);
    assert(search_c(c, 3) == 1);
    insert_c(c, 4, 1, 0);
    assert(search_c(c, 4) == 2);
    destroy_cuckoo_map(c);
}

struct cuckoo_map *create_cuckoo_map(struct map *m1, struct map *m2)
{
    struct cuckoo_map *c;
    c = (struct cuckoo_map *)malloc(sizeof(struct cuckoo_map));
    c->m1 = m1;
    c->m2 = m2;
    return c;
}

char search_c(struct cuckoo_map *c, int value)
{
    if (search(c->m1, value)) return 1;
    if (search(c->m2, value)) return 2;
    return -1;
}

bool insert_c(struct cuckoo_map *c, int value, int table, int depth)
{
    if (depth > P) return false;
    if (table == 1) {
        if (search(c->m1, value)) return insert(c->m1, value);
        return insert_c(c, value, 2, depth + 1);
    }
    else {
        if (search(c->m2, value)) return insert(c->m2, value);
        return insert_c(c, value, 1, depth + 1);
    }
}

bool erase_c(struct cuckoo_map *c, int value)
{
    char m;
    struct map *map;
    m = search_c(c, value);
    map = m == 1 ? c->m1 : m == 2 ? c->m2 : NULL;
    if (map == NULL) return false;
    erase(map, value);
    return true;
}

void print_c(struct cuckoo_map *c)
{
    print_map(c->m1);
    print_map(c->m2);
}

void destroy_cuckoo_map(struct cuckoo_map *c)
{
    destroy_map(c->m1);
    destroy_map(c->m2);
    free(c);
}