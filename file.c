#include <stdio.h>
#include "file.h"
#include<unistd.h>
void saveContactsToFile(AddressBook *addressBook) {     //moving datas from addressbook to .csv file
    int i;
    FILE *fsave;
    fsave = fopen("addressbook.csv","w");       //opening in write mode
    if(fsave==NULL)
    {
        printf("File not found\n");     //file error indication (safety purpose)
        return ;
    }
    for(i=0;i<addressBook->contactCount;i++)    //move the contacts to file till contactcunt times
    {
        fprintf(fsave,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fsave);  //finally close the file 
    for(int i=0;i<=100;i++)     //saing animation with percentage
    {
        printf("\t\tSaving contatcts %d%%\r",i);
        fflush(stdout);
        if(i==100)
        {
            usleep(500000);
        }
        usleep(10000);
    }
    
}

void loadContactsFromFile(AddressBook *addressBook) {       //move contacts from file to addressbook
    int i=0;
    FILE *fp;
    fp = fopen("addressbook.csv","r");      //open read mode
    if(fp==NULL)
    {
        printf("File not found\n");
        return ;
    }
    while(fscanf(fp,"%[^,],%[^,],%s\n",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email)==3)
    {       //the above scan will hapen till the number of successfull scanned argumetns is equal to 3(name,phone,email)
        addressBook->contactCount++;    //increasing countactcount each successfull scan
    }
    fclose(fp);
}
