#include <stdio.h>
#include "common.h"
#include "decoding.h"

Status skip_bmp_header(FILE *fptr)
{
    fseek(fptr, 54, SEEK_SET);
    return success;
}