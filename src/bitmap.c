#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "debug.h"
#include "config.h"
#include "bitmap.h"

void writeBitmaps(const char *fileName, unsigned char *buffer, long bufferSize)
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
    char *bitmapName = malloc(strlen(fileName));
    sprintf(bitmapName, "%s%d.bmp", fileName, i + 1);

    FILE *file = fopen(bitmapName, "wb");
    fwrite(header, 1, 54, file);
    fwrite(pixels, 1, size, file);

    fclose(file);
    debug("Bitmap - Dumped bitmap chunk %d to '%s'", i + 1, bitmapName);
  }

  debug("Bitmap - Generated all %d bitmap(s)", count);
}