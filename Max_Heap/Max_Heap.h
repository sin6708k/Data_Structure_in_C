// Max heap
#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
	int key;
} Element;

typedef struct Heap
{
	Element* items;
	int count;
	int capacity;
} Heap;

Heap* newHeap(int);
void releaseHeap(Heap*);

void pushIntoHeap(Heap*, Element);
Element popFromHeap(Heap*);
Element peekAtHeap(const Heap*);
Element newElement(int);
Element emptyElement();

void printHeap(const Heap*);