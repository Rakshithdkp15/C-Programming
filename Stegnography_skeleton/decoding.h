
#ifndef DECODING_H
#define DECODING_H

#include <stdio.h>
#include "common.h"

typedef struct DecodeInfo
{
    char stego_image_fname[100];
    FILE *stego_image_fptr;

    char output_secret_fname[100];
    FILE *output_secret_fptr;

    char secret_extn[10];
    int secret_extn_size;
    unsigned int secret_file_size;
} DecodeInfo;

Status validate_decode_args(int argc, char *argv[], DecodeInfo *decInfo);

Status do_decoding(int argc, char *argv[], DecodeInfo *decInfo);

Status open_decode_files(DecodeInfo *decInfo);

Status skip_bmp_header(FILE *fptr);

char decode_1byte_from_lsb(char *buffer_8);

int decode_4byte_from_lsb(char *buffer_32);

Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo);

Status decode_secret_extn_size(DecodeInfo *decInfo);

Status decode_secret_file_extn(DecodeInfo *decInfo);

Status decode_secret_file_size(DecodeInfo *decInfo);

Status decode_secret_data(DecodeInfo *decInfo);

#endif
