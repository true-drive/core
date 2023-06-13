#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "binary.h"

void writeBinary(const char *path, const char *fileName, const unsigned char *buffer, long bufferSize)
{
    debug("Binary - Writing binary dump...");

    // Creating binary dump file name
    char *binaryName = malloc(strlen(fileName) + strlen(path));
    sprintf(binaryName, "%s/%s.bin", path, fileName);

    // Opening the file in write mode
    FILE *file = fopen(binaryName, "wb");
    if (!file)
    {
        debug("[Error] Binary - Failed to open file for writing");
    }

    // Writing to file
    for (int i = 0; i < bufferSize; i++)
    {
        fprintf(file, "%d", buffer[i]);
    }

    // Closing the file
    fclose(file);

    debug("Binary - Binary dumped to file '%s'", binaryName);
}
