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
	const char* inputFileName = NULL;
	const char* outputFileName = NULL;

	// Processing parameters
	getParams(argc, argv, &inputFileName, &outputFileName);
	debug("Init - Targeted file '%s'", inputFileName);

	// Opening the file
	long bufferSize;
	unsigned char *buffer = readFile(inputFileName, &bufferSize);
	if (buffer == NULL) {
		exit(1);
	}

	// Writing the binary dump
	writeBinary(inputFileName, buffer, bufferSize);

	// Writing the bitmap dump
	writeBitmaps(inputFileName, buffer, bufferSize);

	// Converting to bitmap dumps to video file
	writeVideo(inputFileName, outputFileName);

	debug("End - Clean-up");
	free(buffer);

	return 0;
}