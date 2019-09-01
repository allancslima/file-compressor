#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "../util/tree/binary_tree.h"
#include "../util/hashtable/hashtable.h"

#define ASCII_TABLE_SIZE 256

/**
 * Character used to represent parent binary tree of two leafs in the Huffman's coding algorithm.
 */
#define INTERNAL_NODE_CHAR '*'

/**
 * Frequency node alias.
 */
typedef struct _symbol_frequency symbol_frequency_t;

typedef struct _symbol_bits symbol_bits_t;

/**
 * Frequency node struct to use as binary tree data.
 */
struct _symbol_frequency {
    unsigned char symbol;
    int frequency;
};

struct _symbol_bits {
    unsigned char symbol;
    char *bits;
};

hashtable_t* make_symbol_frequency_map(char *file_path);

/**
 * Makes a content characters frequency tree of the given file using the Huffman's coding algorithm.
 *
 * @param file pointer to file that will be read.
 * @return pointer to binary tree root of {@link frequency_node_t}.
 *
 * @see https://en.wikipedia.org/wiki/Huffman_coding#Compression
 */
binary_tree_t* make_symbol_frequency_tree(hashtable_t *symbol_frequency_map);

hashtable_t* make_symbol_bits_map(binary_tree_t *symbol_frequency_tree);

#endif
