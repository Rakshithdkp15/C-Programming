
#include "common.h"
#include "decoding.h"

int decode_4byte_from_lsb(char *buffer_32)
{
    int i;
    unsigned int value = 0;

    for (i = 0; i < 32; i++)
    {
        value = (value << 1) |
                ((unsigned char)buffer_32[i] & 1);
    }

    return (int)value;
}
