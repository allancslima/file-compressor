#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

struct _hash_table {
	int capacity;
	int *table;
};

hash_table_t* hashtable_create(int capacity, size_t data_type_size)
{
    int *new_table = (int*) calloc(capacity, sizeof(int) * capacity);
	hash_table_t *new_hash_table = (hash_table_t*) malloc(sizeof(hash_table_t));

	new_hash_table->capacity = capacity;
	new_hash_table->table = new_table;

	return new_hash_table;
}

void hashtable_put(hash_table_t *hash_table, int key, void *value)
{
    hash_table->table[key] += *((int*) value);
}

void* hashtable_get(hash_table_t *hash_table, int key)
{
    if (hash_table->table[key] < 1) {
        return NULL;
    }
    return &hash_table->table[key];
}

void hashtable_remove(hash_table_t *hash_table, int key)
{
    hash_table->table[key] = 0;
}

int hashtable_contains_key(hash_table_t *hash_table, int key)
{
    return hashtable_get(hash_table, key) != NULL;
}

void hashtable_iterate(hash_table_t *hash_table, void (*block)(int key, void *value))
{
    int i;
    for (i = 0; i < hash_table->capacity; i++) {
        void *value = hashtable_get(hash_table, i);
        if (value != NULL) {
            block(i, value);
        }
    }
}
