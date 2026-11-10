#include <stdio.h>
#include "common.h"
#include "encode.h"

Status encode_4byte_to_lsb(int data, char *buffer_32)
{
    int i;
    unsigned int value = (unsigned int)data;

    for (i = 0; i < 32; i++)
    {
        buffer_32[i] = (buffer_32[i] & 0xFE) |
                       ((value >> (31 - i)) & 1);
    }

    return success;
}
