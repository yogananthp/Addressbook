#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
Contact dummy;
int arr[20],size=0;
void print_redi()   //this function is for getting conformation from the user to get back to main menu
{
    char te;
    printf("\tPress a character to redirect to main menu: ");
    scanf(" %c",&te);       //if any character is entered from keyboard it will end the perticular function
    printf("\t\tRedirecting to main menu");
    for (int i = 1; i <= 5; i++)    //creating continous "." with delay
    {
        printf(".");
        fflush(stdout); 
        usleep(250000);
    } 
}
void print_()   //this function is for printing ---> line
{
    printf("------------------------------------------------------------------------\n");
}
int unique_phone(char *temp,AddressBook *addressBook)
{
    int i;
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,temp)==0)  //compares the received temporoary string with existing phone number till contactcount
        {
            printf("\tEnter unique mobile number\n");
            return 1;   //if found return 1 to get the input(unique) again
        }
    }
    return 0;
}
int unique_email(char *temp,AddressBook *addressBook)
{
    int i;
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,temp)==0)  //compares the received temporoary string with existing email till contactcount
        {
            printf("\tEnter unique email id\n");
            return 1;   //if found return 1 to get the input(unique) again
        }
    }
    return 0;
}
int validate_name(char* temp)
{
    int i=0;
    while(temp[i]!='\0')
    {
        if(temp[i]>='a'&&temp[i]<='z'||temp[i]>='A'&&temp[i]<='Z'||temp[i]==' ')    //checks if each element in the string is alphabets are not.
        {
            i++;
        }
        else
        {
            printf("\tEntered name is invalid\n");
            return 1;   //if found return 1 to get the valid input again
        }
    }
    return 0;
}
int validate_mobile(char *temp)
{
    int i=0;
    while(temp[i]!='\0')
    {
        if(temp[i]>='0'&&temp[i]<='9')  //checks fot each element in the string is digit or not 
        {
            i++;
        }
        else
        {
            printf("\tEntered mobile number is invalid\n");     //if it is not digit return 1 to get valid phone number
            return 1;
        }
    }
    if(i>10||i<10)
    {
        printf("\tEntered mobile number is invalid\n");     //checks for no of digits == 10
        return 1;
    }
    else
        return 0;
}
int validate_email(char* temp)
{
    int i=0;
    char com[]=".com";
    char target[]="@";
    if(strstr(temp,com)==NULL)  //checks for substring .com
    {
        printf("\tEntered email is invaild, \".com\" is missing!\n");
        return 1;
    }
    if(strstr(temp,target)==NULL)   //checks for substring @
    {
        printf("\tEnter email is invalid, \"@\" is missing!\n");
        return 1;
    }
    return 0;
}
void listContacts(AddressBook *addressBook) 
{
    int i,j;
    print_();
    printf("\t\t\tMENU - LIST CONTACTS\n");
    print_();
    printf("\t\t\tSelect sort criteria\n");
    printf("1. Sort by name\n");
    printf("2. Sort by phone\n");
    printf("3. Sort by email\n");
    printf("Enter your choice: ");
    int sortChoice;
    scanf("%d", &sortChoice);   //getting sort choise from user
    switch (sortChoice)
    {
        case 1:
            printf("\t\t\tSORTED BY NAME\n");
            for(i=0;i<addressBook->contactCount;i++)    //bubble sort for name
            {
                for(j=0;j<addressBook->contactCount-1;j++)
                {
                    if((strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name))>0)
                    {
                        dummy=addressBook->contacts[j];
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                        addressBook->contacts[j+1]=dummy;
                    }
                }
            }
            break;
        case 2:
            printf("\t\t\tSORTED BY MOBILE NUMBER\n");
            for(i=0;i<addressBook->contactCount;i++)        //bubble sort for mobile
            {
                for(j=0;j<addressBook->contactCount-1;j++)
                {
                    if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                    {
                        dummy=addressBook->contacts[j];
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                        addressBook->contacts[j+1]=dummy;
                    }
                }
            }
            break;
        case 3:
            printf("\t\t\tSORTED BY EMAIL\n");
            for(i=0;i<addressBook->contactCount;i++)        //bubble sort for email
            {
                for(j=0;j<addressBook->contactCount-1;j++)
                {
                    if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                    {
                        dummy=addressBook->contacts[j];
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                        addressBook->contacts[j+1]=dummy;
                    }
                }
            }   
            break;
        default:
            printf("\tSelected sort criteria is invalid\n");
            listContacts(addressBook);
            break;
    }
    print_();
    printf("INDEX\tNAME\t\tMOBILE NUMBER\tEMAIL\n");
    print_(); 
    for(i=0;i<addressBook->contactCount;i++)    //after sorting as per user choice final sorted array of contacts is printed
    {
        printf("%d\t%s\t%s\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    print_();
    print_redi();
}
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);    
    loadContactsFromFile(addressBook);   
}
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
void createContact(AddressBook *addressBook)
{
	char temp[50];
    print_();
    printf("\t\t\tMENU - CREATE CONTACT\n");
    print_();
    do
    {
        printf("Enter the name : ");
        scanf(" %[^\n]",temp);
    } while (validate_name(temp));  //getting name untill the validation passes
    strcpy(addressBook->contacts[addressBook->contactCount].name,temp);     //storing the validated temp data to present countactcouont(index) of contacts array 
    do
    {
        printf("Enter the mobile number : ");
        scanf("%s",temp);
    } while (validate_mobile(temp)|unique_phone(temp,addressBook));     //getting mobile untill the validation passes, or operator is used to avoid short circuiting
    strcpy(addressBook->contacts[addressBook->contactCount].phone,temp);    //storing the validated temp data to present countactcouont(index) of contacts array 
    do
    {
        printf("Enter the email : ");
        scanf("%s",temp);
    } while (validate_email(temp)|unique_email(temp,addressBook));      //getting mobile untill the validation passes, or operator is used to avoid short circuiting
    strcpy(addressBook->contacts[addressBook->contactCount].email,temp);    //storing the validated temp data to present countactcouont(index) of contacts array 
    print_();
    printf("INDEX\tNAME\t\tMOBILE NUMBER\tEMAIL\n");
    print_();
    printf("%d\t%s\t%s\t%s\n",addressBook->contactCount,addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email);
    print_();   //above line prints the added newly added contact
    printf("\t\tContact is created successfully!\n");
    print_();
    addressBook->contactCount++;        //finally increament contactcount + 1 as 1 contact is added newly
    print_redi();
}
int searchContact(AddressBook *addressBook,int n) 
{
    if(n)   //n is taken to print MENU only when the function is called from main menu
    {
        print_();
        printf("\t\t\tMENU - SEARCH CONTACT\n");
        print_();
    }
    int opt,i,count = 0;
    size=0;
    char temp[20];
    printf("1. Search by name\n2. Search by mobile number\n3. Search by email\nEnter the option : ");
    scanf("%d",&opt); 
    switch(opt)     //edit option to select criteria
    {
        case 1:
            do
            {
                printf("Enter the name : ");
                scanf(" %[^\n]",temp);
            } while (validate_name(temp));      //validate name 
            print_();
            printf("INDEX\tNAME\t\tMOBILE NUMBER\tEMAIL\n");
            print_();
            for(i=0;i<addressBook->contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].name,temp)!=NULL)    //check for temp string in each index of contacts if present print it
                {
                    arr[size]=i;    //storing the index of each contact
                    size++;
                    count++;    //for finding any contact is found or not if count == 0 then contact not found
                    printf("%d\t%s\t%s\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            if(count==0)    //if count = 0 print contact not found
            {
                print_();
                printf("\t\t\tContact not found!\n");
                print_();
                if(n)
                    print_redi();
                return 0;
            }
            print_();
            if(n)
                print_redi();
            return 1;
            break;
        case 2:
                printf("Enter the mobile number : ");
                scanf("%s",temp);
            print_();
            printf("INDEX\tNAME\t\tMOBILE NUMBER\tEMAIL\n");
            print_();
            for(i=0;i<addressBook->contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].phone,temp)!=NULL)   //check for temp string in each index of contacts if present print it
                {
                    arr[size]=i;     //storing the index of each contact
                    size++;
                    count++;    //for finding any contact is found or not if count == 0 then contact not found
                    printf("%d\t%s\t%s\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            if(count==0)    //if count = 0 print contact not found
            {
                print_();
                printf("\t\t\tContact not found!\n");
                print_();
                if(n)
                    print_redi();
                return 0;
            }
            print_();
            if(n)
                print_redi();
            return 1;
            break;
        case 3:
            printf("Enter the email : ");
            scanf("%s",temp);
            print_();
            printf("INDEX\tNAME\t\tMOBILE NUMBER\tEMAIL\n");
            print_();
            for(i=0;i<addressBook->contactCount;i++)    //check for temp string in each index of contacts if present print it
            {
                if(strcasestr(addressBook->contacts[i].email,temp)!=NULL)
                {
                    arr[size]=i;    //storing the index of each contact
                    size++;
                    count++;        //for finding any contact is found or not if count == 0 then contact not found
                    printf("%d\t%s\t%s\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            if(count==0)    //if count = 0 print contact not found
            {
                print_();
                printf("\t\t\tContact not found!\n");
                print_();
                if(n)
                    print_redi();
                return 0;
            }
            print_();
            if(n)
                print_redi();
            return 1;
            break;
        default:
            printf("\tEntered option is Invaild!\n");
            searchContact(addressBook,0);   //if invalid option again calling the same function 
    }
}
void editContact(AddressBook *addressBook)
{
    char var[20];
    int index,opt,optf=1;
    print_();
    printf("\t\t\tMENU - EDIT CONTACT\n");
    print_();
	if(searchContact(addressBook,0))
    {
        label:
        printf("Enter the index to edit: ");
        scanf("%d",&index);
        for(int i=0;i<size;i++)
        {
            if(index==arr[i])      //checkin if the entered index is present in arr
            {
                optf=0;
            }
        }
        if(optf)    //if not present 
        {
            printf("\tInvalid Index\n");
            goto label;     //goto to get valid index
        }
        edit:
        printf("1. Edit by name\n2. Edit by mobile number\n3. Edit by email\nEnter the option : ");
        scanf("%d",&opt);   //option for edit option 
        switch(opt)
        {
            case 1:
                do{
                    printf("Enter the name to edit: ");
                    scanf(" %[^\n]",var);
                }while(validate_name(var)); //getting name untill the validation passes
                strcpy(addressBook->contacts[index].name,var);  //copying the validated temp data to present countactcouont(index) of contacts array 
                break;
            case 2:
                do{
                    printf("Enter the mobile to edit: ");
                    scanf(" %[^\n]",var);
                }while(validate_mobile(var)|unique_phone(var,addressBook)); //getting mobile untill the validation passes, or operator is used to avoid short circuiting
                strcpy(addressBook->contacts[index].phone,var);     //copying the validated temp data to present countactcouont(index) of contacts array 
                break;
            case 3:
                do{
                    printf("Enter the email to edit: ");
                    scanf(" %[^\n]",var);
                }while(validate_email(var)|unique_email(var,addressBook));      //getting email untill the validation passes, or operator is used to avoid short circuiting
                strcpy(addressBook->contacts[index].email,var);     //copying the validated temp data to present countactcouont(index) of contacts array 
                break;
            default:
                printf("\tEntered option is invaild\n");    //case default if option is invalid then print a prompt and goto option menu
                goto edit;
                break;
        }
        print_();
        printf("INDEX\tNAME\t\tMOBILE NUMBER\tEMAIL\n");
        print_();
        printf("%d\t%s\t%s\t%s\n",index,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);   //print the edited contact
        printf("\t\tContact edited successfully\n");
        print_();
        print_redi();
    }
}
void deleteContact(AddressBook *addressBook)
{
    int index,i,optf=1;
    char con;
    print_();
    printf("\t\t\tMENU - DELETE CONTACT\n");
    print_();
	if(searchContact(addressBook,0))
    {
        start:
        printf("Enter the index to delete: ");
        scanf("%d",&index);
        for(int i=0;i<size;i++)
        {
            if(index==arr[i])       //checking if the entered index is present in the array or not
            {
                optf=0;
            }
        }
        if(optf)    //if not found then goto to get index input, to get valid index
        {
            printf("\tInvalid Index\n");
            goto start;
        }
        printf("\n");
        print_();
        printf("INDEX\tNAME\t\tMOBILE NUMBER\tEMAIL\n");
        print_();
        printf("%d\t%s\t%s\t%s\n",index,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
        print_();       //abone line prints the index selected by the user 
        label:
        printf("\t\tDelete conformation Y/N: ");    //seeking conformation from the user
        scanf(" %c",&con);
        switch(con)
        {
            case 'y':
            case 'Y':
                for(i=index;i<addressBook->contactCount-1;i++)  //overwrite the index form (index) with next index till contactcount-1 times
                {
                    addressBook->contacts[i]=addressBook->contacts[i+1];
                }
                addressBook->contactCount--;       //finally decrease the contact count by 1 as 1 contact is removed from the array 
                print_();
                printf("\t\tContact deleted successfully!\n");
                print_();
                break;
            case 'n':
            case 'N':
                return;
            default:
                printf("Entered option is Invalid\n");
                goto label;
                break;
        }
        print_redi();
    }
}
