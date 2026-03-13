// This file lists all the functions that user.c will use to interact with the records.txt file

#ifndef USER_H // include guard to prevent multiple inclusions of this header file
#define USER_H 


/* We need records.h because our functions below
 work with struct UserRecord */

 #include "records.h" // include the records.h header file to use the UserRecord struct 

 /*
 checkIn() 
 This function is called when a new customer arrives at the cyber café.
 It collects the user's details, stores them in the users array,
 marks the user as active, and increases the total user count.
 The new record may also be saved to the file.
*/

  void checkIn(struct UserRecord users[], int *count);

  /*
 checkOut()
 This function is called when a customer leaves the cyber café.
 It finds the user's record, sets the logout time, calculates
 the total usage duration and bill, and marks the user as inactive.
*/

void checkOut(struct UserRecord users[], int count);

  /*
 viewAllUsers()
 This function displays the details of all users stored in the users array.
 It loops through the array using the count and prints each user's information.
*/

//Prints a neat table of ALL customers — both active (still sitting) and checked out.

void viewAllUsers(struct UserRecord users[], int count);

/*
 searchUser()
 This function searches for a user in the users array
 using an ID or name and displays the user's details
 if the record is found.
*/

void searchUser(struct UserRecord users[], int count);


// deleteRecord(): Deletes a user's record from the list of users.

void deleteRecord(struct UserRecord users[], int *count); // int *count is a pointer because we will need to decrease the count when we delete a record.

#endif
