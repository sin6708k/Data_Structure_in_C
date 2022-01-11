#include "Max_Heap.h"

int main()
{
	FILE* file;

	if (fopen_s(&file, "input.txt", "r"))
		return -1;

	int capacity;
	fscanf_s(file, "%d", &capacity);
	Heap* heap = createHeap(capacity);

	while (!feof(file))
	{
		int key;
		fscanf_s(file, "%d", &key);
		pushIntoHeap(heap, createElement(key));

		printf("PUSH(%2d)\n", key);
		printHeap(heap);
	}

	fclose(file);
	
	while (heap->count > 0)
	{
		Element element = popFromHeap(heap);

		printf("POP(%2d)\n", element.key);
		printHeap(heap);
	}

	releaseHeap(heap);
	return 0;
}

Heap* createHeap(int capacity)
{
	Heap* heap = malloc(sizeof(*heap));
	heap->arr = malloc(sizeof(*heap->arr) * (capacity + 1));
	heap->count = 0;
	return heap;
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

void releaseHeap(Heap* heap)
{
	free(heap->arr);
	free(heap);
}

void pushIntoHeap(Heap* heap, Element newItem)
{
	if (heap == NULL)
		return;

	Element* items = heap->arr;

	int i = ++heap->count;
	for (; i != 1; i /= 2)
	{
		if (newItem.key < items[i / 2].key)
			break;

		items[i] = items[i / 2];
	}

	items[i] = newItem;
}

Element popFromHeap(Heap* heap)
{
	if (heap == NULL)
		return emptyElement();

	Element* arr = heap->arr;

	Element deletedElement = arr[1];
	Element temp = arr[heap->count];
	arr[heap->count--] = emptyElement();

	int parent = 1;
	for (int child = 2; child <= heap->count; parent = child, child *= 2)
	{
		if (child + 1 <= heap->count && arr[child].key < arr[child + 1].key)
		{
			child++;
		}

		if (temp.key >= arr[child].key)
			break;

		arr[parent] = arr[child];
	}

	arr[parent] = temp;

	return deletedElement;
}

Element peekAtHeap(const Heap* heap)
{
	if (heap == NULL)
		return emptyElement();

	return heap->arr[1];
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

		printf("%2d ", heap->arr[i].key);
	}

	printf("\n\n");
}