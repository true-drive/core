#include <stdio.h>
#include <stdlib.h>
#include "binary.h"



void printBinary(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1);
    }
}

void processBinaryData(const unsigned char *buffer, long size) {
    printf("Binary:\n");

    for (int i = 0; i < size; i++) {
        printBinary(buffer[i]);
    }

    printf("\n");
}

unsigned char* readBinaryFile(const char *filename, long *size) {

    // Opening the file
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return NULL;
    }

    // Getting the content's length
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocating memory to dump the contents to
    unsigned char *buffer = (unsigned char *)malloc(*size * sizeof(unsigned char));
    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    // Storing the file's content into memory
    fread(buffer, sizeof(unsigned char), *size, file);
    fclose(file);

    return buffer;
}
