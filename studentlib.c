#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "stringlib.h"
#include "userFileLib.h"

#define ID_WIDTH 12
#define NAME_WIDTH 33
#define GRADE_WIDTH 7
#define TOTAL_COLUMNS 7

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

void printGrades(char studentDetails[STR_MIN_LEN][MAX_FILE_LINE]) {
    // Print ID
    printf("%s", studentDetails[0]);
    printSpaces(ID_WIDTH - strlen(studentDetails[0]));
    printf("| ");

    // Print Last Name, First Name
    printf("%s, %s", studentDetails[2], studentDetails[1]);
    printSpaces(NAME_WIDTH - (strlen(studentDetails[2]) + strlen(studentDetails[1]) + 3)); // +2 for "|, "

    // Print Grades
    for (int i = 6; i <= 12; i++) 
    {
        printf("| ");
        printf("%s", studentDetails[i]);
        printSpaces(GRADE_WIDTH - (strlen(studentDetails[i]) + 1));
    }
    printf("\n");

    // Print separator
    printf("------------+---------------------------------");
    for (int i = 0; i < TOTAL_COLUMNS; i++) {
        printf("+-------");
    }
    printf("\n");
}


void headerGrades(char *header, int numberOfStud)
{
    // title
    if(numberOfStud > 0) printf("%s: %d\n", header, numberOfStud);
    else printf("%s\n", header);

    // header
    printf("\nid          | last_name, first_name           | MATH  | SCI   | ENG   | FIL   | HIS   | PE    | AVE\n");
    // separator
    printf("------------+---------------------------------");
    for (int i = 0; i < TOTAL_COLUMNS; i++) {
        printf("+-------");
    }
    printf("\n");
}

void viewMyGrades(char *id)
{
    char studentDetails[STR_MID_LEN]; // student details 
    char output[STR_MID_LEN][MAX_FILE_LINE]; // Temporary buffer for student info 
    char *delim = ",";
    char header[STR_MIN_LEN];

    strcpy(header, id);
    getStudentById(id, studentDetails);
    strSplit(studentDetails, output, delim);
    headerGrades(header, 0);
    printGrades(output);
    printf("\n");


}