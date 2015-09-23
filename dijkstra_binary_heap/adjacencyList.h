#include <stdio.h>
#include <stdlib.h>

typedef struct AdjListNode {
    int dest, peso;
    struct AdjListNode *next;
} AdjListNode;

typedef struct AdjList {
    struct AdjListNode *head;
} AdjList;

typedef struct Graph {
    int V;
    struct AdjList *array;
} Graph;

// adiciona uma aresta no grafo nao direcionado
void addEdge(Graph *graph, int src, int dest, int distance);

// cria o grafo
Graph *createGraph(int V);

// cria um novo noh no grafo
AdjListNode *newAdjListNode(int dest, int distance);

// imprime um grafo recebido
void printGraph(Graph *graph);
