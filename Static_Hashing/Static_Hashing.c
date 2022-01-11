#include "Static_Hashing.h"

int main()
{
	FILE* file;

	if (fopen_s(&file, "input.txt", "r"))
		return -1;

	int capacity;
	fscanf_s(file, "%d", &capacity);
	HashTable* table = createTable(capacity);
	
	while (!feof(file))
	{
		char item[20];
		fscanf_s(file, "%s", item, 20);
		insertIntoTable(table, createElement(item));
	}

	fclose(file);

	printTable(table);

	releaseTable(table);
	return 0;
}

HashTable* createTable(int capacity)
{
	HashTable* table = malloc(sizeof(*table));
	table->arr = malloc(sizeof(*table->arr) * capacity);
	table->capacity = capacity;

	for (int i = 0; i < capacity; i++)
	{
		table->arr[i] = emptyNode();
	}

	return table;
}

Node* createNode(Element data)
{
	Node* node = malloc(sizeof(*node));
	node->data = data;
	node->link = NULL;
	return node;
}

Element createElement(char* item)
{
	Element element;
	element.key = convertItemToKey(item);
	strcpy_s(element.item, 20, item);
	return element;
}

Node* emptyNode()
{
	return createNode(emptyElement());
}

Element emptyElement()
{
	return createElement("");
}

void releaseTable(HashTable* table)
{
	for (int i = 0; i < table->capacity; i++)
	{
		releaseNodes(table->arr[i]);
	}

	free(table->arr);
	free(table);
}

void releaseNodes(Node* node)
{
	if (node == NULL)
		return;

	releaseNodes(node->link);
	free(node);
}

Node* searchOnTable(HashTable* table, int key)
{
	if (table == NULL)
		return NULL;

	int hashCode = getHashCode(key, table->capacity);
	return searchOnNodes(table->arr[hashCode], key);
}

Node* searchOnNodes(Node* headerNode, int key)
{
	if (headerNode == NULL)
		return NULL;

	if (headerNode->data.key == key)
		return headerNode;

	return searchOnNodes(headerNode->link, key);
}

Node* searchLastOnNodes(Node* headerNode)
{
	if (headerNode == NULL)
		return NULL;

	if (headerNode->link == NULL)
		return headerNode;

	return searchLastOnNodes(headerNode->link);
}

Node* searchPrevOnNodes(Node* headerNode, int key)
{
	if (headerNode == NULL)
		return NULL;

	if (headerNode->link == NULL)
		return NULL;

	if (headerNode->link->data.key == key)
		return headerNode;

	return searchPrevOnNodes(headerNode, key);
}

void insertIntoTable(HashTable* table, Element element)
{
	int hashCode = getHashCode(element.key, table->capacity);

	Node* prevNode = searchLastOnNodes(table->arr[hashCode]);

	Node* newNode = createNode(element);
	newNode->link = prevNode->link;
	prevNode->link = newNode;
}

void deleteOnTable(HashTable* table, int key)
{
	int hashCode = getHashCode(key, table->capacity);

	Node* prevNode = searchPrevOnNodes(table->arr[hashCode], key);

	if (prevNode == NULL)
		return;

	Node* deletedNode = prevNode->link;
	prevNode->link = deletedNode->link;
	free(deletedNode);
}

void printTable(HashTable* table)
{
	for (int i = 0; i < table->capacity; i++)
	{
		printf("%3d : ", i);
		printNodes(table->arr[i]);
		printf("\n");
	}
}

void printNodes(Node* node)
{
	if (node == NULL)
		return;

	Element element = node->data;

	if (element.key)
	{
		printf("(%d, %s) ", element.key, element.item);
	}

	printNodes(node->link);
}

int convertItemToKey(char* item)
{
	int key = 0;

	while (*item)
	{
		key += *(item++);
	}

	return key;
}

int getHashCode(int key, int capacity)
{
	return key % capacity;
}