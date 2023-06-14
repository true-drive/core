#ifndef VIDEO_UTILS_H
#define VIDEO_UTILS_H

int extractFrames(const char *inputFile, const char *inputPath, const char *debugPath);
void writeVideo(const char *inputFilePattern, const char *debugPath, const char *outputPath);

#endif