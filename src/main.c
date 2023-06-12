#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "param.h"
#include "debug.h"
#include "video.h"
#include "binary.h"
#include "bitmap.h"

int main(int argc, char *argv[])
{
	debug("Init - Starting...");

	// Initializing filenames
	char *inputFileName = NULL;
	char *outputFileName = NULL;
	char *inputFileNamePattern = NULL;

	// Processing parameters
	enum Option command = getParams(argc, argv, &inputFileNamePattern, &inputFileName, &outputFileName);
	debug("Init - Targeted file '%s'", inputFileName);

	if (command == Encode)
	{
		debug("Init - Starting file encoding...");

		// Opening the file
		long bufferSize;
		unsigned char *buffer = readFile(inputFileName, &bufferSize);
		if (buffer == NULL) {
			exit(1);
		}

		// Writing the binary dump
		writeBinary(inputFileNamePattern, buffer, bufferSize);

		// Writing the bitmap dump
		writeBitmaps(inputFileNamePattern, buffer, bufferSize);

		// Converting to bitmap dumps to video file
		writeVideo(inputFileNamePattern, outputFileName);

		free(buffer);
	}
	else
	{
		debug("Init - Starting file decoding...");
	}

	debug("End - Clean-up");

	free(inputFileNamePattern);

	inputFileName = NULL;
	outputFileName = NULL;
	inputFileNamePattern = NULL;

	return 0;
}