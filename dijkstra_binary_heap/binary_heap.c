#include <stdio.h>
#include <stdlib.h>
#include "binary_heap.h"


void preOrdem(node *root){
    if(root != NULL){
		printf("%d ", root->peso);
		preOrdem(root->esq);
		preOrdem(root->dir);
	}
	return;
}

node *buscaRoot(node *root){
    if(root){
        if(root->pai){
            return buscaRoot(root->pai);
        } else {
            return root;
        }
    }
    return NULL;
}

node *buscaMenorEsq(node **root){
    if(root == NULL || *root == NULL) return NULL;

    if((*root)->esq == NULL) return *root;
    return buscaMenorEsq(&((*root)->esq));
}

node *buscaMaiorDir(node **folha){
    if(folha == NULL || *folha == NULL) return NULL;

    if((*folha)->dir == NULL) return *folha;
    return buscaMaiorDir(&((*folha)->dir));
}

node *_insereNo(node **filho, int k, int id){

    if(*filho == NULL) {
        *filho = (node*)malloc(sizeof(node));
        if(*filho == NULL) return NULL;
        (*filho)->esq = NULL;
        (*filho)->dir = NULL;
        (*filho)->pai = NULL;
        (*filho)->peso = k;
        (*filho)->id = id;
        return *filho;
    }

    node *caminho = NULL;

    if((*filho)->esq == NULL && (*filho)->dir == NULL && (*filho)->pai == NULL) {
        (*filho)->esq = (node*)malloc(sizeof(node));
        if((*filho)->esq == NULL) return NULL;
        (*filho)->esq->pai = *filho;
        (*filho)->esq->esq = NULL;
        (*filho)->esq->dir = NULL;
        (*filho)->esq->peso = k;
        (*filho)->esq->id = id;
        return ((*filho)->esq);
    }
    while(1){
        if((*filho)->esq == NULL && (*filho)->dir == NULL && (*filho)->pai) {
            caminho = *filho;
            *filho = (*filho)->pai;
        } else if((*filho)->esq && (*filho)->dir == NULL) {
            node *aux = (node*)malloc(sizeof(node));
            if(aux == NULL) return NULL;
            (*filho)->dir = aux;
            aux->pai = *filho;
            aux->esq = NULL;
            aux->dir = NULL;
            aux->peso = k;
            aux->id = id;
            return ((*filho)->dir);
        } else if((*filho)->esq && (*filho)->dir && (*filho)->pai == NULL && (*filho)->dir == caminho) {
            node *aux = buscaMenorEsq(filho);
            if(aux == NULL) return NULL;
            aux->esq = (node*)malloc(sizeof(node));
            if(aux->esq == NULL) return NULL;
            aux->esq->esq = NULL;
            aux->esq->dir = NULL;
            aux->esq->pai = aux;
            aux->esq->peso = k;
            aux->esq->id = id;
            return (aux->esq);
        } else if((*filho)->esq && (*filho)->dir && (*filho)->esq == caminho) {
            node *aux = buscaMenorEsq(&((*filho)->dir));
            if(aux == NULL) return NULL;
            aux->esq = (node*)malloc(sizeof(node));
            if(aux->esq == NULL) return NULL;
            aux->esq->esq = NULL;
            aux->esq->dir = NULL;
            aux->esq->pai = aux;
            aux->esq->peso = k;
            aux->esq->id = id;
            return (aux->esq);
        } else if((*filho)->esq && (*filho)->dir && (*filho)->pai) {
            caminho = *filho;
            *filho = (*filho)->pai;
        } else {
            return NULL;
        }
    }
}

void swap(node *x, node *y, listaHeap *listaH){
    if(x == NULL || y == NULL) return;
    if(listaH == NULL) return;

    node *aux = listaH[x->id].no;
    listaH[x->id].no = listaH[y->id].no;
    listaH[y->id].no = aux;

    int i = x->peso, j = x->id;
    x->peso = y->peso;
    x->id = y->id;
    y->peso = i;
    y->id = j;
}

