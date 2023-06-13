#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>

void getDirPath(const char *filePath, char *dirPath);
void getFileName(const char *filePath, char *fileName);
unsigned char *readFile(const char *fileName, long *size);
bool hasExtension(const char *fileName, const char *extension);
int getFileCount(const char *directory, const char *extension);

#endif