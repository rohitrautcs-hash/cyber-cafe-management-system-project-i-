/*
 * user.c
 * -------------------------------------------------
 * This file contains the main logic for user operations.
 * The functions here handle customer activities such as
 * check-in, check-out, viewing records, searching users,
 * and deleting records.
 *
 * These functions were declared earlier in user.h.
 */

 #include <stdio.h>
 #include <string.h> 
 #include "user.h" // include the header file where we declared our user functions
 #include "file_ops.h"
 #include "records.h"
 #include <time.h> // for time-related functions

 #include "billing.h" // for calculateBill and printReceipt functions



  /*
 - This function runs when the owner chooses the "Check In" option.
 - It adds a new customer to the system.
  
  Steps performed:
 - First, it checks if the café has reached the maximum number of customers.
 - Then it asks for the customer's name and PC number.
 - The current time is saved as the login time.
 - The customer's record is added to the users array.
 - Finally, the record is saved to the file.
 */

 void checkIn(struct UserRecord users[], int *count) {

  if (*count >= MAX_USERS) {

    printf("  Sorry, the cafe is full. Cannot check in more customers. \n");
    return; // exit the function if we can't add more customers

  }

  struct UserRecord newUser; // create a new UserRecord variable to hold the new customer's data
  printf(" ---- Check In ---- \n");
  newUser.id = *count + 1; // assign a unique ID based on the current count of users

  // ask for the customer's name and PC number, and save them in the newUser struct
  printf(" Enter customer's name: ");
  scanf("%s", newUser.name); 

  printf(" Enter PC number: ");
  scanf("%s", newUser.pc_number);

  // Record the exat time they sat down 
  /*
 - time(NULL) gets the current time from the computer.
 - It returns a number that represents the current time in seconds since January 1, 1970 (the Unix epoch).
 - We store this value in login_time.
 - Later, the program uses it to calculate how long the user used the PC.
 */

 newUser.login_time = time(NULL); // get the current time and save it as the login time

 /*
 - The user just checked in, so we don't know their logout time yet.
 - We set logout_time to 0 to show it hasn't happened.
 */

 /*
 - The user just checked in, so we don't know their logout time yet.
 - We set logout_time to 0 to show it hasn't happened.
 */
  newUser.logout_time = 0; // set logout time to 0 for now 

  // They have used 0 minutes so far, and their bill is also 0 for now.
  newUser.duration_minutes = 0; // set duration to 0 for now

  // Total bill is also 0 for now.
  newUser.total_bill = 0;

  // Mark them as ACTIVE — they are currently at a PC 
  newUser.is_active = 1; 
  
  /*
 - Add the new customer to the users array.
 - *count shows the next empty slot in the array.
 - For example, if 3 customers are already stored, *count = 3,
 - so the new customer goes into users[3].
 */
  users[*count] = newUser; // saves the new user's record in the array

  // Increase the count by 1 since we just added someone
  *count = *count + 1; // update the count of users

  // Immediately write the new customer’s record to records.txt. Even if the program crashes, we dont lose this new record because it's already saved in the file.

  appendToFile(newUser); // save the new record to the file


  // confirm to the owner that the check-in was successful

  printf("  Check-in successful for %s at PC %s. \n", newUser.name, newUser.pc_number); 
  printf("  Login time has been recorded!!");
  printf(" Customer id is:%d\n", newUser.id);
  //printf

 }

 /*
 - FUNCTION 2 — checkOut()
 
 - This function runs when the owner selects "Check Out".
 - It handles a customer leaving the café.
 
  Step by step:
 - Ask for the customer's ID.
 - Find the customer in the users array.
 - Record the current time as their logout time.
 - Calculate how long they used the PC and their total bill.
 - Print a receipt for the customer.
 - Mark them as inactive (no longer using the PC).
 - Save the updated data back to the file.
 */

 void checkOut(struct UserRecord users[], int count) {
  // Ask owner for the customer's ID to check out 

  int searchId;
  printf(" ---- Check Out ---- \n");
  printf(" Enter customer's ID to check out: ");
  scanf("%d", &searchId);

  /*
  - Search for the customer in the users array by ID.
 - foundIndex will store the position in the array.
 - Start with -1 to mean "not found yet". 
 */

 int foundIndex = -1;
 int i; 

  for (i = 0; i < count; i++) {
    
    // Now check if this record matches the ID we are looking for and is currently active (logged in). we don't want to check out someone who is already checked out.

    if (users[i].id == searchId && users[i].is_active == 1) {
      foundIndex = i; // we found the customer, save the index

      break; // stop searching since we found them
    }
  }
    // if found index is still -1 after the loop, it means we didn't find a matching active record

    if (foundIndex == -1) {
      printf(" Error: No active customer found with ID %d. Please check the ID and try again. \n", searchId);

      return; // exit the function if we can't find the customer
    }

    /*As we found them! and now,the customer is leaving, so we save the current time as their logout time. */

    users[foundIndex].logout_time = time(NULL); // get the current time and save it as the logout time

    
    // mark them as no longer active since they are leaving 
    users[foundIndex].is_active = 0;

    /* 
  - calculateBill() and printReceipt()
  - are used in billing.c.
 
  - user.c finds the customer information.
  - billing.c calculates the bill and
  - prints the receipt.
  
  - Each file has its own job.
  This keeps the program clean and organized.
   */


   // calculate the bill (lives in billing.c)
    calculateBill(&users[foundIndex]); // pass the address

    //print the receipt (also in billing.c)
    printReceipt(users[foundIndex]); // pass the struct by value since we only need to read it, not change it

     updateFile(users, count); 


  }

  /*
 - FUNCTION 3 — viewAllUsers()
 
 - This function displays all customer records in a table.
 - It shows whether each customer is currently using the PC ("ACTIVE")
  or has already checked out ("DONE").
 */

 void viewAllUsers(struct UserRecord users[], int count) {

  printf(" ---- All Customer Records ---- \n");

  // if there are no records, print a message and return
  if (count == 0) {
    printf(" No customer records found. \n");
    return;
  }
   
  // print table header

  printf(" \n %-5s %-15s %-10s %-10s %-10s %-10s \n", "ID", "Name", "PC Number", "Duration", "Total Bill", "Status");
  printf(" ------------------------------------------------------------- \n");
  
  // loop through every customer and print one row each

  int i;
  for (i = 0; i < count; i++) {
    
    // show "active " or "done" based on is_active value
    char status[10];
    if(users[i].is_active == 1) {
      strcpy(status, "ACTIVE"); // copies the string "ACTIVE" into the status variable

    } else {
      strcpy (status, "DONE"); // copies the string "DONE" into the status variable
    }

     /* 
      %-5d means: print an integer, left-aligned, 5 spaces wide
      %-15s means: print a string, left-aligned, 15 spaces wide
      This makes all the columns line up neatly
     */

     printf(" %-5d %-15s %-10s %-10.2f %-10.2f %s \n", users[i].id, users[i].name, users[i].pc_number,
      users[i].duration_minutes, users[i].total_bill, status);

  }

  printf(" ------------------------------------------------------------- \n");
  printf(" Total customers: %d \n", count);


 }

 /*
 - FUNCTION 4 — searchUser()
 
 - This function searches for a customer by name.
 - If the customer is found, it prints all their details.
 - If not found, it shows a message saying the user was not found.
 */

 void searchUser(struct UserRecord users[], int count) {

  printf(" ---- Search User ---- \n");
  if (count == 0) {
    printf("No records to search\n ");
    return;
  }

  // now ask for the name to search for
  char searchName[50];
  printf(" Enter customer's name to search: ");
  scanf("%s", searchName);

  // use loop through the users array to find a matching name 
   /*
     - IMPORTANT: In C you can NEVER compare strings with ==
     - if (users[i].name == searchName)  ← THIS IS WRONG
     
     - You MUST use strcmp() from string.h
     - strcmp() returns 0 if the two strings are identical.
     - Think of it as: "string compare — give me 0 if equal" 
     */

     int found = 0; // 0 = not found, 1 = found
     int i;

     for (i = 0; i < count; i++) {

      if (strcmp(users[i].name, searchName) == 0 ) {
        // we found a match, print their details
        found = 1; // mark that we found the user
        printf(" --------------------\n");
        printf(" Customer Found!\n");
        printf("---------------------\n");

        printf("  ID         : %d\n",   users[i].id);
        printf("  Name       : %s\n",   users[i].name);
        printf("  PC Number  : %s\n",   users[i].pc_number);
        printf("  Minutes    : %.2f\n", users[i].duration_minutes);
        printf("  Bill       : Rs %.2f\n", users[i].total_bill);
        printf("  Status     : %s\n", users[i].is_active ? "ACTIVE" : "DONE");
        printf("---------------------\n");

         /* Don't break here — there might be multiple
           visits by the same person. We show all of them. */
      }
     }

     // if looped through everything and found nothing 
     if (found == 0) {
      printf("No customer found with name: %s\n", searchName);
     }

 }

 /*
 - FUNCTION 5 — deleteRecord()
 
 - This function removes a customer from the users array.
 - Since C arrays have fixed size, we can't just delete a slot.
 - Instead, we move all records after the deleted one one step left,
 - and then reduce the total count by 1.
 - This keeps the array packed with no gaps.
 */

 void deleteRecord(struct UserRecord users[], int *count) {

  printf("   Delete Record---!\n");
  if (count == 0) {
    printf("No records to delete\n");
    return;
  }

  // ask which id to delete
  int deleteId;
  printf(" Enter customer's ID to delete: ");
  scanf("%d", &deleteId);

  // search for that id in the array
  int foundIndex = -1;
  int i;

  for (i = 0; i < *count; i++) {
    if (users[i].id == deleteId) {
      foundIndex = i; // we found the record to delete
      break;
    }
  }

  if (foundIndex == -1) {
    printf(" Error: No customer found with ID %d. Please check the ID and try again. \n", deleteId);
    return; // exit if we can't find the record to delete
  }

  // confirm before deleting  -- good habit in real software
  printf(" Are you sure you want to delete the record of %s?? (1= yes / 0 = no): ", users[foundIndex].name);

  int confirm;
  scanf("%d", &confirm);

  if (confirm != 1) {
    printf(" Deletion cancelled. \n");
    return; // exit if the user cancels the deletion
  }


  /*
   Shift all users after the deleted one left by one.
  This overwrites the deleted record and keeps the array packed.
 */

//   Arrays in C cannot shrink automatically. You can’t just “delete” a slot.
// So, if you want to remove a record (say at position foundIndex), you overwrite it with the next record.
// Then do the same for the next one, and so on, shifting everything left.
   
  for (i = foundIndex; i < *count - 1; i++) {
    users[i] = users[i + 1]; // copy the next record into the current slot

  }


    //Reduce the count — the array is now 1 smaller 
    *count = *count - 1;

    // Rewrite the file with the updated array after deletion
    updateFile(users, *count);

    printf(" Record deleted successfully. \n");

 }