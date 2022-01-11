// Binary Search Tree
#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
	int key;
} Element;

typedef struct BinTreeNode
{
	Element element;
	struct BinTreeNode* leftChild;
	struct BinTreeNode* rightChild;
} BinTreeNode;

Element createElement(int);
Element emptyElement();

void releaseBinTree(BinTreeNode*);

void pushIntoBinTree(BinTreeNode**, Element);

void printBinTree(const BinTreeNode*);