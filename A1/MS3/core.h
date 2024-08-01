/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Anton Samofalov
Student ID#: 172271223
Email      : asamofalov@myseneca.ca
Section    : NJJ

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <stdbool.h>

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//Get a valid integer number
int inputInt(void);

//Validate the value entered is greater than 0
int inputIntPositive(void);

//Validate the value entered is between the range
int inputIntRange(int lowerBound, int upperBound);

//Get a single character and validate the character matches
//any of the characters in the received C string argument
char inputCharOption(const char* validChars);

//Obtain user input for a C string value with a length in the character range specified by the 2bnd and 3rd arguments (inclusive)
void inputCString(char* str, int minLength, int maxLength, bool isPhoneNumber);

//Display an array of 10-character digits as a formatted phone number
void displayFormattedPhone(const char* phone);

// Determines if a given year is a leap year
bool isLeapYear(int year);

// Calculates the number of days in a specific month of a given year.
int getDaysInMonth(int year, int month);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
