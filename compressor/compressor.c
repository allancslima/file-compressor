#include <stdio.h>
#include <stdlib.h>
#include "compressor.h"
#include "../util/hashtable/hashtable.h"
#include "../util/queue/priority_queue.h"

#define ASCII_TABLE_SIZE 256

hashtable_t* count_file_chars(FILE *file);

queue_t* order_chars_count(hashtable_t *hashtable);

int compress_file(char *file_path)
{
	FILE *file = fopen(file_path, "rb");
	hashtable_t *chars_frequency_hashtable = count_file_chars(file);
	queue_t *chars_frequency_queue = order_chars_count(chars_frequency_hashtable);
	return 1;
}

hashtable_t* count_file_chars(FILE *file)
{
    if (file == NULL) {
        return NULL;
    }
    hashtable_t *hashtable = hashtable_create(ASCII_TABLE_SIZE, sizeof(int));
    unsigned char c;
    int sum = 1;

    while (fscanf(file, "%c", &c) != EOF) {
        hashtable_put(hashtable, c, &sum);
    }
    return hashtable;
}

queue_t* order_chars_count(hashtable_t *hashtable)
{
    if (hashtable == NULL) {
        return NULL;
    }
    queue_t *priority_queue = queue_create();

    void block(int key, void *value) {
        int *data = (int*) malloc(sizeof(int));
        int priority = *((int*) value);
        *data = key;
        priority_queue_enqueue(priority_queue, data, priority, ASC);
    }

    hashtable_iterate(hashtable, block);
    return priority_queue;
}
