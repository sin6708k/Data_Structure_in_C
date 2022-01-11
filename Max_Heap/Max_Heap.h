// Max heap
#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
	int key;
} Element;

typedef struct Heap
{
	Element* arr;
	int count;
	int capacity;
} Heap;

Heap* createHeap(int);
Element createElement(int);
Element emptyElement();

void releaseHeap(Heap*);

void pushIntoHeap(Heap*, Element);
Element popFromHeap(Heap*);
Element peekAtHeap(const Heap*);

void printHeap(const Heap*);