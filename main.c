/*
Name: Yogananth P
Date: 10-04-2025
Discription: Creating a addressbook to store datas such as name, mobile number and email in each contact
    and with few features as follows:
    1.createContact
    2.searchContact
    3.editContact
    4.deletecontact
    5.list all contacts
*/
#include <stdio.h>
#include "contact.h"

int main() {
    int choice,i=0;
    AddressBook addressBook;    //declaring addreessbook
    initialize(&addressBook);   //intialize function call
    do {                            
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {       //switch for each function
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook,1);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                saveContactsToFile(&addressBook);
                printf("\t\tCONTACTS SAVED SUCCESSFULLY...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);      //loop until 6 is encountered if 6 it will save and exit out from loop
       return 0;
}
