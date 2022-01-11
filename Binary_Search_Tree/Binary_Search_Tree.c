#include "Binary_Search_Tree.h"

int main()
{
	FILE* file;

	if (fopen_s(&file, "input.txt", "r"))
		return -1;

	BinTreeNode* binTree = NULL;

	while (!feof(file))
	{
		int key;
		fscanf_s(file, "%d", &key);
		pushIntoBinTree(&binTree, createElement(key));

		printf("PUSH(%2d) : ", key);
		printBinTree(binTree);
		printf("\n");
	}

	fclose(file);
	releaseBinTree(binTree);
	return 0;
}

Element createElement(int key)
{
	Element element;
	element.key = key;
	return element;
}

Element emptyElement()
{
	return createElement(INT_MIN);
}

void releaseBinTree(BinTreeNode* root)
{
	if (root == NULL)
		return;

	releaseBinTree(root->leftChild);
	releaseBinTree(root->rightChild);
	free(root);
}

void pushIntoBinTree(BinTreeNode** root, Element element)
{
	if (*root == NULL)
	{
		BinTreeNode* newNode = malloc(sizeof(*newNode));
		newNode->element = element;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		*root = newNode;
		return;
	}

	if ((*root)->element.key >= element.key)
	{
		pushIntoBinTree(&(*root)->leftChild, element);
	}
	else
	{
		pushIntoBinTree(&(*root)->rightChild, element);
	}
}

void printBinTree(const BinTreeNode* root)
{
	if (root == NULL)
		return;

	printBinTree(root->leftChild);
	printf("%2d ", root->element.key);
	printBinTree(root->rightChild);
}