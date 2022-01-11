#include "Quick_Sort.h"

int main()
{
	FILE* file;

	if (fopen_s(&file, "input.txt", "r"))
		return -1;

	int capacity;
	fscanf_s(file, "%d", &capacity);
	List* list = createList(capacity);

	for (int i = 0; i < capacity; i++)
	{
		int key;
		fscanf_s(file, "%d", &key);
		addToList(list, createElement(key));
	}

	fclose(file);

	printList(list);
	quickSortAndPrint(list, 0, list->count - 1);
	printList(list);

	releaseList(list);
	return 0;
}

List* createList(int capacity)
{
	List* list = malloc(sizeof(*list));
	list->items = malloc(sizeof(*list->items) * capacity);
	list->count = 0;
	list->capacity = capacity;
	return list;
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

void releaseList(List* list)
{
	free(list->items);
	free(list);
}

void addToList(List* list, Element element)
{
	list->items[list->count++] = element;
}

void printList(List* list)
{
	for (int i = 0; i < list->count; i++)
	{
		printf(" %2d ", list->items[i].key);
	}

	printf("\n");
}

void printListWithHeader(List* list, int left, int right)
{
	for (int i = 0; i < list->count; i++)
	{
		printf("%s%2d%s", (i == left) ? "[" : " ", list->items[i].key, (i == right) ? "]" : " ");
	}

	printf("\n");
}

void quickSortAndPrint(List* list, int left, int right)
{
	if (left >= right)
		return;

	int i = left;
	int j = right + 1;

	Element* items = list->items;

	while (1)
	{
		do i++; while (items[i].key < items[left].key);
		do j--; while (items[j].key > items[left].key);
		
		if (i >= j)
			break;

		swap(&items[i], &items[j]);
	}

	swap(&items[left], &items[j]);

	printListWithHeader(list, left, right);
	quickSortAndPrint(list, left, j - 1);
	quickSortAndPrint(list, j + 1, right);
}

void swap(Element* item1, Element* item2)
{
	Element temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}