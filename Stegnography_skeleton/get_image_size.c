
#include <stdio.h>
#include "common.h"
#include "encode.h"

unsigned int get_image_size_for_bmp(FILE *fptr_image)
{
    unsigned int width, height;

    fseek(fptr_image, 18, SEEK_SET);
    fread(&width, sizeof(unsigned int), 1, fptr_image);
    fread(&height, sizeof(unsigned int), 1, fptr_image);

    return width * height * 3;
}
