
#include <stdio.h>
#include "common.h"
#include "encode.h"

Status encode_extn_size(EncodeInfo *encInfo);
Status encode_secret_file_size(EncodeInfo *encInfo);

Status do_encoding(char *argv[], EncodeInfo *encInfo)
{
    printf("Opening required files\n");

    if (validate_encode_args(argv, encInfo) == failure)
    {
        printf("Read and validate is not successfully done\n");
        return failure;
    }

    if (open_files(encInfo) == failure)
    {
        return failure;
    }
    printf("Opened %s\n", encInfo->src_image_fname);
    printf("Opened %s\n", encInfo->secret_fname);
    printf("Opened %s\n", encInfo->output_image_fname);
    printf("Done\n");

    printf("%u\n",
        get_image_size_for_bmp(encInfo->src_image_fptr));

    if (check_capacity(encInfo) == failure)
    {
        return failure;
    }

    printf("## Encoding Procedure Started ##\n");

    if (copy_bmp_header(encInfo) == failure)
        return failure;

    printf("Copying Image Header\nDone\n");

    if (encode_magic_string(MAGIC_STRING, encInfo) == failure)
        return failure;

    printf("Encoding Magic String Signature\nDone\n");

    if (encode_extn_size(encInfo) == failure)
        return failure;

    if (encode_secret_file_extn(encInfo) == failure)
        return failure;

    printf("Encoding %s File Extension\nDone\n",
           encInfo->secret_fname);

    if (encode_secret_file_size(encInfo) == failure)
        return failure;

    printf("Encoding %s File Size\nDone\n",
           encInfo->secret_fname);

    if (encode_secret_file_data(encInfo) == failure)
        return failure;

    printf("Encoding %s File Data\nDone\n",
           encInfo->secret_fname);

    if (copy_remaining_img_data(encInfo) == failure)
        return failure;

    printf("Copying Left Over Data\nDone\n");
    printf("## Encoding Done Successfully ##\n");

    return success;
}
