#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "userFileLib.h"
#include "userlib.h"

void generateIdTest();
void logCurrentUserTest();
void getCurrentLoggedTest();
void savePassTest();
void getUserPassByIdTest();
void getAllUserTest();
void getAllStudentTest();
void getAllTeacherTest();
void getUserByIdTest();
void getStudentByIdTest();
void getTeacherByIdTest();
void saveUsersTest();
void saveUserTest();
void saveStudentsTest(); 
void saveStudentTest(); 
void saveTeachersTest(); 
void saveTeacherTest(); 
void registerUserPrototype();
void strToCsvFormatTest();
void editUserTest();
void editStudentTest(); 
void editTeacherTest();

int main ()
{

    // generateIdTest(); // goods no issue
    // logCurrentUserTest(); // goods no issue
    // getCurrentLoggedTest(); // goods no issue
    // savePassTest(); // goods no issue
    // getUserPassByIdTest(); // goods no issue
    // getAllUserTest(); // goods no issue
    // getAllStudentTest(); // goods no issue
    // getAllTeacherTest(); // goods no issue
    // getUserByIdTest(); // goods no issue
    // getStudentByIdTest(); // goods no issue
    // getTeacherByIdTest(); // goods no issue
    // saveUsersTest(); // goods no issue
    // saveUserTest(); // goods no issue
    // saveStudentsTest(); // goods no issue
    // saveStudentTest(); // goods no issue
    // saveTeachersTest(); // goods no issue
    // saveTeacherTest(); // goods no issue
    // strToCsvFormatTest(); // goods no issue
    // registerUserPrototype(); // goods no issue
    // editUserTest(); // goods no issue
    // editStudentTest(); // goods no issue
    // editTeacherTest(); // goods no issue

    registerUser(); 
    // loginUser() == 1 ? printf("Welcome user\n") : printf("Please log in\n");

    return 0;
}

void generateIdTest()
{
    printf("%d\n", generateId());
    printf("%d\n", generateId());
    printf("%d\n", generateId());
    printf("%d\n", generateId());
    printf("%d\n", generateId());
    printf("%d\n", generateId());
    printf("%d\n", generateId());
    printf("%d\n", generateId());
    printf("%d\n", generateId());
    printf("%d\n", generateId());
    
    remove(ID_VAL);
}

void logCurrentUserTest()
{
    char *currUser = "240001";
    logCurrentUser(currUser);
}

void getCurrentLoggedTest()
{
    char currUser[STR_MIN_LEN];
    getCurrentLogged(currUser);

    printf("%s\n", currUser);
}

void savePassTest()
{
    char *userDetails = "240000,test";
    savePass(userDetails);
}

void getUserPassByIdTest()
{
    char *id = "240000";
    char password[STR_MIN_LEN];
    getUserPassById(id, password);

    printf("%s", password);
}

void getAllUserTest()
{
    bool isTeacher = false; 
    char *target = ""; 
    char usersDetails[STR_MAX_LEN][MAX_FILE_LINE];

    int data = getAllUser(isTeacher, target, usersDetails);

    for(int i = 0; i < data; i++)
    {
        printf("%s\n", usersDetails[i]);
    }
}

void getAllStudentTest()
{
    char *target = ""; 
    char usersDetails[STR_MAX_LEN][MAX_FILE_LINE];

    int data = getAllStudent(target, usersDetails);

    printf("Student test...\n");
    for(int i = 0; i < data; i++)
    {
        printf("%s\n", usersDetails[i]);
    }
    printf("\n\n\n");
}

void getAllTeacherTest()
{
    char *target = ""; 
    char usersDetails[STR_MAX_LEN][MAX_FILE_LINE];

    int data = getAllTeacher(target, usersDetails);

    printf("Teacher test...\n");
    for(int i = 0; i < data; i++)
    {
        printf("%s\n", usersDetails[i]);
    }
    printf("\n\n\n");
}

