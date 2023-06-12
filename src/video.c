#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "video.h"

void writeVideo(const char *inputFileNamePattern, const char *outputFileName)
{
  debug("Video - Converting bitmap dumps to video output...");
  char command[300];

  char input[100];
  sprintf(input, "%s%%d.bmp", inputFileNamePattern);

  char output[100];
  sprintf(output, "%s.mp4", outputFileName);
  
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