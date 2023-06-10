#ifndef FILE_UTILS_H
#define FILE_UTILS_H

void removeExtension(const char* fileName, char* result);
unsigned char *readFile(const char *fileName, long *size);

#endif