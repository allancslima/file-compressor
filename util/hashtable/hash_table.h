#ifndef hashtable_H
#define hashtable_H

/**
 * Alias for the hash table struct.
 */
typedef struct _hash_table hash_table_t;

/**
 * Allocates memory to an empty {@link hash_table_t}.
 *
 * @param capacity initial capacity of the hash table.
 * @param data_type_size data type size of hash table values.
 * @return pointer to {@link hash_table_t}.
 */
hash_table_t* hashtable_create(int capacity, size_t data_type_size);

/**
 * Associates the specified value to the specified key.
 *
 * @param hash_table where to do the operation.
 * @param key integer key.
 * @param value pointer to the allocated value.
 */
void hashtable_put(hash_table_t *hash_table, int key, void *value);

/**
 * Gets the value associated to the specified key.
 *
 * @param hash_table where to do the operation.
 * @param key integer key.
 * @return value associated to the key
 */
void* hashtable_get(hash_table_t *hash_table, int key);

/**
 * Deallocate from memory the value associated to the specified key.
 *
 * @param hash_table where to do the operation.
 * @param key integer key.
 */
void hashtable_remove(hash_table_t *hash_table, int key);

/**
 * Checks if the specified key has an associated value in the hash table.
 *
 * @param hash_table where to do the operation.
 * @param key integer key.
 * @return 1 if has an associated value or 0 otherwise.
 */
int hashtable_contains_key(hash_table_t *hash_table, int key);

/**
 * Traverses the hash table returning the existent key-value pairs.
 *
 * @param hash_table where to do the operation.
 * @param block pointer to function that receives the existent keys with their associated values.
 */
void hashtable_iterate(hash_table_t *hash_table, void (*block)(int key, void *value));

#endif
