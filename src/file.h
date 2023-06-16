#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>

void getDirPath(const char *path, char **dirPath);
void getFileName(const char *filePath, char **fileName);
bool hasAnyExtension(const char *fileName);
bool hasExtension(const char *fileName, const char *extension);
int getFileCount(const char *directory, const char *extension);
unsigned char *readFile(const char *fileName, size_t *size);
void writeFile(const char *path, const unsigned char *buffer, long bufferSize);

#endif