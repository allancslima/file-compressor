#include <stdio.h>
#include <stdlib.h>
#include "compressor.h"
#include "huffman.h"

int compress_file(char *file_path)
{
	FILE *file = fopen(file_path, "rb");
	binary_tree_t *symbol_frequency_tree = make_symbol_frequency_tree(file);
	make_symbol_bits_map(symbol_frequency_tree);

	return 1;
}

int main()
{
    char *path = "test.txt";
    compress_file(path);

    return 0;
}
