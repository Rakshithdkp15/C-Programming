
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "encode.h"

Status check_capacity(EncodeInfo *encInfo)
{
    unsigned int image_size;
    unsigned long int secret_size;
    unsigned long int required_size;

    printf("Checking for %s size\n", encInfo->secret_fname);

    secret_size = get_file_size(encInfo->secret_fptr);

    if (secret_size == 0)
    {
        printf("Error: Secret file is empty\n");
        return failure;
    }

    encInfo->secret_file_size = secret_size;
    printf("Done. Not Empty\n");

    printf("Checking for %s capacity to handle %s\n",
           encInfo->src_image_fname,
           encInfo->output_image_fname);

    image_size = get_image_size_for_bmp(encInfo->src_image_fptr);

    required_size = (strlen(MAGIC_STRING)
                   + sizeof(int)
                   + encInfo->secret_extn_size
                   + sizeof(int)
                   + secret_size) * 8;

    if (image_size >= required_size)
    {
        printf("Done. Found OK\n");
        return success;
    }

    printf("Error: Image does not have enough capacity\n");
    return failure;
}
