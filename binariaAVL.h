#ifndef ARVBINARIA_H_AVL
#define ARVBINARIA_H_AVL

#include <stdlib.h>
#include <assert.h>

struct NoArvBinariaAVL
{
	int chave;
	int fb;
	struct NoArvBinariaAVL *esq;
	struct NoArvBinariaAVL *dir;
};

typedef struct NoArvBinariaAVL NoArvBinariaAVL;

void printPreOrdem(NoArvBinariaAVL *raiz);

void rotacaoSimplesDireita(NoArvBinariaAVL **raiz);

void rotacaoSimplesEsquerda(NoArvBinariaAVL **raiz);

void rotacaoDuplaDireita(NoArvBinariaAVL **raiz);

void rotacaoDuplaEsquerda(NoArvBinariaAVL **raiz);

void rotaciona(NoArvBinariaAVL **raiz);

int insere(NoArvBinariaAVL **raiz, int k);

// insere um no em uma Arvore Binaria AVL
int insereAVLRec(NoArvBinariaAVL **raiz, int k);




#endif