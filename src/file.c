#include <string.h>
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