#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "debug.h"
#include "color.h"
#include "config.h"
#include "bitmap.h"

void writeBitmaps(const char *path, const char *fileName, unsigned char *buffer, long bufferSize)
{
  // Iterators
  int row, column;

  // The resolution of the bitmap dump
  int width = BITMAP_WIDTH;
  int height = BITMAP_HEIGHT;

  // The number of bits
  int resolution = width * height;
  int size = resolution * 4;

  // The number of bitmap dump files
  int binaryLength = bufferSize * 4;
  float ratio = (float)binaryLength / (float)size;
  int count = ceil(ratio);

  debug("Bitmap - Resolution %dx%d", width, height);
  debug("Bitmap - Size %d", size);
  debug("Bitmap - Binary size %d", binaryLength);
  debug("Bitmap - Dumps count %d", count);

  for (int i = 0; i < count; i++)
  {
    debug("Bitmap - Generating bitmap %d...", i + 1);

    // Initializing bitmap header
    char header[54] = {0};
    strcpy(header, "BM");

    memset(&header[2], (int)(54 + size), 1);
    memset(&header[10], (int)54, 1);
    memset(&header[14], (int)40, 1);

    // Resolution
    memset(&header[18], (int)(width & 0xFF), 1);
    memset(&header[19], (int)((width >> 8) & 0xFF), 1);
    memset(&header[20], (int)((width >> 16) & 0xFF), 1);
    memset(&header[21], (int)((width >> 24) & 0xFF), 1);
    memset(&header[22], (int)(height & 0xFF), 1);
    memset(&header[23], (int)((height >> 8) & 0xFF), 1);
    memset(&header[24], (int)((height >> 16) & 0xFF), 1);
    memset(&header[25], (int)((height >> 24) & 0xFF), 1);
    memset(&header[26], (short)1, 1);

    // 32-bit
    memset(&header[28], (short)32, 1);

    // Pixel size
    memset(&header[34], (int)size, 1);

    int cursor = 0;
    unsigned char *pixels = malloc(size);

    for (row = height - 1; row >= 0; row--)
    {
      for (column = 0; column < width; column++)
      {
        int p = (row * width + column) * 4;
        int offset = resolution * i;
        int index = (cursor++) + offset;

        // If end of file, color red
        if (index > bufferSize - 1)
        {
          pixels[p + 0] = 0;   // blue
          pixels[p + 1] = 0;   // green
          pixels[p + 2] = 255; // red
        }
        else
        {
          int color = buffer[index] == 0 ? 0 : 255;

          pixels[p + 0] = color; // blue
          pixels[p + 1] = color; // green
          pixels[p + 2] = color; // red
        }
      }
    }

    // Creating bitmap dump file name
    char *bitmapName = malloc(strlen(fileName) + strlen(path) + 10);
    sprintf(bitmapName, "%s/%s%d.bmp", path, fileName, i + 1);

    FILE *file = fopen(bitmapName, "wb");
    fwrite(header, 1, 54, file);
    fwrite(pixels, 1, size, file);

    fclose(file);
    debug("Bitmap - Dumped bitmap chunk %d to '%s'", i + 1, bitmapName);
  }

  debug("Bitmap - Generated all %d bitmap(s)", count);
}

int readBitmaps(const char *path, const char *fileName, int frames, int **binary)
{
  for (int i = 0; i < frames; i++)
  {
    debug("Bitmap - Extracting frame %d...", i + 1);

    // Target bitmap path
    char *bitmapPath = malloc(strlen(path) + strlen(fileName) + 10);
    sprintf(bitmapPath, "%s/%s%d.bmp", path, fileName, i + 1);

    FILE *file = fopen(bitmapPath, "rb");
    if (file == NULL)
    {
      debug("[Error] Bitmap - Could not open file '%s'", bitmapPath);
      exit(1);
    }

    BitmapHeader header;
    fread(&header, sizeof(header), 1, file);

    // Move the file pointer to the beginning of the pixel data
    fseek(file, header.dataOffset, SEEK_SET);

    // Calculate the number of bytes per pixel
    int bytesPerPixel = header.bitsPerPixel / 8;

    // Calculate the row size in bytes (including padding)
    int rowSize = ((header.width * bytesPerPixel) + 3) & ~3;

    // Calculate the size of the pixel data
    int size = rowSize * header.height;

    // Allocate memory for a single row
    uint8_t *rowData = (uint8_t *)malloc(size);
    if (rowData == NULL)
    {
      debug("[Error] Bitmap - Memory allocation failed");
      fclose(file);
      exit(1);
    }

    // Allocate memory to store the pixel data
    unsigned char *pixels = malloc(size);
    if (pixels == NULL)
    {
      debug("[Error] Bitmap - Failed to allocate memory for pixel data");
      fclose(file);
      exit(1);
    }

    debug("Bitmap - Resolution %dx%d", header.width, header.height);
    debug("Bitmap - Size %d", size);

    // Iterate over each row
    for (int y = header.height - 1; y >= 0; y--)
    {
      // Read a row of pixel data
      fread(rowData, 1, rowSize, file);

      // Iterate over each pixel in the row
      for (int x = 0; x < header.width; x++)
      {
        // Calculate the pixel index within the row
        int pixelIndex = x * bytesPerPixel;
        int p = (y * header.width + x) * 3;

        // Access individual color channels
        pixels[p] = rowData[pixelIndex];         // blue
        pixels[p + 1] = rowData[pixelIndex + 1]; // green
        pixels[p + 2] = rowData[pixelIndex + 2]; // red
      }
    }

    // Iteration state
    bool ended = false;
    int binarySize = 0;
    *binary = malloc(header.width * header.height * sizeof(int));

    // Iterating over pixels in memory
    for (int y = 0; y < header.height || !ended; y++)
    {
      for (int x = 0; x < header.width; x++)
      {
        int p = (y * header.width + x) * 3;
        unsigned char blue = pixels[p];
        unsigned char green = pixels[p + 1];
        unsigned char red = pixels[p + 2];

        // Calculate the grayscale value
        unsigned char grayscale = (red + green + blue) / 3;

        // Bit stream for file has ended
        if (isRedish(red, green, blue))
        {
          ended = true;
          break;
        }

        // Bit is 0
        else if (grayscale < 128)
        {
          (*binary)[binarySize++] = 0;
        }

        // Bit is 1
        else if (grayscale > 192)
        {
          (*binary)[binarySize++] = 1;
        }
      }
    }

    // Cleanup
    free(pixels);
    free(rowData);
    fclose(file);

    return binarySize;
  }
}