#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "param.h"
#include "debug.h"

enum Option getParams(int argc, char *argv[],  char **inputFileNamePattern, char **inputFileName, char **outputFileName)
{
  // Validating arguments
	if (argc < 6)
	{
		debug("[Usage] %s [option] -i <input file> -o <output file>", argv[0]);
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
			*inputFileName = argv[i + 1];
		}
    else if (strcmp(argv[i], "-o") == 0)
		{
			*outputFileName = argv[i + 1];
		}
    else
    {
			debug("[Error] Init - Invalid option '%s'", argv[i]);
			exit(1);
		}
	}

  if (*inputFileName == NULL || *outputFileName == NULL) {
    debug("[Error] Init - Input and output files must be provided");
    exit(1);
  }

	// Check if the output filename has an extension
	if (hasExtension(*outputFileName)) {
		debug("[Error] Init - The output file should be passed with no extension");
		exit(1);
	}

	// Getting the file name
	char *filename = malloc(strlen(*inputFileName));
	removeExtension(*inputFileName, filename);
	*inputFileNamePattern = malloc(strlen(filename));
	strcpy(*inputFileNamePattern, filename);

	// Check if input and output filenames are the same
	if (strcmp(*inputFileNamePattern, *outputFileName) == 0) {
		debug("[Error] Init - Input and output filenames must be different");
		free(filename);
		exit(1);
	}

	free(filename);
	return command;
}