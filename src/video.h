#ifndef VIDEO_UTILS_H
#define VIDEO_UTILS_H

void extractFrames(const char *inputFile, const char *inputPath, const char *outputPath);
void writeVideo(const char *inputFilePattern, const char *outputPath);

#endif