void getUserByIdTest()
{
    bool isTeacher = true; 
    char *id = "240055"; 
    char userDetails[STR_MAX_LEN];
    getUserById(isTeacher, id, userDetails);

    printf("%s", userDetails);
}

void getStudentByIdTest()
{
    char *id = "240067"; 
    char userDetails[STR_MAX_LEN];

    getStudentById(id, userDetails);
    printf("Student test...\n");
    printf("%s\n", userDetails);
    printf("%c\n", userDetails[0]);
    printf("\n\n\n");
}

void getTeacherByIdTest()
{
    char *id = "240032"; 
    char userDetails[STR_MAX_LEN];

    getTeacherById(id, userDetails);

    printf("Teacher test...\n");
    printf("%s\n", userDetails);
    printf("\n\n\n");
}

void saveUsersTest()
{
    bool isTeacher = false; 
    char usersDetails[STR_MAX_LEN][MAX_FILE_LINE] = {
        "240021,Nils,Mathevet,nmatheveth@disqus.com,27 Cody Point", 
        "240022,Nerte,Castelijn,ncastelijni@taobao.com,754 Corben Hill",
        "240023,Stan,Liptrod,sliptrodj@icio.us,5952 Sommers Avenue",
        ""
    };

    saveUsers(isTeacher, usersDetails);
}

void saveUserTest()
{
    bool isTeacher = true;
    char *userDetails = "240041,Nils,Mathevet,nmatheveth@disqus.com,27 Cody Point";

    saveUser(isTeacher, userDetails) == 1 ? printf("Save success!!!") : printf("Save unsuccessful!!!");
}

void saveStudentsTest() 
{
    char studentDetails[STR_MAX_LEN][MAX_FILE_LINE] = {
        "240045,Melodie,Isakson,misakson1@wisc.edu,4379 Springview Alley",
        "240046,Olly,Croson,ocroson2@123-reg.co.uk,06191 Canary Court",
        "240047,Tiffy,Spadollini,tspadollini3@mysql.com,395 Delaware Hill",
        "240048,Dyann,Pabelik,dpabelik4@cornell.edu,796 Debs Parkway",
        "240049,Randene,Hubbucke,rhubbucke5@newsvine.com,335 Darwin Lane",
        "240050,Greggory,Bartolomivis,gbartolomivis6@arstechnica.com,51934 Merry Junction",
        ""
    };
    int savedData = saveStudents(studentDetails);
    savedData > 0 ? printf("Save success %d students!!!\n", savedData) : printf("Save unsuccessful!!!\n");

}
void saveStudentTest() 
{
    char *studentDetails = "240051,Barnard,Joiris,bjoirisa@mozilla.org,9380 Lyons Lane";
    saveStudent(studentDetails) == 1 ? printf("Save success!!!\n") : printf("Save unsuccessful!!!\n");
}
void saveTeachersTest()
{
    char teacherDetails[STR_MAX_LEN][MAX_FILE_LINE] = {
        "240052,Clari,Chadwick,cchadwickb@icio.us,95648 Continental Street",
        "240053,Joby,Ubach,jubachc@timesonline.co.uk,8557 7th Place",
        "240054,Kasey,Sneesbie,ksneesbied@mapquest.com,0088 Forest Crossing",
        "240055,Donn,Sheward,dshewarde@wordpress.com,297 Dapin Lane",
        "240056,Rossie,McGarahan,rmcgarahanf@flickr.com,614 Rusk Alley",
        "240057,Matilde,Chimenti,mchimentig@nationalgeographic.com,091 Del Sol Road",
        ""
    };
    int savedData = saveTeachers(teacherDetails);
    savedData > 0 ? printf("Save success %d teachers!!!\n", savedData) : printf("Save unsuccessful!!!\n");
}

