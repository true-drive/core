#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "debug.h"
#include "param.h"
#include "folder.h"

enum Option getParams(int argc, char *argv[],  char **inputPath, char **outputPath)
{
  // Validating arguments
	if (argc < 6)
	{
		debug("[Usage] %s [option] -i <input file> -o <output directory>", argv[0]);
		debug("[Usage] Options: encode - Encodes file to binary noise video");
		debug("[Usage] Options: decode - Decodes binary noise video to file");
		exit(1);
	}

	enum Option command;
	const char *commandName = argv[1];

	if (strcmp(commandName, "encode") == 0)
	{
		command = Encode;
	}
	else if (strcmp(commandName, "decode") == 0)
	{
		command = Decode;
	}
	else
	{
		debug("[Error] Init - Invalid option '%s'", commandName);
    exit(1);
	}
	
	for (int i = 2; i < argc; i += 2)
  {
		if (strcmp(argv[i], "-i") == 0)
    {
			*inputPath = argv[i + 1];
		}
    else if (strcmp(argv[i], "-o") == 0)
		{
			*outputPath = argv[i + 1];
		}
    else
    {
			debug("[Error] Init - Invalid option '%s'", argv[i]);
			exit(1);
		}
	}

  if (*inputPath == NULL || *outputPath == NULL) {
    debug("[Error] Init - Input and output paths must be provided");
    exit(1);
  }

	// getting the output directory path
	getDirPath(*outputPath, *outputPath);
	createFolder(*outputPath, command, *outputPath);

	return command;
}