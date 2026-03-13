/* This is called an "include guard" 
It stops the compiler from including the same header file twice
If multiple files include this header file at the same time 
Always put this at the top of every .h file */

#ifndef RECORDS_H // prevents the header file from being included multiple times. 
#define RECORDS_H // mark this file as included 

/* time.h gives us the special type called "time_t"
 -which is how c stores a timestamp (date + time as a number )*/
 #include <time.h>

/*These are constants 
-These are the fixed values that never change while running the program.
-Using #define means if you want to change the value, you only need to change it in one place, and it will update everywhere in the code where it's used.
*/

 #define MAX_USERS 100 // this is a "preprocessor macro" - it replaces all instances of MAX_USERS with 100 before compilation
 #define RATE_PER_MINUTE 5 
 #define RECORDS_FILE "records.txt" // this is the name of the file where we will store the records


 struct UserRecord {

  int id; // unique identifier for each user
  char name[50]; // user's name
  char pc_number[20]; // user's PC number
  time_t login_time; // when the user logged in
  time_t logout_time; // when the user logged out // time_t is a data type defined in time.h that represents time as the number of seconds since January 1, 1970 (the Unix epoch)

  double duration_minutes; // how long the user used the PC in minutes
  double total_bill; // total amount to be paid by the user

  int is_active; // 1 if the user is currently logged in, 0 if logged out

 };

#endif // this ends the include guard

/*
-End of records.h file
-The #endif above closed the #ifndef we opend at the top.
-Every .h file must end with #endif to close the include guard.
*/