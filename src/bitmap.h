#ifndef BITMAP_UTILS_H
#define BITMAP_UTILS_H

#include <stdint.h>

#pragma pack(push, 1)
typedef struct
{
  uint16_t signature;
  uint32_t fileSize;
  uint32_t reserved;
  uint32_t dataOffset;
  uint32_t headerSize;
  int32_t width;
  int32_t height;
  uint16_t planes;
  uint16_t bitsPerPixel;
  uint32_t compression;
  uint32_t imageSize;
  int32_t xPixelsPerMeter;
  int32_t yPixelsPerMeter;
  uint32_t colorsUsed;
  uint32_t colorsImportant;
} BitmapHeader;
#pragma pack(pop)

int readBitmaps(const char *path, const char *fileName, int frames, int **binary);
void writeBitmaps(const char *path, const char *fileName, unsigned char *binary, long bufferSize);

#endif