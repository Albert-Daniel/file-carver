#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) // If too many/few command-line arguments
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    FILE *card = fopen(argv[1], "r"); // Opening the card
    if (card == NULL)
        return 2;

    uint8_t buffer[512]; // Buffer to hold memory

    int JPEG_count = 0; // The number of files already opened

    char filename[8]; // Name of the file
    FILE *img = NULL; // The image currently created

    while (fread(buffer, sizeof(uint8_t), 512, card) == 512) // As long as it's memory
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0) // If it's the start of a JPEG
        {
            if (JPEG_count != 0)
                fclose(img);

            sprintf(filename, "%03i.jpg", JPEG_count);
            img = fopen(filename, "w");
            if (img == NULL)
                return 2;
            fwrite(buffer, sizeof(uint8_t), 512, img);
            JPEG_count++;
        }
        else if (JPEG_count != 0) // If already found JPEG
        {
            fwrite(buffer, sizeof(uint8_t), 512, img);
        }
    }

    // Close any remaining files
    fclose(img);
    fclose(card);
}
