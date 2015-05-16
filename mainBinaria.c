#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binaria.h"

int main(){

	srand(time(NULL));

	NoArvBinaria *i = NULL;

	int num;
	for(num=0; num<20; num++){
		insereArvBinRec(&i, rand()%100);
	}



	//NoArvBinaria *maior = buscaEnderecoDoMaior(i);
	//NoArvBinaria *menor = buscaEnderecoDoMenor(i);
	//NoArvBinaria *kr = buscaArvBinRec(i, 16);
	//NoArvBinaria *ki = buscaArvBinIterativa(i, 4);
	NoArvBinaria **end = buscaEnderecoDoPonteiro(&i, 15);

	if(&(*end) != NULL) removeNo(&(*end));

	//printf("\nmaior chave: %p, %d\n", maior, maior->chave);
	//printf("menor chave: %p, %d\n", menor, menor->chave);
	//printf("busca recursiva: %p, %d\n", kr, kr->chave);
	//printf("busca iterativa: %p, %d\n", ki, ki->chave);

	printPreOrdem(i); printf("Pre Ordem\n");
	//printEmOrdem(i); printf("Em Ordem\n");
	//printPosOrdem(i); printf("Pos Ordem\n");


	return 0;
}