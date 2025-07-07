#include <stdio.h>
#include <stdlib.h>

No *EstruturaPrincipal[10];

int tam = 0;

typedef struct reg {
	int conteudo;
    struct reg *prox;
} No;

No* criarElemento(int valor){
	No *novo = (No *)malloc(sizeof(No));
	if(novo == NULL){
        printf("Falta Memoria\n");
        exit(1);
	}
	novo->conteudo = valor;
	novo->prox = NULL;
	return novo;
}

void inserirNoFinalSemCabecote(No **inicioSemCabecote, int val){
    No *novo;
    No *atual;

    novo = criarElemento(val);

    if(*inicioSemCabecote == NULL)
        *inicioSemCabecote = novo;
    else{
        atual = *inicioSemCabecote;

        while(atual->prox != NULL)
            atual = atual->prox;

        atual->prox = novo;
    }
}

void listarElementos(No* inicio){
	No *p;
	printf ("lista\n");
    for (p = inicio; p != NULL; p = p->prox)
      printf ("%d\n", p->conteudo);
}

void liberarLista(No* inicio){

	No* atual = inicio;
	No* tmp;

	while(atual != NULL){
		tmp = atual->prox;
		free(atual);
		atual = tmp;
	}
}

No* Criar_EstruturaAux(No **inicioSemCabecote, int posicao, int tam){

    printf("Informe a posição que deseja criar a estrutura auxiliar e o tamanho: n\");
    scanf("%d%d", &posicao, &tam);

    No *EstAux = (tam)*(No *)malloc(sizeof(No));
    
}

int main(){

    int opcao;

    printf("\n1. Inserir estrutura\n2. inseir elemento\n3. Listar\n4. Listar ordenado p/ cada estrutura\n5. Listar todos os números ordenados\n6. excluir elemento\n7.aumentar estrutura\n8. sair");


}