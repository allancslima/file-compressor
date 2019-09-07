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

/**
 * Gets the pre order string from the given file.
 *
 * @param file_path compressed file path.
 * @return pre order string or NULL if file does not exists.
 */
unsigned char* get_pre_order_tree_string(char *file_path);


int decompress_file(char *file_path)
{
    unsigned char *pre_order_tree_string = get_pre_order_tree_string(file_path);
    binary_tree_t *tree = tree_from_pre_order_string(pre_order_tree_string);

    FILE *decompressed = fopen("decompressed", "w+");
    printf("%s\n", pre_order_tree_string);

    return 0;
}


char get_trash_size(char *file_path)
{
    FILE *file = fopen(file_path, "r");
    unsigned char first_byte;

    fscanf(file, "%c", &first_byte);

    fclose(file);
    return first_byte >> 5;
}

short get_tree_size(char *file_path)
{
    FILE *file = fopen(file_path, "r");
    short first_byte;
    short second_byte;

    fscanf(file, "%c", (char*) &first_byte);
    fscanf(file, "%c", (char*) &second_byte);

    fclose(file);
    return ((unsigned char) (first_byte << 11) >> 3) | second_byte;
}

unsigned char* get_pre_order_tree_string(char *file_path)
{
    short tree_size = get_tree_size(file_path);
    short string_len = tree_size + 1;
    unsigned char *string = (unsigned char*) malloc(sizeof(char) * string_len);

    FILE *file = fopen(file_path, "r");
    fseek(file, 2, SEEK_SET);
    fgets(string, string_len, file);
    string[string_len - 1] = '\0';

    fclose(file);
    return string;
}
