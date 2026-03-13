/*
 - main.c

 - This is the main starting file of the program.
 - When the program runs, execution begins here.
 
 - It sets up the program and shows the menu
 - for the owner to choose different options.
 
 - The actual work is done by functions in
 - other files. This file mainly calls them.
 */


#include <stdio.h>
#include "records.h"
#include "file_ops.h"
#include "user.h"
#include "billing.h"

void displayMenu() {
  printf("\n---- Cyber Cafe Management System----\n");
  printf("========================================\n");
  printf("\n1. Check In a customer       ");
  printf("\n2. Check Out a customer      ");
  printf("\n3.View all customers         ");
  printf("\n4.Search for a customer       ");
  printf("\n5.Delete a REcord           ");
  printf("\n6.Exit                   \n ");
  
  printf("--------------------------------\n");
  printf("Enter Your Choice: ");
}


  /*
 - main()
 
 - This is where the program starts.
 - Every C program must have one main() function.
 
 - What happens here:
 - Create an array to store customer records.
 - Load any saved records from the file.
 - Show the menu repeatedly until the owner chooses Exit.
 */


int main()
{
    struct UserRecord users[MAX_USERS];

    int count = 0; // this variable tracks how many customers are currently in your array


    /*This will store whatever number the owner types
     when picking from the menu. */
    int choice;

    // welcome message
    printf(" Welcome to Cyber Cafe Management System!!");
    printf("------------------------------------------\n");

    /*
  - Load saved customer records from records.txt.
  - This keeps the previous data when the program starts again.
  -  If the file doesn't exist yet, the program simply starts with empty records.
 */


    /* load any saved records first */
    loadFromFile(users, &count);

    /*
  - MAIN LOOP
 
  - This loop keeps the program running until the owner chooses Exit.
 
  -Each time the loop runs:
  - Display the menu
  - Read the owner's choice
  - Call the function for that option
  - Show the menu again
 */

  while (1) {
    displayMenu();
    scanf("%d", &choice);

    //using switch to check which number was typed and jump to the matching case
    switch (choice) {

      case 1:
      // if owner chooses check in 
      checkIn(users, &count);
      break;

      case 2: // if owner choose check out
      checkOut(users, count); 
      break;

      case 3:
      viewAllUsers(users, count);
      break;
      
       case 4:
      searchUser(users, count);
      break;
      
       case 5:
      deleteRecord(users, &count);
      break;
      
       case 6:
      // deleteRecord(users, &count);
      // owner chooses exit , we say goodbye
      printf("\n Good bye! All data has been saved\n\n");

     return 0; // means program finished successfully

     default:
     printf("\n Invalid choice. Please enter choice 1 to 6. \n");
     break;
  
    }

  }

  /*
  - This line usually won't run because the program exits
  - earlier when the user chooses the Exit option.
  - It is still written here as good programming practice.
 */
    return 0;
}