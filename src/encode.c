#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "debug.h"
#include "video.h"
#include "binary.h"
#include "bitmap.h"

void encode(const char *outputFile, const char *inputPath, const char *outputPath, const char *debugPath)
{
  debug("Init - Starting file encoding...");

  // Opening the file
  size_t bufferSize;
  unsigned char *buffer = readFile(inputPath, &bufferSize);
  if (buffer == NULL)
  {
    debug("[Error] - Failed to allocated memory for file buffer");
    exit(1);
  }

  // Writing the binary dump
  writeBinary(debugPath, outputFile, buffer, bufferSize);

  // Writing the bitmap dump
  writeBitmaps(debugPath, outputFile, buffer, bufferSize);

  // Converting to bitmap dumps to video file
  writeVideo(outputFile, debugPath, outputPath);

  free(buffer);
}