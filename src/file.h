#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>

bool hasExtension(const char* fileName);
void removeExtension(const char* fileName, char* result);
unsigned char *readFile(const char *fileName, long *size);

#endif