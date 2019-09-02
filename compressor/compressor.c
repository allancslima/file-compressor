#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compressor.h"
#include "huffman.h"
#include "../util/bitwise/bitwise.h"

unsigned char calculate_trash_size(hashtable_t *symbol_bits_map, hashtable_t *symbol_frequency_map);

void write_first_byte(FILE *write_in, char trash_size, short tree_size);

void write_second_byte(FILE *write_in, short tree_size);

void write_binary_tree(FILE *write_in, binary_tree_t *symbol_frequency_tree);

void write_bits_map(FILE *write_in, char *file_path, hashtable_t *symbol_bits_map);

int compress_file(char *file_path)
{
    hashtable_t *symbol_frequency_map = make_symbol_frequency_map(file_path);
    queue_t *leaves_priority_queue = make_leaves_priority_queue(symbol_frequency_map);
    binary_tree_t *symbol_frequency_tree = make_symbol_frequency_tree(leaves_priority_queue);
    hashtable_t *symbol_bits_map = make_symbol_bits_map(symbol_frequency_tree);

    char trash_size = calculate_trash_size(symbol_frequency_map, symbol_bits_map);
    short tree_size = binary_tree_size(symbol_frequency_tree);
    FILE *compressed_file = fopen("compressed.huff", "w+");

    write_first_byte(compressed_file, trash_size, tree_size);
    write_second_byte(compressed_file, tree_size);
    write_binary_tree(compressed_file, symbol_frequency_tree);
    write_bits_map(compressed_file, file_path, symbol_bits_map);
    fclose(compressed_file);

    return 1;
}

unsigned char calculate_trash_size(hashtable_t *symbol_frequency_map, hashtable_t *symbol_bits_map)
{
    int bits_count = 0;

    void block(int key, void *data) {
        int symbol_frequency = *((int*) hashtable_get(symbol_frequency_map, key));
        int bits_length = strlen((char*) data);
        bits_count += bits_length * symbol_frequency;
    }

    hashtable_iterate(symbol_bits_map, block);
    return 8 - (bits_count % 8);
}

void write_first_byte(FILE *write_in, char trash_size, short tree_size) {
    unsigned char byte = (trash_size << 5) | (tree_size >> 8);
    fputc(byte, write_in);
}

void write_second_byte(FILE *write_in, short tree_size) {
    unsigned char byte = tree_size;
    fputc(byte, write_in);
}

void write_binary_tree(FILE *write_in, binary_tree_t *symbol_frequency_tree) {

    void block(void *data) {
        char c = *((char*) data);
        fputc(c, write_in);
    }

    binary_tree_pre_order(symbol_frequency_tree, block);
}

void write_bits_map(FILE *write_in, char *file_path, hashtable_t *symbol_bits_map) {
    FILE *read_at = fopen(file_path, "rb");
    unsigned char c;
    unsigned char bits[9];
    bits[0] = '\0';
    int bits_count = 0;

    while (fscanf(read_at, "%c", &c) != EOF) {
        char *bit_path = hashtable_get(symbol_bits_map, c);
        int i;

        for (i = 0; i < strlen(bit_path); i++) {
            int len = strlen(bits);
            bits[len] = bit_path[i];
            bits[len + 1] = '\0';
            bits_count++;

            if (bits_count == 8) {
                unsigned char byte = bits_to_byte(bits);
                fputc(byte, write_in);
                bits[0] = '\0';
                bits_count = 0;
            }
        }
    }
    if (strlen(bits) > 0) {
        int len = strlen(bits);
        while (len < 8) {
            bits[len] = '0';
            len++;
        }
        bits[len] = '\0';
        unsigned char byte = bits_to_byte(bits);
        fputc(byte, write_in);
    }
    fclose(read_at);
}

int main()
{
    char *path = "test.txt";
    compress_file(path);

    return 0;
}
