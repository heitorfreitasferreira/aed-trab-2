#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dinamicStack.h"

//Olha se a precedencia do delimitador do topo
//é maior ou igual a que eu quero inserir
int precedencia(char topo, char atual) {
    return topo >= atual;
}

//Retornos: 
//-1 == precedência nao é obedecida 
//0 == ordem dos fechamentos divergem da ordem das aberturas
//1 == expressão válida
int valida_escopo(char *exp) {
    DinStack delimitadores = dstack_start();
    //Inicializo a flag com 2 para que verifique no final se ela 
    //foi alterada no processo 
    int i, flag = 2; 
    //Percorro a expressão
    for(i = 0; i < strlen(exp); i++) {
        //Se for um delimitador de abertura, eu coloco esse na pilha
        if(exp[i] == '{' || exp[i] == '[' || exp[i] == '(') {
            int topo = 124;
            //Olho no topo da pilha pra ver se existe um delimitador
            //de abertura, inicializo com 124 para o caso em que a pilha
            //esta vazia e que a função precedencia permita colocar o delimitador
            //atual na pilha, já que 124 >= '{' (124 >= 123)
            dget_top(&delimitadores, &topo);  
            if(precedencia((char) topo, exp[i])) {
                if(!dpush(&delimitadores, (int) exp[i])) {
                    printf("Erro no push!");
                    esvazia_pilha(&delimitadores);
                    return 0;
                }
            } else {
                //flag 2 == precedência nao é obedecida
                flag = -1;
                break;
            }
        }
        //Se for um delimitador de fechamento, eu retiro esse da pilha
        if(exp[i] == '}' || exp[i] == ']' || exp[i] == ')') {
            int del;
            //Olho o elemento do topo da pilha, se der errado, é porque
            //a expressão está inválida, pois, tem um delimitador de fechamento
            //na expressão e a pilha já está vazia
            if(!dget_top(&delimitadores, &del)) {
                flag = 0;
                break;
            }
            //Olho se o delimitador de fechamento da expressão está na pilha 
            //de delimitadores de abertura. Se não estiver, quer dizer que
            //o escopo está inválido, já que ocorreu um fechamento de escopo
            //sem se quer ter uma abertura
            if((del == '{' && exp[i] == '}') || (del == '[' && exp[i] == ']') || (del == '(' && exp[i] == ')')) 
                dpop(&delimitadores, &del);
            else {
                //flag 0 == ordem dos fechamentos divergem da ordem das aberturas
                flag = 0;
                break;
            }
        }
    }
    //Se a pilha estiver vazia e não tiver entrado em algum erro,
    //o escopo é válido
    if(dempty_stack(delimitadores) && flag == 2) 
        return 1;
    //A pilha não está vazia, então precisamos esvazia-la 
    //e retornar que o escopo é inválido
    esvazia_pilha(&delimitadores);
    return flag;
}


int main() {
    char expressao[100];
    int escolha, res;
    scanf("%[^\n]", expressao);
    printf("------EXPRESSOES------\n");
    printf("(1)Validar escopo\n");
    printf("(2)Converter expressao\n");
    printf("(3)Avaliar expressao\n");
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);
    switch(escolha) {
        case 1:
            res = valida_escopo(expressao);
            if(res == 1) 
                printf("A expressao e valida");
            else if(res == 0)
                printf("Ordem dos fechamentos divergem da ordem das aberturas da expressao");
            else
                printf("A precedencia nao e obedecida na expressao");
            break;
        /* case 2: 
            converte_expressao(); 
            break;
        case 3: 
            avalia_expressao(); 
            break; */
        default: 
            printf("Saindo do programa...");
    }
    return 0;
}