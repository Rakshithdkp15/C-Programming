#include "addressbook.h"
#include <stdio.h>
#include <string.h>


void search(struct AddressBook *);

void edit_record(struct AddressBook *addressBook)
{
    int sno;
    int index;
    int option;

    addressBook->ir_size = 0;

    search(addressBook);

    if(addressBook->ir_size == 0)
    {
        return;
    }

    printf("Enter S.No to edit: ");
    scanf("%d", &sno);

    if(sno < 1 || sno > addressBook->ir_size)
    {
        printf("Invalid S.No\n");
        return;
    }

    index = addressBook->index_record[sno - 1];

    do
    {
        printf("\nEdit Contact Menu:\n");
        printf("1. Name\n");
        printf("2. Phone No\n");
        printf("3. Email ID\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
                printf("Enter new name: ");
                scanf("%s", addressBook->contacts[index].name);
                printf("Name updated successfully\n");
                break;

            case 2:
                printf("Enter new phone number: ");
                scanf("%s", addressBook->contacts[index].phone);
                printf("Phone number updated successfully\n");
                break;

            case 3:
                printf("Enter new email ID: ");
                scanf("%s", addressBook->contacts[index].email);
                printf("Email ID updated successfully\n");
                break;

            case 0:
                return;

            default:
                printf("Invalid option\n");
        }

    } while(option >= 0 && option <= 3);
}