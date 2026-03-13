// this file lists all the billing functions
// the actual logic code for this function is in billing.c
// this file just tell other file "hey, this exist"

#ifndef BILLING_H
#define BILLING_H

// we need records.h because our function works with strcut UserRecord
#include "records.h"

/*
 * calculateBill()
 *
 * Calculates how long a customer used the PC and their total bill.
 * Updates the original user record directly using a pointer.
 */
void calculateBill(struct UserRecord *user);

/*
 * printReceipt()
 *
 * Prints a formatted receipt for one customer.
 * Only reads the data; does not change the record.
 */
void printReceipt(struct UserRecord user);

#endif