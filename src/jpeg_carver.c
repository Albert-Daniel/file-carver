#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "jpeg_carver.h"
#include <sys/stat.h>
#include <errno.h>

#define BLOCK_SIZE 512

#define JPG_folder "JPEGs"

void carve_jpeg(FILE *card)
{
    if (mkdir(JPG_folder, 0755) == -1 && errno != EEXIST)
    {
        perror("mkdir failed");
    }

    uint8_t buffer[BLOCK_SIZE]; // Buffer to hold the chunks of memory we work with

    int JPEG_count = 0; // Number of files already opened

    FILE *img = NULL;
    char filename[14]; // Filename will have 13 chars + NULL

    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE) // As long as it's memory
    {
        bool is_jpeg = buffer[0] == 0xff && // values a JPEG starts with
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0;

        if (is_jpeg) // If it's the start of a new JPEG file
        {
            if (img != NULL) // if its not the first image
                fclose(img); // close the previous

            sprintf(filename, "%s/%03i.jpg", JPG_folder, JPEG_count); // Create a name (string) for the actual image
            img = fopen(filename, "wb");  // Open the new image file to write binary in it
            if (img == NULL)
                return;
            fwrite(buffer, 1, BLOCK_SIZE, img); // Write the first bytes into the new image
            JPEG_count++; // Increment the number if foung files
        }
        else if (img != NULL) // If already found JPEG
        {
            fwrite(buffer, 1, BLOCK_SIZE, img); // Continue to add bytes
        }
    }

    if (img != NULL)
        fclose(img); // Close the last image
}