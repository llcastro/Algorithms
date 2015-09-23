#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "adjacencyList.h"
#include "binary_heap.h"
//#include "dijkstra.h"

void geraGrafo(Graph *graph){
    if(graph == NULL) return;

    srand(time(NULL));

    int i, j;
    for(i=0; i<(graph->V); i++){
        for(j=i; j<(graph->V); j++){
            if(j != i) {
                addEdge(graph, i, j, rand()%1000);
            }
        }
    }
}

int main(){

    int V = 25;
    Graph *graph = createGraph(V);
    if(graph == NULL) return -1;

    geraGrafo(graph);

    printGraph(graph);

    /*
    addEdge(graph, 0, 1, 5);
    addEdge(graph, 0, 4, 2);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 8);
    addEdge(graph, 1, 4, 1);
    addEdge(graph, 2, 3, 2);
    addEdge(graph, 3, 4, 1);
    addEdge(graph, 4, 2, 4);
    */

    listaHeap *cm = NULL;
    cm = (listaHeap*) dijkstra(graph, 0);

    int i;
    for (i = 0; i < cm->tam; i++) {
        printf("id:%d, idNo:%d, peso:%d\n", i, cm[i].idNo, cm[i].peso);
    }

    printf("ok\n");

    return 0;
}
