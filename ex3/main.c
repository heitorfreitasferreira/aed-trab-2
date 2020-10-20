#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include ".\headers\fila.h"

int read_int();

void imprimir(Fila fila);

void clean_buffer();

int main(){
    char placa[9];

    int sair = 0, fila_criada = 0;
    Fila fila;

    while (sair != 1) {
        int op = 0;

        printf("\n\n[1] Criar fila");
        printf("\n[2] Entrada de veiculo");
        printf("\n[3] Saida de veiculo");
        printf("\n[4] Visualizacao do cenario");
        printf("\n[5] Sair\n");
        scanf("%d", &op);
        clean_buffer();

        switch (op) {
            case 1:
                if (fila_criada)
                    printf("Fila ja esta criada!");
                else {
                    fila = cria_fila();
                    fila_criada = 1;
                    printf("Fila criada!");
                }
                break;
            case 2:
                if (!fila_criada) {
                    printf("Nenhuma fila foi instanciada!");
                } else {
                    printf("Qual a placa do veiculo que deseja dar entrada: ");
                    scanf(" %8[^\n]", placa);
                    clean_buffer();

                    if(!insere_fim(fila, placa))
                        printf("Nao foi possivel inserir o veiculo!");
                    else
                        printf("Veiculo inserido!");
                }
                break;
            case 3:
                if (!fila_criada) {
                    printf("Nenhuma fila foi instanciada!");
                    break;
                } else {
                    printf("Insira a placa do carro que deve ser removido: ");
                    char remover[9];
                    scanf(" %8[^\n]", remover);
                    // Implementar remoção de um veículo em específico
                }
                break;
            case 4:
                if (!fila_criada)
                    printf("Nenhuma fila foi instanciada!");
                else
                    imprimir(fila);
                break;
            case 5:
                sair = 1;
                break;
            default:
                printf("Opcao invalida!");
                break;
        }
    };

    return 0;
}

// ==== Funções do programa aplicativo ==== //

//Imprimir
void imprimir(Fila fila){

    if (fila_vazia(fila)) {
        printf("A fila esta vazia!!");
    } else {
        int qnt = tamanho(fila);

        printf("Carros no estacionamento: %d \n", qnt);

        char **veiculos, placa[9];
        veiculos = (char**) malloc(qnt * sizeof(char*));

        for (int i = 0; i < qnt; i++)
            veiculos[i] = (char*) malloc(sizeof(char[9]));

        printf("    BOX 1       BOX 2       BOX 3       BOX 4       BOX 5   ");

        size_t i = 0;
        while (remove_ini(fila, placa)) {
            if (i > 50) {
                printf("Fila de espera: ");
            } else if (i % 5 == 0)
                printf("\n");
            printf("| %-8s |", placa);
            strcpy(veiculos[i], placa);
            i++;
        }

        for (size_t j = 0; j < qnt; j++)
            insere_fim(fila, veiculos[j]);
    }
}

//Função para limpar buffer (fflush causa UB)
void clean_buffer(){
    int c;
    while((c = getchar()) != EOF && c != '\n');
}
