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
		pushInBinTree(&binTree, newElement(key));
		printf("PUSH(%2d) : ", key);
		printBinTree(binTree);
		printf("\n");
	}

	fclose(file);
	releaseBinTree(binTree);
	return 0;
}

void releaseBinTree(BinTreeNode* root)
{
	if (root == NULL)
		return;

	releaseBinTree(root->leftChild);
	releaseBinTree(root->rightChild);
	free(root);
}

void pushInBinTree(BinTreeNode** root, Element item)
{
	if (*root == NULL)
	{
		BinTreeNode* newNode = malloc(sizeof(*newNode));
		newNode->item = item;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		*root = newNode;
		return;
	}

	if ((*root)->item.key >= item.key)
	{
		pushInBinTree(&(*root)->leftChild, item);
	}
	else
	{
		pushInBinTree(&(*root)->rightChild, item);
	}
}

Element newElement(int key)
{
	Element item;
	item.key = key;
	return item;
}

Element emptyElement()
{
	return newElement(INT_MIN);
}

void printBinTree(const BinTreeNode* root)
{
	if (root == NULL)
		return;

	printBinTree(root->leftChild);
	printf("%2d ", root->item.key);
	printBinTree(root->rightChild);
}