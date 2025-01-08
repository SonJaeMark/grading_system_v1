#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "stringlib.h"
#include "userFileLib.h"

/// @brief Trims whitespace (spaces, tabs, newlines) from the start and end of a string.
/// @param in String to be trimmed.
void strftrim(char *in) {
    char *start = in;  // Pointer to the start of the string
    char *end;

    // Remove leading whitespace
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    // Move the trimmed string to the beginning
    if (start != in) {
        memmove(in, start, strlen(start) + 1);
    }

    // Remove trailing whitespace
    end = in + strlen(in) - 1;
    while (end >= in && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
}


/// @brief generate ID value and it starts in 240000
/// @return int id
int generateId()
{
    FILE *fptr;
    int idInitVal = 240000;
    int currIdVal;
    char buff[STR_MIN_LEN];

    fptr = fopen(ID_VAL, "r");

    if(fptr == NULL)
    {
        fptr = fopen(ID_VAL, "w");
        fprintf(fptr, "%d", idInitVal);
        currIdVal = idInitVal;
    }
    else
    {
        fgets(buff, STR_MIN_LEN, fptr);
        currIdVal = atoi(buff) + 1;

        fptr = fopen(ID_VAL, "w");
        fprintf(fptr, "%d", currIdVal);
    }

    fclose(fptr);
    return currIdVal;
}


/// @brief logged current user
/// @param currUser accepts user
/// @return 1 if success 0 if not
int logCurrentUser(char *currUser)
{
    FILE *fptr;
    int successFlag = 0;

    fptr = fopen(LOGS, "w");
    fprintf(fptr, "%s", currUser);

    fptr = fopen(LOGS, "r");
    
    if(fptr != NULL) successFlag = 1;
    fclose(fptr);
    return successFlag;
}

/// @brief get the current logged in user
/// @param currUser 
void getCurrentLogged(char *currUser)
{
    FILE *fptr;
    fptr = fopen(LOGS, "r");

    if(fptr == NULL)
    {
        strcpy(currUser, "NO USER!!!");
        fclose(fptr);
        return;
    }

    fgets(currUser, STR_MIN_LEN, fptr);
    strftrim(currUser);
    fclose(fptr);
}

void savePass(char *userPass)
{
    FILE *fptr;
    fptr = fopen(PASSWORD_FILE, "r");

    if(fptr == NULL)
    {
        fptr = fopen(PASSWORD_FILE, "w");
        fprintf(fptr, "%s\n", "id,password");
        fprintf(fptr, "%s\n", userPass);
        fclose(fptr);
        return;
    }

    fptr = fopen(PASSWORD_FILE, "a");
    fprintf(fptr, "%s\n", userPass);
    fclose(fptr);
}

void getUserPassById(char *id, char *password)
{
    FILE *fptr = fopen(PASSWORD_FILE, "r");
    if (fptr == NULL) {
        perror("Error opening password file");
        strcpy(password, ""); // Return empty password if file can't be opened
        return;
    }

    char buff[STR_MIN_LEN];
    char output[STR_MID_LEN][MAX_FILE_LINE];
    char *delimiter = ",";
    strcpy(password, ""); // Initialize password as empty

    while (fgets(buff, sizeof(buff), fptr) != NULL) {
        strftrim(buff);
        if (strstr(buff, id) != NULL) {
            strSplit(buff, output, delimiter);
            strcpy(password, output[1]); // Copy password from split result
            break;
        }
    }
    fclose(fptr);
}

int getAllUser(bool isTeacher, char *target, char usersDetails[STR_MAX_LEN][MAX_FILE_LINE])
{
    FILE *fptr;
    char buff[STR_MAX_LEN];
    int lineRead = 0;
    int currLine = 0;
    int result = 0;
    if(isTeacher)
    {
        fptr = fopen(TEACHER_FILE, "r");
    }
    else
    {
        fptr = fopen(STUDENT_FILE, "r");
    }

    if (fptr == NULL)
    {
        printf("ERROR IN OPENING FILE");
        return 0;
    }
    fgets(buff, STR_MAX_LEN, fptr);
    while (fgets(buff, STR_MAX_LEN, fptr) != NULL)
    {
        buff[strlen(buff) - 1] = '\0';
        if(strcmp(target, "") != 0 && strstr(buff, target) != NULL)
        {
            strcpy(usersDetails[lineRead], buff);
            lineRead++;
            result = lineRead;
        }
        else if(strcmp(target, "") == 0)
        {
            strcpy(usersDetails[lineRead], buff);
            lineRead++;
            result = lineRead;
        }
    }
    return result;
}

int getAllStudent(char *target, char usersDetails[STR_MAX_LEN][MAX_FILE_LINE])
{
    bool isTeacher = false;
    return getAllUser(isTeacher, target, usersDetails);
}
int getAllTeacher(char *target, char usersDetails[STR_MAX_LEN][MAX_FILE_LINE])
{
    bool isTeacher = true;
    return getAllUser(isTeacher, target, usersDetails);
}

int getUserById(bool isTeacher, char *id, char *userDetails)
{
    char usersDetails[1024][1024];
    int result = getAllUser(isTeacher, id, usersDetails);

    strcpy(userDetails, usersDetails[0]);
    return result;
}

int getStudentById(char *id, char *userDetails)
{
    bool isTeacher = false;
    getUserById(isTeacher, id, userDetails);
}

int getTeacherById(char *id, char *userDetails)
{
    bool isTeacher = true;
    getUserById(isTeacher, id, userDetails);
}

int saveUsers(bool isTeacher, char usersDetails[STR_MAX_LEN][MAX_FILE_LINE])
{
    FILE *fptr;
    int i;

    if(isTeacher)
    {
        fptr = fopen(TEACHER_FILE, "r"); 
    }
    else
    {
        fptr = fopen(STUDENT_FILE, "r");
    }

    if(fptr == NULL && isTeacher){
        fptr = fopen(TEACHER_FILE, "w");
        fprintf(fptr, "id,first_name,last_name,username,date_of_birth,student_list\n"); // TO DO chage to correct file header 

        while (strcmp(usersDetails[i], ""))
        {
            fprintf(fptr, "%s\n", usersDetails[i]);
            i++;
        }
        fclose(fptr);
        return i;
    }
    else if(fptr == NULL && !isTeacher)
    {
        fptr = fopen(STUDENT_FILE, "w");
        fprintf(fptr, "id,first_name,last_name,username,section,date_of_birth,grades(MATH,SCI,ENG,FIL,HISTORY,PE,AVE\n)"); // TO DO chage to correct file header 

        while (strcmp(usersDetails[i], ""))
        {
            fprintf(fptr, "%s\n", usersDetails[i]);
            i++;
        }
        fclose(fptr);
        return i;
    }
    else if(isTeacher)
    {
        fptr = fopen(TEACHER_FILE, "a");
        while (strcmp(usersDetails[i], "") != 0)
        {
            fprintf(fptr, "%s\n", usersDetails[i]);
            i++;
        }
    }
    else
    {
        fptr = fopen(STUDENT_FILE, "a");
        while (strcmp(usersDetails[i], "") != 0)
        {
            fprintf(fptr, "%s\n", usersDetails[i]);
            i++;
        }
    }
    fclose(fptr);
    return i;
}

int saveUser(bool isTeacher, char *userDetails)
{
    char usersDetails[STR_MAX_LEN][MAX_FILE_LINE];

    strcpy(usersDetails[0], userDetails);
    strcpy(usersDetails[1], "");

    return saveUsers(isTeacher, usersDetails);
}

int saveStudents(char studentDetails[STR_MAX_LEN][MAX_FILE_LINE])
{
    bool isTeacher = false;
    return saveUsers(isTeacher, studentDetails);
}

int saveStudent(char *studentDetails)
{
    bool isTeacher = false;
    return saveUser(isTeacher, studentDetails);
}

int saveTeachers(char teacherDetails[STR_MAX_LEN][MAX_FILE_LINE])
{
    bool isTeacher = true;
    return saveUsers(isTeacher, teacherDetails);
}

int saveTeacher(char *teacherDetails)
{
    bool isTeacher = true;
    return saveUser(isTeacher, teacherDetails);
}

int editUser(bool isTeacher, char *id, char *usersDetails)
{
    FILE *fptr;
    char buff[STR_MAX_LEN];
    int successFlag = 0;
    int i = 0;
    char buffArr[STR_MAX_LEN][MAX_FILE_LINE];


    if(isTeacher)
    {
        fptr = fopen(TEACHER_FILE, "r");
    }
    else
    {
        fptr = fopen(STUDENT_FILE, "r");
    }

    if(fptr == NULL)
    {
        printf("FILE NOT FOUND!");
        return 0;
    }


    while (fgets(buff, STR_MAX_LEN, fptr) != NULL)
    {
        buff[strlen(buff) -1] = '\0';
        if(strstr(buff, id) != NULL)
        {
            strcpy(buffArr[i], usersDetails);
            successFlag = 1;
        }
        else
        {
            strcpy(buffArr[i], buff);
        }
        i++;
    }
    strcpy(buffArr[i], "");
    i = 0;

    if(isTeacher)
    {
        fptr = fopen(TEACHER_FILE, "w");
    }
    else
    {
        fptr = fopen(STUDENT_FILE, "w");
    }

    while (strcmp(buffArr[i], "") != 0)
    {
        fprintf(fptr, "%s\n", buffArr[i]);
        i++;
    }
    

    fclose(fptr);
    return successFlag;
}

int editStudent(char *id, char *usersDetails)
{
    bool isTeacher = false;
    return editUser(isTeacher, id, usersDetails);
}

int editTeacher(char *id, char *usersDetails)
{
    bool isTeacher = true;
    return editUser(isTeacher, id, usersDetails);
}