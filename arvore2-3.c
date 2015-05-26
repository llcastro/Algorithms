#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct noArvore23 {
	int info, info2, ninfo;
	struct noArvore23 *esq;
	struct noArvore23 *centro;
	struct noArvore23 *dir;
} noArvore23;

// retorna 1 se o no for folha, ou 0 caso contrario
int noFolha(noArvore23 *raiz) {
	if(raiz == NULL) return;

	if(((raiz)->esq == NULL) && ((raiz)->centro == NULL) && ((raiz)->dir == NULL))
		return 1;
	return 0;
}

// cria um novo no e retorna o seu endereco
// pe = ponteiro da esquerda
// pc = ponteiro do centro
// pd = ponteiro da direita
noArvore23 *criaNo(int info, int info2, int ninfo, noArvore23 *pe, noArvore23 *pc, noArvore23 *pd) {

	noArvore23  *no = (noArvore23*) malloc(sizeof(noArvore23));
	no->info = info;
	no->info2 = info2;
	no->ninfo = ninfo + 1;
	no->esq = pe;
	no->centro = pc;
	no->dir = pd;

	return no;
}

// adiciona uma nova chave a um no existente
// retorna o no que foi inserido a nova chave
noArvore23 *adicionaChave(noArvore23 *no, int info, noArvore23 *p) {
	if(no == NULL) return NULL;

	if(info > no->info) {
		no->info2 = info;
		no->dir = p;
	} else {
		no->info2 = no->info;
		no->info = info;
		no->dir = no->centro;
		no->centro = p;
	}
	no->ninfo = 2;
	return no;
}

// divide o no em dois
// rval = valor de retorna
noArvore23 *quebraNo(noArvore23 **no, int val, int *rval, noArvore23 *subarvore) {
	assert(no);
	if(*no == NULL) return NULL;

	noArvore23 *paux; // ponteiro para salvar o endereço do ponteiro para a direita

	if(val > (*no)->info2) {
		// limpa o no e salva os seus valores
		*rval = (*no)->info2;
		paux = (*no)->dir;
		(*no)->dir = NULL;
		(*no)->ninfo = 1;
		(*no)->info2 = -1;
		// cria um novo no e o retorna
		//            i1   i2  ni  pe       pc     pd
		return criaNo(val, -1, 0, paux, subarvore, NULL);
	} else {
		if(val >= (*no)->info) {
			*rval = val;
			paux = (*no)->dir;
			(*no)->dir = NULL;
			(*no)->ninfo = 1;
			//                  i1      i2  ni     pe      pc   pd
			return criaNo((*no)->info2, -1, 0, subarvore, paux, NULL);
		} else {
			*rval = (*no)->info;
			//                  i1      i2  ni        pe           pc      pd
			paux = criaNo((*no)->info2, -1, 0, (*no)->centro, (*no)->dir, NULL);
			(*no)->info2 = -1;
			(*no)->info = val;
			(*no)->ninfo = 1;
			(*no)->dir = NULL;
			(*no)->centro = subarvore;
			return paux;
		}
	}
}

