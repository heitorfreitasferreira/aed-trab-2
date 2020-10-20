#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/fila.h"

typedef struct {
    char vagas[max][9]; // Cada indice armazena a placa do carro estacionado na respectiva vaga
    size_t ini, // Indica indice onde está o inicio da fila
        cont; // Conta quantos carros estão estacionados no box (max. 10)
} Box_est;

struct fila{
    Box_est boxes[5];
    char fila_espera[max][9]; // Armazena as placas dos carros em espera para entrar no estacionamento
    size_t ini, // Indica o indice onde está o inicio da fila
        cont; // Conta quantos carros estão na fula de espera (max. 10)
};

Fila cria_fila(){
    Fila F = (Fila) malloc(sizeof(struct fila));

    if (F != NULL) {
        F->ini  = 0;
        F->cont = 0;
        for (size_t i = 0; i < 5; i++) {
            F->boxes[i].ini  = 0;
            F->boxes[i].cont = 0;
        }
    }

    return F;
}

// Retorna 1 se fila estiver vazia, 0 caso contrario
int fila_vazia(Fila fila){
    int teste = 0;
    if (fila->cont == 0) {
        for (size_t i = 0; i < 5; i++){
            if (fila->boxes[i].cont != 0) {
                teste = 1;
                break;
            }
        }
        if (teste == 0)
            return 1; // Fila vazia
    }   
    return 0; // Fila não vazia
}

// Verifica se a fila de espera está cheia
// Se a fila de espera estiver cheia, consequenetemente todo o estacionamento também estará
int fila_cheia(Fila fila){
    // São suportados no máximo 60 carros no estacionamento (10 vagas x 5 boxes + 10 vagas na fila de espera)
    if (tamanho(fila) == 60)
        return 1;
    return 0;
}

int insere_fim(Fila fila, char *placa){
    if (fila_cheia(fila))
        return 0;

    size_t box = 0, // Irá armazenar o indice do box mais vazio
        cont_cheio = 0; // Irá armazenar quantos boxes estão cheios
    for (size_t i = 0; i < 5; i++) {
        if (fila->boxes[i].cont == max) // Verifica se o box esta cheio
            cont_cheio++;
        if (i > 0) {
            if (fila->boxes[i].cont < fila->boxes[i-1].cont)
                box = i;
        }
    }

    if (cont_cheio == 5) { // Boxes cheios. Armazenar na fila de espera
        strcpy(
            fila->fila_espera[(fila->ini + fila->cont) % max],
            placa
        );
        fila->cont++;
    } else { // Armazenar no box mais vazio
        strcpy(
            fila->boxes[box].vagas[(fila->boxes[box].ini + fila->boxes[box].cont) % max],
            placa
        );
        fila->boxes[box].cont++;
    }

    return 1;
}

int remove_ini(Fila fila, char *placa){
    if (fila_vazia(fila)) {
        return 0;
    }

    // Procura o primeiro elemento disponível para remoção no inicio
    // Verifica os boxes, caso algum veículo seja removido, traz um que esteja na fila, se houver, par ao box
    for (size_t i = 0; i < 5; i++) {
        if (fila->boxes[i].cont > 0){
            strcpy(placa, fila->boxes[i].vagas[fila->boxes[i].ini]);
            fila->boxes[i].ini = (fila->boxes[i].ini + 1) % max;
            fila->boxes[i].cont--;

            if (fila->cont != 0) {
                strcpy(
                    fila->boxes[i].vagas[(fila->boxes[i].ini + fila->boxes[i].cont) % max],
                    fila->fila_espera[fila->ini]
                );

                fila->ini = (fila->ini+1) % max; //Incremento circular
                fila->cont--; //Decremento do contador            
            }
            break;
        }
    }

    return 1;
}

// Retorna quantos carros estão no estacionamento (fila de espera + boxes)
int tamanho(Fila fila){
    size_t cont = fila->cont;

    for (size_t i = 0; i < 5; i++)
        cont += fila->boxes[i].cont;
    
    return cont;
}