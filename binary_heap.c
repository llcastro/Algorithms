#include <stdio.h>
#include <stdlib.h>
//#include "binary_heap.h"

typedef struct no {
    int chave;
    struct no *pai;
    struct no *esq;
    struct no *dir;
} no;

void preOrdem(no *root){
    if(root != NULL){
		printf("%d ", root->chave);
		preOrdem(root->esq);
		preOrdem(root->dir);
	}
	return;
}

no *buscaRoot(no *root){
    if(root){
        if(root->pai){
            return buscaRoot(root->pai);
        } else {
            return root;
        }
    }
}

no *buscaMenorEsq(no **root){
    if(root == NULL || *root == NULL) return NULL;

    if((*root)->esq == NULL) return *root;
    return buscaMenorEsq(&((*root)->esq));
}

no *buscaMaiorDir(no **folha){
    if(folha == NULL || *folha == NULL) return NULL;

    if((*folha)->dir == NULL) return *folha;
    return buscaMaiorDir(&((*folha)->dir));
}

no *_insereNo(no **filho, int k){

    if(*filho == NULL) {
        *filho = (no*)malloc(sizeof(no));
        if(*filho == NULL) return NULL;
        (*filho)->esq = NULL;
        (*filho)->dir = NULL;
        (*filho)->pai = NULL;
        (*filho)->chave = k;
        return *filho;
    }

    no *caminho = NULL;

    if((*filho)->esq == NULL && (*filho)->dir == NULL && (*filho)->pai == NULL) {
        (*filho)->esq = (no*)malloc(sizeof(no));
        if((*filho)->esq == NULL) return NULL;
        (*filho)->esq->pai = *filho;
        (*filho)->esq->esq = NULL;
        (*filho)->esq->dir = NULL;
        (*filho)->esq->chave = k;
        return ((*filho)->esq);
    }
    while(1){
        if((*filho)->esq == NULL && (*filho)->dir == NULL && (*filho)->pai) {
            caminho = *filho;
            *filho = (*filho)->pai;
        } else if((*filho)->esq && (*filho)->dir == NULL) {
            no *aux = (no*)malloc(sizeof(no));
            if(aux == NULL) return NULL;
            (*filho)->dir = aux;
            aux->pai = *filho;
            aux->esq = NULL;
            aux->dir = NULL;
            aux->chave = k;
            return ((*filho)->dir);
        } else if((*filho)->esq && (*filho)->dir && (*filho)->pai == NULL && (*filho)->dir == caminho) {
            no *aux = buscaMenorEsq(filho);
            if(aux == NULL) return NULL;
            aux->esq = (no*)malloc(sizeof(no));
            if(aux->esq == NULL) return NULL;
            aux->esq->esq = NULL;
            aux->esq->dir = NULL;
            aux->esq->pai = aux;
            aux->esq->chave = k;
            return (aux->esq);
        } else if((*filho)->esq && (*filho)->dir && (*filho)->esq == caminho) {
            no *aux = buscaMenorEsq(&((*filho)->dir));
            if(aux == NULL) return NULL;
            aux->esq = (no*)malloc(sizeof(no));
            if(aux->esq == NULL) return NULL;
            aux->esq->esq = NULL;
            aux->esq->dir = NULL;
            aux->esq->pai = aux;
            aux->esq->chave = k;
            return (aux->esq);
        } else if((*filho)->esq && (*filho)->dir && (*filho)->pai) {
            caminho = *filho;
            *filho = (*filho)->pai;
        } else {
            return NULL;
        }
    }
}

void swap(no *x, no *y){
    if(x == NULL || y == NULL) return;

    int i = x->chave;
    x->chave = y->chave;
    y->chave = i;
}

void heapify_bottom_up(no **folha){
    if(folha == NULL || *folha == NULL) return;

    no *filho = *folha;

    while(filho->pai) {
        if(filho->pai->esq == filho){
            if(filho->pai->dir){
                if(filho->pai->dir->chave < filho->chave){
                    if(filho->pai->dir->chave < filho->pai->chave){
                        swap(filho->pai->dir, filho->pai);
                        filho = filho->pai;
                    } else {
                        return;
                    }
                } else {
                    if(filho->chave < filho->pai->chave){
                        swap(filho, filho->pai);
                        filho = filho->pai;
                    } else {
                        return;
                    }
                }
            } else {
                if(filho->chave < filho->pai->chave){
                    swap(filho, filho->pai);
                    filho = filho->pai;
                } else {
                    return;
                }
            }
        } else {
            if(filho->chave < filho->pai->esq->chave){
                if(filho->chave < filho->pai->chave){
                    swap(filho, filho->pai);
                    filho = filho->pai;
                } else {
                    return;
                }
            } else {
                if(filho->pai->esq->chave < filho->pai->chave){
                    swap(filho->pai->esq, filho->pai);
                    filho = filho->pai;
                } else {
                    return;
                }
            }
        }
    }
}

no *insereNo(no **folha, int k){
    no *aux = _insereNo(folha, k);
    heapify_bottom_up(&aux);
    return aux;
}

void heapify_top_down(no **root){
    if(root == NULL || *root == NULL) return;

    no *tno = *root;

    while(1){
        if(tno->esq){
            if(tno->dir){
                if(tno->esq->chave < tno->dir->chave){
                    if(tno->esq->chave < tno->chave){
                        swap(tno, tno->esq);
                        tno = tno->esq;
                    } else {
                        return;
                    }
                } else {
                    if(tno->dir->chave < tno->chave){
                        swap(tno, tno->dir);
                        tno = tno->dir;
                    } else {
                        return;
                    }
                }
            } else {
                if(tno->esq->chave < tno->chave){
                    swap(tno->esq, tno);
                    tno = tno->esq;
                } else {
                    return;
                }
            }
        } else {
            return;
        }
    }
}

no *antecessor(no **folha){
    if(folha == NULL || *folha == NULL) return;

    no *tno = *folha;

    while(1) {
        if(tno == (tno)->pai->esq) {
            if((tno)->pai->pai == NULL) return buscaMaiorDir(&((tno)->pai));
            tno = (tno)->pai;
        } else {
            return buscaMaiorDir(&((tno)->pai->esq));
        }
    }
}

void removeNo(no **folha){
    if(folha == NULL || *folha == NULL) return;

    free(*folha);
    *folha = NULL;
}

int extraiMin(no **folha){
    if(folha == NULL || *folha == NULL) return;

    no *root = buscaRoot(*folha);
    int k = root->chave;
    if(root == *folha){
        removeNo(folha);
        return k;
    }
    no *aux = antecessor(folha);
    root->chave = (*folha)->chave;

    if((*folha)->pai != NULL) {
        if((*folha)->pai->esq == *folha)
            removeNo(&(*folha)->pai->esq);
        else
            removeNo(&(*folha)->pai->dir);
    }

    *folha = aux;
    heapify_top_down(&root);

    return k;
}

int main(){

    no *folha = NULL;
    int i;
    for(i=0; i<100; i++){
        folha = insereNo(&folha, i);
    }
    no *aux = buscaRoot(folha);

    for(i=0; i < 1030; i++){
        extraiMin(&folha);
    }

    printf("ok\n");

    return 0;

}
