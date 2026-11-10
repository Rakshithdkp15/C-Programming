#include "addressbook.h"

void save_contacts(struct AddressBook *addressBook)
{
    FILE *fp;
    int i;

    fp = fopen("database.csv", "w");

    if(fp == NULL)
    {
        return;
    }

    for(i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);
}