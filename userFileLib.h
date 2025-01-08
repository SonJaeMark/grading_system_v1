#pragma once

#include "stringlib.h"

#define PASSWORD_FILE "password_file.txt"
#define ID_VAL "id_val.txt"
#define LOGS "curr_user_logs.txt"
#define TEACHER_FILE "teacher_file.txt"
#define STUDENT_FILE "student_file.txt"

void strftrim(char *in);

int generateId();

int logCurrentUser(char *currUser);
void getCurrentLogged(char *currUser);

void savePass(char *userPass);
void getUserPassById(char *id, char *password);

int getAllUser(bool isTeacher, char *target, char usersDetails[STR_MAX_LEN][MAX_FILE_LINE]);
int getAllStudent(char *target, char usersDetails[STR_MAX_LEN][MAX_FILE_LINE]);
int getAllTeacher(char *target, char usersDetails[STR_MAX_LEN][MAX_FILE_LINE]);

int getUserById(bool isTeacher, char *id, char *userDetails);
int getStudentById(char *id, char *userDetails);
int getTeacherById(char *id, char *userDetails);

int saveUsers(bool isTeacher, char usersDetails[STR_MAX_LEN][MAX_FILE_LINE]);
int saveUser(bool isTeacher, char *userDetails);

int saveStudents(char studentDetails[STR_MAX_LEN][MAX_FILE_LINE]);
int saveStudent(char *studentDetails);
int saveTeachers(char teacherDetails[STR_MAX_LEN][MAX_FILE_LINE]);
int saveTeacher(char *teacherDetails);

int editUser(bool isTeacher, char *id, char *usersDetails);
int editStudent(char *id, char *usersDetails);
int editTeacher(char *id, char *usersDetails);

