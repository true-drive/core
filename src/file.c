#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "debug.h"
#include "binary.h"

bool hasExtension(const char *fileName, const char *extension)
{
  const char *fileExtension = strrchr(fileName, '.');
  if (fileExtension == NULL)
  {
    return false;
  }

  return strcmp(fileExtension + 1, extension) == 0;
}

bool hasAnyExtension(const char *fileName)
{
  const char *fileExtension = strrchr(fileName, '.');
  return fileExtension != NULL;
}

void getFileName(const char *filePath, char **fileName)
{
  const char *lastSlash = strrchr(filePath, '/');
  const char *lastBackslash = strrchr(filePath, '\\');
  const char *filenameStart = (lastSlash > lastBackslash) ? lastSlash : lastBackslash;
  const char *dot = strrchr(filePath, '.');

  size_t fileNameSize = (sizeof(char) * (strlen(filePath) - strlen(filenameStart))) + 1;
  *fileName = malloc(fileNameSize);
  if (fileName == NULL)
  {
    debug("[Error] - Failed to allocate memory");
    exit(1);
  }

  if (filenameStart != NULL)
  {
    strcpy(*fileName, filenameStart + 1);
  }
  else
  {
    strcpy(*fileName, filePath);
  }

  if (dot != NULL && dot > filenameStart)
  {
    (*fileName)[dot - filenameStart - 1] = '\0';
  }
}

void getDirPath(const char *path, char **dirPath)
{
  const char *lastSlash = strrchr(path, '/');
  const char *lastBackslash = strrchr(path, '\\');
  const char *lastSeparator = lastSlash > lastBackslash ? lastSlash : lastBackslash;

  if (lastSeparator != NULL)
  {
    size_t dirPathLength = lastSeparator - path + 1;
    *dirPath = malloc(dirPathLength + 1);
    if (dirPath == NULL)
    {
      debug("[Error] Init - Failed to allocate memory for directory path");
      exit(1);
    }

    strncpy(*dirPath, path, dirPathLength);
    (*dirPath)[dirPathLength] = '\0';
  }
  else
  {
    *dirPath = strdup("");
    if (*dirPath == NULL)
    {
      debug("[Error] Init - Failed to allocate memory for directory path");
      exit(1);
    }
  }
}

int getFileCount(const char *directory, const char *extension)
{
  int count = 0;
  DIR *dir = opendir(directory);
  if (dir == NULL)
  {
    perror("Error opening directory");
    return -1;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL)
  {
    struct stat fileInfo;
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s", directory, entry->d_name);

    if (stat(filePath, &fileInfo) == 0 && S_ISREG(fileInfo.st_mode))
    {
      const char *fileExtension = strrchr(entry->d_name, '.');
      if (fileExtension != NULL && strcmp(fileExtension + 1, extension) == 0)
      {
        count++;
      }
    }
  }

  closedir(dir);
  return count;
}

unsigned char *readFile(const char *fileName, size_t *size)
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

void writeFile(const char *path, const char *debugPath, const unsigned char *buffer, long bufferSize)
{
  // Target bitmap path
  char *filePath = malloc(strlen(path) + 50);
  sprintf(filePath, "%s", path);

  FILE *file = fopen(filePath, "wb");
  if (file == NULL)
  {
    debug("[Error] File - Could not open file for writing");
    exit(1);
  }

  debug("File - Writing file '%s'...", filePath);

  // Convert the bit sequence to bytes
  unsigned char byte = 0;
  int bitCount = 0;

  for (long i = 0; i < bufferSize; i++)
  {
    byte = (byte << 1) | buffer[i];
    bitCount++;

    if (bitCount == 8)
    {
      fputc(byte, file);
      byte = 0;
      bitCount = 0;
    }
  }

  if (bitCount > 0)
  {
    byte = byte << (8 - bitCount);
    fputc(byte, file);
  }

  fclose(file);
}