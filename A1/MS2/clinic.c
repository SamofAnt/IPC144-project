/*/////////////////////////////////////////////////////////////////////////
						Assignment 1 - Milestone 2
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

#include <stdio.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

#include <stdlib.h>
#include <string.h>


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
	printf("Pat.# Name            Phone#\n"
		"----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
	if (fmt == FMT_FORM)
	{
		printf("Name  : %s\n"
			"Number: %05d\n"
			"Phone : ", patient->name, patient->patientNumber);
		displayFormattedPhone(patient->phone.number);
		printf(" (%s)\n", patient->phone.description);
	}
	else
	{
		printf("%05d %-15s ", patient->patientNumber,
			patient->name);
		displayFormattedPhone(patient->phone.number);
		printf(" (%s)\n", patient->phone.description);
	}
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
	int selection;

	do {
		printf("Veterinary Clinic System\n"
			"=========================\n"
			"1) PATIENT     Management\n"
			"2) APPOINTMENT Management\n"
			"-------------------------\n"
			"0) Exit System\n"
			"-------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 2);
		putchar('\n');
		switch (selection)
		{
		case 0:
			printf("Are you sure you want to exit? (y|n): ");
			selection = !(inputCharOption("yn") == 'y');
			putchar('\n');
			if (!selection)
			{
				printf("Exiting system... Goodbye.\n\n");
			}
			break;
		case 1:
			menuPatient(data->patients, data->maxPatient);
			break;
		case 2:
			printf("<<< Feature not yet available >>>\n\n");
			break;
		}
	} while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
	int selection;

	do {
		printf("Patient Management\n"
			"=========================\n"
			"1) VIEW   Patient Data\n"
			"2) SEARCH Patients\n"
			"3) ADD    Patient\n"
			"4) EDIT   Patient\n"
			"5) REMOVE Patient\n"
			"-------------------------\n"
			"0) Previous menu\n"
			"-------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 5);
		putchar('\n');
		switch (selection)
		{
		case 1:
			displayAllPatients(patient, max, FMT_TABLE);
			suspend();
			break;
		case 2:
			searchPatientData(patient, max);
			break;
		case 3:
			addPatient(patient, max);
			suspend();
			break;
		case 4:
			editPatient(patient, max);
			break;
		case 5:
			removePatient(patient, max);
			suspend();
			break;
		}
	} while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
	int selection;

	do {
		printf("Edit Patient (%05d)\n"
			"=========================\n"
			"1) NAME : %s\n"
			"2) PHONE: ", patient->patientNumber, patient->name);

		displayFormattedPhone(patient->phone.number);

		printf("\n"
			"-------------------------\n"
			"0) Previous menu\n"
			"-------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 2);
		putchar('\n');

		if (selection == 1)
		{
			printf("Name  : ");
			inputCString(patient->name, 1, NAME_LEN);
			putchar('\n');
			printf("Patient record updated!\n\n");
		}
		else if (selection == 2)
		{
			inputPhoneData(&patient->phone);
			printf("Patient record updated!\n\n");
		}

	} while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
	int i;
	int recordsCount = 0;
	if (fmt == FMT_TABLE)
		displayPatientTableHeader();

	for (i = 0; i < max; i++)
	{
		if (patient[i].patientNumber != 0) {
			displayPatientData(&patient[i], fmt);
			recordsCount++;
		}
	}
	if (!recordsCount)
		printf("*** No records found ***\n");

	putchar('\n');
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
	int selection;
	do
	{
		printf("Search Options\n"
			"==========================\n"
			"1) By patient number\n"
			"2) By phone number\n"
			"..........................\n"
			"0) Previous menu\n"
			"..........................\n"
			"Selection: ");
		selection = inputIntRange(0, 2);
		putchar('\n');
		switch (selection)
		{
		case 1:
			searchPatientByPatientNumber(patient, max);
			suspend();
			break;
		case 2:
			searchPatientByPhoneNumber(patient, max);
			suspend();
			break;
		}
	} while (selection);
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
	int index = -1;
	int newPatientNumber;
	int i;
	for (i = 0; i < max; i++)
	{
		if (patient[i].patientNumber == 0 && index == -1)
			index = i;

	}

	if (index == -1)
		printf("ERROR: Patient listing is FULL!\n");
	else
	{
		newPatientNumber = nextPatientNumber(patient, max);
		patient[index].patientNumber = newPatientNumber;
		inputPatient(&patient[index]);
		printf("*** New patient record added ***\n");
		
	}
	putchar('\n');
}


// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
	int patientNumber;
	int patientIndex;
	printf("Enter the patient number: ");
	scanf("%d", &patientNumber);
	clearInputBuffer();
	putchar('\n');
	patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max);
	if (patientIndex == -1) {
		printf("ERROR: Patient record not found!\n");
		putchar('\n');
	}
	else
		menuPatientEdit(&patient[patientIndex]);

}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
	int patientNumber;
	int patientIndex;
	char selection;
	printf("Enter the patient number: ");
	scanf("%d", &patientNumber);
	clearInputBuffer();
	putchar('\n');
	patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max);
	if (patientIndex == -1)
	{
		printf("ERROR: Patient record not found!\n");
		putchar('\n');
	}
	else
	{
		displayPatientData(&patient[patientIndex], FMT_FORM);
		printf("\nAre you sure you want to remove this patient record? (y/n): ");
		selection = inputCharOption("yn");
		if (selection == 'y')
		{
			patient[patientIndex].patientNumber = 0;
			strcpy(patient[patientIndex].name, "");
			strcpy(patient[patientIndex].phone.description, "");
			strcpy(patient[patientIndex].phone.number, "");

			printf("Patient record has been removed!\n");
		}
		else
		{
			printf("Operation aborted.\n");
		}
		putchar('\n');
	}
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
	int patientNumber;
	int patientIndex;
	printf("Search by patient number: ");
	scanf("%d", &patientNumber);
	putchar('\n');
	clearInputBuffer();
	patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max);
	if (patientIndex == -1)
		printf("*** No records found ***\n");
	else
		displayPatientData(&patient[patientIndex], FMT_FORM);
	putchar('\n');
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
	char phoneNumber[PHONE_LEN + 1];
	int i;
	int recordsCount = 0;
	printf("Search by phone number: ");
	scanf("%10s", phoneNumber);
	clearInputBuffer();
	putchar('\n');
	displayPatientTableHeader();
	for (i = 0; i < max; i++)
	{
		if (!strcmp(patient[i].phone.number, phoneNumber)) {
			displayPatientData(&patient[i], FMT_TABLE);
			recordsCount++;
		}
	}
	if (!recordsCount)
		printf("\n*** No records found ***\n");

	putchar('\n');
}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
	int maxPatientNumber = patient[0].patientNumber;
	int i;
	for (i = 0; i < max; i++)
	{
		if (patient[i].patientNumber > maxPatientNumber)
			maxPatientNumber = patient[i].patientNumber;
	}

	return maxPatientNumber + 1;
}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
	const struct Patient patient[], int max)
{
	int index = -1;
	int i;
	for (i = 0; i < max; i++)
		if (patient[i].patientNumber == patientNumber)
			index = i;
	return index;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
	printf("Patient Data Input\n"
		"------------------\n"
		"Number: %05d\n"
		"Name  : ", patient->patientNumber);
	inputCString(patient->name, 1, NAME_LEN);
	putchar('\n');
	inputPhoneData(&patient->phone);
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
	int selection;
	printf("Phone Information\n"
		"-----------------\n"
		"How will the patient like to be contacted?\n"
		"1. Cell\n"
		"2. Home\n"
		"3. Work\n"
		"4. TBD\n"
		"Selection: ");
	selection = inputIntRange(0, 4);
	putchar('\n');
	switch (selection)
	{
	case 1:
		strcpy(phone->description, "CELL");
		break;
	case 2:
		strcpy(phone->description, "HOME");
		break;
	case 3:
		strcpy(phone->description, "WORK");
		break;

	}
	if (selection == 4) {
		strcpy(phone->description, "TBD");
		strcpy(phone->number, "");
	}
	else
	{
		printf("Contact: %s\n"
			"Number : ", phone->description);
		inputCString(phone->number, 10, 10);
		putchar('\n');
	}

}
