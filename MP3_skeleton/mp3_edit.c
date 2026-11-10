
#include "mp3_header.h"
#include <stdlib.h>

int update_tag(struct MP3 *mp3, char *selected_tag, char *new_content)
{
    FILE *org_fp, *temp_fp;
    unsigned char header[10];
    unsigned char frame_header[10];
    unsigned char *frame_data;
    unsigned char *new_data;
    int tag_size;
    int old_size;
    int new_size;
    int extra_size = 0;
    int i;
    int found = 0;
    int prefix_size;

    org_fp = fopen(mp3->mp3_filename, "rb");

    if(org_fp == NULL)
    {
        printf("ERROR: Unable to open MP3 file\n");
        return 0;
    }

    temp_fp = fopen("temp.mp3", "wb");

    if(temp_fp == NULL)
    {
        printf("ERROR: Unable to create temporary file\n");
        fclose(org_fp);
        return 0;
    }

    if(fread(header, 1, 10, org_fp) != 10)
    {
        printf("ERROR: Invalid MP3 header\n");
        goto error;
    }

    tag_size = ((header[6] & 0x7F) << 21) |
               ((header[7] & 0x7F) << 14) |
               ((header[8] & 0x7F) << 7) |
               (header[9] & 0x7F);

    fwrite(header, 1, 10, temp_fp);

    for(i = 0; i < 6; i++)
    {
        if(fread(frame_header, 1, 10, org_fp) != 10)
            break;

        if(frame_header[0] == 0)
        {
            fwrite(frame_header, 1, 10, temp_fp);
            break;
        }

        old_size = (frame_header[4] << 24) |
                   (frame_header[5] << 16) |
                   (frame_header[6] << 8) |
                   frame_header[7];

        if(old_size <= 0)
            break;

        frame_data = malloc(old_size);

        if(frame_data == NULL)
        {
            printf("Memory allocation failed\n");
            goto error;
        }

        if(fread(frame_data, 1, old_size, org_fp) != old_size)
        {
            free(frame_data);
            goto error;
        }

        if(strcmp((char *)frame_header, selected_tag) == 0)
        {
            found = 1;

            if(strcmp(selected_tag, "COMM") == 0)
                prefix_size = 5;
            else
                prefix_size = 1;

            if(old_size < prefix_size)
            {
                free(frame_data);
                goto error;
            }

            new_size = prefix_size + strlen(new_content);

            new_data = malloc(new_size);

            if(new_data == NULL)
            {
                free(frame_data);
                goto error;
            }

            for(int j = 0; j < prefix_size; j++)
                new_data[j] = frame_data[j];

            for(int j = 0; j < strlen(new_content); j++)
                new_data[prefix_size + j] = new_content[j];

            frame_header[4] = (new_size >> 24) & 0xFF;
            frame_header[5] = (new_size >> 16) & 0xFF;
            frame_header[6] = (new_size >> 8) & 0xFF;
            frame_header[7] = new_size & 0xFF;

            fwrite(frame_header, 1, 10, temp_fp);
            fwrite(new_data, 1, new_size, temp_fp);

            extra_size = new_size - old_size;

            free(new_data);
        }
        else
        {
            fwrite(frame_header, 1, 10, temp_fp);
            fwrite(frame_data, 1, old_size, temp_fp);
        }

        free(frame_data);
    }

    if(!found)
    {
        printf("ERROR: Selected tag not found\n");
        goto error;
    }

    /* Copy remaining MP3 data */
    {
        int ch;

        while((ch = fgetc(org_fp)) != EOF)
            fputc(ch, temp_fp);
    }

    /* Update ID3 tag size */
    tag_size = tag_size + extra_size;

    header[6] = (tag_size >> 21) & 0x7F;
    header[7] = (tag_size >> 14) & 0x7F;
    header[8] = (tag_size >> 7) & 0x7F;
    header[9] = tag_size & 0x7F;

    fseek(temp_fp, 0, SEEK_SET);
    fwrite(header, 1, 10, temp_fp);

    fclose(org_fp);
    fclose(temp_fp);

    if(rename("temp.mp3", mp3->mp3_filename) != 0)
    {
        printf("ERROR: Unable to replace original MP3 file\n");
        remove("temp.mp3");
        return 0;
    }

    return 1;

error:
    fclose(org_fp);
    fclose(temp_fp);
    remove("temp.mp3");
    printf("ERROR: Unable to update MP3 file\n");
    return 0;
}


void edit(struct MP3 *mp3)
{
    int choice;
    char new_content[1000];

    char *tag_ids[] =
    {
        "TIT2",
        "TPE1",
        "TALB",
        "TYER",
        "TCON",
        "COMM"
    };

    char *tag_names[] =
    {
        "Title",
        "Artist",
        "Album",
        "Year",
        "Genre",
        "Comment"
    };

    while(1)
    {
        printf("\n========== MP3 TAG EDITOR ==========\n\n");

        printf("1. Edit Title\n");
        printf("2. Edit Artist\n");
        printf("3. Edit Album\n");
        printf("4. Edit Year\n");
        printf("5. Edit Genre\n");
        printf("6. Edit Comment\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");

        if(scanf("%d", &choice) != 1)
        {
            printf("Invalid input\n");

            while(getchar() != '\n')
                ;

            continue;
        }

        while(getchar() != '\n')
            ;

        if(choice == 7)
        {
            printf("Exiting MP3 editor\n");
            break;
        }

        if(choice < 1 || choice > 6)
        {
            printf("Invalid choice\n");
            continue;
        }

        printf("Enter new %s: ", tag_names[choice - 1]);

        if(fgets(new_content, sizeof(new_content), stdin) == NULL)
            continue;

        new_content[strcspn(new_content, "\n")] = '\0';

        if(strlen(new_content) == 0)
        {
            printf("Content cannot be empty\n");
            continue;
        }

        if(update_tag(mp3, tag_ids[choice - 1], new_content))
        {
            printf("\n%s updated successfully!\n",
                   tag_names[choice - 1]);
        }
    }
}
