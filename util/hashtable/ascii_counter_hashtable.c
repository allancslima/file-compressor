#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

struct _hashtable {
	int capacity;
	int *table;
};

hashtable_t* hashtable_create(int capacity, size_t data_type_size)
{
    int *new_table = (int*) calloc(capacity, sizeof(int) * capacity);
	hashtable_t *new_hashtable = (hashtable_t*) malloc(sizeof(hashtable_t));
	new_hashtable->capacity = capacity;
	new_hashtable->table = new_table;

	return new_hashtable;
}

void hashtable_put(hashtable_t *hashtable, int key, void *value)
{
    hashtable->table[key] += *((int*) value);
}

void* hashtable_get(hashtable_t *hashtable, int key)
{
    if (hashtable->table[key] < 1) {
        return NULL;
    }
    return &hashtable->table[key];
}

void hashtable_remove(hashtable_t *hashtable, int key)
{
    hashtable->table[key] = 0;
}

int hashtable_contains_key(hashtable_t *hashtable, int key)
{
    return hashtable_get(hashtable, key) != NULL;
}

void hashtable_iterate(hashtable_t *hashtable, void (*block)(int key, void *value))
{
    int i;
    for (i = 0; i < hashtable->capacity; i++) {
        void *value = hashtable_get(hashtable, i);
        if (value != NULL) {
            block(i, value);
        }
    }
}
