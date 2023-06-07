#ifndef BINARY_UTILS_H
#define BINARY_UTILS_H

void printBinary(unsigned char byte);
void processBinaryData(const unsigned char *buffer, long size);
unsigned char* readBinaryFile(const char *filename, long *size);

#endif