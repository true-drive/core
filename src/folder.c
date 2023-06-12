#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "debug.h"
#include "param.h"
#include "config.h"
#include "folder.h"

void createFolder(const char *path, enum Option option, char *folderPath) {
  char mode[7];
  time_t currentTime = time(NULL);
  struct tm *timeInfo = localtime(&currentTime);

  switch(option)
  {
    case Encode:
    {
      strcpy(mode, "encode");
      break;
    }
    case Decode:
    {
      strcpy(mode, "decode");
      break;
    }
  }

  char folderName[256];
  snprintf(folderName, sizeof(folderName), "%s%s_%s_%04d%02d%02d_%02d%02d%02d",
        path, OUTPUT_FOLDER, mode, timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday,
        timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);

  if (mkdir(folderName, 0777) == 0)
  {
    strcpy(folderPath, folderName);
    debug("Init - Dump folder '%s' was created", folderName);
  }
  else
  {
    debug("[Error] Init - Failed to create dump folder");
  }
}