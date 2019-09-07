#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "../util/hashtable/hashtable.h"
#include "../util/queue/priority_queue.h"
#include "../util/tree/binary_tree.h"

#define ASCII_TABLE_SIZE 256

/**
 * Character used to represent parent binary tree of two leafs in the Huffman's coding algorithm.
 */
#define INTERNAL_NODE_SYMBOL '*'
/**
 * Character used to scape the internal node symbol and itself symbol on leaves.
 */
#define SCAPE_SYMBOL '\\'

/**
 * Frequency node alias.
 */
typedef struct _symbol_frequency symbol_frequency_t;

/**
 * Frequency node struct to use as binary tree data.
 */
struct _symbol_frequency {
    unsigned char symbol;
    int frequency;
};

/**
 * Maps the frequency of each symbol of given file in a hashtable.
 *
 * @param file string to file path.
 * @return pointer to {@link hashtable_t} or NULL if file does not exists.
 */
hashtable_t* make_symbol_frequency_map(char *file_path);

/**
 * Creates a leaves priority queue prioritized by symbol frequency in ascending order.
 *
 * @param symbol_frequency_map pointer to symbol frequency hashtable.
 * @return pointer to {@link queue_t} or NULL if function input is NULL.
 */
queue_t* make_leaves_priority_queue(hashtable_t *symbol_frequency_map);

/**
 * Creates a binary tree based on the Huffman's coding algorithm.
 *
 * @param leaves_priority_queue pointer to leaves priority queue prioritized by symbol frequency in ascending order.
 * @return pointer to {@link binary_tree_t} root of {@link frequency_node_t} or NULL if function input is NULL or is
 * a empty queue.
 */
binary_tree_t* make_symbol_frequency_tree(queue_t *leaves_priority_queue);

/**
 * Maps each symbol of frequency tree in its respective binary code based on the Huffman's coding algorithm.
 *
 * @param symbol_frequency_tree pointer to symbol frequency tree.
 * @return pointer to {@link hashtable_t} or NULL if function input is NULL.
 */
hashtable_t* make_symbol_bits_map(binary_tree_t *symbol_frequency_tree);

/**
 * Converts a pre order string to a binary tree.
 *
 * @param string pointer to pre order string.
 * @return pointer to root node of binary tree.
 */
binary_tree_t* tree_from_pre_order_string(unsigned char *string);

#endif
