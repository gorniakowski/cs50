// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // remember filenames and f.
    double f = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    //chceck is f is betwenn 0.0 and 100.00
    if (f <= 0.0 || f >= 100.00)
    {
        fprintf(stderr, "f must be between 0.0 and 100.00\n");
        return 1;
    }


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    bi.biWidth *= f;
    bi.biHeight *= f;
    // determine padding for scanlines
    int oldPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    //printf ("oldPadding: %i\n", oldPadding);
    //printf ("newPadding: %i\n", padding);
    RGBTRIPLE arr[bi.biWidth];
    // iterate over infile's scanlines


    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {




        int counter = 0;

        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            for (int k = 0; k < f; k++)
            {
                // write RGB triple to outfile
                //  fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                arr[counter] = triple;
                counter++;
            }



        }
        for (int l = 0; l < f; l++)
        {
            fwrite (arr, sizeof(arr), 1, outptr);
            for (int m = 0; m < padding; m++)
            {
                fputc(0x00, outptr);
            }


        }

        //skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);

        //then add it back (to demonstrate how)
        //for (int k = 0; k < padding; k++)
        //{
        //  fputc(0x00, outptr);
        //}


    }



    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
