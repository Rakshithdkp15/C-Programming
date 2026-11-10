
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "decoding.h"

Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo)
{
    char buffer[8];
    char decoded_char;
    int i;

    for (i = 0; magic_string[i] != '\0'; i++)
    {
        if (fread(buffer, 1, 8, decInfo->stego_image_fptr) != 8)
        {
            printf("Error: Unable to read magic string\n");
            return failure;
        }

        decoded_char = decode_1byte_from_lsb(buffer);

        if (decoded_char != magic_string[i])
        {
            printf("Error: Magic string does not match\n");
            return failure;
        }
    }

    printf("Magic string decoded successfully.\n");
    return success;
}
