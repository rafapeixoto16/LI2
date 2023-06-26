//
// Created by rafael on 27-04-2022.
//
#include "operacoes.h"


int operacao4 (STACK *s,char *token){
    if (range(s,token) || arrayMake(s,token) || leTodasAsLinhas(s,token) || stringMake(s,token) || sepWP(s,token) ||
        sepNL(s,token) ){
        return 1;
    }
    return 0;
}

int range (STACK *s, char *token){
    if (strcmp(token, ",") == 0) {
        STACK_ELEM x;

        if (pop(s, &x) == 0){
            if (x.t==ARR) {
                push(intF(((STACK*)x.elem)->sp),s);
            }
            else if (x.t==STR){
                push(intF(strlen(x.elem)),s);
            }

            else if (x.t==INT) {
                STACK *temp =initStack();
                int i = 0;

                for (;i<*(int *)x.elem;i++){
                    push(intF(i),temp);
                }
                push(arrayF(temp),s);
            } else if (x.t==CHAR) {
                STACK *temp = initStack();
                char i = 'a';
                for (;i<*(char *)x.elem;i++){
                    push(charF(i),temp);
                }
                push(arrayF(temp),s);
            }
        }
        return 1;
    }
    return 0;
}

int arrayMake (STACK *s ,char *token){
    if (strcmp(token, "]") == 0) {
        STACK *temp = initStack();
        STACK *aux  = initStack();
        STACK_ELEM x;

        int i = 1;

        while (i>0 &&(pop(s,&x)==0 )){
            if (strcmp((char *)x.elem," [")==0 || strcmp((char *)x.elem,"[")==0||(*(char *)x.elem)==91)
                i=0;
            else push(x,temp);
        }
        while (pop(temp,&x)==0)
            push(x,aux);
        free(temp->arr);
        free(temp);
        push(arrayF(aux),s);
        return 1;
    }
    return 0;
}

int leTodasAsLinhas (STACK *s ,char *token){
    if (strcmp(token, "t") == 0) {
        char line[BUFSIZ];
        int tamanhoAtual =0;

        while (fgets(line+tamanhoAtual,BUFSIZ,stdin)!=NULL){
            tamanhoAtual = strlen(line);
        }
        push(stringF(line),s);
        return 1;
    }
    return 0;
}

int stringMake (STACK* s ,char *token){
    int tamanhoToken = strlen(token);

    if (token[0]=='"' || token[tamanhoToken - 1]=='"'){
        if (tamanhoToken>1) {
            if (token[0]=='"') {
                char *temp = strdup((token + 1));
                int tamanho = strlen(temp);
                if (token[tamanhoToken - 1] == '"')
                    temp[tamanho - 1] = '\0';
                push(stringF(temp), s);
            } else{
                char *temp = malloc(sizeof tamanhoToken+1);
                temp[0]=' ';
                for (int i = 1; i < tamanhoToken; i++) {
                    temp[i]=token[i-1];
                }
                temp[tamanhoToken]='\0';
                push(stringF(temp),s);
            }
        }
        return 1;
    }
    return 0;
}

int sepWP (STACK* s ,char *token){
    if (strcmp(token,"S/") == 0){
        STACK_ELEM x;
        if (pop(s,&x)==0){
            if (x.t==STR){
                int stringlen = strlen(x.elem),i=0;
                char *dup= strdup(x.elem);
                for (;i<stringlen; i++) {
                    push(charF(dup[i]),s);
                    if (i+1!=stringlen)
                        push(charF(' '),s);
                }
            } else push(x,s);
        }
        return  1;
    }
    return 0;
}


int sepNL(STACK* s ,char *token) {
    if (strcmp(token,"N/") == 0){
        STACK_ELEM x;
        if (pop(s,&x)==0){

            if (x.t==STR){
                int stringlen = strlen(x.elem),i=0;
                char *dup= strdup(x.elem);
                for (;i<stringlen; i++) {
                    push(charF(dup[i]),s);
                    if (i+1!=stringlen)
                        push(charF('\n'),s);
                }
            } else push(x,s);
        }
        return  1;
    }
    return 0;
}