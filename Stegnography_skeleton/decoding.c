
#include <stdio.h>
#include "common.h"
#include "decoding.h"

Status do_decoding(int argc, char *argv[], DecodeInfo *decInfo)
{
    if (validate_decode_args(argc, argv, decInfo) == failure)
    {
        return failure;
    }

    printf("Arguments validated successfully.\n");

    if (open_decode_files(decInfo) == failure)
    {
        return failure;
    }

    if (skip_bmp_header(decInfo->stego_image_fptr) == failure)
    {
        fclose(decInfo->stego_image_fptr);
        return failure;
    }

    if (decode_magic_string(MAGIC_STRING, decInfo) == failure)
    {
        fclose(decInfo->stego_image_fptr);
        return failure;
    }

    if (decode_secret_file_extn(decInfo) == failure)
    {
        fclose(decInfo->stego_image_fptr);
        return failure;
    }

    if (decode_secret_file_size(decInfo) == failure)
    {
        fclose(decInfo->stego_image_fptr);
        fclose(decInfo->output_secret_fptr);
        return failure;
    }

    if (decode_secret_data(decInfo) == failure)
    {
        fclose(decInfo->stego_image_fptr);
        fclose(decInfo->output_secret_fptr);
        return failure;
    }

    printf("Secret data decoded successfully.\n");

    fclose(decInfo->stego_image_fptr);
    fclose(decInfo->output_secret_fptr);

    return success;
}
