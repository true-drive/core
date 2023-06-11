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
    long bufferSize;
    unsigned char *buffer = readFile(targetFile, &bufferSize);
    if (buffer == NULL) {
        return 1;
    }

    // Writing the binary dump
    writeBinary(fileName, buffer, bufferSize);

    // Writing the bitmap dump
    writeBitmaps(fileName, buffer, bufferSize);

    debug("End - Clean-up");
    free(buffer);

    return 0;
}