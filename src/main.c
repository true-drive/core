#include <stdio.h>

int main(int argc, char *argv[]) {
    
    // Validating arguments
    if (argc != 2) {
        printf("Usage: ./truedrive <filename>\n");
        return 1;
    }

    // Fetching passes input file path
    const char *filename = argv[1];

    // Opening the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    
    // Printing content
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    
    // Concluding
    fclose(file);
    return 0;
}