// rval = valor de retorna usado na recursao
// pai = o pai do NO na descida da recursao, usado para identificar a necessidade da criacao
//		 de outra raiz para a arvore
noArvore23 *insere(noArvore23 **no, int val, int *rval, noArvore23 **pai) {
	assert(no);

	if(*no == NULL)	{
		*no = criaNo(val, -1, 0, NULL, NULL, NULL);
		return NULL;
	}

	noArvore23 *paux, *paux2;
	int vaux, promov;

	if(noFolha(*no)) {
		if((*no)->ninfo == 1) {
			*no = adicionaChave(*no, val, NULL);
			return NULL;
		} else {
			paux = quebraNo(no, val, &vaux, NULL);
			*rval = vaux;
			if(*pai == NULL) {
				*no = criaNo(*rval, -1, 0, *no, paux, NULL);
				return NULL;
			} else
				return paux;
		}
	} else {
		if(val < (*no)->info)
			paux = insere(&((*no)->esq), val, &vaux, no);
		else {
			if(((*no)->ninfo == 1) || (val < (*no)->info2))
				paux = insere(&((*no)->centro), val, &vaux, no);
			else
				paux = insere(&((*no)->dir), val, &vaux, no);
		}
	}
	if(paux == NULL)
		return NULL;
	else {
		if((*no)->ninfo == 1) {
			*no = adicionaChave(*no, vaux, paux);
			return NULL;
		} else {
			paux2 = quebraNo(no, vaux, &promov, paux);
			*rval = promov;
			if(*pai == NULL) {
				*no = criaNo(*rval, -1, 0, *no, paux2, NULL);
				return NULL;
			} else
				return paux2;
		}
	}
}


void listar(noArvore23 *raiz)
{
	if(raiz != NULL)
	{
		listar(raiz->esq);
		printf("%d\n",raiz->info);
		listar(raiz->centro);
		if(raiz->ninfo == 2)
			printf("%d\n",raiz->info2);
		listar(raiz->dir);
	}
}


int buscar(noArvore23 *raiz, int valor)
{
	int achou =0;
	if(raiz != NULL)
	{
		if(raiz->info == valor)
			return 1;
		else
		{
			if(raiz->ninfo == 2)
			{
				if(raiz->info2 == valor)
					return 1;
				else
				{
					if(raiz->info2 < valor)
						achou = buscar(raiz->dir,valor);
					else
					{
						if((raiz->info2 > valor) && (raiz->info < valor))
							achou = buscar(raiz->centro,valor);
						else
							achou = buscar(raiz->esq,valor);
					}

				}
			}
			else
			{
				if(raiz->info > valor)
					achou = buscar(raiz->esq,valor);
				else
					achou = buscar(raiz->centro,valor);
			}
		}
	}
	return achou;
}

/*
int menu()
{
int op = 0;
printf("1 - Inserir\n");
printf("2 - Buscar\n");
printf("3 - Listar\n");
printf("4 - Sair\n");
printf("Digite o numero de sua escolha!\n");
scanf("%d ",&op);
return op;
}
*/

void preOrdem(noArvore23 *no){
	if(no != NULL){
		printf("%d ", no->info);
		if(no->ninfo == 2)
			printf("%d", no->info2);
		printf("\n");
		preOrdem(no->esq);
		preOrdem(no->centro);
		preOrdem(no->dir);
	}
	return;
}


int main() {

	noArvore23 *no = NULL, *pai = NULL;
	int opcao, val, rval;

	insere(&no,10,&rval,&pai);
	insere(&no,20,&rval,&pai);
	insere(&no,24,&rval,&pai);
	insere(&no,23,&rval,&pai);
	insere(&no,15,&rval,&pai);
	insere(&no,14,&rval,&pai);
	insere(&no,17,&rval,&pai);
	insere(&no,3,&rval,&pai);
	//insere(&no,16,&rval,&pai);

	preOrdem(no);

	return 0;

}
/*
do
{
noArvore23 *pai;
pai = NULL;
opcao = menu();
switch (opcao)
{
case 1:
{
printf("Digite o numero a ser inserido!\n");
scanf("%d",&val);
insere(&no,val,&rval,&pai);
printf("\nElemento inserido com sucesso!\n\n");
break;
}
case 2:
{
printf("Digite o numero a ser buscado!\n");
scanf("%d",&val);
if(buscar(no,val))
printf("\nElemento encontrado!\n\n");
else
printf("\nElemento nao encontrado!\n\n");
break;
}
case 3:
{
printf("\n");
listar(no);
printf("\n");
break;
}
default:
{
if(opcao != 4)
printf("Opcao invalida!\n");
break;
}
}


}while(opcao != -1);
return 0;
}
*/
