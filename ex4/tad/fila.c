#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\headers\fila.h"

typedef struct{
    char nome[20];
    int vol;
    float preco;
}Bebida;

struct no {
    Bebida info;
    struct no *prox;
};

struct fila{
    struct no *ini;
    struct no *fim;
};

Fila cria_fila(){
    Fila F = (Fila) malloc(sizeof(struct fila));

    if (F != NULL) {
        F->ini = NULL;
        F->fim = NULL;
    }

    return F;
}

int fila_vazia(Fila fila){
    if (fila->ini == NULL)
        return 1;
    return 0;
}

int insere_fim(Fila fila, char *nome, int vol, float preco){
    struct no *N = (struct no*) malloc(sizeof(struct no));
    if (N == NULL)
        return 0;

    strcpy(N->info.nome, nome);
    N->info.vol = vol;
    N->info.preco = preco;
    N->prox = NULL;

    if (fila_vazia(fila))
        fila->ini = N;
    else
        (fila->fim)->prox = N;
    fila->fim = N;

    return 1;
}

int remove_ini(Fila fila, char *nome, int *vol, float *preco){
    if (fila_vazia(fila))
        return 0;
    
    struct no *aux = fila->ini; //aux aponta para o primeiro nó

    //Retorna valor do elemento por referência
    strcpy(nome, aux->info.nome);
    *vol = aux->info.vol;
    *preco = aux->info.preco;

    //Verifica se a fila tem um único nó
    if (fila->ini == fila->fim)
        fila->fim = NULL;

    fila->ini = aux->prox; //Retira primeiro nó da fila
    free(aux); //Libera memória

    return 1;
}

int esvazia_fila(Fila fila){
    if (fila_vazia(fila))
        return 0;
    
    struct no *aux;

    while (fila->ini->prox != NULL){
        aux = fila->ini;
        fila->ini = aux->prox;
        free(aux);
    }
    fila->ini = NULL;
    fila->fim = NULL;
    return 1;
}

int apaga_fila(Fila *fila){
    if (fila_vazia(*fila)) {
        free(*fila);
        *fila = NULL;
        return 0;
    }
    
    struct no *aux;

    while ((*fila)->ini->prox != NULL){
        aux = (*fila)->ini;
        (*fila)->ini = aux->prox;
        free(aux);
    }
    
    (*fila)->ini = NULL;
    (*fila)->fim = NULL;

    free((*fila));

    (*fila) = NULL;
    return 1;
}