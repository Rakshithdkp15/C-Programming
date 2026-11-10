#include "addressbook.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void name(struct AddressBook *addressBook)
{
    char name[50];

    addressBook->ir_size = 0;

    printf("Enter the name: ");
    scanf("%s", name);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].name, name) == 0)
        {
            printf("%-5d %-15s %-15s %-25s\n",
                   addressBook->ir_size + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            addressBook->index_record[addressBook->ir_size] = i;

            addressBook->ir_size++;
        }
    }

    if(addressBook->ir_size == 0)
    {
        printf("Contact not found\n");
    }
}


void phone_no(struct AddressBook *addressBook)
{
    char phone[15];

    addressBook->ir_size = 0;

    printf("Enter the phone_no: ");
    scanf("%s", phone);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("%-5d %-15s %-15s %-25s\n",
                   addressBook->ir_size + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            addressBook->index_record[addressBook->ir_size] = i;

            addressBook->ir_size++;
        }
    }

    if(addressBook->ir_size == 0)
    {
        printf("Contact not found\n");
    }
}


void email_ID(struct AddressBook *addressBook)
{
    char email[50];

    addressBook->ir_size = 0;

    printf("Enter the email_ID: ");
    scanf("%s", email);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printf("%-5d %-15s %-15s %-25s\n",
                   addressBook->ir_size + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            addressBook->index_record[addressBook->ir_size] = i;

            addressBook->ir_size++;
        }
    }

    if(addressBook->ir_size == 0)
    {
        printf("Contact not found\n");
    }
}


void search(struct AddressBook *addressBook)
{
    int option;

    printf("\nSearch contact Menu:\n");
    printf("1. name\n");
    printf("2. phone_no\n");
    printf("3. email_ID\n");
    printf("0. Exit\n");

    scanf("%d", &option);

    switch(option)
    {
        case 1:
            name(addressBook);
            return;

        case 2:
            phone_no(addressBook);
            return;

        case 3:
            email_ID(addressBook);
            return;

        case 0:
            return;

        default:
            printf("Invalid option\n");
    }
}