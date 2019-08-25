#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "../util/hashtable/hashtable.h"
#include "../util/queue/priority_queue.h"

hashtable_t* create_frequency_hashtable(FILE *file);

queue_t* create_leaves_priority_queue(hashtable_t *frequency_hashtable);

frequency_node_t* create_frequency_node(unsigned char c, int frequency);

binary_tree_t* make_frequency_tree_from_file(FILE *file)
{
    hashtable_t *frequency_hashtable = create_frequency_hashtable(file);
    queue_t *tree_priority_queue = create_leaves_priority_queue(frequency_hashtable);

    if (queue_is_empty(tree_priority_queue)) {
        return NULL;
    }
    while (size(tree_priority_queue) > 1) {
        binary_tree_t *leaf1 = priority_queue_dequeue(tree_priority_queue)->data;
        binary_tree_t *leaf2 = priority_queue_dequeue(tree_priority_queue)->data;

        frequency_node_t *node1 = (frequency_node_t*) leaf1->data;
        frequency_node_t *node2 = (frequency_node_t*) leaf2->data;

        frequency_node_t *parent_node = create_frequency_node(INTERNAL_NODE_CHAR, node1->frequency + node2->frequency);
        binary_tree_t *parent_tree = binary_tree_create(parent_node, leaf1, leaf2);

        priority_queue_enqueue(tree_priority_queue, parent_tree, parent_node->frequency, ASC);
    }
    return priority_queue_dequeue(tree_priority_queue)->data;
}

hashtable_t* create_frequency_hashtable(FILE *file)
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

queue_t* create_leaves_priority_queue(hashtable_t *frequency_hashtable)
{
    if (frequency_hashtable == NULL) {
        return NULL;
    }
    queue_t *priority_queue = queue_create();

    void block(int key, void *value) {
        unsigned char c = key;
        int priority = *((int*) value);
        frequency_node_t *frequency_node = create_frequency_node(c, priority);
        binary_tree_t *leaf = binary_tree_create(frequency_node, NULL, NULL);

        priority_queue_enqueue(priority_queue, leaf, priority, ASC);
    }

    hashtable_iterate(frequency_hashtable, block);
    return priority_queue;
}

frequency_node_t* create_frequency_node(unsigned char value, int frequency)
{
    frequency_node_t *node = (frequency_node_t*) malloc(sizeof(frequency_node_t));
    node->value = value;
    node->frequency = frequency;

    return node;
}
