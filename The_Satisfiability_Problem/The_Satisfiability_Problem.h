// The Satisfiability Problem
#include <stdio.h>
#include <stdlib.h>

typedef struct BinTreeNode
{
	char symbol;
	int value;
	struct BinTreeNode* leftChild;
	struct BinTreeNode* rightChild;
} BinTreeNode;

typedef struct StackNode
{
	BinTreeNode* data;
	struct StackNode* link;
} StackNode;

BinTreeNode* createBinTree(char*);
void releaseBinTree(BinTreeNode*);

void setValue(BinTreeNode*, int, int, int);
int evaluate(BinTreeNode*);

void pushIntoStack(StackNode**, BinTreeNode*);
BinTreeNode* popFromStack(StackNode**);
BinTreeNode* peekAtStack(const StackNode*);