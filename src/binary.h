#ifndef BINARY_UTILS_H
#define BINARY_UTILS_H

unsigned char *charToBinary(unsigned char byte);
unsigned char *readBinaryFile(const char *fileName, long *size);
unsigned char *writeBinaryFile(const char *fileName, const unsigned char *content);

#endif