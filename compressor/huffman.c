#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

typedef enum binary_tree_direction { ROOT, LEFT, RIGHT } BINARY_TREE_DIRECTION;

symbol_frequency_t* create_symbol_frequency(unsigned char symbol, int frequency);

void find_bit_paths(
        binary_tree_t *symbol_frequency_tree,
        BINARY_TREE_DIRECTION direction,
        char *traversal_bits,
        void (*block)(unsigned char symbol, char *bit_path)
);

hashtable_t* make_symbol_frequency_map(char *file_path)
{
    FILE *file = fopen(file_path, "rb");

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

queue_t* make_leaves_priority_queue(hashtable_t *symbol_frequency_map)
{
    if (symbol_frequency_map == NULL) {
        return NULL;
    }
    queue_t *priority_queue = queue_create();

    void block(int key, void *value) {
        unsigned char symbol = key;
        int priority = *((int*) value);
        symbol_frequency_t *symbol_frequency = create_symbol_frequency(symbol, priority);
        binary_tree_t *leaf = binary_tree_create(symbol_frequency, NULL, NULL);

        priority_queue_enqueue(priority_queue, leaf, priority, ASC);
    }

    hashtable_iterate(symbol_frequency_map, block);
    return priority_queue;
}

binary_tree_t* make_symbol_frequency_tree(queue_t *leaves_priority_queue)
{
    if (leaves_priority_queue == NULL || queue_is_empty(leaves_priority_queue)) {
        return NULL;
    }
    while (size(leaves_priority_queue) > 1) {
        binary_tree_t *leaf1 = priority_queue_dequeue(leaves_priority_queue)->data;
        binary_tree_t *leaf2 = priority_queue_dequeue(leaves_priority_queue)->data;

        symbol_frequency_t *symbol_frequency1 = (symbol_frequency_t*) leaf1->data;
        symbol_frequency_t *symbol_frequency2 = (symbol_frequency_t*) leaf2->data;

        symbol_frequency_t *parent_symbol_frequency = create_symbol_frequency(
                INTERNAL_NODE_CHAR,
                symbol_frequency1->frequency + symbol_frequency2->frequency
        );
        binary_tree_t *parent_tree = binary_tree_create(parent_symbol_frequency, leaf1, leaf2);

        priority_queue_enqueue(leaves_priority_queue, parent_tree, parent_symbol_frequency->frequency, ASC);
    }
    return priority_queue_dequeue(leaves_priority_queue)->data;
}

hashtable_t* make_symbol_bits_map(binary_tree_t *symbol_frequency_tree)
{
    if (symbol_frequency_tree == NULL) {
        return NULL;
    }
    hashtable_t *hashtable = hashtable_create(ASCII_TABLE_SIZE, sizeof(int));

    void block(unsigned char symbol, char *bit_path) {
        hashtable_put(hashtable, symbol, bit_path);
    }

    find_bit_paths(symbol_frequency_tree, ROOT, NULL, block);
    return hashtable;
}

symbol_frequency_t* create_symbol_frequency(unsigned char symbol, int frequency)
{
    symbol_frequency_t *symbol_frequency = (symbol_frequency_t*) malloc(sizeof(symbol_frequency_t));
    symbol_frequency->symbol = symbol;
    symbol_frequency->frequency = frequency;

    return symbol_frequency;
}

void find_bit_paths(
        binary_tree_t *symbol_frequency_tree,
        BINARY_TREE_DIRECTION direction,
        char *traversal_bits,
        void (*block)(unsigned char symbol, char *bit_path)
)
{
    if (direction == ROOT) {
        traversal_bits = (char*) malloc(sizeof(char));
        traversal_bits[0] = '\0';
        find_bit_paths(symbol_frequency_tree->left, LEFT, traversal_bits, block);
        find_bit_paths(symbol_frequency_tree->right, RIGHT, traversal_bits, block);
    } else {
        int new_length = strlen(traversal_bits) + 2;
        traversal_bits = (char*) realloc(traversal_bits, sizeof(char) * new_length);
        traversal_bits[new_length - 2] = direction == LEFT ? '0' : '1';
        traversal_bits[new_length - 1] = '\0';

        if (binary_tree_is_leaf(symbol_frequency_tree)) {
            unsigned char symbol = ((symbol_frequency_t*) symbol_frequency_tree->data)->symbol;
            char *copy = (char*) malloc(sizeof(char) * (strlen(traversal_bits) + 1));

            strcpy(copy, traversal_bits);
            block(symbol, copy);
        } else {
            find_bit_paths(symbol_frequency_tree->left, LEFT, traversal_bits, block);
            find_bit_paths(symbol_frequency_tree->right, RIGHT, traversal_bits, block);
        }
        // Removing last character
        new_length = strlen(traversal_bits);
        traversal_bits = (char*) realloc(traversal_bits, sizeof(char) * new_length);
        traversal_bits[new_length - 1] = '\0';
    }
}
