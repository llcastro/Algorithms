#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "binariaAVL.h"

/*
* Autor: Luis Angelo Loss de Castro
*/

void printPreOrdem(NoArvBinariaAVL *raiz){
	if(raiz != NULL){
		printf("%d %d\n", raiz->chave, raiz->fb);
		printPreOrdem(raiz->esq);
		printPreOrdem(raiz->dir);
	}
	return;
}

/*		c
*	   /
* 	  b      ->	  b
*    /			 / \
*   a 			a   c
*/
void rotacaoSimplesDireita(NoArvBinariaAVL **raiz){
	assert(raiz);
	if(*raiz == NULL) return;

	NoArvBinariaAVL *aux = *raiz;
	*raiz = (*raiz)->esq;
	aux->esq = (*raiz)->dir;
	(*raiz)->dir = aux;

	if(aux->esq == NULL && aux->dir == NULL){
		aux->fb = 0;
		(*raiz)->fb = 0;
	} else if(aux->esq != NULL && aux->dir != NULL){
		aux->fb = 0;
		(*raiz)->fb = 1;
	} else if(aux->esq == NULL){
		aux->fb = 1;
		(*raiz)->fb = 1;
	} else{
		aux->fb = -1;
		(*raiz)->fb = 1;
	}
}

/*	a
*	 \
* 	  b      ->	  b
*      \		 / \
*    	c		a   c
*/
void rotacaoSimplesEsquerda(NoArvBinariaAVL **raiz){
	assert(raiz);
	if(*raiz == NULL) return;

	NoArvBinariaAVL *aux = *raiz;
	*raiz = (*raiz)->dir;
	aux->dir = (*raiz)->esq;
	(*raiz)->esq = aux;

	if(aux->esq == NULL && aux->dir == NULL){
		aux->fb = 0;
		(*raiz)->fb = 0;
	} else if(aux->esq != NULL && aux->dir != NULL){
		aux->fb = 0;
		(*raiz)->fb = -1;
	} else if(aux->esq == NULL){
		aux->fb = 1;
		(*raiz)->fb = -1;
	} else{
		aux->fb = -1;
		(*raiz)->fb = -1;
	}
}

/*		c 		  c
*	   /	     /
* 	  a    ->   b	->   b
*      \	   /  		/ \
*    	b	  a		   a   c
*/
void rotacaoDuplaDireita(NoArvBinariaAVL **raiz){
	assert(raiz);
	if(*raiz == NULL) return;
	
	// primeira rotacao
	NoArvBinariaAVL *aux = (*raiz)->esq;
	(*raiz)->esq = (*raiz)->esq->dir;
	aux->dir = (*raiz)->esq->esq;
	(*raiz)->esq->esq = aux;

	// segunda rotacao
	aux = *raiz;
	(*raiz) = (*raiz)->esq;
	aux->esq = (*raiz)->dir;
	(*raiz)->dir = aux;

	short int dir=0;
	short int esq=0;

	if(aux->esq == NULL && aux->dir == NULL){
		aux->fb = 0;
	} else if(aux->esq != NULL && aux->dir != NULL){
		aux->fb = 0;
		dir = 1;
	} else if(aux->esq == NULL){
		aux->fb = 1;
		dir = 1;
	} else{
		aux->fb = -1;
		dir = 1;
	}

	if((*raiz)->esq->esq == NULL && (*raiz)->esq->dir == NULL){
		(*raiz)->esq->fb = 0;
	} else if((*raiz)->esq->esq != NULL && (*raiz)->esq->dir != NULL){
		(*raiz)->esq->fb = 0;
		esq = 1;
	} else if((*raiz)->esq->esq == NULL){
		(*raiz)->esq->fb = 1;
		esq = 1;
	} else {
		(*raiz)->esq->fb = -1;
		esq = 1;
	}

	(*raiz)->fb = dir - esq;
}

/*		a 		 a
*	     \	      \
* 	      c  ->    b	->   b
*        /	        \  		/ \
*    	b	  		 c     a   c
*/
void rotacaoDuplaEsquerda(NoArvBinariaAVL **raiz){
	assert(raiz);
	if(*raiz == NULL) return;

	// primeira particao
	NoArvBinariaAVL *aux = (*raiz)->dir;
	(*raiz)->dir = (*raiz)->dir->esq;
	aux->esq = (*raiz)->dir->dir;
	(*raiz)->dir->dir = aux;

	// segunda particao
	aux = *raiz;
	*raiz = (*raiz)->dir;
	aux->dir = (*raiz)->esq;
	(*raiz)->esq = aux;
	
	short int dir=0;
	short int esq=0;

	if(aux->esq == NULL && aux->dir == NULL){
		aux->fb = 0;
	} else if(aux->esq != NULL && aux->dir != NULL){
		aux->fb = 0;
		esq = 1;
	} else if(aux->esq == NULL){
		aux->fb = 1;
		esq = 1;
	} else{
		aux->fb = -1;
		esq = 1;
	}

	if((*raiz)->dir->esq == NULL && (*raiz)->dir->dir == NULL){
		(*raiz)->dir->fb = 0;
	} else if((*raiz)->dir->esq != NULL && (*raiz)->dir->dir != NULL){
		(*raiz)->dir->fb = 0;
		dir = 1;
	} else if((*raiz)->dir->esq == NULL){
		(*raiz)->dir->fb = 1;
		dir = 1;
	} else {
		(*raiz)->dir->fb = -1;
		dir = 1;
	}

	(*raiz)->fb = dir - esq;
}




