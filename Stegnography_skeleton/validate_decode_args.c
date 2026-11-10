
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "decoding.h"

Status validate_decode_args(int argc, char *argv[], DecodeInfo *decInfo)
{
    char *extension;

    /* Check argument count: 3 or 4 */
    if (argc < 3 || argc > 4)
    {
        printf("Error: Invalid number of arguments\n");
        printf("Usage: ./a.out -d stego.bmp [output]\n");
        return failure;
    }

    /* Check decoding option */
    if (strcmp(argv[1], "-d") != 0)
    {
        printf("Error: Invalid decoding option\n");
        return failure;
    }

    /* Check BMP extension */
    extension = strrchr(argv[2], '.');

    if (extension == NULL || strcmp(extension, ".bmp") != 0)
    {
        printf("Error: Input file must have .bmp extension\n");
        return failure;
    }

    /* Store input image filename */
    if (strlen(argv[2]) >= sizeof(decInfo->stego_image_fname))
    {
        printf("Error: Input filename is too long\n");
        return failure;
    }

    strcpy(decInfo->stego_image_fname, argv[2]);

    /* Store optional output filename */
    if (argc == 4)
    {
        if (strlen(argv[3]) >= sizeof(decInfo->output_secret_fname))
        {
            printf("Error: Output filename is too long\n");
            return failure;
        }

        strcpy(decInfo->output_secret_fname, argv[3]);
    }
    else
    {
        strcpy(decInfo->output_secret_fname, "decoded");
    }

    return success;
}
