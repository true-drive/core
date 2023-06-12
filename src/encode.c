#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "debug.h"
#include "video.h"
#include "binary.h"
#include "bitmap.h"

void encode(char *inputFile, char *inputPath, char *outputPath)
{
  debug("Init - Starting file encoding...");

  // Opening the file
  long bufferSize;
  unsigned char *buffer = readFile(inputPath, &bufferSize);
  if (buffer == NULL) {
    exit(1);
  }
  // Writing the binary dump
  writeBinary(outputPath, inputFile, buffer, bufferSize);

  // Writing the bitmap dump
  writeBitmaps(outputPath, inputFile, buffer, bufferSize);

  // Converting to bitmap dumps to video file
  writeVideo(inputFile, outputPath);

  free(buffer);
}