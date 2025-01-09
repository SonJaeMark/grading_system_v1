#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "stringlib.h"
#include "userFileLib.h"
#include "userlib.h"

int registerUser() {
    char ans[100];
    Student student;
    Teacher teacher;
    char strArr[STR_MID_LEN][MAX_FILE_LINE]; 
    char strInCsvFormat[STR_MAX_LEN];
    int id = generateId();
    int successFlag = 0;
    char idStr[20]; // Allocated buffer for ID string

    while(1) 
    {
        printf("Register as [t] Teacher || [s] Student: ");
        fgets(ans, sizeof(ans), stdin);
        strftrim(ans); // Remove newline

        if(strcmp("t", ans) == 0) // TEACHER
        { 
            if(registerTeacher(teacher, id, strArr, strInCsvFormat, idStr) == 1)
            {
                successFlag = 1;
                 break;
            }
            printf("Registration unsuccessful!\n");
        } 
        else if(strcmp("s", ans) == 0) // STUDENT
        { 
            if(registerStudent(student, id, strArr, strInCsvFormat, idStr) == 1)
            {
                successFlag = 1;
                 break;
            }
            printf("Registration unsuccessful!\n");
        } 
        else 
        {
            printf("Invalid choice. Please enter 't' for Teacher or 's' for Student.\n");
        }
    }

    return successFlag;
}

int registerTeacher(Teacher teacher, int id, char strArr[STR_MID_LEN][MAX_FILE_LINE], char *strInCsvFormat, char *idStr)
{
    char dobStr[20];
    char retype[STR_MIN_LEN];
    char *delimiter = ","; 
    int successFlag = 0;
    teacher.id = id;
    char loggedUser[20];

    printf("Enter teacher's first name: ");
    fgets(teacher.fname, STR_MIN_LEN, stdin);
    strftrim(teacher.fname);

    printf("Enter teacher's last name: ");
    fgets(teacher.lname, STR_MIN_LEN, stdin);
    strftrim(teacher.lname);

    printf("Enter teacher's username: ");
    fgets(teacher.userName, STR_MIN_LEN, stdin);
    strftrim(teacher.userName);

    printf("Enter teacher's date of birth (MM DD YYYY): ");
    scanf("%d %d %d", &teacher.dateOfBirth.MM, &teacher.dateOfBirth.DD, &teacher.dateOfBirth.YYYY);
    getchar(); // Clear the buffer

    while (1) 
    {
        printf("Enter teacher's password: ");
        fgets(teacher.password, STR_MIN_LEN, stdin);
        strftrim(teacher.password);

        printf("Re-enter teacher's password: ");
        fgets(retype, STR_MIN_LEN, stdin);
        strftrim(retype);

            if (strcmp(teacher.password, retype) == 0) {
                break;
            }
        printf("Passwords do not match. Please try again.\n");
    }

    snprintf(idStr, sizeof(idStr), "%d", teacher.id);
    snprintf(dobStr, sizeof(dobStr), "%d/%d/%d", teacher.dateOfBirth.MM, teacher.dateOfBirth.DD, teacher.dateOfBirth.YYYY);

    strcpy(strArr[0], idStr);
    strcpy(strArr[1], teacher.fname);
    strcpy(strArr[2], teacher.lname);
    strcpy(strArr[3], teacher.userName);
    strcpy(strArr[4], dobStr);
    strcpy(strArr[5], "");

    strToCsvFormat(strArr, delimiter, strInCsvFormat);
    successFlag = saveTeacher(strInCsvFormat);

    if(successFlag == 1)
    {
        strcpy(loggedUser, idStr);
        strcat(loggedUser, ",");
        strcat(loggedUser, teacher.password);
        savePass(loggedUser);

        // strcpy(loggedUser, idStr);
        // strcat(loggedUser, "-");
        // strcat(loggedUser, teacher.userName);
        // logCurrentUser(loggedUser);

        printf("Your ID is: %d\n", teacher.id);
    }

    return successFlag;
}

