#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "param.h"
#include "debug.h"
#include "folder.h"
#include "encode.h"
#include "decode.h"

int main(int argc, char *argv[])
{
	debug("Init - Starting...");

	// Initializing filenames
	char *inputPath = NULL;
	char *outputPath = NULL;
	size_t inputPathSize = 0;
	size_t outputPathSize = 0;

	// Processing parameters
	enum Option command = getParams(argc, argv, &inputPath, &inputPathSize, &outputPath, &outputPathSize);

	// getting the debug directory path
	char *debugDir = NULL;
	getDirPath(outputPath, &debugDir);

	// Debug folder
	char *debugPath = NULL;
	createFolder(debugDir, command, &debugPath);

	// getting the input file name
	char *outputFile = NULL;
	getFileName(outputPath, &outputFile);

	// Creating dump folder
	debug("Init - Input file '%s'", inputPath);
	debug("Init - Output file '%s'", outputPath);
	debug("Init - Debug directory '%s'", debugPath);

	if (command == Encode)
	{
		encode(outputFile, inputPath, outputPath, debugPath);
	}
	else
	{
		decode(outputFile, inputPath, outputPath, debugPath);
	}

	debug("End - Clean-up");

	inputPath = NULL;
	outputPath = NULL;

	return 0;
}