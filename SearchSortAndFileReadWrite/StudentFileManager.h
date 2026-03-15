#pragma once
#include "Student.h"

typedef struct studentDetails_FileBlock
{
   char m_firstName[BUF_SIZE], m_lastName[BUF_SIZE];
   int m_sNo;		
   char m_batch[BATCHSIZE];
   unique_code m_uniqueStudentCode;
   streamCode m_streamCode;
   char m_college[COLLEGE_SIZE];
   
} studentFileBlock;



int readAllStudentsFromFile(student studentList[], int *size);

int WriteAllStudentsToFile(const student studentList[], const int size);


int copyToFileBlock(studentFileBlock *target, const student source);
int copyFromFileBlock(student *target, const studentFileBlock source);

