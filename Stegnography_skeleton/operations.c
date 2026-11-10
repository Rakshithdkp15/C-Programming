
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "encode.h"

Opr_type check_operation(char *option)
{
    if (strcmp(option, "-e") == 0)
    {
        return encode;
    }
    else if (strcmp(option, "-d") == 0)
    {
        return decode;
    }
    else
    {
        return unsupported;
    }
}

Status copy_remaining_img_data(EncodeInfo *encInfo)
{
    char ch;

    while (fread(&ch, 1, 1, encInfo->src_image_fptr) == 1)
    {
        if (fwrite(&ch, 1, 1, encInfo->output_image_fptr) != 1)
        {
            return failure;
        }
    }

    return success;
}
