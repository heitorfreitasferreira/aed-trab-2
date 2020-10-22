#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include ".\headers\fila.h"

//Lê somente valor inteiro
int read_int();

//Imprimir
void imprimir(Fila fila);

//Função para limpar buffer (fflush causa UB)
void clean_buffer();

int main(){
    char nome[20];
    int vol;
    float preco;

    int sair = 0;
    Fila fila = NULL;

    while (sair != 1) {
        int op = 0;

        printf("\n\n[1] Criar fila");
        printf("\n[2] Imprimir fila");
        printf("\n[3] Inserir no final");
        printf("\n[4] Remover no inicio");
        printf("\n[5] Esvaziar fila");
        printf("\n[6] Apagar fila");
        printf("\n[7] Sair\n");
        scanf("%d", &op);
        clean_buffer();

        switch (op) {
            case 1:
                if (fila != NULL)
                    printf("Fila ja esta criada!");
                else {
                    fila = cria_fila();
                    printf("Fila criada!");
                }
                break;
            case 2:
                if (fila == NULL)
                    printf("Nenhuma fila foi instanciada!");
                else
                    imprimir(fila);
                break;
            case 3:
                if (fila == NULL) {
                    printf("Nenhuma fila foi instanciada!");
                } else {
                    printf("Qual o nome da bebida que deseja inserir: ");
                    scanf(" %19[^\n]", nome);
                    clean_buffer();

                    printf("Qual o volume de %s: ", nome);
                    vol = read_int();
                    
                    printf("Qual o preco de %s: ", nome);
                    scanf("%f", &preco);

                    if(insere_fim(fila, nome, vol, preco) == 0)
                        printf("Nao foi possivel inserir o elemento!");
                    else
                        printf("Elemento inserido!");
                }
                break;
            case 4:
                if (fila == NULL) {
                    printf("Nenhuma fila foi instanciada!");
                    break;
                } else {
                    if (!remove_ini(fila, nome, &vol, &preco))
                        printf("Falha ao remover elemento. Ele pode nao estar na fila!!");
                    else
                        printf("Elemento removido! %s foi removido.", nome);
                }
                break;
            case 5:
                if (fila == NULL) {
                    printf("Nenhuma fila foi instanciada!");
                    break;
                } else {
                if(esvazia_fila(fila))
                    printf("A fila agora esta vazia!");
                else
                    printf("A fila ja esta vazia!");
                }
                break;
            case 6:
                if (fila == NULL) {
                    printf("Nenhuma fila foi instanciada!");
                    break;
                } else {
                    apaga_fila(&fila);
                    printf("A fila foi apagada!");
                }
                break;
            case 7:
                sair = 1;
                break;
            default:
                printf("Opcao invalida!");
                break;
        }
    };
    return 0;
}

//Funcoes do programa app
int read_int(){
    char input[11]; 
    int inp_error = 1;
    while(inp_error) {
        fgets(input, sizeof(input), stdin);
        //Removendo '\n'
        input[strlen(input) - 1] = '\0';
        //Percorrendo a string a procura de caracteres não numéricos
        for (size_t i = 0; i < strlen(input); i++) {
            // 43 = '+' ASCII
            //sinais quer dizer '-' ou '+'
            //Impedindo de digitar sinas com numero antes
            if((input[i] == 43 || input[i] == '-') && (i >= 1 && isdigit(input[i-1]))) {
                printf("Insira um valor valido (inteiro): ");
                break;    
            }
            //Impedindo de digitar sinas seguidos de nada
            if ((input[i] == 43 || input[i] == '-') && (i < (strlen(input)) && input[i+1] == '\0')) {
                printf("Insira um valor valido (inteiro): ");
                break;
            }
            //Impedindo de digitar qualquer coisa que não seja digito, exceto sinais
            if(!isdigit(input[i]) && input[i] != '-' && input[i] != 43) { // 43 = '+' ASCII
                printf("Insira um valor valido (inteiro): ");
                break;
            }
            if (i == strlen(input) - 1)
                inp_error = 0;
        }
    }
    //Convertendo a string para inteiro
    return strtol(input, NULL, 10);
}

void imprimir(Fila fila){
    if (fila_vazia(fila) == 1) {
        printf("A fila esta vazia!!");
    } else {
        char nome[20];
        int vol;
        float preco;

        Fila temp = cria_fila();
        if (temp == NULL)
            printf("Erro ao imprimir!");

        printf("Fila: \n");
        size_t i = 0;
        while (remove_ini(fila, nome, &vol, &preco)) {
            printf("\n--------------");
            printf("\nNome: %s", nome);
            printf("\nVolume: %d", vol);
            printf("\nPreco: %.2f", preco);

            insere_fim(temp, nome, vol, preco);
        }
        while (remove_ini(temp, nome, &vol, &preco)) {
            insere_fim(fila, nome, vol, preco);
        }
    }
}

void clean_buffer(){
    int c;
    while((c = getchar()) != EOF && c != '\n');
}
