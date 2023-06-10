#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

unsigned char *writeBinaryFile(const char *filename, const unsigned char *content)
{
    // Opening the file in write mode
    FILE *file = fopen(filename, "w");
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
    return binary;
}
