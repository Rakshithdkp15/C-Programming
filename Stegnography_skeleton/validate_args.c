#include <stdio.h>
#include <string.h>
#include "common.h"
#include "encode.h"

Status validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    char *ext;

    ext = strrchr(argv[2], '.');

    if (ext == NULL || strcmp(ext, ".bmp") != 0)
    {
        printf("Error: Input image must be a .bmp file\n");
        return failure;
    }

    encInfo->src_image_fname = argv[2];

    ext = strrchr(argv[3], '.');

    if (ext == NULL || strlen(ext) >= sizeof(encInfo->secret_extn))
    {
        printf("Error: Invalid secret file extension\n");
        return failure;
    }

    encInfo->secret_fname = argv[3];
    strcpy(encInfo->secret_extn, ext);
    encInfo->secret_extn_size = strlen(ext);

    if (argv[4] == NULL)
    {
        encInfo->output_image_fname = "stego.bmp";
    }
    else
    {
        ext = strrchr(argv[4], '.');

        if (ext == NULL || strcmp(ext, ".bmp") != 0)
        {
            printf("Error: Output image must be a .bmp file\n");
            return failure;
        }

        encInfo->output_image_fname = argv[4];
    }

    return success;
}