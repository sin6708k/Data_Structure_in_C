// Insertion Sort
#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
	int key;
} Element;

typedef struct List
{
	Element* items;
	int count;
	int capacity;
} List;

List* createList(int);
Element createElement(int);
Element emptyElement();

void releaseList(List*);

void addToList(List*, Element);

void printList(List*);
void printListWithHeader(List*, int, int);
void insertionSortAndPrint(List*);