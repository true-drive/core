#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "debug.h"
#include "video.h"
#include "binary.h"
#include "bitmap.h"

int main(int argc, char *argv[])
{
    debug("Init - Starting...");

    // Validating arguments
    if (argc < 3)
    {
        debug("[Usage] ./truedrive <input file> <output file>\n");
        exit(1);
    }

    // Fetching the passed params
    const char* inputFileName = argv[1];
    const char* outputFileName = argv[2];

    debug("Init - Targeted file '%s'", inputFileName);

    // Getting the file name
    const size_t fileNameSize = sizeof(char) * strlen(inputFileName);
    char *fileName = malloc(fileNameSize);
    removeExtension(inputFileName, fileName);

    // Check if input and output filenames are the same
    if (strcmp(fileName, outputFileName) == 0) {
        debug("[Error] Init - Input and output filenames must be different");
        exit(1);
    }

    // Opening the file
    long bufferSize;
    unsigned char *buffer = readFile(inputFileName, &bufferSize);
    if (buffer == NULL) {
        exit(1);
    }

    // Writing the binary dump
    writeBinary(fileName, buffer, bufferSize);

    // Writing the bitmap dump
    writeBitmaps(fileName, buffer, bufferSize);

    // Converting to bitmap dumps to video file
    writeVideo(fileName, outputFileName);

    debug("End - Clean-up");
    free(buffer);

    return 0;
}