
#include "mp3_header.h"

void view(struct MP3 *mp3)
{
    mp3->org_mp3_fptr = fopen(mp3->mp3_filename, "rb");

    if(mp3->org_mp3_fptr == NULL)
    {
        printf("ERROR: Unable to open MP3 file\n");
        return;
    }

    printf("MP3 file opened successfully\n");

    print_tag_data(mp3->org_mp3_fptr);

    fclose(mp3->org_mp3_fptr);
}

void print_tag_data(FILE *org_mp3_fptr)
{
    char tag[5] = {'\0'};
    unsigned char size_bytes[4];
    unsigned char flags[2];
    unsigned char encoding;
    char data[100];
    int size;
    int text_size;
    int i;

    fseek(org_mp3_fptr, 10, SEEK_SET);

    for(i = 0; i < 6; i++)
    {
        if(fread(tag, 1, 4, org_mp3_fptr) != 4)
        {
            break;
        }

        tag[4] = '\0';

        if(fread(size_bytes, 1, 4, org_mp3_fptr) != 4)
        {
            break;
        }

        size = (size_bytes[0] << 24) |
               (size_bytes[1] << 16) |
               (size_bytes[2] << 8) |
               size_bytes[3];

        if(size <= 0)
        {
            break;
        }

        if(fread(flags, 1, 2, org_mp3_fptr) != 2)
        {
            break;
        }

        if(fread(&encoding, 1, 1, org_mp3_fptr) != 1)
        {
            break;
        }

        text_size = size - 1;

        if(text_size > 99)
        {
            text_size = 99;
        }

        if(fread(data, 1, text_size, org_mp3_fptr) != text_size)
        {
            break;
        }

        data[text_size] = '\0';

        if(strcmp(tag, "COMM") == 0)
        {
            if(text_size > 4)
            {
                printf("%-8s: %s\n", "Comment", data + 4);
            }
        }
        else
{
    tag_to_name(tag);
    printf(" : %s\n", data);
}

        fseek(org_mp3_fptr, size - 1 - text_size, SEEK_CUR);
    }
}
