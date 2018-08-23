#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //check the usage
    if (argc != 2)
    {
        fprintf (stderr, "Usage: ./recover image\n");
        return 1;
    }
    char *inputFile = argv[1];
    //open a file with error checck
    FILE *in = fopen (inputFile, "r");
    if (in == NULL)
    {
        fprintf (stderr, "Could not open file\n");
        return 2;
    }

    unsigned char buffer[512];
    char *filename = malloc(sizeof(char) * 8);
    int filecounter = 0;
    FILE *img;

    while (fread(buffer, 512, 1, in) == 1)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            if (filecounter > 0)
            {
                fclose(img);
            }

            sprintf (filename, "%03i.jpg", filecounter);
            img = fopen (filename, "w");
            fwrite (buffer, 512, 1, img);
            filecounter++;
        }
        else
        {
            if (filecounter > 0)
            {
                fwrite (buffer, 512, 1, img);
            }
        }



    }

    fclose (in);
    free(filename);
}