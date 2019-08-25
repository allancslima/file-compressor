#include <stdio.h>
#include <stdlib.h>
#include "compressor.h"
#include "huffman.h"

int compress_file(char *file_path)
{
	FILE *file = fopen(file_path, "rb");
	binary_tree_t *frequency_tree = make_frequency_tree_from_file(file);

	void block(void *data) {
	    frequency_node_t *node = (frequency_node_t*) data;
	    printf("%c %d\n", node->value, node->frequency);
	}
	binary_tree_pre_order(frequency_tree, block);

	return 1;
}

int main()
{
    char *path = "test.txt";
    compress_file(path);
    return 0;
}
