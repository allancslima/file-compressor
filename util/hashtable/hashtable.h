#ifndef HASHTABLE_H
#define HASHTABLE_H

/**
 * Alias for the hash table struct.
 */
typedef struct _hashtable hashtable_t;

/**
 * Allocates memory to an empty {@link hashtable_t}.
 *
 * @param capacity initial capacity of the hash table.
 * @param data_type_size data type size of hash table values.
 * @return pointer to {@link hashtable_t}.
 */
hashtable_t* hashtable_create(int capacity, size_t data_type_size);

/**
 * Associates the specified value to the specified key.
 *
 * @param hashtable where to do the operation.
 * @param key integer key.
 * @param value pointer to the allocated value.
 */
void hashtable_put(hashtable_t *hashtable, int key, void *value);

/**
 * Gets the value associated to the specified key.
 *
 * @param hashtable where to do the operation.
 * @param key integer key.
 * @return value associated to the key
 */
void* hashtable_get(hashtable_t *hashtable, int key);

/**
 * Deallocate from memory the value associated to the specified key.
 *
 * @param hashtable where to do the operation.
 * @param key integer key.
 */
void hashtable_remove(hashtable_t *hashtable, int key);

/**
 * Checks if the specified key has an associated value in the hash table.
 *
 * @param hashtable where to do the operation.
 * @param key integer key.
 * @return 1 if has an associated value or 0 otherwise.
 */
int hashtable_contains_key(hashtable_t *hashtable, int key);

/**
 * Traverses the hash table returning the existent key-value pairs.
 *
 * @param hashtable where to do the operation.
 * @param block pointer to function that receives the existent keys with their associated values.
 */
void hashtable_iterate(hashtable_t *hashtable, void (*block)(int key, void *value));

#endif
