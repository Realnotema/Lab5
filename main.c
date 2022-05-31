#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "input.h"
#include "process.h"

int Dialog(const char *options[], int CountOptions) {
    int choose = 0;
    for (int i = 0; i < CountOptions; i++)
        puts(options[i]);
    char *errmess = "";
    do {
        puts(errmess);
        do {
            choose = getInt();
        } while (choose > CountOptions || choose < 0);
        if (choose < 0 || choose > CountOptions)
            errmess = "Incorrect input. Try again";
    } while (choose < 0 || choose > CountOptions);
    return choose;
}

void askCoordinate (int *x, int *y) {
    *x = getInt();
    *y = getInt();
}

int delMenu (int choose, Graph *graph) {
    if (graph == NULL)
        return 1;
    int x, y;
    int x1, y1;
    const char *mess[] = {"Enter coordinate", NULL,
                          "Enter the first coordinate",
                          "Enter the second coordinate"};
    switch (choose) {
        case 1:
            puts(mess[0]);
            askCoordinate(&x, &y);
            delVertex (graph, x, y);
            break;
        case 2:
            puts(mess[2]);
            askCoordinate(&x, &y);
            puts(mess[3]);
            askCoordinate(&x1, &y1);
            delEdge(graph, x, y, x1, y1);
            break;
        case 3:
            return 1;
        default:
            return -1;
    }
    return 0;
}

int addMenu (int choose, Graph *graph) {
    int x, y;
    int x1, y1;
    int weight;
    const char *mess[] = {"Enter coordinate", NULL,
                          "Enter the first coordinate",
                          "Enter the second coordinate"};
    switch (choose) {
        case 1:
            puts(mess[0]);
            askCoordinate(&x, &y);
            addVertex(graph, x, y);
            break;
        case 2:
            puts(mess[2]);
            askCoordinate(&x, &y);
            puts(mess[3]);
            askCoordinate(&x1, &y1);
            addEdge(graph, x, y, x1, y1);
            break;
        case 3:
            return 1;
        default:
            return -1;
    }
    return 0;
}

int Menu (int choose, Graph *graph) {
    FILE *fo;
    Vertex *ptr = NULL;
    Queue *queue = NULL;
    int x, y;
    int flag = 0;
    const char *errmess[] = {"Error: Incorrect entry"};
    const char *addmess[] = {"1. Add vertex:", "2. Add edge:", "3. Quit"};
    const char *delmess[] = {"1. Delete vertex", "2. Delete edge:", "3. Quit"};
    switch (choose) {
        case 1:
            do {
                flag = addMenu(Dialog(addmess, 3), graph);
                if (flag == -1) {
                    puts(errmess[0]);
                    flag = 0;
                }
            } while (flag == 0);
            break;
        case 2:
            do {
                flag = delMenu(Dialog(delmess, 3), graph);
                if (flag == -1) {
                    puts(errmess[0]);
                    flag = 0;
                }
            } while (flag == 0);
            break;
        case 3:
            printAsAdjacencyList(graph);
            break;
        case 4:
            queue = (Queue *) calloc(1, sizeof(Queue));
            askCoordinate(&x, &y);
            ptr = findVertex (graph, x, y);
            breadthFirstSearch (graph, ptr, queue);
            printQueue(queue);
            break;
        case 5:
            break;
        case 6:
            return 1;
        default:
            return -1;
    }
    return 0;
}

int main() {
    int flag = 0;
    Graph *graph = calloc(1, sizeof(Graph));
    graph->vertex = calloc(VALUE, sizeof(Vertex *));
    const char *errmess[] = {"Error: Incorrect entry"};
    const char *options[] = {"1. Add vertex or edge", "2. Dell vertex or edge",
                             "3. Print as adjacency list", "4. Finding a path",
                             "5. IN PROCESS", "6. Quit"};
    do {
        flag = Menu(Dialog(options, 6), graph);
        if (flag == -1) {
            puts(errmess[0]);
            flag = 0;
        }
    } while (flag == 0);
    puts("Enter name of file to save your graph:");
    FILE *fb = fopen(getStr(), "w");
    writeGraph(fb, graph);
    fclose(fb);
    system("dot -Tpng test.dot -o test.png");
    return 0;
}
