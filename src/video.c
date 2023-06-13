#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "video.h"
#include "config.h"

void extractFrames(const char *inputFile, const char *inputPath, const char *outputPath)
{
  debug("Video - Extracting frames from video...");
  char command[300];

  char input[100];
  sprintf(input, "%s", inputPath);
  
  char output[100];
  sprintf(output, "%s/%s%%d.bmp", outputPath, inputFile);

  // Constructing ffmpeg command
  sprintf(command, "ffmpeg -i %s -vf \"select='eq(n,0)',setpts=N/TB,scale=w=-1:h=-1\" -frames:v 1 %s", input, output);
  
  // Running ffmpeg
  int error = system(command);
  if (error) {
    debug("[Error] Video - FFMPEG could not extract video frames");
    exit(1);
  }
}

void writeVideo(const char *inputFilePattern, const char *outputPath)
{
  debug("Video - Converting bitmap dumps to video output...");
  char command[300];

  char input[100];
  sprintf(input, "%s/%s%%d.bmp", outputPath, inputFilePattern);

  char output[100];
  sprintf(output, "%s/%s.%s", outputPath, OUTPUT_FILE, OUTPUT_EXTENSION);
  
  // Constructing ffmpeg command
  sprintf(command, "ffmpeg -framerate 30 -i %s -c:v libx264 -r 30 %s", input, output);
  
  // Running ffmpeg
  int error = system(command);
  if (error) {
    debug("[Error] Video - FFMPEG could not write video output");
    exit(1);
  }

  debug("Video - Video output written to '%s'", output);
}