#ifndef STRUCT_H
#define STRUCT_H

#define VALUE 30

#define white 0
#define black 1
#define grey 2

typedef struct Vertex {
    int x;
    int y;
    unsigned int weight;
    int color;
    struct Vertex *next, *prev;
} Vertex;

typedef struct Graph {
    struct Vertex **vertex;
    int count;
} Graph;

typedef struct Queue {
    int x, y;
    struct Queue *next;
} Queue;

#endif
