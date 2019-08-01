#include <collections.h>

struct elem { int hash; char *value; } elems[] = {
    {1, "hello"},
    {2, "world"},
    {3, "foo"},
    {4, "bar"}
};

static
void fill_map(
    ecs_map_t *map)
{
    int i, count = sizeof(elems) / sizeof(struct elem);

    for (i = 0; i < count; i ++) {
        ecs_map_set(map, elems[i].hash, &elems[i].value);
    }
}

void Map_setup() {
    ecs_os_set_api_defaults();
}

void Map_count() {
    ecs_map_t *map = ecs_map_new(char*, 16);
    fill_map(map);
    test_int(ecs_map_count(map), 4);
    ecs_map_free(map);
}

void Map_count_empty() {
    ecs_map_t *map = ecs_map_new(char*, 16);
    test_int(ecs_map_count(map), 0);
    ecs_map_free(map);
}

void Map_set_overwrite() {
    ecs_map_t *map = ecs_map_new(char*, 16);
    fill_map(map);
    ecs_map_set(map, 1, &(char*){"foobar"});
    char *value = ecs_map_get_ptr(map, char*, 1);
    test_assert(value != NULL);
    test_str(value, "foobar");
    ecs_map_free(map);
}

void Map_set_rehash() {
    ecs_map_t *map = ecs_map_new(char*, 8);
    fill_map(map);

    test_int(ecs_map_bucket_count(map), 16);

    int i;
    for (i = 5; i < 16; i ++) {
        ecs_map_set(map, i, &(char*){"zzz"});
    }

    test_int(ecs_map_bucket_count(map), 32);
    test_str(ecs_map_get_ptr(map, char*, 1), "hello");
    test_str(ecs_map_get_ptr(map, char*, 2), "world");
    test_str(ecs_map_get_ptr(map, char*, 3), "foo");
    test_str(ecs_map_get_ptr(map, char*, 4), "bar");
    test_str(ecs_map_get_ptr(map, char*, 5), "zzz");
    test_str(ecs_map_get_ptr(map, char*, 6), "zzz");
    test_str(ecs_map_get_ptr(map, char*, 7), "zzz");

    for (i = 1; i < 8; i ++) {
        ecs_map_set(map, i + 1000000, &(char*){"yyy"});
    }    

    test_int(ecs_map_bucket_count(map), 32);
    test_str(ecs_map_get_ptr(map, char*, 1 + 1000000), "yyy");
    test_str(ecs_map_get_ptr(map, char*, 2 + 1000000), "yyy");
    test_str(ecs_map_get_ptr(map, char*, 3 + 1000000), "yyy");
    test_str(ecs_map_get_ptr(map, char*, 4 + 1000000), "yyy");
    test_str(ecs_map_get_ptr(map, char*, 5 + 1000000), "yyy");
    test_str(ecs_map_get_ptr(map, char*, 6 + 1000000), "yyy");
    test_str(ecs_map_get_ptr(map, char*, 7 + 1000000), "yyy");

    ecs_map_free(map);
}

void Map_set_zero_buckets() {
    ecs_map_t *map = ecs_map_new(char*, 0);
    ecs_map_set(map, 1, &(char*){"hello"});
    test_int(ecs_map_count(map), 1);
    ecs_map_free(map);
}

void Map_get() {
    ecs_map_t *map = ecs_map_new(char*, 16);
    fill_map(map);
    char *value = ecs_map_get_ptr(map, char*, 1);
    test_assert(value != NULL);
    test_str(value, "hello");
    ecs_map_free(map);
}

void Map_get_all() {
    ecs_map_t *map = ecs_map_new(char*, 16);
    fill_map(map);

    char *value = ecs_map_get_ptr(map, char*, 1);;
    test_assert(value != NULL);
    test_str(value, "hello");

    value = ecs_map_get_ptr(map, char*, 2);
    test_assert(value != NULL);
    test_str(value, "world");

    value = ecs_map_get_ptr(map, char*, 3);
    test_assert(value != NULL);
    test_str(value, "foo");

    value = ecs_map_get_ptr(map, char*, 4);
    test_assert(value != NULL);
    test_str(value, "bar");

    ecs_map_free(map);
}

void Map_get_empty() {
    ecs_map_t *map = ecs_map_new(char*, 16);
    char *value = ecs_map_get_ptr(map, char*, 1);
    test_assert(value != NULL);
    ecs_map_free(map);
}

void Map_get_unknown() {
    ecs_map_t *map = ecs_map_new(char*, 16);
    fill_map(map);
    char *value = ecs_map_get_ptr(map, char*, 5);
    test_assert(value != NULL);
    ecs_map_free(map);
}

void Map_iter() {
    ecs_map_t *map = ecs_map_new(char*, 16);
    fill_map(map);

    ecs_map_iter_t it = ecs_map_iter(map);
    test_str(ecs_map_next_ptr(&it, char*, NULL), "hello");
    test_str(ecs_map_next_ptr(&it, char*, NULL), "world");
    test_str(ecs_map_next_ptr(&it, char*, NULL), "foo");
    test_str(ecs_map_next_ptr(&it, char*, NULL), "bar");
    test_assert(ecs_map_next_ptr(&it, char*, NULL) == NULL);
}

void Map_iter_empty() {
    ecs_map_t *map = ecs_map_new(char*, 16);
    ecs_map_iter_t it = ecs_map_iter(map);
    test_assert(!ecs_map_next(&it, char*, NULL));
    ecs_map_free(map);
}

void Map_iter_zero_buckets() {
    ecs_map_t *map = ecs_map_new(char*, 0);
    ecs_map_iter_t it = ecs_map_iter(map);
    test_assert(!ecs_map_next(&it, char*, NULL));
    ecs_map_free(map);
}

void Map_remove() {
    ecs_map_t *map = ecs_map_new(char*, 16);
    fill_map(map);
    ecs_map_remove(map, 3);
    test_assert(ecs_map_get(map, char*, 3) != NULL);
    test_int(ecs_map_count(map), 3);
    ecs_map_free(map);
}

void Map_remove_empty() {
    ecs_map_t *map = ecs_map_new(char*, 16);
    ecs_map_remove(map, 3);
    test_int(ecs_map_count(map), 0);
    ecs_map_free(map);
}

void Map_remove_unknown() {
    ecs_map_t *map = ecs_map_new(char*, 16);
    fill_map(map);
    ecs_map_remove(map, 5);
    test_str(ecs_map_get_ptr(map, char*, 1), "hello");
    test_str(ecs_map_get_ptr(map, char*, 2), "world");
    test_str(ecs_map_get_ptr(map, char*, 3), "foo");
    test_str(ecs_map_get_ptr(map, char*, 4), "bar");
    test_int(ecs_map_count(map), 4);
    ecs_map_free(map);
}

