#include <stdio.h>
#include <stdlib.h>
#include "adjacencyList.h"

AdjListNode *newAdjListNode(int dest, int peso){
    if(dest < 0 || peso < 0) return NULL;

    AdjListNode *newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->peso = peso;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int V){
    if(V < 1) return NULL;

    Graph *graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;

    graph->array = (AdjList*) malloc(V * sizeof(AdjList));

    int i;
    for (i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void addEdge(Graph *graph, int src, int dest, int peso){
    if(graph == NULL) return;
    if(src < 0 || src > graph->V || dest < 0 || dest > graph->V) return;
    if(peso < 0) return;

    AdjListNode *newNode = newAdjListNode(dest, peso);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, peso);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printGraph(Graph *graph){
    if(graph == NULL) return;

    int v;
    for (v = 0; v < graph->V; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n%d ", v, v);
        while (pCrawl) {
            printf("-> %d-%d", pCrawl->dest, pCrawl->peso);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}
