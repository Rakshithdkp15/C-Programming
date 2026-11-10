
#include <stdio.h>
#include "common.h"
#include "decoding.h"

Status open_decode_files(DecodeInfo *decInfo)
{
    decInfo->stego_image_fptr =
        fopen(decInfo->stego_image_fname, "rb");

    if (decInfo->stego_image_fptr == NULL)
    {
        perror("Error opening stego image");
        return failure;
    }

    printf("Stego image opened successfully.\n");

    return success;
}