int insere(NoArvBinariaAVL **raiz, int k){
	*raiz = (NoArvBinariaAVL*)malloc(sizeof(NoArvBinariaAVL));
	if(*raiz == NULL) return;

	(*raiz)->chave = k;
	(*raiz)->fb = 0;
	(*raiz)->dir = NULL;
	(*raiz)->esq = NULL;
	return 1;
}

void rotaciona(NoArvBinariaAVL **raiz){
	assert(raiz);

	//if((*raiz)->esq != NULL){
		if((*raiz)->fb < -1){
			if((*raiz)->esq->fb < 0)
				rotacaoSimplesDireita(raiz);
			else
				rotacaoDuplaDireita(raiz);
		}
	//} else {
		if((*raiz)->fb > 1){
			if((*raiz)->dir->fb > 0)
				rotacaoSimplesEsquerda(raiz);
			else
				rotacaoDuplaEsquerda(raiz);
		}
	//}
}

int insereAVLRec(NoArvBinariaAVL **raiz, int k){
	assert(raiz);

	if(*raiz == NULL){
		return insere(raiz, k);
	}
	if(k > (*raiz)->chave){
		int f = insereAVLRec(&((*raiz)->dir), k);
		
		(*raiz)->fb += f;
		if((*raiz)->fb > 1 || (*raiz)->fb < -1){
			rotaciona(raiz);
			return 0;
		}
		return f;
	} else {
		int f = insereAVLRec(&((*raiz)->esq), k);
		
		(*raiz)->fb -= f;
		if((*raiz)->fb > 1 || (*raiz)->fb < -1){
			rotaciona(raiz);
			return 0;
		}
		return f;
	}
}

// recebe o endereco do valor que se quer achar o proximo
NoArvBinariaAVL *enderecoProxDir(NoArvBinariaAVL **raiz){
	assert(raiz);
	if(*raiz == NULL) return NULL;

	if((*raiz)->esq != NULL){
		(*raiz)->fb += 1;

		if((*raiz)->fb > 1 || (*raiz)->fb < -1){
			NoArvBinariaAVL *root = *raiz;
			rotaciona(raiz);
			*raiz = root;
		}

		if((*raiz)->esq->esq == NULL) {
			if((*raiz)->esq->dir == NULL){
				NoArvBinariaAVL *aux = (*raiz)->esq;
				(*raiz)->esq = NULL;
				return aux;
			} else {
				NoArvBinariaAVL *aux = ((*raiz)->esq);
				(*raiz)->esq = (*raiz)->esq->dir;
				return aux;
			}
		}
		return enderecoProxDir(&((*raiz)->esq));
	} else {
		if((*raiz)->dir == NULL)
			return *raiz;
		NoArvBinariaAVL *aux = ((*raiz)->dir);
		(*raiz)->dir = (*raiz)->dir->dir;
		return aux;
	}
}

int deletaNoAVLRec(NoArvBinariaAVL **raiz, int k){
	assert(raiz);
	if(*raiz == NULL) return -1;

	if(k > (*raiz)->chave) {
		int fb = deletaNoAVLRec(&((*raiz)->dir), k);
		(*raiz)->fb -= fb;
		if((*raiz)->fb > 1 || (*raiz)->fb < -1){
			rotaciona(raiz);
			return 0;
		}
		return fb;
	} else if(k < (*raiz)->chave) {
		int fb = deletaNoAVLRec(&((*raiz)->esq), k);
		(*raiz)->fb += fb;
		if((*raiz)->fb > 1 || (*raiz)->fb < -1){
			rotaciona(raiz);
			return 0;
		}
		return fb;
	} else if((*raiz)->dir == NULL && (*raiz)->esq == NULL){
		free(*raiz);
		*raiz = NULL;
		return 1;
	} else {
		NoArvBinariaAVL *prox = enderecoProxDir(&((*raiz)->dir));
		if(prox == NULL) return -1;
		
		(*raiz)->chave = prox->chave;
		free(prox);
		prox = NULL;

		(*raiz)->fb -= 1;
		return 0;
	}
}
