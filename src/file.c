#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "debug.h"
#include "binary.h"

void getFileName(const char *filePath, char *fileName) {
  const char* lastSlash = strrchr(filePath, '/');
  const char* lastBackslash = strrchr(filePath, '\\');
  const char* filenameStart = (lastSlash > lastBackslash) ? lastSlash : lastBackslash;
  const char* dot = strrchr(filePath, '.');

  if (filenameStart != NULL)
  {
    strcpy(fileName, filenameStart + 1);
  } else
  {
    strcpy(fileName, filePath);
  }

  if (dot != NULL && dot > filenameStart)
  {
    fileName[dot - filenameStart - 1] = '\0';
  }
}

void getDirPath(const char *filePath, char *dirPath) {
  const char* lastSlash = strrchr(filePath, '/');
  const char* lastBackslash = strrchr(filePath, '\\');
  const char* filenameStart = (lastSlash > lastBackslash) ? lastSlash : lastBackslash;

  if (filenameStart != NULL)
  {
    strncpy(dirPath, filePath, filenameStart - filePath + 1);
    dirPath[filenameStart - filePath + 1] = '\0';
  } else
  {
    strcpy(dirPath, "");
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
  unsigned char *buffer = (unsigned char *)malloc(*size * sizeof(unsigned char) * 8);
  if (buffer == NULL)
  {
    debug("[Error] File - Memory allocation failed");
    fclose(file);
    return NULL;
  }

  unsigned char byte;
  size_t bytesRead = 0;
  long bitIndex = 0;

  // Reading file byte by byte and extracting bits
  while (fread(&byte, sizeof(unsigned char), 1, file) == 1)
  {
    for (int i = 7; i >= 0; i--)
    {
      unsigned char bit = (byte >> i) & 1;
      buffer[bitIndex] = bit;
      bitIndex++;
    }

    bytesRead++;
  }

  *size = bytesRead * 8;
  fclose(file);

  debug("File - File opened");
  debug("File - File size %d", *size);

  return buffer;
}
