#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "binaria.h"

/*
* Autor: Luis Angelo Loss de Castro
*/

NoArvBinaria *buscaArvBinRec(NoArvBinaria *raiz, int k){
	if(raiz == NULL) return NULL;

	if(raiz->chave == k) return raiz;
	if(k < raiz->chave)
		return buscaArvBinRec(raiz->esq, k);
	return buscaArvBinRec(raiz->dir, k);
}

NoArvBinaria *buscaArvBinIterativa(NoArvBinaria *raiz, int k){

	while(raiz != NULL){
		if(raiz->chave == k) return raiz;
		if(k < raiz->chave) 
			raiz = raiz->esq;
		else 
			raiz = raiz->dir;
	}
	return NULL;
}

NoArvBinaria *buscaEnderecoDoMenor(NoArvBinaria *raiz){
	if(raiz == NULL) return NULL;

	if(raiz->esq == NULL) return raiz;
	return buscaEnderecoDoMenor(raiz->esq);
}

NoArvBinaria *buscaEnderecoDoMaior(NoArvBinaria *raiz){
	if(raiz == NULL) return NULL;

	if(raiz->dir == NULL) return raiz;
	return buscaEnderecoDoMaior(raiz->dir);
}

NoArvBinaria **buscaEnderecoDoPonteiro(NoArvBinaria **raiz, int k){
	assert(raiz);

	if(*raiz == NULL) return NULL;

	if((*raiz)->chave == k) return &(*raiz);
	if(k > (*raiz)->chave)
		return buscaEnderecoDoPonteiro(&(*raiz)->dir, k);
	return buscaEnderecoDoPonteiro(&(*raiz)->esq, k);
}

NoArvBinaria **buscaEnderecoDoPonteiroDoMenor(NoArvBinaria **raiz){
	assert(raiz);

	if(*raiz == NULL) return NULL;

	if((*raiz)->esq == NULL) return &(*raiz);
	return buscaEnderecoDoPonteiroDoMenor(&(*raiz)->esq);
}

NoArvBinaria **buscaEnderecoDoPonteiroDoMaior(NoArvBinaria **raiz){
	assert(raiz);

	if(*raiz == NULL) return NULL;

	if((*raiz)->dir == NULL) return &(*raiz);
	return buscaEnderecoDoPonteiroDoMaior(&((*raiz)->dir));
}

void removeFolha(NoArvBinaria **raiz){
	assert(raiz);

	if(*raiz == NULL) return;

	free((*raiz));
	*raiz = NULL;
}

void removeNoComSomenteUmFilho(NoArvBinaria **raiz){
	assert(raiz);
	if(*raiz == NULL) return;

	NoArvBinaria *aux;

	if((*raiz)->dir != NULL) aux = (*raiz)->dir;
	else aux = (*raiz)->esq;

	free(*raiz);
	*raiz = aux;
}

void removeNo(NoArvBinaria **raiz){
	assert(raiz);

	if(*raiz == NULL) return;

	if((*raiz)->dir != NULL && (*raiz)->esq != NULL){
		NoArvBinaria **aux = buscaEnderecoDoPonteiroDoMenor(&((*raiz)->dir));
		(*raiz)->chave = (*aux)->chave;
		removeNoComSomenteUmFilho(&(*aux));
	} else {
		removeNoComSomenteUmFilho(&(*raiz));
	}
}

void removeNo1(NoArvBinaria **raiz){
	assert(raiz);
	if(*raiz == NULL) return;

	if((*raiz)->esq != NULL && (*raiz)->dir != NULL){

	}
}

void printPreOrdem(NoArvBinaria *raiz){
	if(raiz != NULL){
		printf("%d ", raiz->chave);
		printPreOrdem(raiz->esq);
		printPreOrdem(raiz->dir);
	}
	return;
}

void printEmOrdem(NoArvBinaria *raiz){
	if(raiz != NULL){
		printEmOrdem(raiz->esq);
		printf("%d ", raiz->chave);
		printEmOrdem(raiz->dir);
	}
	return;
}

void printPosOrdem(NoArvBinaria *raiz){
	if(raiz != NULL){
		printPosOrdem(raiz->esq);
		printPosOrdem(raiz->dir);
		printf("%d ", raiz->chave);
	}
}

NoArvBinaria *insere(int k){
	NoArvBinaria *raiz = (NoArvBinaria*) malloc(sizeof(NoArvBinaria));
	if(raiz == NULL) return NULL;

	raiz->esq = NULL;
	raiz->dir = NULL;
	raiz->chave = k;
	return &(*raiz);
}

NoArvBinaria *insereArvBinRec(NoArvBinaria **raiz, int k){
	assert(raiz);

	if(*raiz == NULL) return *raiz = insere(k);
	if((*raiz)->chave == k) return *raiz;

	if(k > (*raiz)->chave){
		if((*raiz)->dir == NULL)
			return (*raiz)->dir = insere(k);
		return insereArvBinRec(&((*raiz)->dir), k);
	} else {
		if((*raiz)->esq == NULL)
			return (*raiz)->esq = insere(k);
		return insereArvBinRec(&((*raiz)->esq), k);
	}
}

NoArvBinaria *insereArvBinRec1(NoArvBinaria **raiz, int k){
	assert(raiz);

	if(*raiz == NULL) return *raiz = insere(k);
	if((*raiz)->chave == k) return *raiz;
	
	if(k > (*raiz)->chave)
		return insereArvBinRec1(&((*raiz)->dir), k);
	return insereArvBinRec1(&((*raiz)->esq), k);
}

NoArvBinaria *insereArvBinIterativa(NoArvBinaria **raiz, int k){
	if(*raiz == NULL)
		return *raiz = insere(k);

	while(1){
		if(k > (*raiz)->chave){
			if((*raiz)->dir == NULL)
				return (*raiz)->dir = insere(k);
			*raiz = (*raiz)->dir;
		} else {
			if((*raiz)->esq == NULL)
				return (*raiz)->esq = insere(k);
			*raiz = (*raiz)->esq;
		}
	}
}
