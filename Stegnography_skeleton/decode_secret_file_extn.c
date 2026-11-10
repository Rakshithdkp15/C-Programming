
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "decoding.h"

Status decode_secret_file_extn(DecodeInfo *decInfo)
{
    char buffer[8];
    int i;

    printf("Starting extension decoding...\n");

    if (decode_secret_extn_size(decInfo) == failure)
        return failure;

    printf("Extension size received: %d\n",
           decInfo->secret_extn_size);

    for (i = 0; i < decInfo->secret_extn_size; i++)
    {
        if (fread(buffer, 1, 8, decInfo->stego_image_fptr) != 8)
        {
            printf("Error: Unable to read secret extension\n");
            return failure;
        }

        decInfo->secret_extn[i] = decode_1byte_from_lsb(buffer);
    }

    decInfo->secret_extn[decInfo->secret_extn_size] = '\0';

    printf("Secret extension: %s\n", decInfo->secret_extn);

    if (strchr(decInfo->output_secret_fname, '.') == NULL)
    {
        if (strlen(decInfo->output_secret_fname) +
            strlen(decInfo->secret_extn) >=
            sizeof(decInfo->output_secret_fname))
        {
            printf("Error: Output filename is too long\n");
            return failure;
        }

        strcat(decInfo->output_secret_fname, decInfo->secret_extn);
    }

    decInfo->output_secret_fptr =
        fopen(decInfo->output_secret_fname, "wb");

    if (decInfo->output_secret_fptr == NULL)
    {
        perror("Error opening output file");
        return failure;
    }

    printf("Output file opened: %s\n",
           decInfo->output_secret_fname);

    return success;
}