int registerStudent(Student student, int id, char strArr[STR_MID_LEN][MAX_FILE_LINE], char *strInCsvFormat, char *idStr)
{
    char dobStr[20];
    char grades[STR_MAX_LEN];
    char retype[STR_MIN_LEN];
    char *delimiter = ","; 
    student.id = id;
    int successFlag = 0;
    char loggedUser[20];

    printf("Enter student's first name: ");
    fgets(student.fname, STR_MIN_LEN, stdin);
    strftrim(student.fname);

    printf("Enter student's last name: ");
    fgets(student.lname, STR_MIN_LEN, stdin);
    strftrim(student.lname);

    printf("Enter student's username: ");
    fgets(student.userName, STR_MIN_LEN, stdin);
    strftrim(student.userName);

    printf("Enter section: ");
    fgets(student.section, STR_MIN_LEN, stdin);
    strftrim(student.section);

    printf("Enter student's date of birth (MM DD YYYY): ");
    scanf("%d %d %d", &student.dateOfBirth.MM, &student.dateOfBirth.DD, &student.dateOfBirth.YYYY);
    getchar(); // Clear the buffer

    while (1) {
        printf("Enter student's password: ");
        fgets(student.password, STR_MIN_LEN, stdin);
        strftrim(student.password);

        printf("Re-enter student's password: ");
        fgets(retype, STR_MIN_LEN, stdin);
        strftrim(retype);

        if (strcmp(student.password, retype) == 0) {
            break;
        }
        printf("Passwords do not match. Please try again.\n");
    }

    student.grades.MATH = 0;
    student.grades.SCI = 0;
    student.grades.ENG = 0;
    student.grades.FIL = 0;
    student.grades.HISTORY = 0;
    student.grades.PE = 0;
    student.grades.AVE = 0;

    snprintf(idStr, sizeof(idStr), "%d", student.id);
    snprintf(dobStr, sizeof(dobStr), "%d/%d/%d", student.dateOfBirth.MM, student.dateOfBirth.DD, student.dateOfBirth.YYYY);
    snprintf(grades, sizeof(grades), "%f,%f,%f,%f,%f,%f,%f", 
        student.grades.MATH, student.grades.SCI, student.grades.ENG, 
        student.grades.FIL, student.grades.HISTORY, student.grades.PE,
        student.grades.AVE
    );

    strcpy(strArr[0], idStr);
    strcpy(strArr[1], student.fname);
    strcpy(strArr[2], student.lname);
    strcpy(strArr[3], student.userName);
    strcpy(strArr[4], dobStr);
    strcpy(strArr[5], student.section);
    strcpy(strArr[6], grades);
    strcpy(strArr[7], "");

    strToCsvFormat(strArr, delimiter, strInCsvFormat);
    successFlag = saveStudent(strInCsvFormat);

    if(successFlag == 1)
    {
        strcpy(loggedUser, idStr);
        strcat(loggedUser, ",");
        strcat(loggedUser, student.password);
        savePass(loggedUser);

        // strcpy(loggedUser, idStr);
        // strcat(loggedUser, "-");
        // strcat(loggedUser, student.userName);
        // logCurrentUser(loggedUser);

        printf("Your ID is: %d\n", student.id);
    }

    return successFlag;
}

/// @brief login user 
/// @return 1 if teacher 2 if student 0 if failed
int loginUser(char *id)
{
    // char id[STR_MIN_LEN];
    char password[STR_MIN_LEN];
    char typedPass[STR_MIN_LEN];
    char userDetails[STR_MIN_LEN];
    char userDetailsOutput[STR_MID_LEN][MAX_FILE_LINE];
    char *delim = ",";
    char userLogs[STR_MIN_LEN];
    int successFlag = 0;

    while (1)
    {
        printf("Enter ID: ");
        fgets(id, STR_MIN_LEN, stdin);
        strftrim(id);

        printf("Enter password: ");
        fgets(typedPass, STR_MIN_LEN, stdin);
        strftrim(typedPass);

        getUserPassById(id, password);
        
        if(strcmp(password, typedPass) == 0) break;
        printf("Password or id is incorrect!\n\n");
    }

    if(getTeacherById(id, userDetails) == 1) successFlag = 1;
    if(getStudentById(id, userDetails) == 1) successFlag = 2;
    if(successFlag > 0)
    {
        strSplit(userDetails, userDetailsOutput, delim);
        strcpy(userLogs, userDetailsOutput[0]);
        strcat(userLogs, "-");
        strcat(userLogs, userDetailsOutput[3]);

        logCurrentUser(userLogs);
        getCurrentLogged(userLogs);
        printf("Welcome %s\n", userLogs);
        successFlag = 1;
    }

    return successFlag; 
}

void logout()
{
    char userLogs[STR_MIN_LEN];
    char ans[20];
    getCurrentLogged(userLogs);

    while (1)
    {
        printf("Do you want to logout %s?\n[y]Yes || [n]No: ", userLogs);
        fgets(ans, sizeof(ans), stdin);
        strftrim(ans); // Remove newline

        if(strcmp("y", ans) == 0)
        {
            strcpy(userLogs, "");
            logCurrentUser(userLogs);
            return;
        }
        else if(strcmp("n", ans) == 0)
        {
            return;
        }
        else
        {
        printf("Please submit correct response!\n");
        }
    }
    

}
