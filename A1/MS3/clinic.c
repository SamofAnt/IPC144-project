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

#include <stdio.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

#include <float.h>
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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
	printf("Clinic Appointments for the Date: ");

	if (isAllRecords)
	{
		printf("<ALL>\n\n");
		printf("Date       Time  Pat.# Name            Phone#\n"
			"---------- ----- ----- --------------- --------------------\n");
	}
	else
	{
		printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
		printf("Time  Pat.# Name            Phone#\n"
			"----- ----- --------------- --------------------\n");
	}
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
	const struct Appointment* appoint,
	int includeDateField)
{
	if (includeDateField)
	{
		printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
			appoint->date.day);
	}
	printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
		patient->patientNumber, patient->name);

	displayFormattedPhone(patient->phone.number);

	printf(" (%s)\n", patient->phone.description);
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
			menuAppointment(data);
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
			inputCString(patient->name, 1, NAME_LEN, false);
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
	int selection;

	do {
		printf("Appointment Management\n"
			"==============================\n"
			"1) VIEW   ALL Appointments\n"
			"2) VIEW   Appointments by DATE\n"
			"3) ADD    Appointment\n"
			"4) REMOVE Appointment\n"
			"------------------------------\n"
			"0) Previous menu\n"
			"------------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 4);
		putchar('\n');
		switch (selection)
		{
		case 1:
			viewAllAppointments(data);
			suspend();
			break;
		case 2:
			viewAppointmentSchedule(data);
			suspend();
			break;
		case 3:
			addAppointment(data->appointments, data->maxAppointments,
				data->patients, data->maxPatient);
			suspend();
			break;
		case 4:
			removeAppointment(data->appointments, data->maxAppointments,
				data->patients, data->maxPatient);
			suspend();
			break;
		}
	} while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
			strncpy(patient[patientIndex].name, "", NAME_LEN);
			strncpy(patient[patientIndex].phone.description, "", PHONE_DESC_LEN);
			strncpy(patient[patientIndex].phone.number, "", PHONE_LEN);

			printf("Patient record has been removed!\n");
		}
		else
		{
			printf("Operation aborted.\n");
		}
		putchar('\n');
	}
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(const struct ClinicData* data) {
	int patientIndex = -1;
	int i;
	bubbleSort(data->appointments, data->maxAppointments);
	displayScheduleTableHeader(NULL, 1);
	for (i = 0; i < data->maxAppointments; i++)
	{
		if (data->appointments[i].patientNumber != 0)
		{
			patientIndex = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
			displayScheduleData(&data->patients[patientIndex], &data->appointments[i], 1);
		}

	}
	putchar('\n');
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data) {
	int maxDays, i, patientIndex;
	struct Date date = { 0 };
	printf("Year        : ");
	date.year = inputIntPositive();
	printf("Month (1-12): ");
	date.month = inputIntRange(1, 12);
	maxDays = getDaysInMonth(date.year, date.month);
	printf("Day (1-%d)  : ", maxDays);
	date.day = inputIntRange(1, maxDays);
	putchar('\n');
	displayScheduleTableHeader(&date, 0);
	for (i = 0; i < data->maxAppointments; i++)
	{
		if ((data->appointments[i].patientNumber != 0) &&
			(data->appointments[i].date.year == date.year &&
				data->appointments[i].date.month == date.month &&
				data->appointments[i].date.day == date.day))
		{
			patientIndex = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
			displayScheduleData(&data->patients[patientIndex], &data->appointments[i], 0);
		}
	}
	putchar('\n');
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appoints, int maxAppoints, struct Patient* patients, int maxPatient) {
	int patientNumber;
	struct Date date;
	struct Time time;
	int index = findEmptyAppointmentSlot(appoints, maxAppoints);
	bool isValid = true;

	if (index == -1)
	{
		printf("ERROR: Appointment listing is FULL!\n");
		isValid = false;
	}

	if (isValid)
	{
		patientNumber = getValidPatientNumber(patients, maxPatient);
		if (patientNumber == -1)
		{
			isValid = false;
		}
	}
	if (isValid)
	{
		do {
			date = getValidDate();
			time = getValidTime();
			isValid = isTimeSlotAvailable(appoints, maxAppoints, &date, &time);
			if (!isValid)
			{
				putchar('\n');
				printf("ERROR: Appointment timeslot is not available!\n\n");
			}
		} while (!isValid);
		appoints[index].patientNumber = patientNumber;
		appoints[index].date = date;
		appoints[index].time = time;
		printf("\n*** Appointment scheduled! ***\n");
		clearInputBuffer();
		putchar('\n');
	}
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appoints, int maxAppoints, struct Patient* patients, int maxPatient) {
	int patientNumber, i;
	int patientIndex;
	bool isFound = false;
	struct Date date;
	char selection;
	
	patientNumber = getValidPatientNumber(patients, maxPatient);
	
	if(patientNumber != -1)
	{
		patientIndex = findPatientIndexByPatientNum(patientNumber, patients, maxPatient);
		date = getValidDate();
		for (i = 0; i < maxAppoints; i++)
		{
			if (appoints[i].patientNumber == patientNumber &&
				appoints[i].date.year == date.year &&
				appoints[i].date.month == date.month &&
				appoints[i].date.day == date.day &&
				isFound == false)
			{
				putchar('\n');
				displayPatientData(&patients[patientIndex], FMT_FORM);
				printf("Are you sure you want to remove this appointment (y,n): ");
				selection = inputCharOption("yn");
				if (selection == 'y')
				{
					appoints[i].patientNumber = 0;
					appoints[i].date.day = 0;
					appoints[i].date.month = 0;
					appoints[i].date.year = 0;
					appoints[i].time.hour = 0;
					appoints[i].time.min = 0;
					printf("\nAppointment record has been removed!\n");
					isFound = true;
				}
				else
				{
					printf("Operation aborted.\n");
				}
				putchar('\n');
			}
		}
		if(!isFound)
		{
			printf("ERROR: Appointment not found!\n");
		}
	}
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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

// Compares two appointments based on their dates
int compareDates(const struct Appointment* first, const struct Appointment* second)
{
	int diff = 0;
	if (first->date.year != second->date.year)
		diff = first->date.year - second->date.year;
	else if (first->date.month != second->date.month)
		diff = first->date.month - second->date.month;
	else if (first->date.day != second->date.day)
		diff = first->date.day - second->date.day;
	else if (first->time.hour != second->time.hour)
		diff = first->time.hour - second->time.hour;
	else
		diff = first->time.min - second->time.min;
	return diff;
}

// Sorts an array of appointments in ascending order based on their dates using bubble sort
void bubbleSort(struct Appointment* appoints, int max)
{
	int i, j;
	for (i = max - 1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (appoints->patientNumber != 0 && compareDates(&appoints[j], &appoints[j + 1]) > 0)
			{
				struct Appointment temp = appoints[j];
				appoints[j] = appoints[j + 1];
				appoints[j + 1] = temp;
			}
		}
	}
}

