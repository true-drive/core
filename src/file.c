#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "binary.h"

void removeExtension(const char *fileName, char *result)
{
  // Find the last dot in the file name
  const char *dot = strrchr(fileName, '.');

  if (dot)
  {
    // Calculate the length of the name without extension
    size_t length = dot - fileName;

    // Copy the name without extension to the result
    strncpy(result, fileName, length);
    result[length] = '\0';
  }
  else
  {
    // If no dot found, return the original file name
    strcpy(result, fileName);
  }
}

unsigned char *readFile(const char *fileName, long *size)
{
  debug("File - Opening file '%s'...", fileName);

  // Opening the file
  FILE *file = fopen(fileName, "rb");
  if (file == NULL)
  {
    debug("[Error] File - Error opening the file");
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
    debug("[Error] File - Memory allocation failed");
    fclose(file);
    return NULL;
  }

  // Storing the file's content into memory
  fread(buffer, sizeof(unsigned char), *size, file);
  fclose(file);

  debug("File - File opened");
  debug("File - Buffer length %d", strlen((char *)buffer));

  return buffer;
}
