#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

No *vetorPrincipal[TAM];

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/

int ehPosicaoValida(int posicao);

int criarEstruturaAuxiliar(int posicao, int tamanho){
    
    int retorno = 0;

    // se posição é um valor válido {entre 1 e 10}
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        retorno = POSICAO_INVALIDA;
    }
    posicao--; // ajusta a posição para o vetor de 0 a 9

    // a posicao pode já existir estrutura auxiliar
    if(vetorPrincipal[posicao] != NULL){
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    }
    // o tamanho nao pode ser menor que 1
    if(tamanho < 1){
        retorno = TAMANHO_INVALIDO;
    }
    vetorPrincipal[posicao] = malloc(sizeof(No));
    if(vetorPrincipal[posicao] == NULL){
        retorno = SEM_ESPACO_DE_MEMORIA;
    }
    // deu tudo certo, crie
    else{
        vetorPrincipal[posicao]->QtdElementos = 0;
        vetorPrincipal[posicao]->tam = tamanho;
        vetorPrincipal[posicao]->prox = NULL;
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor){
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;

    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        retorno = POSICAO_INVALIDA;
    }
    else{
        // testar se existe a estrutura auxiliar
        posicao--;
        if(vetorPrincipal[posicao] != NULL){
            if(vetorPrincipal[posicao]->QtdElementos < vetorPrincipal[posicao]->tam){
                //insere
                No *novo = malloc(sizeof(No));
                novo->conteudo = valor;
                novo->prox = NULL;
                No *aux = vetorPrincipal[posicao];
                while(aux->prox != NULL){
                    aux = aux->prox;
                }
                aux->prox = novo;
                vetorPrincipal[posicao]->QtdElementos++;
                retorno = SUCESSO;
            }
            else{
                retorno = SEM_ESPACO;
            }
        }
        else{
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }
    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (!ehPosicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao--; // ajusta índice (1 a 10 → 0 a 9)

    // Proteção: estrutura auxiliar não criada
    if (vetorPrincipal[posicao] == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    // Proteção: lista encadeada vazia
    if (vetorPrincipal[posicao]->prox == NULL)
        return ESTRUTURA_AUXILIAR_VAZIA;

    // Avança até o último nó
    No *aux = vetorPrincipal[posicao]->prox;
    No *ant = vetorPrincipal[posicao];

    while (aux->prox != NULL) {
        ant = aux;
        aux = aux->prox;
    }

    free(aux);
    ant->prox = NULL;
    vetorPrincipal[posicao]->QtdElementos--;

    return SUCESSO;
}


/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    int retorno;

    if (!ehPosicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }

    posicao--;

    if (vetorPrincipal[posicao] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (vetorPrincipal[posicao]->QtdElementos <= 0 || vetorPrincipal[posicao]->prox == NULL) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    No *apagar, *aux = vetorPrincipal[posicao];

    // Se o número a ser excluído estiver no primeiro nó da lista
    if (aux->prox->conteudo == valor) {
        apagar = aux->prox;
        aux->prox = apagar->prox;
        free(apagar);
        vetorPrincipal[posicao]->QtdElementos--;
        return SUCESSO;
    }

    // Busca o valor na lista
    aux = vetorPrincipal[posicao]->prox;
    while (aux->prox != NULL && aux->prox->conteudo != valor) {
        aux = aux->prox;
    }

    if (aux->prox != NULL && aux->prox->conteudo == valor) {
        apagar = aux->prox;
        aux->prox = apagar->prox;
        free(apagar);
        vetorPrincipal[posicao]->QtdElementos--;
        retorno = SUCESSO;
    } else {
        retorno = NUMERO_INEXISTENTE;
    }

    return retorno;
}


// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao){
    int retorno = 0;
    if(posicao < 1 || posicao > 10){
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){
    int retorno = 0;
    if(ehPosicaoValida(posicao) == SUCESSO){
        posicao--;
        if(vetorPrincipal[posicao] != NULL){
            if(vetorPrincipal[posicao]->QtdElementos > 0){
                No *aux = vetorPrincipal[posicao]->prox;
                int cont = 0;
                while(aux != NULL){
                    vetorAux[cont] = aux->conteudo;
                    aux = aux->prox;
                    cont++;
                }
                retorno = SUCESSO;
            }
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else{
        retorno = POSICAO_INVALIDA;
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){

    int retorno = 0;
    if(ehPosicaoValida(posicao) == SUCESSO){
        posicao--;
        if(vetorPrincipal[posicao] != NULL){
            if(vetorPrincipal[posicao]->QtdElementos > 0){
                No *aux = vetorPrincipal[posicao]->prox;
                int cont = 0;
                while(aux != NULL){
                    vetorAux[cont] = aux->conteudo;
                    aux = aux->prox;
                    cont++;
                }
                for(int i = 0; i < cont; i++){
                    for(int j = 0; j < cont; j++){
                        if(vetorAux[i] < vetorAux[j]){
                            int troca = vetorAux[j];
                            vetorAux[j] = vetorAux[i];
                            vetorAux[i] = troca;
                        }
                    }
                }
                retorno = SUCESSO;
            }
            else{
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
            }
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else{
        retorno = POSICAO_INVALIDA;
    }

    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]){
    int retorno = 0;
    int cont = 0;

    for(int i = 0; i < TAM; i++){
        if(vetorPrincipal[i] != NULL){
            if(vetorPrincipal[i]->QtdElementos > 0){
                No *aux = vetorPrincipal[i]->prox;    
                while(aux != NULL){
                    vetorAux[cont] = aux->conteudo;
                    aux = aux->prox;
                    cont++;
                }
                retorno = SUCESSO;
            }
        }
    }
    if(retorno != SUCESSO){
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]){
    int retorno = 0;
    int cont = 0;

    for(int i = 0; i < TAM; i++){
        if(vetorPrincipal[i] != NULL){
            if(vetorPrincipal[i]->QtdElementos > 0){
                No *aux = vetorPrincipal[i]->prox;    
                while(aux != NULL){
                    vetorAux[cont] = aux->conteudo;
                    aux = aux->prox;
                    cont++;
                }
                retorno = SUCESSO;
            }
        }
    }
    if(retorno != SUCESSO){
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    else if(retorno == SUCESSO){
        for(int i = 0; i < cont; i++){
            for(int j = 0; j < cont; j++){
                if(vetorAux[i] > vetorAux[j]){
                    int troca = vetorAux[j];
                    vetorAux[j] = vetorAux[i];
                    vetorAux[i] = troca;
                }
            }
        }
    }
    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho){
    int retorno = 0;
    if(ehPosicaoValida(posicao) == SUCESSO){
        posicao--;
        if(vetorPrincipal[posicao] != NULL){
            int tamAtual = vetorPrincipal[posicao]->tam;
            int tamDesejado = tamAtual + novoTamanho;
            if(tamDesejado >= 1){
                vetorPrincipal[posicao]->tam = tamDesejado;
                if(vetorPrincipal[posicao]->QtdElementos > tamDesejado){
                    while(vetorPrincipal[posicao]->QtdElementos > tamDesejado){
                        excluirNumeroDoFinaldaEstrutura(posicao + 1);
                    }
                }
            }
            else{
                retorno = NOVO_TAMANHO_INVALIDO;
            }
        }
        else{
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }
    else{
        retorno = POSICAO_INVALIDA;
    }

    return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao){
    int retorno = 0;
    if(ehPosicaoValida(posicao) == SUCESSO){
        posicao--;
        if(vetorPrincipal[posicao] != NULL){
            if(vetorPrincipal[posicao]->QtdElementos > 0){
                retorno = vetorPrincipal[posicao]->QtdElementos;
            }
            else{
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
            }
        }
        else{
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }
    else{
        retorno = POSICAO_INVALIDA;
    }

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote(){
    int retorno = 0;
    No *listaTodos = malloc(sizeof(No));
    if(listaTodos == NULL){
        return NULL;
    }
    listaTodos->prox = NULL;
    No *copiaListaGeral = listaTodos;
    for(int i = 0; i < TAM; i++){
        if(vetorPrincipal[i] != NULL){
            if(vetorPrincipal[i]->QtdElementos > 0){
                No *copiaParcial = vetorPrincipal[i]->prox;
                while(copiaParcial != NULL){
                    No *novoNo = malloc(sizeof(No));
                    if(novoNo == NULL){
                        destruirListaEncadeadaComCabecote(&listaTodos);
                        return NULL;
                    }
                    novoNo->conteudo = copiaParcial->conteudo;
                    novoNo->prox = NULL;
                    copiaListaGeral->prox = novoNo;
                    copiaListaGeral = novoNo;
                    copiaParcial = copiaParcial->prox;
                }
                retorno = SUCESSO;
            }
        }
    }
    if(retorno == SUCESSO){
        return listaTodos;
    }
    else if(retorno = 0){
        free(listaTodos);
        return NULL;
    }
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]){
    if(inicio->prox != NULL){
        No *aux = inicio->prox;
        int cont = 0;
        while(aux != NULL){
            vetorAux[cont] = aux->conteudo;
            aux = aux->prox;
            cont++;
        }
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio){
    No *aux = *inicio;
    No *proximo;
    while(aux != NULL){
        proximo = aux->prox;
        free(aux);
        aux = proximo;
    }
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar(){
    for(int i = 0; i < TAM; i++){
        vetorPrincipal[i] = NULL;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar(){
    for(int i = 0; i < TAM; i++){
        if(vetorPrincipal[i] != NULL){
            No *aux = vetorPrincipal[i];
            No *proximo;
            while(aux != NULL){
                proximo = aux->prox;
                free(aux);
                aux = proximo;
            }
        }
        vetorPrincipal[i] = NULL;
    }
}