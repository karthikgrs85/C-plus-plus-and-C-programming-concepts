#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "Student.h"
#include "StudentFileManager.h"

#define STUDENT_BIN_FILE "StudentRecords.bin"

extern int sNo_start;

int copyToFileBlock(studentFileBlock* target, const student source)
{

    if(target == NULL || source.m_firstName==NULL|| source.m_lastName== NULL || source.m_uniqueStudentCode==NULL || source.m_college==NULL)
        return EXIT_FAILURE;


    strncpy(target->m_firstName,source.m_firstName, strlen(source.m_firstName)+1);
    strncpy(target->m_lastName,source.m_lastName, strlen(source.m_lastName)+1);
    
    target->m_sNo = source.m_sNo;
    strncpy(target->m_batch, source.m_batch, strlen(source.m_batch)+1);
 
    strncpy(target->m_uniqueStudentCode.studentCode, source.m_uniqueStudentCode->studentCode, strlen(source.m_uniqueStudentCode->studentCode)+1);

    target->m_streamCode = source.m_streamCode;
    
    strncpy(target->m_college, source.m_college, strlen(source.m_college)+1);

    return EXIT_SUCCESS;
}

int copyFromFileBlock(student *target, const studentFileBlock source)
{
    if(target==NULL)
        return EXIT_FAILURE;
    
    if(target->m_firstName!=NULL)
    {
        free(target->m_firstName);
        target->m_firstName = NULL;
    }

	target->m_firstName = (char*)calloc(strlen(source.m_firstName)+1,sizeof(char));
	if(target->m_firstName == NULL)
	{
		fprintf(stderr," Unable to allocate memory!");
		return EXIT_FAILURE;
	}
    
    strncpy(target->m_firstName,source.m_firstName, strlen(source.m_firstName)+1);

    if(target->m_lastName!=NULL)
    {
        free(target->m_lastName);
        target->m_lastName = NULL;
    }

	target->m_lastName = (char*)calloc(strlen(source.m_lastName)+1,sizeof(char));
	if(target->m_lastName == NULL)
	{
		fprintf(stderr," Unable to allocate memory!");
		return EXIT_FAILURE;
	}
    
    strncpy(target->m_lastName,source.m_lastName, strlen(source.m_lastName)+1);
    
    target->m_sNo = source.m_sNo;

    strncpy(target->m_batch, source.m_batch, strlen(source.m_batch)+1);
    
    if(target->m_uniqueStudentCode!=NULL)
    {
        free(target->m_uniqueStudentCode);
        target->m_uniqueStudentCode = NULL;
    }
    target->m_uniqueStudentCode = (unique_code*)calloc(1,sizeof(unique_code));
    
    strncpy(target->m_uniqueStudentCode->studentCode, source.m_uniqueStudentCode.studentCode, strlen(source.m_uniqueStudentCode.studentCode)+1);

    target->m_streamCode = source.m_streamCode;
    
    if(target->m_college!=NULL)
    {
        free(target->m_college);
        target->m_college = NULL;
    }

	target->m_college = (char*)calloc(strlen(source.m_college)+1,sizeof(char));
	if(target->m_college == NULL)
	{
		fprintf(stderr," Unable to allocate memory!");
		return EXIT_FAILURE;
	}
    
    strncpy(target->m_college,source.m_college, strlen(source.m_college)+1);
    

    return EXIT_SUCCESS;   
    

}



int readAllStudentsFromFile(student studentList[], int *size)
{
    FILE *fp = fopen(STUDENT_BIN_FILE, "rb");  
    int index = 0;
    if(fp==NULL)
    {
        fprintf(stderr,"\n Student records file does not exist!");
        return EXIT_FAILURE;
    }
    studentFileBlock sFB;
    *size = 0;

	while(fread(&sFB,sizeof(studentFileBlock),1,fp))
	{
		init(&studentList[index]);
        copyFromFileBlock(&studentList[index],sFB);
        printf("\n Read %d records from student records file ", ++index);
        (*size)++;
   	}
    sNo_start = studentList[index-1].m_sNo + 1;
    fclose(fp);    
    
    return EXIT_SUCCESS;
}

int WriteAllStudentsToFile(const student studentList[], const int size)
{
	FILE *fp = fopen(STUDENT_BIN_FILE,"wb");
    int i = 0;
    studentFileBlock sFB;
	
	for(i = 0; i< size; ++i)
    {
        
        copyToFileBlock(&sFB,studentList[i]);
	    if(fwrite(&sFB, sizeof(studentFileBlock), 1, fp)!=0)
	    {
		    printf("\n Write of student %d successful! ", i+1);
	    }
    }
	fclose(fp);
    if(i==size)
        return EXIT_SUCCESS;

	return EXIT_FAILURE;
	
}
