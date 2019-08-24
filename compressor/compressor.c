#include <stdio.h>
#include <stdlib.h>
#include "compressor.h"
#include "../util/hashtable/hash_table.h"
#include "../util/queue/priority_queue.h"

#define ASCII_TABLE_SIZE 256

hash_table_t* count_file_chars(FILE *file);

queue_t* order_chars_count(hash_table_t *hash_table);

int compress_file(char *file_path)
{
	FILE *file = fopen(file_path, "rb");
	hash_table_t *char_count_set = count_file_chars(file);
	queue_t *priority_queue = order_chars_count(char_count_set);
	return 1;
}

hash_table_t* count_file_chars(FILE *file)
{
    if (file == NULL) {
        return NULL;
    }
    hash_table_t *hash_table = hashtable_create(ASCII_TABLE_SIZE, sizeof(int));
    unsigned char c;
    int sum = 1;

    while (fscanf(file, "%c", &c) != EOF) {
        hashtable_put(hash_table, c, &sum);
    }
    return hash_table;
}

queue_t* order_chars_count(hash_table_t *hash_table)
{
    if (hash_table == NULL) {
        return NULL;
    }
    queue_t *priority_queue = queue_create();

    void block(int key, void *value) {
        int *data = (int*) malloc(sizeof(int));
        int priority = *((int*) value);
        *data = key;
        priorityqueue_enqueue(priority_queue, data, priority, ASC);
    }

    hashtable_iterate(hash_table, block);
    return priority_queue;
}
