#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Student.h"

int sNo_start = 1;
char curr_batch[BATCHSIZE] = "2022";


void init(student *s)
{
    s->m_firstName = NULL;
    s->m_lastName = NULL;
    s->m_sNo = 0;
    strcpy(s->m_batch,"");
    s->m_uniqueStudentCode= NULL;
    s->m_college=NULL;

}


int inputName(char **fName, char **lName)
{
	char buff[BUF_SIZE];
	char *pos = NULL;

	printf("\n Enter first name :");
	fgets(buff,BUF_SIZE,stdin);
	if(pos = strrchr(buff,'\n'))
		*pos = '\0';
	if(*fName!=NULL)
    {
        free(*fName);
        *fName = NULL;
    }
	*fName = (char*)calloc(strlen(buff)+1,sizeof(char));
	if(*fName == NULL)
	{
		fprintf(stderr," Unable to allocate memory!");
		return EXIT_FAILURE;
	}
	strncpy(*fName,buff,strlen(buff)+1);

	printf("\n Enter last name :");
	fgets(buff,BUF_SIZE,stdin);
	if(pos = strrchr(buff,'\n'))
		*pos = '\0';
    if(*lName!=NULL)
     {
        free(*lName);
        *lName = NULL;
     }
	*lName = (char*)calloc(strlen(buff)+1,sizeof(char));
        if(*lName == NULL)
	{
		fprintf(stderr," Unable to allocate memory!");
		return EXIT_FAILURE;
	}	
	strncpy(*lName,buff,strlen(buff)+1);	
	return EXIT_SUCCESS;
}

int inputStreamAndCollege(streamCode *m_streamCode, char **collegeName)
{
    char choice[CHOICE_LEN]="";
    char buff[COLLEGE_SIZE]="";
    char *pos= NULL;
    printf("\n Enter input stream : "
           "\n 1 for Science "
           "\n 2 for Engineering "
           "\n 3 for Commerce "
           "\n 4 for Medicine :\n");
    fgets(choice,CHOICE_LEN,stdin);
    
    if(pos = strrchr(choice,'\n'))
		*pos = '\0';
    
    switch(atoi(choice))
    {
        case 1:
             *m_streamCode = streamCode::SCIENCE;
             break;
        case 2:
            *m_streamCode = streamCode::ENGINEERING;
            break;
        case 3:
            *m_streamCode = streamCode::COMMERCE;
            break;
        case 4:
            *m_streamCode = streamCode::MEDICINE;
            break;
        default:
            *m_streamCode = streamCode::UNDEFINED;

    
    }
  
    printf("\n Enter name of college :\n ");
    fgets(buff,COLLEGE_SIZE,stdin);
    if(pos = strrchr(buff,'\n'))
		*pos = '\0';

    if(*collegeName!=NULL)
    {
        free(*collegeName);
        *collegeName = NULL;
    }
	*collegeName = (char*)calloc(strlen(buff)+1,sizeof(char));
	if(*collegeName == NULL)
	{
		fprintf(stderr," Unable to allocate memory!");
		return EXIT_FAILURE;
	}
    
    strncpy(*collegeName,buff,strlen(buff)+1);

    return EXIT_SUCCESS;
    
}

int setSerialNumberAndBatch(int *sNo, char batch[])
{
    char *pos = NULL;    
    (*sNo) = sNo_start++;
    printf("\n Enter batch year in the format starting year "
            "\n Example: for course commencing in 2003 enter 2003 :\n");
    
    fgets(batch,BATCHSIZE,stdin);
    if(pos = strrchr(batch,'\n'))
		*pos = '\0';

    return EXIT_SUCCESS;
}



int displayDetails(const student s)
{
    if(s.m_firstName==NULL|| s.m_lastName== NULL || s.m_uniqueStudentCode==NULL || s.m_college==NULL)
        return EXIT_FAILURE;

    
	printf("\n Student details ");
    printf("\n--------------------------------------------"); 
    printf("\n Serial No. : %d ",s.m_sNo);
    printf("\n Student ID : %d ",s.m_uniqueStudentCode->studentID);
	printf("\n First name : %s, Last name : %s ",s.m_firstName,s.m_lastName);
	printf("\n Batch : %s ", s.m_batch);
    printf("\n College : %s", s.m_college);
    printf("\n Stream :");
    switch(s.m_streamCode)
    {
    case streamCode::SCIENCE:
            printf("Science \n");
            break;
    case streamCode::ENGINEERING:
            printf("Engineering \n") ;
            break;
    case streamCode::COMMERCE:
            printf("Commerce \n") ;
            break;
    case streamCode::MEDICINE:
            printf("Medicine \n") ;
            break;
    default:
            printf("Undefined \n") ;
    
    }
	printf("\n--------------------------------------------\n"); 
    return EXIT_SUCCESS;
}

