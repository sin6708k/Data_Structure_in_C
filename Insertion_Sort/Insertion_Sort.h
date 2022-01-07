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

List* newList(int);
void releaseList(List*);

void addToList(List*, Element);
Element newElement(int);
Element emptyElement();

void printList(List*);
void printListWithHeader(List*, int, int);
void sortAndPrintList(List*);