void heapify_bottom_up(node **folha, listaHeap *listaH){
    if(folha == NULL || *folha == NULL) return;
    if(listaH == NULL) return;

    node *filho = *folha;

    while(filho->pai) {
        if(filho->pai->esq == filho){
            if(filho->pai->dir){
                if(filho->pai->dir->peso < filho->peso){
                    if(filho->pai->dir->peso < filho->pai->peso){
                        swap(filho->pai->dir, filho->pai, listaH);
                        filho = filho->pai;
                    } else {
                        return;
                    }
                } else {
                    if(filho->peso < filho->pai->peso){
                        swap(filho, filho->pai, listaH);
                        filho = filho->pai;
                    } else {
                        return;
                    }
                }
            } else {
                if(filho->peso < filho->pai->peso){
                    swap(filho, filho->pai, listaH);
                    filho = filho->pai;
                } else {
                    return;
                }
            }
        } else {
            if(filho->peso < filho->pai->esq->peso){
                if(filho->peso < filho->pai->peso){
                    swap(filho, filho->pai, listaH);
                    filho = filho->pai;
                } else {
                    return;
                }
            } else {
                if(filho->pai->esq->peso < filho->pai->peso){
                    swap(filho->pai->esq, filho->pai, listaH);
                    filho = filho->pai;
                } else {
                    return;
                }
            }
        }
    }
}

node *insereNo(node **folha, int k, int id, listaHeap *listaH){
    node *aux = _insereNo(folha, k, id);
    if(aux == NULL) return NULL;
    listaH[aux->id].no = aux;
    heapify_bottom_up(&aux, listaH);
    return aux;
}

void heapify_top_down(node **root, listaHeap *listaH){
    if(root == NULL || *root == NULL) return;
    if(listaH == NULL) return;

    node *no = *root;

    while(1){
        if(no->esq){
            if(no->dir){
                if(no->esq->peso < no->dir->peso){
                    if(no->esq->peso < no->peso){
                        swap(no, no->esq, listaH);
                        no = no->esq;
                    } else {
                        return;
                    }
                } else {
                    if(no->dir->peso < no->peso){
                        swap(no, no->dir, listaH);
                        no = no->dir;
                    } else {
                        return;
                    }
                }
            } else {
                if(no->esq->peso < no->peso){
                    swap(no->esq, no, listaH);
                    no = no->esq;
                } else {
                    return;
                }
            }
        } else {
            return;
        }
    }
}

node *antecessor(node **folha){
    if(folha == NULL || *folha == NULL) return NULL;

    node *no = *folha;

    while(1) {
        if(no == (no)->pai->esq) {
            if((no)->pai->pai == NULL) return buscaMaiorDir(&((no)->pai));
            no = (no)->pai;
        } else {
            return buscaMaiorDir(&((no)->pai->esq));
        }
    }
}

void removeNo(node **folha){
    if(folha == NULL || *folha == NULL) return;

    free(*folha);
    *folha = NULL;
}

int extraiMin(node **folha, listaHeap *listaH){
    if(folha == NULL || *folha == NULL) return -1;
    if(listaH == NULL) return -1;

    node *root = buscaRoot(*folha);
    if(root == NULL) return -1;
    int k = root->id;
    listaH[root->id].no = NULL;
    if(root == *folha){
        listaH[(*folha)->id].no = NULL;
        removeNo(folha);
        return k;
    }
    node *aux = antecessor(folha);
    root->peso = (*folha)->peso;
    root->id = (*folha)->id;

    listaH[(*folha)->id].no = root;

    if((*folha)->pai != NULL) {
        if((*folha)->pai->esq == *folha)
            removeNo(&(*folha)->pai->esq);
        else
            removeNo(&(*folha)->pai->dir);
    }

    *folha = aux;
    heapify_top_down(&root, listaH);

    return k;
}

void decreaseKey(int idNo, listaHeap *listaH, int novaChave){
    if(listaH == NULL) return;
    if(idNo > listaH->tam || idNo < 0) return;
    if(novaChave < 0) return;

    if(novaChave > listaH[idNo].no->peso) return;

    listaH[idNo].no->peso = novaChave;
    heapify_bottom_up(&(listaH[idNo].no), listaH);
}
