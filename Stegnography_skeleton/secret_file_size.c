
#include <stdio.h>
#include "common.h"
#include "encode.h"

Status encode_secret_file_size(EncodeInfo *encInfo)
{
    char buffer[32];

    if (fread(buffer, 1, 32, encInfo->src_image_fptr) != 32)
    {
        return failure;
    }

    if (encode_4byte_to_lsb((int)encInfo->secret_file_size, buffer) == failure)
    {
        return failure;
    }

    if (fwrite(buffer, 1, 32, encInfo->output_image_fptr) != 32)
    {
        return failure;
    }

    return success;
}
