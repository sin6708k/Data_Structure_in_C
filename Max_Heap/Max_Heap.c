#include "Max_Heap.h"

int main()
{
	FILE* file;

	if (fopen_s(&file, "input.txt", "r"))
		return -1;

	int capacity;
	fscanf_s(file, "%d", &capacity);
	Heap* heap = newHeap(capacity);

	while (!feof(file))
	{
		int key;
		fscanf_s(file, "%d", &key);
		pushInHeap(heap, newElement(key));
		printf("PUSH(%2d)\n", key);
		printHeap(heap);
	}

	fclose(file);
	
	while (heap->count > 0)
	{
		Element item = popInHeap(heap);
		printf("POP(%2d)\n", item.key);
		printHeap(heap);
	}

	releaseHeap(heap);
	return 0;
}

Heap* newHeap(int capacity)
{
	Heap* heap = malloc(sizeof(*heap));
	heap->items = malloc(sizeof(*heap->items) * (capacity + 1));
	heap->count = 0;
	return heap;
}

void releaseHeap(Heap* heap)
{
	free(heap->items);
	free(heap);
}

void pushInHeap(Heap* heap, Element newItem)
{
	if (heap == NULL)
		return;

	Element* items = heap->items;
	int i = ++heap->count;

	for (; i != 1; i /= 2)
	{
		if (newItem.key < items[i / 2].key)
			break;

		items[i] = items[i / 2];
	}

	items[i] = newItem;
}

Element popInHeap(Heap* heap)
{
	if (heap == NULL)
		return emptyElement();

	Element* items = heap->items;

	Element deletedItem = items[1];
	Element lastItem = items[heap->count];
	items[heap->count--] = emptyElement();

	int parent = 1;

	for (int child = 2; child <= heap->count; parent = child, child *= 2)
	{
		if (child + 1 <= heap->count && items[child].key < items[child + 1].key)
		{
			child++;
		}

		if (lastItem.key >= items[child].key)
			break;

		items[parent] = items[child];
	}

	items[parent] = lastItem;

	return deletedItem;
}

Element peekInHeap(const Heap* heap)
{
	if (heap == NULL)
		return emptyElement();

	return heap->items[1];
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

void printHeap(const Heap* heap)
{
	for (int i = 1, n = 2; i <= heap->count; i++)
	{
		if (i == n)
		{
			printf("\n");
			n += n;
		}

		printf("%2d ", heap->items[i].key);
	}

	printf("\n\n");
}