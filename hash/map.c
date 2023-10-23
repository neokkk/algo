#include <assert.h>
#include "../util.c"

#define P 7

typedef int (*hash_func)(int n);

struct map {
    int size;
    int *table;
    hash_func func;
};

struct map *create_map(int size, hash_func func);
bool search(struct map *map, int value);
bool insert(struct map *map, int value);
bool erase(struct map *map, int value);
void print_map(struct map *map);
void destroy_map(struct map *map);

int modulo_func(int n)
{
    return n % P;
}

void run_map()
{
    struct map *map;
    map = create_map(P, modulo_func);
    assert(insert(map, 3));
    insert(map, 6);
    insert(map, 9);
    insert(map, 10);
    assert(search(map, 3) == false);
    assert(search(map, 9) == true);
    erase(map, 9);
    assert(search(map, 9) == false);
    destroy_map(map);
}

struct map *create_map(int size, hash_func func)
{
    struct map *map;
    map = (struct map *)malloc(sizeof(struct map));
    map->size = size;
    map->table = (int *)calloc(map->size, sizeof(int));
    map->func = func;
    return map;
}

bool search(struct map *map, int value)
{
    int hash_key = map->func(value);
    return map->table[hash_key] == value;
}

bool insert(struct map *map, int value)
{
    int hash_key = map->func(value);
    if (hash_key >= map->size) return false;
    map->table[hash_key] = value;
    return true;
}

bool erase(struct map *map, int value)
{
    int hash_key;
    if (!search(map, value)) return false;
    hash_key = map->func(value);
    map->table[hash_key] = 0;
    return true;
}

void print_map(struct map *map)
{
    for (int i = 0; i < map->size; i++)
        printf("[%d] %d\n", i, map->table[i]);
}

void destroy_map(struct map *map)
{
    free(map->table);
    free(map);
}