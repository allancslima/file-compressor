#include <stdio.h>
#include <string.h>
#include "compression/compressor.h"
#include "compression/decompressor.h"

#define ARG_COMPRESS "compress"
#define ARG_DECOMPRESS "decompress"
#define ARG_INPUT  "-i"
#define ARG_OUTPUT "-o"

void handle_input(char *operation, char *input_file_path, char *output_file_path);

int is_valid_input_file(char *input_file_path);

int main(int argc, char **argv)
{
    if (argc < 6) {
        printf("Few arguments.\n");
        return -1;
    }
    if (strcmp(argv[1], ARG_COMPRESS) != 0 && strcmp(argv[1], ARG_DECOMPRESS)) {
        printf("Invalid operation.\n");
        return -1;
    }
    char *operation = argv[1];
    char *input_file_path;
    char *output_file_path;

    if (strcmp(argv[2], ARG_INPUT) != 0) {
        printf("Invalid input argument.\n");
        return -1;
    } else {
        input_file_path = argv[3];
    }

    if (strcmp(argv[4], ARG_OUTPUT) != 0) {
        printf("Invalid output argument.\n");
        return -1;
    } else {
        output_file_path = argv[5];
    }
    handle_input(operation, input_file_path, output_file_path);
    return 0;
}

void handle_input(char *operation, char *input_file_path, char *output_file_path)
{
    if (!is_valid_input_file(input_file_path)) {
        printf("The file not exists or is empty.\n");
        return;
    }
    if (strcmp(operation, ARG_COMPRESS) == 0) {
        compress_file(input_file_path, output_file_path);
        printf("The file has been compressed successfully!\n");
    } else {
        decompress_file(input_file_path, output_file_path);
        printf("The file has been decompressed successfully!\n");
    }
}

int is_valid_input_file(char *input_file_path)
{
    FILE *file = fopen(input_file_path, "r");

    if (file == NULL) {
        return 0;
    }
    char c;

    if (fscanf(file, "%c", &c) == EOF) {
        fclose(file);
        return 0;
    } else {
        fclose(file);
        return 1;
    }
}
