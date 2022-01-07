#include "The_Satisfiability_Problem.h"

int main()
{
	FILE* file;

	if (fopen_s(&file, "input.txt", "r"))
		return;

	char postfix[100];
	fscanf_s(file, "%s", postfix, 100);
	printf("f(a, b, c) with postfix = %s\n\n", postfix);
	fclose(file);

	BinTreeNode* binTree = createBinTree(postfix);

	for (int a = 0; a <= 1; a++)
	{
		for (int b = 0; b <= 1; b++)
		{
			for (int c = 0; c <= 1; c++)
			{
				setValue(binTree, a, b, c);
				printf("f(%d, %d, %d) = %d\n", a, b, c, evaluate(binTree));
			}
		}
	}

	releaseBinTree(binTree);
	return 0;
}

BinTreeNode* createBinTree(char* postfix)
{
	StackNode* stack = NULL;

	for (char* symbol = postfix; *symbol != '\0'; symbol++)
	{
		BinTreeNode* binTree = malloc(sizeof(BinTreeNode));
		binTree->symbol = *symbol;

		if (*symbol == '~') // NOT
		{
			binTree->rightChild = popFromStack(&stack);
			binTree->leftChild = NULL;
		}
		else if (*symbol == '&') // AND
		{
			binTree->rightChild = popFromStack(&stack);
			binTree->leftChild = popFromStack(&stack);
		}
		else if (*symbol == '|') // OR
		{
			binTree->rightChild = popFromStack(&stack);
			binTree->leftChild = popFromStack(&stack);
		}
		else
		{
			binTree->rightChild = NULL;
			binTree->leftChild = NULL;
		}

		pushIntoStack(&stack, binTree);
	}

	return popFromStack(&stack);
}

void releaseBinTree(BinTreeNode* root)
{
	if (root == NULL)
		return;

	releaseBinTree(root->leftChild);
	releaseBinTree(root->rightChild);
	free(root);
}

void setValue(BinTreeNode* root, int a, int b, int c)
{
	if (root == NULL)
		return;

	if (root->symbol == 'a')
	{
		root->value = a;
	}
	else if (root->symbol == 'b')
	{
		root->value = b;
	}
	else if (root->symbol == 'c')
	{
		root->value = c;
	}
	else
	{
		root->value = -1;
	}

	setValue(root->leftChild, a, b, c);
	setValue(root->rightChild, a, b, c);
}

int evaluate(BinTreeNode* root)
{
	if (root == NULL)
		return -1;

	int leftValue = evaluate(root->leftChild);
	int rightValue = evaluate(root->rightChild);

	if (root->symbol == '~') // NOT
	{
		root->value = !rightValue;
		return root->value;
	}
	else if (root->symbol == '&') // AND
	{
		root->value = leftValue && rightValue;
		return root->value;
	}
	else if (root->symbol == '|') // OR
	{
		root->value = leftValue || rightValue;
		return root->value;
	}
	else
	{
		return root->value;
	}
}

void pushIntoStack(StackNode** top, BinTreeNode* data)
{
	StackNode* newNode = malloc(sizeof(*newNode));
	newNode->data = data;

	if (*top)
	{
		newNode->link = *top;
	}
	else
	{
		newNode->link = NULL;
	}

	*top = newNode;
}

BinTreeNode* popFromStack(StackNode** top)
{
	if (*top == NULL)
		return NULL;

	StackNode* deletedNode = *top;
	BinTreeNode* binTree = deletedNode->data;
	*top = deletedNode->link;
	free(deletedNode);
	return binTree;
}

BinTreeNode* peekAtStack(const StackNode* top)
{
	if (top == NULL)
		return NULL;

	return top->data;
}