// Checks if a specific time slot is available for scheduling an appointment
bool isTimeSlotAvailable(const struct Appointment* appoints, int max, const struct Date* date, const struct Time* time)
{
	int i;
	bool isValid = true;
	for (i = 0; i < max; i++)
	{
		if (appoints[i].patientNumber >= 1 &&
			appoints[i].date.year == date->year &&
			appoints[i].date.month == date->month &&
			appoints[i].date.day == date->day &&
			appoints[i].time.hour == time->hour &&
			appoints[i].time.min == time->min)
		{
			isValid = false;
		}
	}
	return isValid;
}

// Finds the first available slot in the appointment array
int findEmptyAppointmentSlot(struct Appointment* appoints, int max)
{
	int i;
	int index = -1;
	for (i = 0; i < max; i++)
	{
		if (appoints[i].patientNumber < 1 && index == -1)
			index = i;
	}
	return index;
}

// Validates a patient number if it exists in the lists of patients
int getValidPatientNumber(struct Patient* patients, int max)
{
	int patientNumber;
	printf("Patient Number: ");
	scanf("%d", &patientNumber);
	clearInputBuffer();
	if (findPatientIndexByPatientNum(patientNumber, patients, max) == -1) {
		printf("ERROR: Patient record not found!\n");
		putchar('\n');
		patientNumber = -1;
	}
	return patientNumber;
}

// Prompts the user to enter a valid date and returns it as a Date structure
struct Date getValidDate(void)
{
	struct Date date;
	int maxDays;
	printf("Year        : ");
	date.year = inputIntPositive();
	printf("Month (1-12): ");
	date.month = inputIntRange(1, 12);
	maxDays = getDaysInMonth(date.year, date.month);
	printf("Day (1-%d)  : ", maxDays);
	date.day = inputIntRange(1, maxDays);
	return date;
}

// Prompts the user to enter a valid time and returns it as a Time structure
struct Time getValidTime(void)
{
	struct Time time;
	bool isValid = false;
	do {
		printf("Hour (0-23)  : ");
		scanf("%d", &time.hour);
		printf("Minute (0-59): ");
		scanf("%d", &time.min);
		if (time.hour >= START_HOUR && (time.hour < END_HOUR || (time.hour == END_HOUR && time.min == 0)) && time.min % INTERVAL == 0) {
			isValid = true;
		}
		else {
			printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", START_HOUR, END_HOUR, INTERVAL);
		}
	} while (!isValid);
	return time;
}
//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
	printf("Patient Data Input\n"
		"------------------\n"
		"Number: %05d\n"
		"Name  : ", patient->patientNumber);
	inputCString(patient->name, 1, NAME_LEN, false);
	putchar('\n');
	inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
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
		inputCString(phone->number, 10, 10, true);
		putchar('\n');
	}

}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
	int i = 0;
	FILE* fp = NULL;

	fp = fopen(datafile, "r");
	if (fp != NULL)
	{
		while (i < max && fscanf(fp, "%d|%15[^|]|%4[^|]|%10[^\n]\n",
			&patients[i].patientNumber,
			patients[i].name,
			patients[i].phone.description,
			patients[i].phone.number) != EOF) {
			i++;
		}
		fclose(fp);
	}
	else {
		printf("Failed to open file\n");
	}
	return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
	int i = 0;
	FILE* fp = NULL;

	fp = fopen(datafile, "r");
	if (fp != NULL)
	{
		while (i < max && fscanf(fp, "%d,%d,%d,%d,%d,%d",
			&appoints[i].patientNumber,
			&appoints[i].date.year,
			&appoints[i].date.month,
			&appoints[i].date.day,
			&appoints[i].time.hour,
			&appoints[i].time.min) == 6) {
			i++;
		}
		bubbleSort(appoints, max);
		fclose(fp);
	}
	else {
		printf("Failed to open file\n");
	}
	return i;
}