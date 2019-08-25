#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "../util/tree/binary_tree.h"

#define ASCII_TABLE_SIZE 256

/**
 * Character used to represent parent binary tree of two leafs in the Huffman's coding algorithm.
 */
#define INTERNAL_NODE_CHAR '*'

/**
 * Frequency node alias.
 */
typedef struct _frequency_node frequency_node_t;

/**
 * Frequency node struct to use as binary tree data.
 */
struct _frequency_node {
    unsigned char value;
    int frequency;
};

/**
 * Makes a content characters frequency tree of the given file using the Huffman's coding algorithm.
 *
 * @param file pointer to file that will be read.
 * @return pointer to binary tree root of {@link frequency_node_t}.
 *
 * @see https://en.wikipedia.org/wiki/Huffman_coding#Compression
 */
binary_tree_t* make_frequency_tree_from_file(FILE *file);

#endif
