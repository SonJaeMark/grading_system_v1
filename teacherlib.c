
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "userlib.h"
#include "userFileLib.h"
#include "stringlib.h"
#include "studentlib.h"
#include "teacherlib.h"

#define STUDENT_ID_START_INDEX 5
#define MAX_STUDENTS 10

#define NUM_GRADES 6  // Define yung number ng subjects

int getAllMyStudents(char *id) 
{
    char studGrades[STR_MID_LEN][MAX_FILE_LINE];
    char studsInfo[STR_MID_LEN][MAX_FILE_LINE];
    char *delim = ",";
    char *header = "STUDENT LIST";
    int studentsCount = 0;

    studentsCount = getAllMyStudentById(id, studsInfo);
    headerGrades(header, studentsCount);
    for (int i = 0; i < studentsCount; i++) {
        strSplit(studsInfo[i], studGrades, delim);
        printGrades(studGrades);
    }
    printf("\n");

    return 1;
}

void giveGrades(char *id)
{
    char ans[STR_MIN_LEN];
    char studsInfo[STR_MID_LEN][MAX_FILE_LINE];
    char studInfoSubStr[STR_MID_LEN][MAX_FILE_LINE];
    char studEditedInfo[STR_MIN_LEN];
    int studCount = getAllMyStudentById(id, studsInfo);
    char *delim = ",";
    char idHolder[STR_MIN_LEN];
    int isStudExistInTeacher = 0;
    int editSuccess = 0;

    float grades[7];
    char *strBuff;

    if (studCount <= 0) {
        return;
    }

    printf("Please enter the ID of the student you want to give grades (type 'exit' or 'e' to quit): ");
    while (1)
    {
        fgets(ans, STR_MIN_LEN, stdin);
        strftrim(ans);

        strcpy(idHolder, ans); // the id to use ans repeatedly

        if(strcmp("exit", ans) == 0 || strcmp("e", ans) == 0) break;

        for (int i = 0; i < studCount; i++)
        {
            strSplit(studsInfo[i], studInfoSubStr, delim);
            if(strcmp(ans, studInfoSubStr[0]) == 0)
            {
                printf("Enter grade for Math: "); // ask grade
                fgets(ans, STR_MIN_LEN, stdin); // get grade
                strftrim(ans);
                grades[0] = roundToDecimal(strtof(ans, &strBuff), 2); // convert ans to float and store in grades array for acomputation of ave

                strcpy(studInfoSubStr[6], ans); // copy to studInfoSubStr

                printf("Enter grade for Science: "); // ask grade
                fgets(ans, STR_MIN_LEN, stdin); // get grade
                strftrim(ans); // trims for spaces, tabs, newlines before and after ans
                grades[1] = roundToDecimal(strtof(ans, &strBuff), 2);

                strcpy(studInfoSubStr[7], ans); // copy to studInfoSubStr

                printf("Enter grade for English: "); // ask grade
                fgets(ans, STR_MIN_LEN, stdin); // get grade
                strftrim(ans); // trims for spaces, tabs, newlines before and after ans
                grades[2] = roundToDecimal(strtof(ans, &strBuff), 2);

                strcpy(studInfoSubStr[8], ans); // copy to studInfoSubStr

                printf("Enter grade for Filipino: "); // ask grade
                fgets(ans, STR_MIN_LEN, stdin); // get grade
                strftrim(ans); // trims for spaces, tabs, newlines before and after ans
                grades[3] = roundToDecimal(strtof(ans, &strBuff), 2);

                strcpy(studInfoSubStr[9], ans); // copy to studInfoSubStr

                printf("Enter grade for History: "); // ask grade
                fgets(ans, STR_MIN_LEN, stdin); // get grade
                strftrim(ans); // trims for spaces, tabs, newlines before and after ans
                grades[4] = roundToDecimal(strtof(ans, &strBuff), 2);

                strcpy(studInfoSubStr[10], ans); // copy to studInfoSubStr

                printf("Enter grade for P.E.: "); // ask grade
                fgets(ans, STR_MIN_LEN, stdin); // get grade
                strftrim(ans); // trims for spaces, tabs, newlines before and after ans
                grades[5] = roundToDecimal(strtof(ans, &strBuff), 2);

                strcpy(studInfoSubStr[11], ans); // copy to studInfoSubStr

                snprintf(studInfoSubStr[12], sizeof(studInfoSubStr[12]), "%.3f", getAve(grades));

                strcpy(studInfoSubStr[13], ""); // copy to studInfoSubStr empty string in order use strToCsvFormat
                
                strToCsvFormat(studInfoSubStr, delim, studEditedInfo); // convert to csv format

                while (1)
                {
                    printf("[s]Save || [c]Cancel: "); // ask for confirmation
                    fgets(ans, STR_MIN_LEN, stdin); // get confirmation
                    strftrim(ans); // trims for spaces, tabs, newlines before and after ans

                    if(strcmp("s", ans) == 0)
                    {
                        editSuccess = editStudent(studInfoSubStr[0], studEditedInfo);
                        break;
                    }
                    else if(strcmp("c", ans) == 0) break;
                }
                isStudExistInTeacher = 1;
            }
        }

        if(editSuccess == 1) printf("Edit Success!!!\n");
        if(isStudExistInTeacher == 0) printf("Student %s does not exist or is not your student list. Please input a valid ID.\n", idHolder);
        printf("Please enter the ID of the student you want to give grades (type 'exit' or 'e' to quit): ");
    }
}

