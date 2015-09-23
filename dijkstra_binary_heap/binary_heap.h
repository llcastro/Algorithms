#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int peso;
    int id;
    struct node *pai;
    struct node *esq;
    struct node *dir;
} node;

typedef struct listaHeap {
    struct node *no;
    int peso;
    int idNo;
    int tam;
} listaHeap;

// imprime a chave de cada no na arvore em Pre Ordem.
void preOrdem(node *root);

// recebe um no qualquer de uma arvore e busca a raiz.
node *buscaRoot(node *root);

// busca o menor no a esquerda do no recebido.
node *buscaMenorEsq(node **root);

// busca o maior no a direita do no recebido.
node *buscaMaiorDir(node **folha);

// insere um no em um heap binario.
// funcao secudaria.
node *_insereNo(node **filho, int k, int id);

// recebe dois nós e troca seus valores chave.
void swap(node *x, node *y, listaHeap *listaH);

// procedimento heapify bottom up.
void heapify_bottom_up(node **folha, listaHeap *listaH);

// insere um no em um heap binario.
// funcao principal.
node *insereNo(node **folha, int k, int id, listaHeap *listaH);

// procedimento heapify top down.
void heapify_top_down(node **root, listaHeap *listaH);

// busca o antecessor de um no no heap.
node *antecessor(node **folha);

// remove um no folha recebido.
// procedimento secundario.
void removeNo(node **folha);

// extrai menor valor do heap.
int extraiMin(node **folha, listaHeap *listaH);

// decrementa o valor chave de um nó no heap
void decreaseKey(int idNo, listaHeap *listaH, int novaChave);

/*
---- Para inserir no heap, por bottom up --------
if(é nulo) insere
if(nao tem filho && pai é nulo) insere a esquerda
if(nao tem filho && tem pai) vai pro pai
if(tem um filho na esquerda && nao tem filho na direita) insere a direita
if(tem dois filhos && tem pai) vai pro pai
if(tem dois filhos && nao tem pai && vim da direita) insere no menor da esquerda
if(tem dois filhos && vim da esquerda) insere no menor da direita

*/
