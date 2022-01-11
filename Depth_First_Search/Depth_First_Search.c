#include "Depth_First_Search.h"

int main()
{
	FILE* file;

	if (fopen_s(&file, "input.txt", "r"))
		return -1;

	int numOfVertex;
	fscanf_s(file, "%d", &numOfVertex);
	Graph* graph = newGraph(numOfVertex);

	while (!feof(file))
	{
		int u, v;
		fscanf_s(file, "%d %d", &u, &v);
		addUndirectedEdge(graph, u, v);
	}

	printGraph(graph);
	depthFirstSearchAndPrintGraph(graph, 0);
	depthFirstSearchAndPrintGraph(graph, 4);

	releaseGraph(graph);
	return 0;
}

Graph* newGraph(int numOfVertex)
{
	Graph* graph = malloc(sizeof(*graph));
	graph->edges = malloc(sizeof(*graph->edges) * numOfVertex);
	graph->numOfVertex = numOfVertex;

	for (int i = 0; i < numOfVertex; i++)
	{
		graph->edges[i] = NULL;
	}
	
	return graph;
}

void releaseGraph(Graph* graph)
{
	if (graph == NULL)
		return;

	for (int i = 0; i < graph->numOfVertex; i++)
	{
		releaseEdges(graph->edges[i]);
	}

	free(graph);
}

void releaseEdges(Edge* edge)
{
	if (edge == NULL)
		return;

	releaseEdges(edge->link);
	free(edge);
}

void addUndirectedEdge(Graph* graph, int u, int v)
{
	addDirectedEdge(graph, u, v);
	addDirectedEdge(graph, v, u);
}

void addDirectedEdge(Graph* graph, int u, int v)
{
	Edge* newNode = malloc(sizeof(*newNode));
	newNode->vertex = v;
	newNode->link = graph->edges[u];
	graph->edges[u] = newNode;
}

void printGraph(const Graph* graph)
{
	if (graph == NULL)
		return;

	for (int i = 0; i < graph->numOfVertex; i++)
	{
		printf("%2d : ", i);
		printEdges(graph->edges[i]);
		printf("\n");
	}

	printf("\n");
}

void printEdges(const Edge* edge)
{
	if (edge == NULL)
		return;

	printf("%2d ", edge->vertex);
	printEdges(edge->link);
}

void depthFirstSearchAndPrintGraph(const Graph* graph, int vertex)
{
	if (graph == NULL)
		return;

	int* visited = malloc(sizeof(*visited) * graph->numOfVertex);

	for (int i = 0; i < graph->numOfVertex; i++)
	{
		visited[i] = 0;
	}

	printf("DFS(%2d) : ", vertex);
	depthFirstSearchAndPrintEdges(graph, vertex, visited);
	printf("\n");
	free(visited);
}

void depthFirstSearchAndPrintEdges(const Graph* graph, int vertex, int* visited)
{
	if (graph == NULL)
		return;

	if (visited[vertex] == 1)
		return;

	visited[vertex] = 1;
	printf("%2d ", vertex);

	for (Edge* edge = graph->edges[vertex]; edge; edge = edge->link)
	{
		if (visited[edge->vertex] == 0)
		{
			depthFirstSearchAndPrintEdges(graph, edge->vertex, visited);
		}
	}
}