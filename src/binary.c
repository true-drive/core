#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary.h"

char *charToBinary(unsigned char byte)
{
    char *binary = (char *)malloc(9 * sizeof(char));
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

void writeBinaryFile(const char *filename, const unsigned char *content)
{
    // Opening the file in write mode
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Failed to open file for writing.\n");
        return;
    }

    // Content length
    int size = strlen((char *)content);

    // Writing the content to the file
    for (int i = 0; i < size; i++)
    {
        const char *binary = charToBinary(content[i]);
        fprintf(file, "%s", binary);
    }

    // Closing the file
    fclose(file);
}

unsigned char *readBinaryFile(const char *filename, long *size)
{
    // Opening the file
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return NULL;
    }

    // Getting the content's length
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocating memory to dump the contents to
    unsigned char *buffer = (unsigned char *)malloc(*size * sizeof(unsigned char));
    if (buffer == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    // Storing the file's content into memory
    fread(buffer, sizeof(unsigned char), *size, file);
    fclose(file);

    return buffer;
}
