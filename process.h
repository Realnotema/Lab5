#ifndef PROCESS_H
#define PROCESS_H

#include "struct.h"

int addVertex (Graph *graph, int x, int y);
int addEdge (Graph *graph, int x1, int y1, int x2, int y2);
int printAsAdjacencyList (Graph *graph);
int writeGraph (FILE *fb, Graph *graph);
int delVertex (Graph *graph, int x, int y);
int delEdge (Graph *graph, int x1, int y1, int x2, int y2);
int breadthFirstSearch (Graph *graph, Vertex *ptr, Queue *queue);
Vertex *findVertex (Graph *graph, int x, int y);
int printQueue(Queue *queue);

#endif PROCESS_H
