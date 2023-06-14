#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "debug.h"
#include "video.h"
#include "config.h"

int extractFrames(const char *inputFile, const char *inputPath, const char *debugPath)
{
  debug("Video - Extracting frames from video...");
  char command[300];

  char input[100];
  sprintf(input, "%s", inputPath);

  char output[100];
  sprintf(output, "%s/%s%%d.bmp", debugPath, inputFile);

  // Constructing ffmpeg command
  sprintf(command, "ffmpeg -loglevel quiet -i %s %s", input, output);

  // Running ffmpeg
  int error = system(command);
  if (error)
  {
    debug("[Error] Video - FFMPEG could not extract video frames");
    exit(1);
  }

  int frames = getFileCount(debugPath, "bmp");
  debug("Video - Extracted %d frames from video", frames);

  return frames;
}

void writeVideo(const char *inputFilePattern, const char *debugPath, const char *outputPath)
{
  debug("Video - Converting bitmap dumps to video output...");
  char command[300];

  char input[100];
  sprintf(input, "%s/%s%%d.bmp", debugPath, inputFilePattern);

  char output[100];
  sprintf(output, "%s.%s", outputPath, OUTPUT_EXTENSION);

  // Constructing ffmpeg command
  // Default: sprintf(command, "ffmpeg -loglevel quiet -framerate 30 -i %s -c:v libx264 -r 30 %s", input, output);
  // Lossless: sprintf(command, "ffmpeg -framerate 30 -i %s -c:v ffv1 -level 3 -g 1 %s", input, output);
  sprintf(command, "ffmpeg -loglevel quiet -framerate 30 -i %s -c:v libx264rgb -preset ultrafast -crf 0 %s", input, output);

  // Running ffmpeg
  int error = system(command);
  if (error)
  {
    debug("[Error] Video - FFMPEG could not write video output");
    exit(1);
  }

  debug("Video - Video output written to '%s'", output);
}