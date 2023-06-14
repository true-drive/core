#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "debug.h"
#include "param.h"

enum Option getParams(int argc, char *argv[], char **inputPath, size_t *inputPathSize, char **outputPath, size_t *outputPathSize)
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
			*inputPathSize = sizeof(char) * strlen(argv[i + 1]);
			*inputPath = (char *)malloc(sizeof(char) * *inputPathSize);
			if (inputPath == NULL)
			{
				debug("[Error] Init - Faild to allocate memory for input path");
				exit(1);
			}

			*inputPath = argv[i + 1];
		}
		else if (strcmp(argv[i], "-o") == 0)
		{
			*outputPathSize = sizeof(char) * strlen(argv[i + 1]);
			*outputPath = (char *)malloc(sizeof(char) * *outputPathSize);
			if (inputPath == NULL)
			{
				debug("[Error] Init - Faild to allocate memory for output path");
				exit(1);
			}

			*outputPath = argv[i + 1];
		}
		else
		{
			debug("[Error] Init - Invalid option '%s'", argv[i]);
			exit(1);
		}
	}

	if (*inputPath == NULL || *outputPath == NULL)
	{
		debug("[Error] Init - Input and output paths must be provided");
		exit(1);
	}

	if (command == Encode && hasAnyExtension(*outputPath))
	{
		debug("[Error] Init - Output file should not have an extension");
		exit(1);
	}

	return command;
}