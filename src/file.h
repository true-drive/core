#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>

void getFileName(const char* filePath, char* fileName);
void getDirPath(const char *filePath, char *dirPath);
unsigned char *readFile(const char *fileName, long *size);

#endif