/*
  billing.c
 - This file contains the actual code for the 2 functions
 -  we declared in billing.h
 
 -  Function 1 — calculateBill() : does the math
 -  Function 2 — printReceipt()  : prints the receipt
 */

#include <stdio.h>
#include "records.h"
#include "billing.h"

/*
 - FUNCTION 1 — calculateBill()
 
 - Calculates how many minutes a customer used the PC
 - and the total bill based on the rate.
 
 - Uses a POINTER so it can update the original record directly.
 
 - Example call: calculateBill(&users[i]);
 - The & gives the function the address of the record.
 */
void calculateBill(struct UserRecord *user) {
  
  /*
 - Calculate how long the customer used the PC.
 - difftime() returns the difference in seconds.
 - Use user->logout_time to access the logout time from the pointer.
 - (-> is used with pointers instead of .)
 */

 double duration_seconds = difftime(user->logout_time, user->login_time); // calculates time diff in seconds

 // convert seconds into minutes
 user->duration_minutes = duration_seconds / 60.0; // convert to minutes and store in the record

 // calculate the bill 
 user->total_bill = user->duration_minutes * RATE_PER_MINUTE ;
}

/*
 -  FUNCTION 2 — printReceipt()
 
 -  This just prints a nice clean receipt on the screen.
 -  No math here — just formatting and printf.
 
 -  Notice it receives the struct directly (no pointer)
 -  because we are only READING — not changing anything.

 */
void printReceipt(struct UserRecord user) {
    

    /* 
     - We want to show the login and logout times in a
     - human readable format like "14:30:00"
     - not as a big raw number like "1748293847"
     
     - ctime() converts a time_t number into a readable
     - string automatically. It adds a \n at the end
     - so we don't need to add one ourselves. 
     */

     printf("\n");
     printf("--------------------------\n");
     printf(" CyberCafe Receipt !!\n");
     printf("--------------------------\n");
     printf("  ID          :%d\n", user.id);
     printf("  Name        :%s\n", user.name);
     printf("  PC          :%s\n",user.pc_number);
     printf("----------------------------\n");
    printf("  Logged in    :%s", ctime(&user.login_time));
    printf("  Logged out   :%s", ctime(&user.logout_time));
    printf("----------------------------\n");

    printf(" Duration      :%.2f\n", user.duration_minutes);
    printf(" Rate          :Rs%d / min\n", RATE_PER_MINUTE);
    printf("---------------------------\n");
    printf(" Total bill    :Rs%.2f\n", user.total_bill);
    printf("==============================\n");
    printf("THANKYOU!! COME AGAIN!!");
     printf("==============================\n");

}

