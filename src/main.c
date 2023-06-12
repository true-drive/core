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
		debug("Init - Starting file encoding...");

		// Opening the file
		long bufferSize;
		unsigned char *buffer = readFile(inputPath, &bufferSize);
		if (buffer == NULL) {
			exit(1);
		}
		// Writing the binary dump
		writeBinary(outputPath, inputFile, buffer, bufferSize);

		// Writing the bitmap dump
		writeBitmaps(outputPath, inputFile, buffer, bufferSize);

		// Converting to bitmap dumps to video file
		writeVideo(inputFile, outputPath);

		free(buffer);
	}
	else
	{
		debug("Init - Starting file decoding...");
	}

	debug("End - Clean-up");

	inputPath = NULL;
	outputPath = NULL;

	return 0;
}