int addStudentToClass(char *id)
{
    char studentDetails[STR_MAX_LEN];
    char teacherDetails[STR_MAX_LEN];
    char editedTeacherDetails[STR_MAX_LEN];
    char teacherDetailsSubStr[STR_MID_LEN][MAX_FILE_LINE];
    char *delim = ",";
    char ans[STR_MIN_LEN];
    int successFlag = 0;
    int teacherDetailsSubStrLen = 0;

    while (1)
    {
        getTeacherById(id, teacherDetails);
        teacherDetailsSubStrLen = strSplit(teacherDetails, teacherDetailsSubStr, delim);

        // minus 5 because in substr index 4 is dob and index 5 to index 14 is where the id's of students found
        if((teacherDetailsSubStrLen - 5) > MAX_STUDENTS) 
        {
            printf("Max allowable number of student\n");
            return 0;
        }

        printf("Enter id of the student you want add to your class (type 'exit' or 'e' to quit): ");
        fgets(ans, STR_MIN_LEN, stdin);
        strftrim(ans); 

        if(strcmp("exit", ans) == 0 || strcmp("e", ans) == 0) break;

        if(getStudentById(ans, studentDetails) == 1)
        {
            strcpy(teacherDetailsSubStr[teacherDetailsSubStrLen], ans);
            strcpy(teacherDetailsSubStr[teacherDetailsSubStrLen + 1], "");
            strToCsvFormat(teacherDetailsSubStr, delim, editedTeacherDetails); 

            while (1)
            {
                printf("[s]Save || [c]Cancel: ");
                fgets(ans, STR_MIN_LEN, stdin);
                strftrim(ans);

                if(strcmp("s", ans) == 0)
                {
                    successFlag = editTeacher(id, editedTeacherDetails);
                    break;
                }
                else if(strcmp("c", ans) == 0) break;
            }
        }
        else
        {
            printf("Id %s not found, please enter correct id number!\n");
        }
        if(successFlag == 1) printf("Save success!\n");
    }
    
}

int removeStudentToClass(char *id)
{

}

void viewGradesOfStudentById(char *id)
{

}

// erin
float getAve(float *gradesArray) {
    float totalGrades = 0.0;

    // Calculate total grades using the arrays
    for (int i = 0; i < NUM_GRADES; i++) {
        totalGrades += gradesArray[i];
    }

    // Calculate average
    float ave = totalGrades / NUM_GRADES;
    return ave;
}

int getAllMyStudentById(char *id, char studsInfo[STR_MID_LEN][MAX_FILE_LINE]) {
    char *delim = ",";
    char userDetails[STR_MAX_LEN];
    char studIds[STR_MID_LEN][MAX_FILE_LINE];
    int teacherDetailsSubStrLen = 0;
    int studentCount = 0;

    // Validate input parameters
    if (id == NULL || studsInfo == NULL) {
        printf("Error: Invalid input.\n");
        return -1; // Return error code for invalid input
    }

    // Get teacher details by ID
    if (getTeacherById(id, userDetails) != 1) {
        printf("Error: Teacher with ID %s not found.\n", id);
        return 0;
    }

    // Split teacher details into substrings to get student IDs
    teacherDetailsSubStrLen = strSplit(userDetails, studIds, delim);
    if (teacherDetailsSubStrLen <= STUDENT_ID_START_INDEX) {
        printf("No students found for teacher ID %s.\n", id);
        return 0;
    }

    // Retrieve student details and store in studsInfo
    for (int i = STUDENT_ID_START_INDEX; i < teacherDetailsSubStrLen; i++) {
        if (getStudentById(studIds[i], studsInfo[studentCount]) != 1) {
            printf("Warning: Student with ID %s not found.\n", studIds[i]);
            continue;
        }
        studentCount++;
    }
    

    return studentCount; // Return the number of students retrieved
}

float roundToDecimal(float num, int decimalPlaces) 
{
    float factor = powf(10, decimalPlaces);
    return roundf(num * factor) / factor;
}