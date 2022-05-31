#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <math.h>

int writeGraph (FILE *fb, Graph *graph) {
    if (graph == 0)
        return 1;
    fprintf(fb, "digraph GG {\n");
    Vertex *ptr = NULL;
    Vertex *pos = NULL;
    for (int i = 0; i < graph->count; i++) {
        ptr = graph->vertex[i];
        pos = ptr;
        if (ptr->next == NULL)
            fprintf(fb, "\t\"(%d, %d)\"\n", pos->x, pos->y);
        while (ptr->next != NULL) {
            int j = 0;
            ptr = ptr->next;
            fprintf(fb, "\t\"(%d, %d)\" -> \"(%d, %d)\" [label=\"%u\"]\n", pos->x, pos->y, ptr->x, ptr->y, ptr->weight);
            j++;
        }
    }
    fprintf(fb, "}");
    return 0;
}

int addVertex (Graph *graph, int x, int y) {
    if (graph == NULL)
        return 1;
    Vertex *temp = calloc(1, sizeof(Vertex));
    Vertex *ptr = graph->vertex[0];
    int i = 0;
    temp->x = x;
    temp->y = y;
    while (ptr != NULL)
        ptr = graph->vertex[++i];
    graph->vertex[i] = temp;
    i = 0;
    if (graph->vertex[i]->x)
    graph->count++;
    return 0;
}

Vertex *findVertex (Graph *graph, int x, int y) {
    int i = 0;
    Vertex *ptr = graph->vertex[0];
    while (ptr != NULL && ptr->x != x && ptr->y != y)
        ptr = graph->vertex[++i];
    return ptr;
}

int printQueue(Queue *queue) {
    if (queue == NULL)
        return 1;
    while (queue != NULL) {
        Queue *ptr = queue;
        queue = queue->next;
        printf("(%d, %d)\n", ptr->x, ptr->y);
        free(ptr);
    }
    return 0;
}

int isInQueue (Queue *queue, Vertex *ptr) {
    Queue *pos = queue;
    while (pos->next != NULL) {
        if (pos->x == ptr->x && pos->y == ptr->y)
            return 1;
        else
            pos = pos->next;
    }
    return 0;
}

int breadthFirstSearch (Graph *graph, Vertex *ptr, Queue *queue) {
    if (graph == NULL || ptr == NULL)
        return 1;
    if (queue->next == NULL) {
        queue->x = ptr->x;
        queue->y = ptr->y;
    }
    for (int i = 0; i < graph->count && ptr != NULL; i++) {
        while (ptr->next != NULL) {
            Queue *temp = calloc(1, sizeof(Queue));
            ptr = ptr->next;
            if (!isInQueue(queue, ptr)) {
                temp->x = ptr->x;
                temp->y = ptr->y;
                queue->next = temp;
                temp = NULL;
            }
        }
        ptr = findVertex(graph, ptr->prev->x, ptr->prev->y);
        if (ptr == NULL)
            break;
    }
    return 0;
}

int delNode (Vertex *ptr) {
    if (ptr == NULL)
        return 1;
    while (ptr->next != NULL)
        ptr = ptr->next;
    while (ptr->prev != NULL) {
        ptr = ptr->prev;
        ptr->next = NULL;
        free(ptr->next);
    }
    free(ptr);
    return 0;
}

int delVertex (Graph *graph, int x, int y) {
    if (graph ==  NULL)
        return 1;
    Vertex *ptr = findVertex (graph, x, y);
    Vertex *temp = NULL;
    Vertex *next = ptr;
    if (ptr != NULL)
        temp = ptr->next;
    else return 0;
    while (temp != NULL) {
        temp = findVertex(graph, temp->x, temp->y);
        while (temp != NULL && temp->x != ptr->x && temp->y != ptr->y)
            temp = temp->next;
        if (temp->next) {
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
        }
        temp->prev->next = NULL;
        free(temp);
        next = next->next;
        temp = next->next;
    }
    int i = 0;
    while (graph->vertex[i] != ptr)
        i++;
    graph->vertex[i] = NULL;
    delNode(ptr);
    return 0;
}

int delEdge (Graph *graph, int x1, int y1, int x2, int y2) {
    if (graph == NULL)
        return 1;
    Vertex *first = findVertex(graph, x1, y1);
    while (first != NULL && first->next != NULL && first->x != x2 && first->y != y2)
        first = first->next;
    Vertex *second = findVertex(graph, x2, y2);
    while (second != NULL && second->next != NULL && second->x != x1 && second->y != y1)
        second = second->next;
    Vertex *ptr = first;
    for (int i = 0; i < 2; i++) {
        if (ptr->next) {
            ptr->next->prev = ptr->prev;
            ptr->prev->next = ptr->next;
            free(ptr);
        } else {
            ptr->prev->next = NULL;
            free(ptr);
        }
        ptr = second;
    }
    return 0;
}

unsigned int calculateWeight (int x1, int y1, int x2, int y2) {
    int a = (int) (pow(x2 - x1, 2) + 0.5);
    int b = (int) (pow(y2 - y1, 2) + 0.5);
    unsigned int res = (int) sqrt(a + b);
    return res;
}

int addEdge (Graph *graph, int x1, int y1, int x2, int y2) {
    if (graph == NULL)
        return 1;
    Vertex *ptr = graph->vertex[0];
    Vertex *temp1 = calloc(1, sizeof(Vertex));
    temp1->x = x1;
    temp1->y = y1;
    Vertex *temp2 = calloc(1, sizeof(Vertex));
    temp2->x = x2;
    temp2->y = y2;
    Vertex *in = temp2;
    int x = x1, y = y1;
    for (int i = 0, j = 0; j < 2; j++) {
        if (j != 0) {
            in = temp1;
            x = x2;
            y = y2;
        }
        while (ptr->x != x && ptr->y != y)
            ptr = graph->vertex[++i];
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = in;
        in->prev = ptr;
        in->weight = calculateWeight(x1, y1, x2, y2);
        i = 0;
    }
    return 0;
}

int printAsAdjacencyList (Graph *graph) {
    if (graph == NULL)
        return 1;
    Vertex *ptr = NULL;
    for (int i = 0; i < graph->count; i++) {
        ptr = graph->vertex[i];
        if (ptr == NULL)
            continue;
        printf("|%d/%d|", ptr->x, ptr->y);
        while (ptr->next) {
            ptr = ptr->next;
            if (ptr)
                printf("%d/%d ", ptr->x, ptr->y);
        }
        printf("\n");
    }
    return 0;
}