void saveTeacherTest()
{
    char *teacherDetails = "240058,Madeline,Peinton,mpeintonh@acquirethisname.com,65 Sutteridge Alley";
    saveTeacher(teacherDetails)  == 1 ? printf("Save success!!!\n") : printf("Save unsuccessful!!!\n");
}

void registerUserPrototype()
{
    char userDetails[STR_MIN_LEN];
    char buff[STR_MIN_LEN][STR_MID_LEN];
    char *delim = ",";
    char isTeacher[10];
    char id[10];
    int idval = generateId();
    int i = 0;

    memset(buff[0], 0, sizeof(buff[0]));

    sprintf(id, "%d", idval);
    strcpy(buff[0], "");

    strcpy(buff[0], id);

    printf("Is teacher [y]Yes || [n]NO: ");
    scanf("%s", isTeacher);

    printf("Enter first name: ");
    scanf("%s", buff[1]);

    printf("Enter last name: ");
    scanf("%s", buff[2]);

    printf("Enter email: ");
    scanf("%s", buff[3]);

    printf("Enter home address: ");
    scanf("%s", buff[4]);

    

    strcpy(buff[5], "");


    while (userDetails[i] != '\0')
    {
        userDetails[i] = userDetails[i+1];
        i++;
    }
    
    strToCsvFormat(buff, delim, userDetails);
    printf("%s is your ID.", id);
    printf("%s\n", userDetails);
    if(strcmp("y", isTeacher))
    {
        saveStudent(userDetails)  == 1 ? printf("Save success!!!\n") : printf("Save unsuccessful!!!\n");
    }
    else
    {
        saveTeacher(userDetails)  == 1 ? printf("Save success!!!\n") : printf("Save unsuccessful!!!\n");
    }
    
}

void editUserDetailsPrototye() // TODO
{
    char *idSupplied;
    char isteacher;

    printf("Enter ID to edit details: ");
    scanf("%s", idSupplied);

    printf("Is teacher [y]Yes || [n]No: ");
    scanf("%s", isteacher);

    switch (isteacher)
    {
    case 'y':
        /* code */
        break;
    case 'n':
        /* code */
        break;
    
    default:
        break;
    }


}

void strToCsvFormatTest()
{
    char str[STR_MIN_LEN][STR_MID_LEN] = {"Mark", "jayson", "Lanuzo", "BSIT-1.7", ""};
    char *delim = ",";
    char strCsv[STR_MIN_LEN];
    char id[10];
    int idval = generateId();
    sprintf(id, "%d", idval);

    strcpy(str[4], id);
    strcpy(str[5], "");
    
    strToCsvFormat(str, delim, strCsv);

    printf("%s\n", strCsv);
}

void editUserTest()
{
    // 240041,Nils,Mathevet,nmatheveth@disqus.com,27 Cody Point - before
    bool isTeacher = true;
    char *id = "240041";
    char *userDetails = "240041,Nils,Ruppert,nmatheveth@disqus.com,27 Cody Point"; // after edit

    editUser(isTeacher, id, userDetails) == 1 ? printf("Edit success!!!\n") : printf("Edit unsuccessful!!!\n");
}

void editStudentTest()
{
    // 240051,Barnard,Joiris,bjoirisa@mozilla.org,9380 Lyons Lane
    char *id = "240051";
    char *userDetails = "240051,Barnard,Kengkoy,bjoirisa@mozilla.org,9380 Lyons Lane";
    editStudent(id, userDetails) == 1 ? printf("Edit success!!!\n") : printf("Edit unsuccessful!!!\n");
}

void editTeacherTest()
{
    // 240037,Olly,Manneville,omannevilleg@oaic.gov.au,69983 Tony Circle
    char *id = "240037";
    char *userDetails = "240037,Olly,Kolokoy,omannevilleg@oaic.gov.au,69983 Tony Circle";
    editTeacher(id, userDetails) == 1 ? printf("Edit success!!!\n") : printf("Edit unsuccessful!!!\n");
}



