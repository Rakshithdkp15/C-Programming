#include "mp3_header.h"

int validate_cla(int argc, char *argv[], struct MP3 *mp3)
{
    /* Check for no arguments */
    if(argc == 1)
    {
        printf("--------------------------------------------------\n");
        printf("ERROR: INVALID ARGUMENTS\n");
        printf("Usage: ./a.out -v mp3filename\n");
        printf("Usage: ./a.out -e mp3filename\n");
        printf("Usage: ./a.out --help\n");
        printf("--------------------------------------------------\n");
        return 0;
    }

    /* Help option */
    if(strcmp(argv[1], "--help") == 0)
    {
        printf("---------------- HELP ----------------\n");
        printf("1. -v : View MP3 file contents\n");
        printf("2. -e : Edit MP3 file contents\n");
        printf("--------------------------------------\n");
        return 0;
    }

    /* View option */
    if(strcmp(argv[1], "-v") == 0)
    {
        if(argc != 3)
        {
            printf("ERROR: Invalid arguments for viewing\n");
            printf("Usage: ./a.out -v mp3filename\n");
            return 0;
        }

        mp3->mp3_filename = argv[2];

        return VIEW;
    }

    /* Edit option */
    if(strcmp(argv[1], "-e") == 0)
    {
        if(argc != 3)
        {
            printf("ERROR: Invalid arguments for editing\n");
            printf("Usage: ./a.out -e mp3filename\n");
            return 0;
        }

        mp3->mp3_filename = argv[2];

        /* Call interactive editing function */
        edit(mp3);

        return 0;
    }

    printf("ERROR: Invalid option\n");
    return 0;
}

/* Convert frame ID into tag name */
void tag_to_name(char *tag)
{
    if(strcmp(tag, "TIT2") == 0)
        printf("Title");

    else if(strcmp(tag, "TPE1") == 0)
        printf("Artist");

    else if(strcmp(tag, "TALB") == 0)
        printf("Album");

    else if(strcmp(tag, "TYER") == 0)
        printf("Year");

    else if(strcmp(tag, "TCON") == 0)
        printf("Genre");

    else if(strcmp(tag, "COMM") == 0)
        printf("Comment");
}

/* Convert big-endian size into little-endian */
void toggle_endianess(struct MP3 *mp3, int *size)
{
    unsigned char byte1, byte2, byte3, byte4;

    byte1 = (*size >> 24) & 0xFF;
    byte2 = (*size >> 16) & 0xFF;
    byte3 = (*size >> 8) & 0xFF;
    byte4 = *size & 0xFF;

    *size = byte1 |
            (byte2 << 8) |
            (byte3 << 16) |
            (byte4 << 24);
}
