#pragma once

#include "userlib.h"


int getAllMyStudents(char *id);
int getAllMyStudentById(char *id, char studsInfo[STR_MID_LEN][MAX_FILE_LINE]);
void giveGrades(char *id);
int addStudentToClass(char *id);
int removeStudentToClass(char *id);
void viewGradesOfStudentById(char *id);

float getAve(float *gradesArray);
float roundToDecimal(float num, int decimalPlaces);