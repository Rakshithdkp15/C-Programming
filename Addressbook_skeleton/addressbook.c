#include "addressbook.h"

void load_contacts_from_file(struct AddressBook *addressBook)
{
    void load_contacts(struct AddressBook *);

    load_contacts(addressBook);
}

void save_contacts_to_file(struct AddressBook *addressBook)
{
    void save_contacts(struct AddressBook *);

    save_contacts(addressBook);
}

void add_contact(struct AddressBook *addressBook)
{
    void validate_phone(struct AddressBook *);

    validate_phone(addressBook);
}

void search_contact(struct AddressBook *addressBook)
{
    void search(struct AddressBook *);

    search(addressBook);
}

void edit_contact(struct AddressBook *addressBook)
{
    void edit_record(struct AddressBook *);

    edit_record(addressBook);
}

void delete_contact(struct AddressBook *addressBook)
{
    void delete_record(struct AddressBook *);

    delete_record(addressBook);
}

void list_contacts(struct AddressBook *addressBook)
{
    void display_contacts(struct AddressBook *);

    display_contacts(addressBook);
}