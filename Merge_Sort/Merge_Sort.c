#include "Merge_Sort.h"

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
	sortAndPrintList(list, 0, list->count - 1);
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

void sortAndPrintList(List* list, int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;
	sortAndPrintList(list, left, mid);
	sortAndPrintList(list, mid + 1, right);
	mergeList(list, left, mid, right);

	for (int i = 0; i < list->count; i++)
	{
		printf("%s%2d%s", (i == left) ? "[" : " ", list->items[i].key, (i == right) ? "]" : " ");
	}

	printf("\n");
}

void mergeList(List* list, int left, int mid, int right)
{
	Element* items = list->items;
	List* sortedList = newList(list->capacity);
	Element* sortedItems = sortedList->items;

	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right)
	{
		if (items[i].key <= items[j].key)
		{
			sortedItems[k++] = items[i++];
		}
		else
		{
			sortedItems[k++] = items[j++];
		}
	}

	if (i > mid)
	{
		for (int m = j; m <= right; m++)
		{
			sortedItems[k++] = items[m];
		}
	}
	else
	{
		for (int m = i; m <= mid; m++)
		{
			sortedItems[k++] = items[m];
		}
	}

	for (int m = left; m <= right; m++)
	{
		items[m] = sortedItems[m];
	}

	releaseList(sortedList);
}

void swap(Element* item1, Element* item2)
{
	Element temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}