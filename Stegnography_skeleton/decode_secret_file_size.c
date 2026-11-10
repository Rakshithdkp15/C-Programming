
#include <stdio.h>
#include "common.h"
#include "decoding.h"

Status decode_secret_file_size(DecodeInfo *decInfo)
{
    char buffer[32];

    if (fread(buffer, 1, 32, decInfo->stego_image_fptr) != 32)
    {
        printf("Error: Unable to read secret file size\n");
        return failure;
    }

    decInfo->secret_file_size =
        (unsigned int)decode_4byte_from_lsb(buffer);

    printf("Secret file size: %u bytes\n",
           decInfo->secret_file_size);

    return success;
}
