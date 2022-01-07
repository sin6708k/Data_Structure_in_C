#include "Insertion_Sort.h"

int main()
{
	FILE* file;

	if (fopen_s(&file, "input.txt", "r"))
		return -1;

	int capacity;
	fscanf_s(file, "%d", &capacity);
	List* list = newList(capacity);

	for (int i = 0; i < capacity; i++)
	{
		int key;
		fscanf_s(file, "%d", &key);
		addToList(list, newElement(key));
	}

	fclose(file);

	printList(list);
	sortAndPrintList(list);
	printList(list);

	releaseList(list);
	return 0;
}

List* newList(int capacity)
{
	List* list = malloc(sizeof(*list));
	list->items = malloc(sizeof(*list->items) * capacity);
	list->count = 0;
	list->capacity = capacity;
	return list;
}

void releaseList(List* list)
{
	free(list->items);
	free(list);
}

void addToList(List* list, Element item)
{
	list->items[list->count++] = item;
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

void printList(List* list)
{
	for (int i = 0; i < list->capacity; i++)
	{
		printf(" %2d ", list->items[i].key);
	}

	printf("\n");
}

void printListWithHeader(List* list, int left, int right)
{
	for (int i = 0; i < list->capacity; i++)
	{
		printf("%s%2d%s", (i == left) ? "[" : " ", list->items[i].key, (i == right) ? "]" : " ");
	}

	printf("\n");
}

void sortAndPrintList(List* list)
{
	Element* items = list->items;

	for (int i = 1; i < list->count; i++)
	{
		Element temp = items[i];

		int j;
		for (j = i - 1; j >= 0 && items[j].key > temp.key; j--)
		{
			items[j + 1] = items[j];
		}

		items[j + 1] = temp;
		
		printListWithHeader(list, 0, i);
	}
}