
#include <stdio.h>
#include "common.h"
#include "encode.h"
#include "decoding.h"

Opr_type check_operation(char *option);

int main(int argc, char *argv[])
{
    EncodeInfo encodeInfo;
    DecodeInfo decodeInfo;

    if (argc < 2)
    {
        printf("Error: Missing arguments\n");
        printf("Usage:\n");
        printf("Encoding: ./a.out -e beautiful.bmp secret.txt [output.bmp]\n");
        printf("Decoding: ./a.out -d stego.bmp [output.txt]\n");
        return 1;
    }

    int opr = check_operation(argv[1]);

    if (opr == encode)
    {
        if (argc < 4 || argc > 5)
        {
            printf("Error: Invalid encoding arguments\n");
            printf("Usage: ./a.out -e beautiful.bmp secret.txt [output.bmp]\n");
            return 1;
        }

        printf("Encoding operation selected\n");

        if (do_encoding(argv, &encodeInfo) == failure)
        {
            printf("Encoding failed\n");
            return 1;
        }

        printf("Encoding completed successfully\n");
    }
    else if (opr == decode)
    {
        if (argc < 3 || argc > 4)
        {
            printf("Error: Invalid decoding arguments\n");
            printf("Usage: ./a.out -d stego.bmp [output.txt]\n");
            return 1;
        }

        printf("Decoding operation selected\n");

        if (do_decoding(argc, argv, &decodeInfo) == failure)
        {
            printf("Decoding failed\n");
            return 1;
        }

        printf("Decoding completed successfully\n");
    }
    else
    {
        printf("Error: Unsupported operation\n");
        return 1;
    }

    return 0;
}
