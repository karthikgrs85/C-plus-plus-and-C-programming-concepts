#define _CRT_SECURE_NO_WARNINGS

#pragma once

#define BATCHSIZE 6
#define BUF_SIZE 40
#define COLLEGE_SIZE 100
#define STU_CODE_SIZE 8
#define CHOICE_LEN 3
#define BUF_LEN 40


#define MAX_STUDENTS 100


typedef union code
{
    char studentCode[STU_CODE_SIZE];
    int studentID;
} unique_code;

 enum class streamCode: int
{
    SCIENCE = 1,    
    ENGINEERING,
    COMMERCE,
    MEDICINE,
    UNDEFINED = 0

};

typedef struct studentDetails
{
   char *m_firstName, *m_lastName;
   int m_sNo;		
   char m_batch[BATCHSIZE];
   unique_code *m_uniqueStudentCode;
   streamCode m_streamCode;
   char *m_college;
   
} student;

void init(student *s);
int inputName(char **fName, char **lName);
int inputStreamAndCollege(streamCode *_streamCode, char **collegeName);
int setSerialNumberAndBatch(int *rollno, char batch[]);
int setUniqueCode(unique_code **code, const student s);
int shallowCopy(student *target, const student source);
int deepCopy(student *target, const student source);
int displayDetails(const student s);
int freeSpace(student *s);


