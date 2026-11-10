#include <stdio.h>
#include "common.h"
#include "decoding.h"

Status decode_secret_extn_size(DecodeInfo *decInfo)
{
    char buffer[32];

    if (fread(buffer, 1, 32, decInfo->stego_image_fptr) != 32)
    {
        printf("Error: Unable to read extension size\n");
        return failure;
    }

    decInfo->secret_extn_size =
        decode_4byte_from_lsb(buffer);

    if (decInfo->secret_extn_size <= 0 ||
        decInfo->secret_extn_size >= sizeof(decInfo->secret_extn))
    {
        printf("Error: Invalid extension size\n");
        return failure;
    }

    printf("Secret extension size: %d\n",
           decInfo->secret_extn_size);

    return success;
}
