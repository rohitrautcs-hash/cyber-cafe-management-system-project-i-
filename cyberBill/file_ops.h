/* file_ops.h - This header file DECLARES  the three functions that handle reading and writing 
to our records.txt file.
-We will just declare the functions here, and the actual code logic for these functions will be in file_ops.c
*/

#ifndef FILE_OPS_H // include guard to prevent multiple inclusions of this header file
#define FILE_OPS_H // mark this file as included

/*
 * We include records.h because our functions below use
 * "struct UserRecord" — the compiler needs to know
 * what that is before we can mention it here.
 */
#include "records.h" // include the records.h header file to use the UserRecord struct


/*
 * loadFromFile()
 
  -When the program starts up, we call this function.
  It opens records.txt and reads all the saved customer
  data back into our array in memory.
 
  -users[]  = the array where we store all customer records
 -count    = a pointer to our counter variable so we can
             update how many records we loaded
             (we use a pointer because we want to CHANGE
            the original variable, not a copy of it)
 */

 void loadFromFile(struct UserRecord users[], int *count);

 /*
 * appendToFile()
 
  -Every time a NEW customer checks in, we call this.
  It takes that one customer's data and adds (appends)
  it to the END of records.txt.
 
 -We pass the struct by VALUE here — meaning a copy
  of the customer data is sent to this function.
  That's fine because we just need to read and save it.
 
 - u = one complete UserRecord to save
 */

 void appendToFile(struct UserRecord u);

 /*
 * updateFile()
 
 -Called when a customer checks OUT or when we delete
  a record. It rewrites the ENTIRE records.txt from
  scratch using the current array in memory.
 
  -Why rewrite everything? Because .txt files don't let
  you "edit the middle" easily. It's simpler and safer
  to just wipe and rewrite the whole file.
 
 - users[] = the full array of all customer records
 - count   = how many records are in that array
 */

 void updateFile(struct UserRecord users[], int count);

 #endif // end of include guard