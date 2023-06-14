#ifndef PARAM_UTILS_H
#define PARAM_UTILS_H

enum Option
{
  Encode,
  Decode
};

enum Option getParams(int argc, char *argv[], char **inputPath, size_t *inputPathSize, char **outputPath, size_t *outputPathSize);

#endif