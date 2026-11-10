#include "addressbook.h"
#include<stdio.h>
#include <string.h>
#include <ctype.h>

void validate_phone(struct AddressBook *addressBook)
{
    //defining the name,phone_no,emailID.    
    char name[50];
    printf("enter the name\n");
    scanf("%s", name);
    
    

    //reading the name and phone_no.
    char phone_no[12];
    printf("enter the phone_no\n");
    scanf("%s", phone_no);
    
//the total character of the phone no is should be 10.
    if(strlen(phone_no)!=10)
    {
        printf("The number should in the limit of 10\n");
        return;
    }

//the character entered are only digits or not.
    for(int i=0;i<10;i++)
    {
        if(!isdigit(phone_no[i]))
        {
            printf("only digits allowed\n");
            return;
        }
    }
    
    //chechking the range of 1st character bt 6 to 9
    if(phone_no[0]<'6' || phone_no[0]>'9')
    {
        printf("Please enter the number in range of 6 to 9\n");
        return;
    }

    //chechking the phone number is existed or not
    for(int i = 0; i < addressBook->contactCount; i++)
{
    if(strcmp(phone_no, addressBook->contacts[i].phone) == 0)
    {
        printf("Phone number already exists\n");
        return;
    }
}


    

//read email
    char email_ID[30];
    printf("enter the email_ID\n");
    scanf("%s", email_ID);

//converting upper to lower case.
       for(int i = 0; email_ID[i] != '\0'; i++)
    {
        email_ID[i] = tolower(email_ID[i]);
    }

//chechking the @ is not the 1st character in email.
    if(email_ID[0]=='@')
    {
        printf("@ should not be the first character of email\n");
        return;
    }
// checking that the email is ending with the ".com" .
    int len;

    len = strlen(email_ID);

    if(len < 4)
    {
        printf("Invalid email\n");
        return;
    }

    if(strcmp(&email_ID[len - 10], "@gmail.com") != 0)
    {
        printf("Email should end with @gmail.com\n");
        return;
    }    

    // chechking the email is existed or not
    for(int i = 0; i < addressBook->contactCount; i++)
{
    if(strcmp(email_ID, addressBook->contacts[i].email) == 0)
    {
        printf("email_ID already exists\n");
        return;
    }
}

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone_no);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email_ID);
    addressBook->contactCount++;

    printf("Contact stored successfully\n");
}