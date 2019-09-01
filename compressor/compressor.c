#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compressor.h"
#include "huffman.h"

int calculate_trash_size(hashtable_t *symbol_bits_map, hashtable_t *symbol_frequency_map);

int compress_file(char *file_path)
{
    hashtable_t *symbol_frequency_map = make_symbol_frequency_map(file_path);
    queue_t *leaves_priority_queue = make_leaves_priority_queue(symbol_frequency_map);
    binary_tree_t *symbol_frequency_tree = make_symbol_frequency_tree(leaves_priority_queue);
    hashtable_t *symbol_bits_map = make_symbol_bits_map(symbol_frequency_tree);

    int trash_size = calculate_trash_size(symbol_frequency_map, symbol_bits_map);

    return 1;
}

int calculate_trash_size(hashtable_t *symbol_frequency_map, hashtable_t *symbol_bits_map)
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

int main()
{
    char *path = "test.txt";
    compress_file(path);

    return 0;
}
