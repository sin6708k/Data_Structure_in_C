// Binary Search Tree
#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
	int key;
} Element;

typedef struct BinTreeNode
{
	Element item;
	struct BinTreeNode* leftChild;
	struct BinTreeNode* rightChild;
} BinTreeNode;

void releaseBinTree(BinTreeNode*);

void pushInBinTree(BinTreeNode**, Element);
Element newElement(int);
Element emptyElement();

void printBinTree(const BinTreeNode*);