#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "adjacencyList.h"
#include "binary_heap.h"
//#include "dijkstra.h"

listaHeap *dijkstra(Graph *graph, int source){
    if(graph == NULL) return NULL;
    if(source > graph->V || source < 0) return NULL;

    listaHeap *lista = (listaHeap*)malloc((graph->V)*sizeof(listaHeap));
    if(lista == NULL) return NULL;
    lista->tam = graph->V;

    node *heap = NULL;
    heap = insereNo(&heap, 0, source, lista);
    lista[source].idNo = source;
    lista[source].peso = 0;

    int i;
    for (i = 0; i < lista->tam; i++) {
        if(i != source) {
            heap = insereNo(&heap, INT_MAX, i, lista);
            lista[i].idNo = i;
            lista[i].peso = INT_MAX;
        }
    }

    while(heap){
        int min = extraiMin(&heap, lista);

        AdjListNode *no = graph->array[min].head;

        while(no){
            int id = no->dest;

            if(lista[id].no) {
                if(lista[id].no->peso > no->peso + lista[min].peso) {
                    decreaseKey(id, lista, no->peso + lista[min].peso);
                    lista[id].peso = no->peso + lista[min].peso;
                    lista[id].idNo = min;
                }
            }
            no = no->next;
        }
    }

    return lista;
}