int setUniqueCode(unique_code **code, const student s)
{
    if(*code!=NULL)
    {
        free(*code);
        *code = NULL;
    }
    *code = (unique_code*)calloc(1,sizeof(unique_code)); 

    if(*code == NULL)
	{
		fprintf(stderr," Unable to allocate memory!");
		return EXIT_FAILURE;
	}
   
    strcpy((*code)->studentCode,"");
    if(s.m_firstName==NULL || s.m_lastName == NULL ||s.m_college == NULL)
        return EXIT_FAILURE;

    sprintf(((*code)->studentCode),"%c%c%d%c%c%c%c",s.m_firstName[0],s.m_lastName[0],s.m_sNo,s.m_batch[2],s.m_batch[3],s.m_college[0],s.m_college[1]);
    return EXIT_SUCCESS;
}


int freeSpace(student *s)
{
    if(s->m_firstName!=NULL)
    {   
        free(s->m_firstName);
        s->m_firstName = NULL;
    }
    if(s->m_lastName!=NULL)
    {        
        free(s->m_lastName);
        s->m_lastName = NULL;
    }
    s->m_sNo= 0;
    strcpy(s->m_batch,"");

    if(s->m_uniqueStudentCode!=NULL)
    {
        free(s->m_uniqueStudentCode);
        s->m_uniqueStudentCode=NULL;
    }

    if(s->m_college!=NULL)
    {
        free(s->m_college);
        s->m_college= NULL;
    }

    return EXIT_SUCCESS;
}

int shallowCopy(student *target, const student source)
{	
	
    if(target->m_firstName!=NULL)
    {
        free(target->m_firstName);
        target->m_firstName= NULL;
    }    
    target->m_firstName = source.m_firstName;

    if(target->m_lastName!=NULL)
    {
        free(target->m_lastName);
        target->m_lastName= NULL;
    }
    target->m_lastName = source.m_lastName;
    target->m_sNo = source.m_sNo;
    target->m_streamCode = source.m_streamCode;

    strncpy(target->m_batch, source.m_batch, sizeof(source.m_batch));
    
    if(target->m_uniqueStudentCode!=NULL)
    {
        free(target->m_uniqueStudentCode);
        target->m_uniqueStudentCode = NULL;
    }
    target->m_uniqueStudentCode = source.m_uniqueStudentCode;
	return EXIT_SUCCESS;

} 

int deepCopy(student *target, const student source)
{
    if(target->m_firstName!=NULL)
    {
        free(target->m_firstName);
        target->m_firstName= NULL;
    }

    target->m_firstName = (char*)calloc(strlen(source.m_firstName)+1,sizeof(char));
    if(target->m_firstName == NULL)
	{
		fprintf(stderr," Unable to allocate memory!");
		return EXIT_FAILURE;
	}
    
    strncpy(target->m_firstName, source.m_firstName, strlen(source.m_firstName)+1);
    
    if(target->m_lastName!=NULL)
    {
        free(target->m_lastName);
        target->m_lastName= NULL;
    }

    target->m_lastName = (char*)calloc(strlen(source.m_lastName)+1,sizeof(char));
    if(target->m_lastName == NULL)
	{
		fprintf(stderr," Unable to allocate memory!");
		return EXIT_FAILURE;
	}
    strncpy(target->m_lastName, source.m_lastName, strlen(source.m_lastName)+1);

    target->m_streamCode = source.m_streamCode;

    target->m_sNo = source.m_sNo;
    strncpy(target->m_batch, source.m_batch, sizeof(source.m_batch));
    
    if(target->m_uniqueStudentCode!=NULL)
    {
        free(target->m_uniqueStudentCode);
        target->m_uniqueStudentCode = NULL;
    }
    target->m_uniqueStudentCode = (unique_code*)calloc(1, sizeof(unique_code));
	strncpy(target->m_uniqueStudentCode->studentCode, source.m_uniqueStudentCode->studentCode, strlen(source.m_uniqueStudentCode->studentCode)+1);

    if(target->m_college!=NULL)
    {
        free(target->m_college);
        target->m_college= NULL;
    }

    target->m_college = (char*)calloc(strlen(source.m_college)+1,sizeof(char));
    if(target->m_college == NULL)
	{
		fprintf(stderr," Unable to allocate memory!");
		return EXIT_FAILURE;
	}
    strncpy(target->m_college, source.m_college, strlen(source.m_college)+1);

        
}

