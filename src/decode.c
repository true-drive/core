#include <stdlib.h>

#include "file.h"
#include "video.h"
#include "debug.h"
#include "binary.h"
#include "config.h"
#include "bitmap.h"

void decode(const char *outputFile, const char *inputPath, const char *outputPath, const char *debugPath)
{
  debug("Init - Starting file decoding...");

  // Checking if the file to decode is of a valid type
  if (!hasExtension(inputPath, OUTPUT_EXTENSION))
  {
    debug("[Error] Video - '%s' is not of a valid type", inputPath);
    exit(1);
  }

  // Extracting frames from video
  int frames = extractFrames(outputFile, inputPath, debugPath);

  // Reading bitmaps
  int *binary;
  int binarySize = readBitmaps(debugPath, outputFile, frames, &binary);

  // Copying binary over to buffer
  unsigned char *buffer = malloc(binarySize);
  for (int i = 0; i < binarySize; i++)
  {
    buffer[i] = binary[i];
  }

  // Outputing binary
  writeBinary(debugPath, outputFile, buffer, binarySize);

  // Writing original file
  writeFile(outputPath, buffer, binarySize);

  free(binary);
  free(buffer);
}