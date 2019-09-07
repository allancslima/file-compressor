#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compressor.h"
#include "huffman.h"
#include "../util/bitwise/bitwise.h"

/**
 * Writes in a file the leaves of a binary tree traversed in pre order.
 *
 * @param write_in pointer to file.
 * @param symbol_frequency_tree pointer to node root of symbol frequency tree.
 * @return tree size in 2 bytes because 13 bits are needed.
 */
short write_pre_order_tree(FILE *write_in, binary_tree_t *symbol_frequency_tree);

/**
 * Writes in a file the mapped bytes of a symbol bits dictionary.
 *
 * @param write_in pointer to file.
 * @param read_at_path path string of original file.
 * @param symbol_bits_map symbol bits dictionary.
 * @return trash size in 1 byte because 3 bits are needed.
 */
char write_body(FILE *write_in, char *read_at_path, hashtable_t *symbol_bits_map);


int compress_file(char *file_path)
{
    hashtable_t *symbol_frequency_map = make_symbol_frequency_map(file_path);
    queue_t *leaves_priority_queue = make_leaves_priority_queue(symbol_frequency_map);
    binary_tree_t *symbol_frequency_tree = make_symbol_frequency_tree(leaves_priority_queue);
    hashtable_t *symbol_bits_map = make_symbol_bits_map(symbol_frequency_tree);
    FILE *compressed_file = fopen("compressed.huff", "w+");

    fputc(0, compressed_file);
    fputc(0, compressed_file);

    short tree_size = write_pre_order_tree(compressed_file, symbol_frequency_tree);
    char trash_size = write_body(compressed_file, file_path, symbol_bits_map);
    unsigned char first_byte = (trash_size << 5) | (tree_size >> 8);
    unsigned char second_byte = tree_size;

    rewind(compressed_file);
    fputc(first_byte, compressed_file);
    fputc(second_byte, compressed_file);
    fclose(compressed_file);

    return 1;
}


short write_pre_order_tree(FILE *write_in, binary_tree_t *symbol_frequency_tree)
{
    short tree_size = 0;

    void on_internal_node(void *data) {
        unsigned char c = *((char*) data);
        fputc(c, write_in);
        tree_size++;
    }

    void on_leaf(void *data) {
        unsigned char c = *((char*) data);

        if (c == INTERNAL_NODE_SYMBOL || c == SCAPE_SYMBOL) {
            fputc(SCAPE_SYMBOL, write_in);
            tree_size++;
        }
        fputc(c, write_in);
        tree_size++;
    }

    binary_tree_pre_order_2(symbol_frequency_tree, on_internal_node, on_leaf);
    return tree_size;
}

char write_body(FILE *write_in, char *read_at_path, hashtable_t *symbol_bits_map)
{
    FILE *read_at = fopen(read_at_path, "r");
    unsigned char c;
    unsigned char bits[9] = "\0";
    char bits_count = 0;

    while (fscanf(read_at, "%c", &c) != EOF) {
        char *bit_path = hashtable_get(symbol_bits_map, c);
        int i;

        for (i = 0; i < strlen(bit_path); i++) {
            bits[bits_count] = bit_path[i];
            bits[++bits_count] = '\0';

            if (bits_count == 8) {
                fputc(bits_to_byte(bits), write_in);
                bits_count = 0;
                bits[0] = '\0';
            }
        }
    }
    char trash_size = 0;
    char bits_len = strlen(bits);

    if (bits_len > 0) {
        trash_size = 8 - bits_len;

        while (bits_len < 8) {
            bits[bits_len] = '0';
            bits_len++;
        }
        bits[bits_len] = '\0';
        fputc(bits_to_byte(bits), write_in);
    }
    fclose(read_at);
    return trash_size;
}
