#include <string.h>
#include "stringlib.h"



/// @brief split string in given delimiter e.g. "Hello,world,hi,univeres" -> "Hello", "world", "hi", "univeres"
/// @param input char array
/// @param output array of char array 
/// @param delimiter char array that will mark as division
/// @return number of splitted substring
int strSplit(char *input, char output[STR_MID_LEN][MAX_FILE_LINE], char *delimiter)
{
    int i = 0;
    char *str = strtok(input, delimiter);
  
    while (str != NULL) {
        strcpy(output[i], str);
        str = strtok(NULL, delimiter);
        i++;
    }
    return i;
}


/// @brief convert array of string into one string e.g. "Hello", "world", "hi", "univeres" -> "Hello,world,hi,univeres" 
/// @param strArr string array to be converted to one string
/// @param delimiter separator of each string e.g. delimiter is ",": "Hello", "world", "hi", "univeres" -> "Hello,world,hi,univeres" 
/// @param strInCsvFormat output string 
/// @param len number of strings that will be joined together
void strToCsvFormat(char strArr[STR_MIN_LEN][STR_MID_LEN], char *delimiter, char *strInCsvFormat){

    int i = 0;
    while (strcmp(strArr[i], "") != 0)
    {
        strcat(strInCsvFormat, strArr[i]);
        strcat(strInCsvFormat, delimiter);
        i++;  
    }
    strInCsvFormat[strlen(strInCsvFormat) -1] = '\0';
}