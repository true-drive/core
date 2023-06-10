#ifndef BINARY_UTILS_H
#define BINARY_UTILS_H

unsigned char *charToBinary(unsigned char byte);
unsigned char *readBinaryFile(const char *filename, long *size);
unsigned char *writeBinaryFile(const char *filename, const unsigned char *content);

#endif