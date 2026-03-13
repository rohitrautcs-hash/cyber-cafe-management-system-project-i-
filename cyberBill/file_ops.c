/*
 file_ops.c - This file contains actual logic code of those three functions we declared in 
 file_ops.h
 */

 #include <stdio.h>
 #include <stdlib.h> // for file operations and memory management
 #include "file_ops.h" // include the header file where we declared our functions
 #include "records.h" // include the header file where we defined our UserRecord struct

  /*  FUNCTION 1 — loadFromFile()
 
  This runs ONCE when the program first starts.
   It opens records.txt and reads every saved customer
   record back into our array in memory.
 */

 void loadFromFile (struct UserRecord users[], int *count) {

  /*fopen() tries to open a file and gives us back a "FILE pointer" 
  "r" means open for reading only
  */
  
  FILE *fp = fopen(RECORDS_FILE, "r"); // open the file for reading 

  if (fp == NULL) { // if fopen returns NULL, it means the file doesn't exist or can't be opened
    printf("  (No saved records found. Starting fresh.) \n");
 
  }

  while (*count < MAX_USERS) {
    // read one full UserRecord from the file

    int result = fscanf(fp, "%d %s %s %ld %ld %lf %lf %d", &users[*count].id, &users[*count].name, &users[*count].pc_number, &users[*count].login_time, &users[*count].logout_time, &users[*count].duration_minutes, &users[*count].total_bill, &users[*count].is_active);
    

    if (result != 8) {
      // if fscanf doesn't read exactly 8 items, it means we've reached the end of the file. Stop looping. 
      break;
    }

   *count = *count + 1; // increase the count of loaded records
    }

    // close the file after done reading 
    fclose(fp);

    printf("  Loaded %d records from file. \n", *count); // print how many records we loaded
  }

  /* FUNCTION 2 — appendToFile()
  
 
 Called every time a NEW customer checks in.
 It adds just that ONE customer's data to the
 END of records.txt without touching the rest.

 "Append" means "add to the end of the file"
 */

 void appendToFile(struct UserRecord u) 
 {

  // "a" means open for appending (writing at the end of the file)


  FILE *fp = fopen(RECORDS_FILE, "a"); // open the file for appending

  // check if the file opened successfully 

  if (fp == NULL) {
    printf("  Error: Could not open file to save record. \n");
    return; // exit the function if we can't open the file

  }
  // write all the fields of this one customer to the file 

  // fprintf() is like printf but it writes to a file instead of the console

  fprintf(fp, "%d %s %s %ld %ld %.2lf %.2lf %d\n", u.id, u.name, u.pc_number, u.login_time, u.logout_time, u.duration_minutes, u.total_bill, u.is_active); 

  // close the file after writing

  fclose(fp);
  printf("  Record saved to file. \n");
 }

 /*
  FUNCTION 3 — updateFile()
  Called when a customer checks OUT or when we delete a record. It rewrites the ENTIRE records.txt from scratch using the current array in memory.

 */

 void updateFile (struct UserRecord users[], int count) 
 {

  // open records.txt in write mode
  // "w" means open for writing and erase everything that was in the file before

  FILE *fp = fopen(RECORDS_FILE, "w"); // open the file for writing

  if (fp == NULL) {

    printf("  Error: Could not open file to update records. \n");

    return; // exit the function if we can't open the file

  }

  // loop through the array of user records and write each one to the file

  int i;
  for (i = 0; i < count; i++) {
    fprintf(fp, "%d %s %s %ld %ld %.2lf %.2lf %d\n", users[i].id, users[i].name, users[i].pc_number, users[i].login_time, users[i].logout_time, users[i].duration_minutes, users[i].total_bill, users[i].is_active); 
  }

  // close the file after writing 
  fclose(fp);

  printf("  File updated successfully. \n");
 }