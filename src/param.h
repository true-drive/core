#ifndef PARAM_UTILS_H
#define PARAM_UTILS_H

enum Option {
  Encode,
  Decode
};

enum Option getParams(int argc, char *argv[], char **inputPath, char **outputPath);

#endif