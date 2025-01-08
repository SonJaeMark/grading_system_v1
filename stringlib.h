#pragma once

#define STR_MIN_LEN 256
#define STR_MID_LEN 512
#define STR_MAX_LEN 1024

#define MAX_FILE_LINE 1024
#define MID_FILE_LINE 512
#define MIN_FILE_LINE 256

int strSplit(char *input, char *output[MAX_FILE_LINE], char *delimiter);
void strToCsvFormat(char strArr[STR_MIN_LEN][STR_MID_LEN], char *delimiter, char *strInCsvFormat);