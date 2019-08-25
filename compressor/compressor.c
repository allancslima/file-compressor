#include <stdio.h>
#include <stdlib.h>
#include "compressor.h"
#include "huffman.h"

int compress_file(char *file_path)
{
	FILE *file = fopen(file_path, "rb");
	binary_tree_t *frequency_tree = make_symbol_frequency_tree(file);

	void block(void *data) {
        symbol_frequency_t *node = (symbol_frequency_t*) data;
	    printf("%c %d\n", node->symbol, node->frequency);
	}
	binary_tree_pre_order(frequency_tree, block);

	return 1;
}
