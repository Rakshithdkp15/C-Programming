
#include <stdio.h>
#include "common.h"
#include "encode.h"

Status copy_bmp_header(EncodeInfo *encInfo)
{
    char header[54];

    rewind(encInfo->src_image_fptr);

    if (fread(header, 1, 54, encInfo->src_image_fptr) != 54)
    {
        printf("Error: Unable to read BMP header\n");
        return failure;
    }

    if (fwrite(header, 1, 54, encInfo->output_image_fptr) != 54)
    {
        printf("Error: Unable to write BMP header\n");
        return failure;
    }

    return success;
}
