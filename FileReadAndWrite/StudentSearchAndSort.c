#include "Student.h"
#include "StudentSearchAndSort.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int MergeSortFirstName(student studentList[], int low, int high)
{
    if(low<high)
    {
        int mid = low +(high-low)/2;
        MergeSortFirstName(studentList, low, mid);
        MergeSortFirstName(studentList, mid+1, high);
        MergeByFirstName(studentList, low, mid, high);
    }
    return EXIT_SUCCESS;
}

int MergeByFirstName(student studentList[], int low, int mid, int high)
{
    int n1 = mid-low+1;
    int i,j,k, n2 = high - mid;
    student L[MAX_STUDENTS], M[MAX_STUDENTS];

    for(i = 0; i <n1; ++i)
    {
        init(&L[i]);
        deepCopy(&L[i], studentList[low+i]);
    }

    for(j = 0;j<n2; ++j)
    {
        init(&M[j]);        
        deepCopy(&M[j], studentList[mid+j+1]);
    }
    //Merge the two arrays to studentList from low to high
    i =0;
    j =0;
    k = low;    
    while(i<n1 && j < n2)
    {
        if(strcmp(L[i].m_firstName, M[j].m_firstName)<=0)
            {
                deepCopy(&studentList[k++],L[i++]);
            }
        else if(strcmp(L[i].m_firstName, M[j].m_firstName)>0)
            {
                deepCopy(&studentList[k++], M[j++]);
            }
    }
    
    while(i<n1)
        deepCopy(&studentList[k++],L[i++]);

    while(j<n2)
        deepCopy(&studentList[k++], M[j++]);
    
    for(i = 0;i<n1;++i)
        freeSpace(&L[i]);
    
    for(j = 0; j<n2; ++j)
        freeSpace(&M[j]);

    return EXIT_SUCCESS;

}
int MergeSortByFirstName(student studentList[], const int size)
{
    MergeSortFirstName(studentList, 0, size-1);
    printf("\n Student List successfully sorted by First Name using Merge Sort!...");
    return EXIT_SUCCESS;
}

int swap(student *i, student *j)
{
    if(i==NULL||i->m_firstName== NULL|| i->m_lastName==NULL|| i->m_uniqueStudentCode==NULL || i->m_college==NULL)
        return EXIT_FAILURE;
    
    if(j==NULL||j->m_firstName== NULL|| j->m_lastName==NULL|| j->m_uniqueStudentCode==NULL || j->m_college==NULL)
        return EXIT_FAILURE;

    student temp;
    init(&temp);
    deepCopy(&temp,*i);
    deepCopy(i, *j);
    deepCopy(j, temp);
    freeSpace(&temp);

    return EXIT_SUCCESS;
}

int HeapifyByFirstName(student studentList[], int n, int i)
{
	
	int largest = i;
	int left = 2*i + 1;
	int right = 2*i + 2;

	if(left<n && strcmp(studentList[left].m_firstName,studentList[largest].m_firstName)>0)
		largest = left;
	
	if(right<n && strcmp(studentList[right].m_firstName,studentList[largest].m_firstName)>0)
		largest = right;

	if(largest!= i)
	{
		swap(&studentList[largest], &studentList[i]);
		HeapifyByFirstName(studentList, n, largest);
	}		

	return EXIT_SUCCESS;
}

int HeapSortByFirstName(student studentList[], const int size)
{
    //Heapify all non leaf nodes
    int i;
    for(i = size/2 -1; i>=0; --i)
    {
        HeapifyByFirstName(studentList, size, i);
    }

    for(i = size-1;i>0; --i)
    {
        swap(&studentList[0], &studentList[i]);
        HeapifyByFirstName(studentList, i, 0);
    }
        
    printf("\n Student List successfully sorted by First Name using Heap Sort!...");
        
    return EXIT_SUCCESS;

}


int MergeSortSNo(student studentList[], int low, int high)
{
    if(low<high)
    {
        int mid = low +(high-low)/2;
        MergeSortSNo(studentList, low, mid);
        MergeSortSNo(studentList, mid+1, high);
        MergeBySNo(studentList, low, mid, high);
    }
    return EXIT_SUCCESS;
}

int MergeBySNo(student studentList[], int low, int mid, int high)
{
    int n1 = mid-low+1;
    int i,j,k, n2 = high - mid;
    student L[MAX_STUDENTS], M[MAX_STUDENTS];

    for(i = 0; i <n1; ++i)
    {
        init(&L[i]);
        deepCopy(&L[i], studentList[low+i]);
    }

    for(j = 0;j<n2; ++j)
    {
        init(&M[j]);        
        deepCopy(&M[j], studentList[mid+j+1]);
    }
    //Merge the two arrays to studentList from low to high
    i =0;
    j =0;
    k = low;    
    while(i<n1 && j < n2)
    {
        if(L[i].m_sNo <= M[j].m_sNo)
            {
                deepCopy(&studentList[k++],L[i++]);
            }
        else 
            {
                deepCopy(&studentList[k++], M[j++]);
            }
    }
    
    while(i<n1)
        deepCopy(&studentList[k++],L[i++]);

    while(j<n2)
        deepCopy(&studentList[k++], M[j++]);
    
    for(i = 0;i<n1;++i)
        freeSpace(&L[i]);
    
    for(j = 0; j<n2; ++j)
        freeSpace(&M[j]);

    return EXIT_SUCCESS;
}

int MergeSortBySNo(student studentList[], const int size)
{
    MergeSortSNo(studentList, 0, size-1);
    printf("\n Student List successfully sorted by Serial Number using Merge Sort!...");
    return EXIT_SUCCESS;
}


int HeapifyBySNo(student studentList[], int size, int i)
{
    int largest = i;
	int left = 2*i + 1;
	int right = 2*i + 2;

	if(left<size && (studentList[left].m_sNo > studentList[largest].m_sNo))
		largest = left;
	
	if(right<size && (studentList[right].m_sNo > studentList[largest].m_sNo))
		largest = right;

	if(largest!= i)
	{
		swap(&studentList[largest], &studentList[i]);
		HeapifyBySNo(studentList, size, largest);
	}		

	return EXIT_SUCCESS;
}


int HeapSortBySNo(student studentList[], const int size)
{
    //Heapify all non leaf nodes
    int i;
    for(i = size/2 -1; i>=0; --i)
    {
        HeapifyBySNo(studentList, size, i);
    }

    for(i = size-1;i>0; --i)
    {
        swap(&studentList[0], &studentList[i]);
        HeapifyBySNo(studentList, i, 0);
    }
        
    printf("\n Student List successfully sorted by Serial Number using Heap Sort!...");
        
    return EXIT_SUCCESS;
    
}

int binarySearchByFirstName(student studentList[], const char* firstName,  const int low, const int high)
{

    if(low<=high)
	{
		int mid = low + (high-low)/2;
		if(!strcmp(studentList[mid].m_firstName,firstName))
			return mid;
	
		if(strcmp(studentList[mid].m_firstName,firstName)>0)
			return binarySearchByFirstName(studentList,firstName,low, mid-1);

		return binarySearchByFirstName(studentList,firstName,mid+1, high);	

	}
	
	return -1;

}
int binarySearchBySNo(student studentList[], const int sno,  const int low, const int high)
{
    if(low<=high)
	{
		int mid = low + (high-low)/2;
		if(studentList[mid].m_sNo ==sno)
			return mid;
	
		if(studentList[mid].m_sNo>sno)
			return binarySearchBySNo(studentList,sno,low, mid-1);

		return binarySearchBySNo(studentList,sno,mid+1, high);	

	}
	
	return -1;
}
