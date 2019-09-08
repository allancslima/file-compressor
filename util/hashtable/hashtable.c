#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

struct _hashtable {
	int capacity;
	void **table;
};

hashtable_t* hashtable_create(int capacity, size_t data_type_size)
{
    void **new_table = (void**) malloc(sizeof(data_type_size) * capacity);
	hashtable_t *new_hashtable = (hashtable_t*) malloc(sizeof(hashtable_t));
	new_hashtable->capacity = capacity;
	new_hashtable->table = new_table;

	int i;
	for (i = 0; i < capacity; i++) {
	    new_table[i] = NULL;
	}
	return new_hashtable;
}

void hashtable_put(hashtable_t *hashtable, int key, void *value)
{
    hashtable->table[key] = value;
}

void* hashtable_get(hashtable_t *hashtable, int key)
{
    if (hashtable->table[key] == NULL) {
        return NULL;
    }
    return hashtable->table[key];
}

void hashtable_remove(hashtable_t *hashtable, int key)
{
    free(hashtable_get(hashtable, key));
    hashtable->table[key] = NULL;
}

int hashtable_contains_key(hashtable_t *hashtable, int key)
{
    return hashtable_get(hashtable, key) != NULL;
}

void hashtable_iterate(hashtable_t *hashtable, void (*on_pair)(int key, void *value))
{
    int i;
    for (i = 0; i < hashtable->capacity; i++) {
        void *value = hashtable_get(hashtable, i);
        if (value != NULL) {
            on_pair(i, value);
        }
    }
}

void hashtable_free(hashtable_t *hashtable)
{
    int i;
    for (i = 0; i < hashtable->capacity; i++) {
        hashtable_remove(hashtable, i);
    }
    free(hashtable->table);
    free(hashtable);
}
