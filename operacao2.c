//
// Created by rafael on 17-04-2022.
//
#include "operacoes.h"

//!Percorre todas as operaçoes do guião 2.

int operacao2 (STACK *s,char *token,STACK_ELEM vars[]){
    if(dupe(s,token)|| ord3(s,token)|| pops(s,token)|| ord2(s,token)|| changeTipe)
        return 1;
    else return 0;
}

//! Duplica o elemento do topo da STACK, caso o valor do token seja "_" .

int dupe (STACK *s, char *token){
    if (strcmp(token, "_") == 0) {
        STACK_ELEM x;

        if (pop(s, &x) == 0){
            push(x,s);
            push(x,s);
        }
        return 1;
    }
    return 0;
}

//! Troca a ordem dos 3 elementos no topo da stack (Ex 123 -> 231),caso o valor do token seja " @ ".

int ord3 (STACK *s, char *token){
    if (strcmp(token, "@") == 0) {
        STACK_ELEM x, y, z;

        if ((pop(s, &x) == 0)&&(pop(s, &y) == 0)&&(pop(s, &z) == 0)){
            push(y,s);
            push(x,s);
            push(z,s);
        }
        return 1;
    }
    return 0;
}

//!Retira o elemento que se encontra no topo da stack,caso o valor ddo token seja ";"

int pops (STACK *s, char *token) {
    if (strcmp(token,";")==0) {
        STACK_ELEM x;
        if (pop (s,&x) == 0) {}
        return 1;
    }
    return 0;
}

//!Troca os dois elementos do topo da stack, caso o valor do token seja "\\".

int ord2 (STACK *s, char *token) {
    if (strcmp(token,"\\")==0) {
        STACK_ELEM x,y;
        if (pop (s,&x) == 0 && pop (s,&y) == 0) {
            push (x,s);
            push (y,s);
        }
        return 1;
    }
    return 0;
}

//!Transforma um numero num caracter da tabela ascci caso o valor do token seja "c".

int forC(STACK *s, char *token){
    if (strcmp(token,"c")==0) {
        STACK_ELEM x,ret;
        if (pop (s,&x) == 0){

            if (x.t==INT)
                ret= charF((char )*(long *)x.elem);

            else if (x.t==DBL)
                ret = charF((char )*(double *)x.elem);

            else if (x.t==CHAR)
                ret = x;
        }
        push(ret,s);
        return 1;
    }
    return 0;
}

//!Transforma um caracter da tabela ascci num numero caso o valor do token seja "i".

int forI(STACK *s, char *token){
    if (strcmp(token,"i")==0) {
        STACK_ELEM x,ret;
        if (pop (s,&x) == 0){

            if (x.t==INT)
                ret = x;

            else if (x.t==DBL)
                ret = intF((int )(*(double *)x.elem));

            else if (x.t==CHAR)
                ret = intF((*(char *)x.elem));

            else if (x.t==STR) {
                char *string = strdup(x.elem);
                ret = intF(strtol(string, NULL, 10));
            }
        }
        push(ret,s);
        return 1;
    }
    return 0;
}
//!Transforma um caracter da tabela ascci num numero caso o valor do token seja "f".

int forF(STACK *s, char *token){
    if (strcmp(token,"f")==0) {
        STACK_ELEM x,ret;
        if (pop (s,&x) == 0){

            if (x.t==INT)
                ret = doubleF( (double )(*(long *)x.elem));

            else if (x.t==DBL)
                ret = doubleF(*(double *)x.elem);

            else if (x.t==CHAR)
                ret = doubleF((*(char *)x.elem));

            else if (x.t==STR) {
                ret = doubleF(strtod((char *)x.elem,NULL));
            }
        }
        push(ret,s);
        return 1;
    }
    return 0;
}
//!Converte o topo da string para caracter quando o valor do token seja "s".

int forS(STACK *s, char *token){
    if (strcmp(token,"s")==0) {
        STACK_ELEM x,ret;
        if (pop (s,&x) == 0){

            if (x.t==INT)
                ret = charF((char )(*(int *)x.elem));

            else if (x.t==DBL)
                ret = intF((char )(*(double *)x.elem));

            else
                ret=x;
        }
        push(ret,s);
        return 1;
    }
    return 0;
}

//!Copia n-ésimo elemento para o topo da stack 0 é o topo da stack

int forDollar(STACK *s, char *token){
    if (strcmp(token,"$")==0){
        STACK_ELEM x,ret;

        if (pop(s,&x)==0){
            ret = s->arr[s->sp-1-(*(int *)x.elem)];
            push(ret,s);
        }
        return 1;
    }
    return 0;
}

//!Le a linha seguinte caso nao seja nula.

int lerL(STACK *s,char *token,STACK_ELEM vars[]) {
    char linha[BUFSIZ];
    char tokenAux[BUFSIZ];
    if (strcmp(token, "l") == 0) {
        if (fgets(linha, BUFSIZ, stdin)!=NULL)
            while (sscanf(linha, "%s%[^\n]", tokenAux, linha) == 2) {
                handle(s,tokenAux,vars);
            }
        handle(s,tokenAux,vars);
        return 1;
    }
    return 0;
}