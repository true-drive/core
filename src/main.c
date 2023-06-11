#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "debug.h"
#include "binary.h"
#include "bitmap.h"

int main(int argc, char *argv[])
{
    debug("Init - Starting...");

    // Validating arguments
    if (argc != 2)
    {
        printf("Usage: ./truedrive <target file>\n");
        return 1;
    }

    // Fetching the passed input file path
    const char *targetFile = argv[1];
    debug("Init - Targeted file '%s'", targetFile);

    // Getting the file name
    const size_t fileNameSize = sizeof(char) * strlen(targetFile);
    char *fileName = malloc(fileNameSize);
    removeExtension(targetFile, fileName);

    // Opening the file
    long file_size;
    unsigned char *buffer = readFile(targetFile, &file_size);
    if (buffer == NULL) {
        return 1;
    }

    // Writing the binary dump
    unsigned char *binary = writeBinary(fileName, buffer);
    if (binary == NULL) {
        return 1;
    }

    // Writing the bitmap dump
    unsigned char *pixels = writeBitmaps(fileName, binary);
     if (pixels == NULL) {
        return 1;
    }

    debug("End - Clean-up");
    free(buffer);
    free(binary);
    free(pixels);

    return 0;
}