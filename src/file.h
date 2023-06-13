#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>

void getDirPath(const char *filePath, char *dirPath);
void getFileName(const char *filePath, char *fileName);
bool hasExtension(const char *fileName, const char *extension);
unsigned char *readFile(const char *fileName, long *size);

#endif