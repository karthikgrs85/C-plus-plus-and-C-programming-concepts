#pragma once
#include "Student.h"

//Sort by First Name

//Merge Sort
int MergeSortFirstName(student studentList[], int low, int high);
int MergeByFirstName(student studentList[], int low, int mid, int high);
int MergeSortByFirstName(student studentList[], const int size);

int swap(student *i, student *j);

//Heap Sort
int HeapSortByFirstName(student studentList[], const int size);
int HeapifyByFirstName(student studentList[], int size, int i);


//Sort by Serial Number
//Merge Sort
int MergeSortSNo(student studentList[], int low, int high);
int MergeBySNo(student studentList[], int low, int mid, int high);
int MergeSortBySNo(student studentList[], const int size);

//Heap Sort
int HeapSortBySNo(student studentList[], const int size);
int HeapifyBySNo(student studentList[], int size, int i);

//Binary Search
int binarySearchByFirstName(student studentList[], const char*,  const int low, const int high);
int binarySearchBySNo(student studentList[], const int sno,  const int low, const int high);

