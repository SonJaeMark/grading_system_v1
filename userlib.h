#pragma once

#include "stringlib.h"

typedef struct Grades
{
    float MATH;
    float SCI;
    float ENG;
    float FIL;
    float HISTORY;
    float PE;
    float AVE;
} Grades;

typedef struct Date
{
    int MM;
    int DD;
    int YYYY;
} Date;

typedef struct Student
{
    int id;
    char fname[STR_MIN_LEN];
    char lname[STR_MIN_LEN];
    char userName[STR_MIN_LEN];
    char password[STR_MIN_LEN];
    char section[STR_MIN_LEN];
    struct Date dateOfBirth;
    struct Grades grades;
} Student;

typedef struct Teacher
{
    int id;
    char fname[STR_MIN_LEN];
    char lname[STR_MIN_LEN];
    char userName[STR_MIN_LEN];
    char password[STR_MIN_LEN];
    struct Date dateOfBirth;
    struct StudentList *studentsList;
} Teacher;

typedef struct Logs { // to remove
    char name[STR_MIN_LEN];
    int id;
} Logs;

typedef struct StudentList
{
    int id;
    char lname[STR_MIN_LEN];
}StudentList;

int registerUser();
int registerTeacher(Teacher teacher, int id, char strArr[STR_MIN_LEN][STR_MID_LEN], char *strInCsvFormat, char *idStr);
int registerStudent(Student student, int id, char strArr[STR_MIN_LEN][STR_MID_LEN], char *strInCsvFormat, char *idStr);

int loginUser();
void logout();