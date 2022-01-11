#include "Merge_Sort.h"

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
	mergeSortAndPrint(list, 0, list->count - 1);
	printList(list);

	releaseList(list);
	return 0;
}

List* createList(int capacity)
{
	List* list = malloc(sizeof(*list));
	list->arr = malloc(sizeof(*list->arr) * capacity);
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
	free(list->arr);
	free(list);
}

void addToList(List* list, Element element)
{
	list->arr[list->count++] = element;
}

void printList(List* list)
{
	for (int i = 0; i < list->count; i++)
	{
		printf(" %2d ", list->arr[i].key);
	}

	printf("\n");
}

void printListWithHeader(List* list, int left, int right)
{
	for (int i = 0; i < list->count; i++)
	{
		printf("%s%2d%s", (i == left) ? "[" : " ", list->arr[i].key, (i == right) ? "]" : " ");
	}

	printf("\n");
}

void mergeSortAndPrint(List* list, int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;
	mergeSortAndPrint(list, left, mid);
	mergeSortAndPrint(list, mid + 1, right);
	mergeList(list, left, mid, right);

	for (int i = 0; i < list->count; i++)
	{
		printf("%s%2d%s", (i == left) ? "[" : " ", list->arr[i].key, (i == right) ? "]" : " ");
	}

	printf("\n");
}

void mergeList(List* list, int left, int mid, int right)
{
	Element* arr = list->arr;
	List* sortedList = createList(list->capacity);
	Element* sortedArr = sortedList->arr;

	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right)
	{
		if (arr[i].key <= arr[j].key)
		{
			sortedArr[k++] = arr[i++];
		}
		else
		{
			sortedArr[k++] = arr[j++];
		}
	}

	if (i > mid)
	{
		for (int m = j; m <= right; m++)
		{
			sortedArr[k++] = arr[m];
		}
	}
	else
	{
		for (int m = i; m <= mid; m++)
		{
			sortedArr[k++] = arr[m];
		}
	}

	for (int m = left; m <= right; m++)
	{
		arr[m] = sortedArr[m];
	}

	releaseList(sortedList);
}

void swap(Element* item1, Element* item2)
{
	Element temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}