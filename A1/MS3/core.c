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

#define _CRT_SECURE_NO_WARNINGS
#define MAX_BUFFER_SIZE 100

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"

#include <ctype.h>

#include "clinic.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

//Get a valid integer number
int inputInt(void)
{
	int value;
	char newLine = 'x';

	do
	{
		scanf("%d%c", &value, &newLine);
		if (newLine != '\n')
		{
			clearInputBuffer();
			printf("Error! Input a whole number: ");
		}
	} while (newLine != '\n');

	return value;
}

//Validate the value entered is greater than 0
int inputIntPositive(void)
{
	int value;
	do
	{
		value = inputInt();
		if (value <= 0)
			printf("ERROR! Value must be > 0: ");
	} while (value <= 0);

	return value;
}

//Validate the value entered is between the range
int inputIntRange(int lowerBound, int upperBound)
{
	int value;
	do
	{
		value = inputInt();
		if (value < lowerBound || value > upperBound)
			printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);

	} while (value < lowerBound || value > upperBound);

	return value;
}

//Get a single character and validate the character matches
//any of the characters in the received C string argument
char inputCharOption(const char* validChars)
{
	char ch;
	bool isValidChar;
	do
	{
		isValidChar = false;
		ch = getchar();

		if(ch != '\n')
		{
			if (strchr(validChars, ch) != NULL)
			{
				isValidChar = true;
			}
			while(getchar() != '\n')
			{
				isValidChar = false;
			}
		}
		
		if (!isValidChar)
			printf("ERROR: Character must be one of [%s]: ", validChars);
	} while (!isValidChar);

	return ch;
}

//Obtain user input for a C string value with a length in the character range specified by the 2bnd and 3rd arguments (inclusive)
void inputCString(char* str, int minLength, int maxLength, bool isPhoneNumber)
{
	int length;
	int i;
	bool isValidLength = false;
	char temp[MAX_BUFFER_SIZE];
	do
	{
		scanf("%[^\n]", temp);
		clearInputBuffer();
		length = strlen(temp);
		if(isPhoneNumber)
		{
			if (length != PHONE_LEN)
				printf("Invalid 10-digit number! Number: ");
			else
				isValidLength = true;
		}
		else
		{
			if (minLength == maxLength && length != minLength)
				printf("ERROR: String length must be exactly %d chars: ", minLength);
			else if (length > maxLength)
				printf("ERROR: String length must be no more than %d chars: ", maxLength);
			else if (length < minLength)
				printf("ERROR: String length must be between %d and %d chars: ", minLength, maxLength);
			else
				isValidLength = true;
		}
	} while (!isValidLength);

	for (i = 0; i < length; i++)
		str[i] = temp[i];
	str[length] = '\0';
}

//Display an array of 10-character digits as a formatted phone number
void displayFormattedPhone(const char* phone)
{
	bool isValidNumber = true;
	int i;
	if (phone != NULL) {
		for (i = 0; i < 10; i++)
		{
			if (!isdigit(phone[i]))
				isValidNumber = false;
		}

		if (phone[10] != '\0')
		{
			isValidNumber = false;
		}

		if (isValidNumber)
		{
			printf("(%c%c%c)%c%c%c-%c%c%c%c", phone[0],
				phone[1], phone[2], phone[3], phone[4],
				phone[5], phone[6], phone[7], phone[8], phone[9]);
		}
		else
		{
			printf("(___)___-____");
		}
	}
	else
	{
		printf("(___)___-____");
	}
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Determines if a given year is a leap year
bool isLeapYear(int year)
{
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Calculates the number of days in a specific month of a given year.
int getDaysInMonth(int year, int month)
{
	int days;
	if (month == 2)
	{
		days = isLeapYear(year) ? 29 : 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		days = 30;
	}
	else
	{
		days = 31;
	}
	return days;
}