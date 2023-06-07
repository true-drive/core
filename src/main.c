#include <stdio.h>
#include <stdlib.h>
#include "binary.h"


int main(int argc, char *argv[]) {
    
    // Validating arguments
    if (argc != 2) {
        printf("Usage: ./truedrive <filename>\n");
        return 1;
    }

    // Fetching passes input file path
    const char *filename = argv[1];

    // Opening the file
    long file_size;
    unsigned char *buffer = readBinaryFile(filename, &file_size);

    if (buffer != NULL) {
        processBinaryData(buffer, file_size);
        free(buffer);
    }

    return 0;
}