#include <stdio.h>
#include "common.h"
#include "encode.h"

unsigned int get_file_size(FILE *fptr)
{
    unsigned int size;

    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    rewind(fptr);

    return size;
}