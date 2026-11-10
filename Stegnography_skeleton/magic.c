
#include <stdio.h>
#include "common.h"
#include "encode.h"

Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    char buffer[8];
    int i;

    for (i = 0; magic_string[i] != '\0'; i++)
    {
        if (fread(buffer, 1, 8, encInfo->src_image_fptr) != 8)
            return failure;

        if (encode_1byte_to_lsb(magic_string[i], buffer) == failure)
            return failure;

        if (fwrite(buffer, 1, 8, encInfo->output_image_fptr) != 8)
            return failure;
    }

    return success;
}
