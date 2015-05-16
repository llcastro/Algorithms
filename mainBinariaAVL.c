#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binariaAVL.h"

int main(){

	srand(time(NULL));
	
	NoArvBinariaAVL *raiz = NULL;

	// 14, 17, 11, 7, 53, 4, 13, 12, 10, 9
	/*
	insereAVLRec(&(raiz), 14);
	insereAVLRec(&(raiz), 17);
	insereAVLRec(&(raiz), 11);
	insereAVLRec(&(raiz), 7);
	insereAVLRec(&(raiz), 53);
	insereAVLRec(&(raiz), 4);
	insereAVLRec(&(raiz), 13);
	insereAVLRec(&(raiz), 12);
	insereAVLRec(&(raiz), 10);
	insereAVLRec(&(raiz), 9);
	insereAVLRec(&(raiz), 90);
	insereAVLRec(&(raiz), 15);
	*/
	int i;
	for(i=0; i<10;i++){
		insereAVLRec(&(raiz), rand()%100);
	}

	printPreOrdem(raiz);

	//printf("\n%d\n", raiz->esq->esq->fb);


	return 0;
}