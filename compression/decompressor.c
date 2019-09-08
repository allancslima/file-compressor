#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "../util/bitwise/bitwise.h"

/**
 * Gets the trash size of the given file.
 *
 * @param file_path compressed file path.
 * @return trash size in 1 byte because 3 bits are needed.
 */
char get_trash_size(char *file_path);

/**
 * Gets the tree size of the given file.
 *
 * @param file_path compressed file path.
 * @return tree size in 2 bytes because 13 bits are needed.
 */
short get_tree_size(char *file_path);


void decompress_file(char *file_path, char *output_path)
{
    FILE *compressed_file = fopen(file_path, "r");
    short tree_size = get_tree_size(file_path);

    fseek(compressed_file, 2, SEEK_SET);
    binary_tree_t *symbol_tree = tree_from_pre_order_file(compressed_file, 2, tree_size);

    fseek(compressed_file, 0, SEEK_END);
    long compressed_file_bytes = ftell(compressed_file);

    rewind(compressed_file);
    fseek(compressed_file, 2 + tree_size, SEEK_SET);

    FILE *decompressed_file = fopen(output_path, "w+");
    binary_tree_t *aux_tree = symbol_tree;
    char trash_size = get_trash_size(file_path);
    unsigned char c;

    while (fscanf(compressed_file, "%c", &c) != EOF) {
        char bit;
        char until = ftell(compressed_file) == compressed_file_bytes ? trash_size : 0;

        for (bit = 7; bit >= until; bit--) {
            if (is_bit_set(c, bit)) {
                aux_tree = aux_tree->right;
            } else {
                aux_tree = aux_tree->left;
            }
            if (binary_tree_is_leaf(aux_tree)) {
                unsigned char symbol = *((char*) aux_tree->data);
                fputc(symbol, decompressed_file);
                aux_tree = symbol_tree;
            }
        }
    }
    binary_tree_free(symbol_tree);
}


char get_trash_size(char *file_path)
{
    FILE *file = fopen(file_path, "r");
    unsigned char first_byte = fgetc(file);
    fclose(file);
    return first_byte >> 5;
}

short get_tree_size(char *file_path)
{
    FILE *file = fopen(file_path, "r");
    unsigned char first_byte = fgetc(file);
    unsigned char second_byte = fgetc(file);

    short size = first_byte;
    size <<= 11;
    size >>= 3;
    size |= second_byte;

    fclose(file);
    return size;
}
