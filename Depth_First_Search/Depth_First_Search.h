// Depth First Search
#include <stdio.h>
#include <stdlib.h>

typedef struct Edge
{
	int vertex;
	struct Edge* link;
} Edge;

typedef struct Graph
{
	Edge** edges;
	int numOfVertex;
} Graph;

Graph* newGraph(int);
void releaseGraph(Graph*);
void releaseEdges(Edge*);

void addUndirectedEdge(Graph*, int, int);
void addDirectedEdge(Graph*, int, int);

void printGraph(const Graph*);
void printEdges(const Edge*);
void searchAndPrintGraph(const Graph*, int);
void searchAndPrintEdges(const Graph*, int, int*);