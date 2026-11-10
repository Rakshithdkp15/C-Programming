
#include <stdio.h>
#include "common.h"
#include "encode.h"

Status encode_secret_file_data(EncodeInfo *encInfo)
{
    char data;
    char buffer[8];

    rewind(encInfo->secret_fptr);

    while (fread(&data, 1, 1, encInfo->secret_fptr) == 1)
    {
        if (fread(buffer, 1, 8, encInfo->src_image_fptr) != 8)
            return failure;

        if (encode_1byte_to_lsb(data, buffer) == failure)
            return failure;

        if (fwrite(buffer, 1, 8, encInfo->output_image_fptr) != 8)
            return failure;
    }

    return success;
}

