#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "binary.h"

unsigned char *charToBinary(unsigned char byte)
{
    unsigned char *binary = (unsigned char *)malloc(9 * sizeof(char));
    if (binary == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    for (int i = 7; i >= 0; i--)
    {
        binary[7 - i] = '0' + ((byte >> i) & 1);
    }

    binary[8] = '\0';
    return binary;
}

unsigned char *writeBinary(const char *fileName, const unsigned char *content)
{
    debug("Binary - Writing binary dump...");

    // Creating binary dump file name
    char *binaryName = malloc(strlen(fileName));
    strcpy(binaryName, fileName);
    strcat(binaryName, ".bin");

    // Opening the file in write mode
    FILE *file = fopen(binaryName, "w");
    if (!file)
    {
        printf("Failed to open file for writing.\n");
        return NULL;
    }

    // Content length
    int size = strlen((char *)content);
    unsigned char *binary = (unsigned char *)malloc(size * 9 * sizeof(char));

    // Writing the content to the file
    for (int i = 0; i < size; i++)
    {
        strcat((char *)binary, (char *)charToBinary(content[i]));
    }

    // Writing to file
    fprintf(file, "%s", binary);

    // Closing the file
    fclose(file);

    debug("Binary - Binary dumped to file '%s'", binaryName);
    debug("Binary - Binary length %d", strlen((char *)binary));

    return binary;
}
