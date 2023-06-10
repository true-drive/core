#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "binary.h"
#include "bitmap.h"

int main(int argc, char *argv[])
{
    // Validating arguments
    if (argc != 2)
    {
        printf("Usage: ./truedrive <target file>\n");
        return 1;
    }

    // Fetching the passed input file path
    const char *targetFile = argv[1];

    // Getting the file name
    const size_t fileNameSize = sizeof(char) * strlen(targetFile);
    char *fileName = malloc(fileNameSize);
    removeExtension(targetFile, fileName);

    // Opening the file
    long file_size;
    unsigned char *buffer = readBinaryFile(targetFile, &file_size);

    // Creating binary dump file name
    char *binaryName = malloc(fileNameSize);
    strcpy(binaryName, fileName);
    strcat(binaryName, ".bin");

    // Writing the binary dump
    unsigned char *binary = writeBinaryFile(binaryName, buffer);

    // Creating bitmap dump file name
    char *bitmapName = malloc(fileNameSize);
    strcpy(bitmapName, fileName);
    strcat(bitmapName, ".bmp");

    // Writing the bitmap dump
    unsigned char *pixels = writeBitmapFile(bitmapName, binary);

    free(buffer);
    free(binary);
    free(pixels);

    return 0;
}