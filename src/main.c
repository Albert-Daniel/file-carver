#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "jpeg_carver.h"


int main(int argc, char *argv[])
{
    if (argc != 2) // There should be a command-line argument 
    {
        printf("Usage: %s input_file\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "rb"); // argv[0] is ./main, but argv[1] is the card.raw
    if (f == NULL) // Checking if card's file could be opened
    {
        printf("Could not open file\n");
        return 2;
    }
    carve_jpeg(f); // Carving JPEGs from the file
    fclose(f); // Closing the file
    return 0;
}