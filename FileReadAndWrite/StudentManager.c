#include "Student.h"
#include "StudentSearchAndSort.h"
#include "StudentFileManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

#define INP_BUF_LEN 20

int displayAllStudents(const student studentList[],const int size)
{
    if(size==0)
    {
        printf("\n Student List Empty!");
        return EXIT_SUCCESS;    
    }
    for(int i = 0;i<size;++i)
    {
        printf("\n Student %d",i+1);
        if(displayDetails(studentList[i])==EXIT_FAILURE)
        {
            fprintf(stderr,"\n Invalid details");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int getStudentBySerialNumber(const student studentList[], const int size, const int sNo)
{

    for(int i = 0;i<size;++i)
    {
        if(studentList[i].m_sNo == sNo)
        {
            return i;
        }
    }
    return -1;
}

int getStudentByStudentID(const student studentList[], const int size, const int studentID)
{

    for(int i = 0;i<size;++i)
    {
        if(studentList[i].m_uniqueStudentCode->studentID == studentID)
        {
            return i;
        }
    }
    return -1;
}



int deleteStudentByIndex(student studentList[], int *size, const int index)
{
    int i;
    if(index < 0 || index >= (*size) )
    {
        fprintf(stderr,"\n Invalid index !\n Delete unsuccessful...");
        return EXIT_FAILURE;
    }
    for(i=index;i<(*size)-1;i++)
    {
        deepCopy(&studentList[i],studentList[i+1]);
    }
    freeSpace(&studentList[i]);
    (*size)--;
    return EXIT_SUCCESS;
}

int deleteAllStudents(student studentList[], int *size)
{
    int len = *size;        
    
    for(int i=0;i<len;i++)
    {
        freeSpace(&studentList[i]);
        (*size)--;
    }
    return EXIT_SUCCESS;
}


int main()
{
    char choice[CHOICE_LEN]="", subChoice[CHOICE_LEN]="", inpBuffer[BUF_LEN]="", *token=NULL, transactOption[CHOICE_LEN]= "";
        
    char *pos = NULL;
    student studentList[MAX_STUDENTS], s;
    int numStudents = 0, index = 0;
    bool run = true, isAppend = true;
    readAllStudentsFromFile(studentList, &numStudents);
    
    do
    {
        printf("\n Welcome to the Student Management Console !"
               "\n Choose from the following options :"
                "\n 1. To add a student "
                "\n 2. To view the students "
                "\n 3. To view a particular student "
                "\n 4. To delete a student "
                "\n 5. Sort by first name "
                "\n 6. Sort by serial number  "
                "\n 0 to exit \n\n");
        
        fgets(choice,CHOICE_LEN,stdin);
        if(pos = strrchr(choice,'\n'))
            *pos ='\0';
        switch(atoi(choice))
        {
            case 1:
                init(&studentList[numStudents]);
                if(inputName(&studentList[numStudents].m_firstName, &studentList[numStudents].m_lastName)==EXIT_FAILURE)
                {
                    fprintf(stderr,"\n Error entering name \n");
                    break;
                }		        
       
                inputStreamAndCollege(&studentList[numStudents].m_streamCode, &studentList[numStudents].m_college);  	
    
	            setSerialNumberAndBatch(&studentList[numStudents].m_sNo,studentList[numStudents].m_batch);

                setUniqueCode(&studentList[numStudents].m_uniqueStudentCode, studentList[numStudents]);    
                
                printf("\n Student successfully Added !");
                
                displayDetails(studentList[numStudents++]);

                break;
        
        case 2:
            displayAllStudents(studentList, numStudents);
            break;

        case 3:
            printf("\n Enter rollno or student code to view  -n <firstName> or -s <serial no>:");
            fgets(inpBuffer, INP_BUF_LEN, stdin);
            if(pos = strrchr(inpBuffer,'\n'))
                *pos ='\0';
            
            token = strtok(inpBuffer," ");
            strncpy(transactOption,token,CHOICE_LEN);
            transactOption[CHOICE_LEN - 1] = '\0';

            token = strtok(NULL, inpBuffer);
            if(!strncmp(transactOption,"-n",2))
            {
                HeapSortByFirstName(studentList, numStudents);
                index = binarySearchByFirstName(studentList,token, 0, numStudents-1);
            }
            else if(!strncmp(transactOption,"-s",2))
            {   
                HeapSortBySNo(studentList, numStudents);
                index  = binarySearchBySNo(studentList, atoi(token), 0, numStudents-1);
            }
            else
            {
                fprintf(stderr,"\n Invalid entry! ...");
                break;
            }
            
            if(index == -1)
                fprintf(stderr,"\n Roll No. or Student ID does not exist !...");
            else
            {
                displayDetails(studentList[index]);
            }
            
            break;
       
      case 4:
            printf("\n Enter rollno or student code to delete \n -s <serial no> or -i <studentid> :");
            fgets(inpBuffer, INP_BUF_LEN, stdin);
            if(pos = strrchr(inpBuffer, '\n'))
                *pos = '\0';
            
            token = strtok(inpBuffer," ");
            strncpy(transactOption,token,CHOICE_LEN);
            transactOption[CHOICE_LEN - 1] = '\0';

            token = strtok(NULL," ");
            if(!strncmp(transactOption,"-s",2))
            {   
                index  = getStudentBySerialNumber(studentList, numStudents, atoi(token));
            }
            else if(!strncmp(transactOption,"-i",2))
            {
                index = getStudentByStudentID(studentList, numStudents, atoi(token));
            }
            else
            {
                fprintf(stderr,"\n Invalid entry! ...");
                break;
            }
            displayDetails(studentList[index]);
            printf("\n Confirm Delete ? Y or N ");
            fgets(subChoice, CHOICE_LEN, stdin);
            
            if(pos = strrchr(subChoice,'\n'))
                *pos ='\0';   
            if((subChoice[0]=='y')||(subChoice[0]=='Y'))
            {
                if(deleteStudentByIndex(studentList,&numStudents,index)==EXIT_SUCCESS)
                    printf("\n Delete Successful! ...");
            }
            else
                printf("\n Delete aborted...");

            break; 
       
      case 5:
        printf("\n Select from the following options :"
               "\n 1. Sort by First Name using Merge Sort "
               "\n 2. Sort by First Name using Heap Sort :\n");
        fgets(subChoice,CHOICE_LEN, stdin);
        if(pos = strrchr(subChoice,'\n'))
         *pos ='\0';
        if(atoi(subChoice)==1)        
            MergeSortByFirstName(studentList, numStudents);    
        else if(atoi(subChoice)==2)
            HeapSortByFirstName(studentList, numStudents);
        else
            fprintf(stderr, "\n Invalid input! Going back to main menu...");  
        
        break;

      case 6:
        printf("\n Select from the following options :"
               "\n 1. Sort by Roll No using Merge Sort "
               "\n 2. Sort by Roll No using Heap Sort :\n");
        fgets(subChoice,CHOICE_LEN, stdin);
        if(pos = strrchr(subChoice,'\n'))
         *pos ='\0';
        if(atoi(subChoice)==1)        
            MergeSortBySNo(studentList, numStudents);    
        else if(atoi(subChoice)==2)
            HeapSortBySNo(studentList, numStudents);
        else
            fprintf(stderr, "\n Invalid input! Going back to main menu...");  
         break;

      case 0:
        if(!strcmp(choice,"0"))
            run = false;
        else
            fprintf(stderr, "\n Invalid input! Try again ...");
     }                  

    }while(run);
    
    //HeapSortBySNo(studentList, numStudents);
    WriteAllStudentsToFile(studentList, numStudents);

    printf("\n Program Terminating ....");
    deleteAllStudents(studentList,&numStudents);

    if(numStudents == 0)
    {
        printf("\n All memory freed up..\n");
        return EXIT_SUCCESS;
    }
    
    printf("\n Error freeing up memory!..\n");
    return EXIT_FAILURE;

}
