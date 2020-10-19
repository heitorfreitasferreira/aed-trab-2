#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dinamicStack.h"

//Verifica se o char é um operador
int op(char opDel) {
    return opDel == '+' || opDel == '-' || opDel == '/' || opDel == '*' || opDel == '^';
}

//Verifica se o char é um delimitador de abertura
int del(char opDel) {
    return opDel == '{' || opDel == '[' || opDel == '(';
}

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
        if(del(exp[i])) {
            //Olho no topo da pilha pra ver se existe um delimitador
            //de abertura, inicializo com 124 para o caso em que a pilha
            //esta vazia e que a função precedencia permita colocar o delimitador
            //atual na pilha, já que 124 >= '{' (124 >= 123)
            int topo = 124;
            dget_top(&delimitadores, &topo);  
            if(precedencia((char) topo, exp[i])) {
                if(!dpush(&delimitadores, (int) exp[i])) {
                    printf("Erro no push!");
                    esvazia_pilha(&delimitadores);
                    return 0;
                }
            } else {
                //flag -1 == precedência nao é obedecida
                flag = -1;
                break;
            }
        }
        //Se for um delimitador de fechamento, eu retiro o de abertura correspondente
        //da pilha
        if(exp[i] == '}' || exp[i] == ']' || exp[i] == ')') {
            int del;
            //Olho o elemento do topo da pilha, se der errado, é porque
            //a expressão está inválida, pois, tem um delimitador de fechamento
            //na expressão e a pilha já está vazia
            if(!dget_top(&delimitadores, &del)) {
                //flag 0 == ordem dos fechamentos divergem da ordem das aberturas
                flag = 0;
                break;
            }
            //Olho se o delimitador de fechamento da expressão está na pilha 
            //de delimitadores de abertura. Se não estiver, quer dizer que
            //o escopo está inválido, já que ocorreu um fechamento de escopo
            //sem se quer ter sua abertura correspondente
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

//Ordem de precedencia dos operadores aritméticos
//e delimitadores
int compare(char op) {
    if(op == '^')
        return 6;
    if(op == '*' || op == '/')
        return 5;
    if(op == '+' || op == '-')
        return 4;
    if(op == '{')
        return 3;
    if(op == '[')
        return 2;
    if(op == '(')
        return 1;
    return 0;    
}

//Olha se a precedencia dos operadores do topo
//é maior ou igual a que eu quero inserir
int precedencia_converte(char topo, char atual) {
    int top = compare(topo), comp = compare(atual);
    return top >= comp;
}

//Tabela de retornos:
//1 == sucesso
//0 == erro
int converte_expressao(char *exp) {
    DinStack stack = dstack_start();
    int i;
    //Percorro a expressão
    for(i = 0; i < strlen(exp); i++) {
        //Se for um operando, eu imprimo esse
        if((exp[i] >= 'a' && exp[i] <= 'z') || (exp[i] >= 'A' && exp[i] <= 'Z')) 
            printf("%c", exp[i]);
        //Se for um operador, eu coloco esse na pilha
        if(op(exp[i])) {
            //Olho no topo da pilha, inicializo com 0 para o caso em que a pilha
            //esta vazia e que a função precedencia_converte nao permita retirar o elemento
            //do topo da pilha
            int topo = 0;
            dget_top(&stack, &topo);  
            //Enquanto a precedencia do topo for maior ou igual ao elemento atual
            while(precedencia_converte((char) topo, exp[i])) {
                //Eu desempilho e imprimo os operadores 
                //Se estiver vazia, eu paro
                if(!dpop(&stack, &topo)) break;
                printf("%c", topo);
                dget_top(&stack, &topo);  
            }
            //Após desempilhar e imprimir eu simplesmente empilho o operador
            if(!dpush(&stack, (int) exp[i])) {
                printf("Erro no push!");
                esvazia_pilha(&stack);
                return 0;
            } 
        }
        //Se for um delimitador de abertura, eu coloco esse na pilha
        if(del(exp[i])) {
            //Olho no topo da pilha pra ver se existe um delimitador
            //de abertura, inicializo com 123 para o caso em que a pilha
            //esta vazia e que a função precedencia_converte permita colocar o delimitador
            //atual na pilha, já que 123 >= '{' (123 >= 123)
            int topo = 123;
            dget_top(&stack, &topo);  
            if(precedencia_converte((char) topo, exp[i])) {
                if(!dpush(&stack, (int) exp[i])) {
                    printf("Erro no push!");
                    esvazia_pilha(&stack);
                    return 0;
                }
            } else
                //Nao segue a precedencia dos delimitadores
                return 0;            
        }
        //Se for um delimitador de fechamento, eu retiro tudo até chegar
        //no delimitador de abertura correspondente
        if(exp[i] == '}' || exp[i] == ']' || exp[i] == ')') {
            int del, atual;
            //Associo o delimitador de fechamento ao de 
            //abertura correspondente
            if(exp[i] == '}') atual = '{';
            if(exp[i] == ']') atual = '[';
            if(exp[i] == ')') atual = '(';
            do {
                //Se a pilha estiver vazia eu paro
                if(!dpop(&stack, &del)) break;
                //Se o elemento removido da pilha for um delimitador de 
                //abertura diferente do atual, a expressão é inválida
                if(del != atual && (del == '{' || del == '[' || del == '('))
                    return 0;
                //Delimitador de abertura não é impresso
                if(del != atual) printf("%c", del);
            } while(del != atual);
        }
    }
    //Se a pilha não estiver vazia
    //eu desempilho e imprimo tudo
    if(!dempty_stack(stack)) {
        int op;
        do {
            dpop(&stack, &op);
            printf("%c", op);
        } while(!dempty_stack(stack));
    }
    return 1;
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
        case 2: 
            if(converte_expressao(expressao)) 
                printf("\nConvertido com sucesso!");
            else
                printf("\nNao foi possivel converter");
            break;
        /* case 3: 
            avalia_expressao(); 
            break; */
        default: 
            printf("Saindo do programa...");
    }
    return 0;
}