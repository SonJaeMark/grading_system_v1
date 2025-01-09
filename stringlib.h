#pragma once

#define STR_MIN_LEN 128
#define STR_MID_LEN 256
#define STR_MAX_LEN 512

#define MAX_FILE_LINE 512

int strSplit(char *input, char output[STR_MID_LEN][MAX_FILE_LINE], char *delimiter);
void strToCsvFormat(char strArr[STR_MID_LEN][MAX_FILE_LINE], char *delimiter, char *strInCsvFormat);