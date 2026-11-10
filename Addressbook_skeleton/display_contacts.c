#include "addressbook.h"
#include <stdio.h>

void display_contacts(struct AddressBook *addressBook)
{
    printf("DISPLAY CONTACTS\n");
    printf("%-5s %-15s %-15s %-25s\n","SI.No","Name","Phone No","Email ID\n");

    for(int i = 0; i < addressBook->contactCount; i++)
    {
       printf("%-5d %-15s %-15s %-25s\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}