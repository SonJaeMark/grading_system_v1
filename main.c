#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "userFileLib.h"
#include "userlib.h"
#include "teacherlib.h"
#include "studentlib.h"

int main ()
{
    char *id = "240000";
    char ans[STR_MIN_LEN];


    while (1)
    {
        printf("Select action [0]getAllMyStudents  || [1]giveGrades (type 'exit' or 'e' to quit): ");
        fgets(ans, STR_MIN_LEN, stdin);
        strftrim(ans);

        if(strcmp("0", ans) == 0) getAllMyStudents(id);
        else if(strcmp("1", ans) == 0) giveGrades(id);
        else if(strcmp("exit", ans) == 0 || strcmp("e", ans) == 0) break;
        else printf("Give correct reponse\n");

    }
    
    
    return 0;
}



