#include <stdlib.h>

#include "file.h"
#include "param.h"
#include "debug.h"
#include "encode.h"
#include "decode.h"

int main(int argc, char *argv[])
{
	debug("Init - Starting...");

	// Initializing filenames
	char *inputPath = NULL;
	char *outputPath = NULL;
	char *inputFile = malloc(256);

	// Processing parameters
	enum Option command = getParams(argc, argv, &inputPath, &outputPath);

	// getting the input file name
	getFileName(inputPath, inputFile);

	// Creating dump folder
	debug("Init - Targeted file '%s'", inputPath);

	if (command == Encode)
	{
		encode(inputFile, inputPath, outputPath);
	}
	else
	{
		decode(inputFile, inputPath, outputPath);
	}

	debug("End - Clean-up");

	inputPath = NULL;
	outputPath = NULL;

	return 0;
}