#include "addressbook.h"
#include <stdio.h>

void search(struct AddressBook *);

void delete_record(struct AddressBook *addressBook)
{
    int sno;
    int index;

    addressBook->ir_size = 0;

    search(addressBook);

    if(addressBook->ir_size == 0)
    {
        return;
    }

    printf("Enter S.No to delete: ");
    scanf("%d", &sno);

    if(sno < 1 || sno > addressBook->ir_size)
    {
        printf("Invalid S.No\n");
        return;
    }

    index = addressBook->index_record[sno - 1];

    for(int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully\n");
}