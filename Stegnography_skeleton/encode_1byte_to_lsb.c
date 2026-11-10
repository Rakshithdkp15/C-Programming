
#include <stdio.h>
#include "common.h"
#include "encode.h"

Status encode_1byte_to_lsb(char data, char *buffer_8)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        buffer_8[i] = (buffer_8[i] & 0xFE) |
                      (((unsigned char)data >> (7 - i)) & 1);
    }

    return success;
}
