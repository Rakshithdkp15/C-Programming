
#include "common.h"
#include "decoding.h"

char decode_1byte_from_lsb(char *buffer_8)
{
    int i;
    unsigned char ch = 0;

    for (i = 0; i < 8; i++)
    {
        ch = (ch << 1) | ((unsigned char)buffer_8[i] & 1);
    }

    return (char)ch;
}
