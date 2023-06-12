#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "param.h"
#include "debug.h"

void getParams(int argc, char *argv[], const char **inputFileName, const char **outputFileName)
{
  // Validating arguments
	if (argc < 5)
	{
		debug("[Usage] %s -i <input file> -o <output file>\n", argv[0]);
		exit(1);
	}

	for (int i = 1; i < argc; i += 2)
  {
		if (strcmp(argv[i], "-i") == 0)
    {
			*inputFileName = argv[i + 1];
		}
    else if (strcmp(argv[i], "-o") == 0) {
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
	if (hasExtension(outputFileName)) {
		debug("[Error] Init - The output file should be passed with no extension");
		exit(1);
	}

	// Getting the file name
	removeExtension(inputFileName, inputFileName);

	// Check if input and output filenames are the same
	if (strcmp(inputFileName, outputFileName) == 0) {
		debug("[Error] Init - Input and output filenames must be different");
		exit(1);
	}
}