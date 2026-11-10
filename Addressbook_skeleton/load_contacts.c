#include "addressbook.h"

void load_contacts(struct AddressBook *addressBook)
{
    FILE *fp;

    fp = fopen("database.csv", "r");

    if(fp == NULL)
    {
        return;
    }

    while(fscanf(fp, "%49[^,],%14[^,],%49[^\n]\n",
                 addressBook->contacts[addressBook->contactCount].name,
                 addressBook->contacts[addressBook->contactCount].phone,
                 addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(fp);
}