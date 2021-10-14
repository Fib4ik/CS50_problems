// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // resize variable
    int resize = atoi(argv[1]);
    if (resize < 1 || resize > 100)
    {
        fprintf(stderr, "Resize factor must be in [1, 100]\n");
        return 0;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

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

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // saving headers
    int headers[4] = {bf.bfSize, bi.biWidth, bi.biHeight, bi.biSizeImage};

    // new headers
    bi.biWidth = bi.biWidth * resize;
    bi.biHeight = bi.biHeight * resize;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + ((4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4)) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + 54;

    // determine padding for scanlines
    int padding_new = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // changing back
    bf.bfSize = headers[0];
    bi.biWidth = headers[1];
    bi.biHeight = headers[2];
    bi.biSizeImage = headers[3];

    // triple array
    RGBTRIPLE pixels[bi.biWidth];
    int padding_old = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write triple to array
            pixels[j] = triple;

            //fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        for (int r0 = 0; r0 < resize; r0++)
        {
            for (int j = 0; j < bi.biWidth; j++)
            {
                for (int r1 = 0; r1 < resize; r1++)
                {
                    RGBTRIPLE triple;
                    triple = pixels[j];
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
        }

        // skip over padding, if any
        fseek(inptr, padding_old, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding_new; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
