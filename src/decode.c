#include "file.h"
#include "video.h"
#include "debug.h"
#include "config.h"

void decode(char *inputFile, char *inputPath, char *outputPath)
{
  debug("Init - Starting file decoding...");

  // Checking if the file to decode is of a valid type
  if (!hasExtension(inputPath, OUTPUT_EXTENSION))
  {
    debug("[Error] Video - '%s' is not of a valid type", inputPath);
    exit(1);
  }

  // Extracting frames from video
  extractFrames(inputFile, inputPath, outputPath);

  // Get stats
}