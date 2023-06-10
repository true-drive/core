#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitmap.h"

unsigned char *writeBitmapFile(const char *fileName, unsigned char *binary)
{
  int row, column;
  int width = 10;
  int height = 10;
  int size = width * height * 4; // for 32-bit bitmap only

  char header[54] = {0};
  strcpy(header, "BM");
  memset(&header[2], (int)(54 + size), 1);
  memset(&header[10], (int)54, 1); // always 54
  memset(&header[14], (int)40, 1); // always 40
  memset(&header[18], (int)width, 1);
  memset(&header[22], (int)height, 1);
  memset(&header[26], (short)1, 1);
  memset(&header[28], (short)32, 1); // 32bit
  memset(&header[34], (int)size, 1); // pixel size

  int cursor = 0;
  unsigned char *pixels = malloc(size);

  for (row = height - 1; row >= 0; row--)
  {
    for (column = 0; column < width; column++)
    {
      int p = (row * width + column) * 4;
      int index = cursor > (int)strlen((char *)binary) ? 0 : cursor++;
      int color = binary[index] == 48 ? 0 : 255;

      pixels[p + 0] = color; // blue
      pixels[p + 1] = color; // green
      pixels[p + 2] = color; // red
    }
  }

  FILE *file = fopen(fileName, "wb");
  fwrite(header, 1, 54, file);
  fwrite(pixels, 1, size, file);

  fclose(file);

  return pixels;
}