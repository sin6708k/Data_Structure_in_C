// Static Hashing
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Element
{
	int key;
	char item[20];
} Element;

typedef struct Node
{
	Element data;
	struct Node* link;
} Node;

typedef struct HashTable
{
	Node** arr;
	int capacity;
} HashTable;

HashTable* createTable(int);
Node* createNode(Element);
Element createElement(char*);

Node* emptyNode();
Element emptyElement();

void releaseTable(HashTable*);
void releaseNodes(Node*);

Node* searchOnTable(HashTable*, int);
Node* searchOnNodes(Node*, int);
Node* searchLastOnNodes(Node*);
Node* searchPrevOnNodes(Node*, int);

void insertIntoTable(HashTable*, Element);
void deleteOnTable(HashTable*, int);

void printTable(HashTable*);
void printNodes(Node*);

int convertItemToKey(char*);
int getHashCode(int, int);