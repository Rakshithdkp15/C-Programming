
#include <stdio.h>
#include "common.h"
#include "decoding.h"

Status decode_secret_data(DecodeInfo *decInfo)
{
    char buffer[8];
    char ch;
    unsigned int i;

    for (i = 0; i < decInfo->secret_file_size; i++)
    {
        if (fread(buffer, 1, 8, decInfo->stego_image_fptr) != 8)
        {
            printf("Error: Unable to read secret data\n");
            return failure;
        }

        ch = decode_1byte_from_lsb(buffer);

        if (fputc(ch, decInfo->output_secret_fptr) == EOF)
        {
            printf("Error: Unable to write secret data\n");
            return failure;
        }
    }

    printf("Secret data decoded successfully.\n");
    return success;
}
