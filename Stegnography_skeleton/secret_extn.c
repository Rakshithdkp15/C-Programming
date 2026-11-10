
#include <stdio.h>
#include "common.h"
#include "encode.h"

Status encode_secret_file_extn(EncodeInfo *encInfo)
{
    int i;
    char buffer[8];

    for (i = 0; encInfo->secret_extn[i] != '\0'; i++)
    {
        if (fread(buffer, 1, 8, encInfo->src_image_fptr) != 8)
            return failure;

        if (encode_1byte_to_lsb(encInfo->secret_extn[i], buffer) == failure)
            return failure;

        if (fwrite(buffer, 1, 8, encInfo->output_image_fptr) != 8)
            return failure;
    }

    return success;
}
