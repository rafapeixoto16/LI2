//
// Created by rafael on 14/04/22.
//

#include "operacoes.h"


//!Percorre todas as operaçoes do guião 1.

int operacao1(STACK *s,char *token) {
    if(operacao1Matematica || and(s,token) || or(s,token) || xor(s,token) || neg(s,token) || orElem(s,token))
        return 1;
    else
        return 0;
}

//!Acrementa o numero da topo da stack em 1, caso o token seja igual a ")".

int acc(STACK*s,char *token){
    if (strcmp(token,")")==0){
        STACK_ELEM x,ret;

        if (pop(s,&x)==0){
            if (x.t==ARR){
                pop(x.elem,&ret);
                push(x,s);
            }
            else if (x.t==INT)
                ret =intF((*(long *) x.elem )+1);

            else if (x.t==DBL)
                ret =doubleF((*(double *) x.elem)+1);

            else if (x.t==CHAR)
                ret= charF((char )(((int )*(char *)x.elem)+1));

            else if(x.t==STR){
                int tamanho = strlen(x.elem);
                char *string = x.elem;
                ret= charF(*(string+tamanho-1));
                *(string+tamanho-1)='\0';
                push(x,s);
            }
        }
        push(ret,s);
        return 1;
    }
    return 0;
}

//!Descrementa o numero da topo da stack em 1, caso o token seja igual a "(".

int des(STACK*s,char *token){
    if (strcmp(token,"(")==0){
        STACK_ELEM x,ret;

        if (pop(s,&x)==0){
            if (x.t==ARR) {
                ret = retiraPrimeiroArray((x.elem));
                push(x,s);
            }
            else if (x.t==INT)
                ret =intF((*(long *) x.elem )-1);

            else if (x.t==DBL)
                ret =doubleF((*(double *) x.elem)-1);

            else if (x.t==CHAR)
                ret= charF((char )(((int )*(char *)x.elem)-1));

            else if (x.t==STR){
                ret = retiraPrimeiroString(&x);
                push(x,s);
            }
        }
        push(ret,s);
        return 1;
    }
    return 0;
}

//!Soma os dois primeiros numero.
//!do topo da stack, caso o token seja igual "+".

int add(STACK*s,char *token) {
    if (strcmp(token,"+")==0) {
        STACK_ELEM x, y ,ret;

        if(pop(s,&y)==0 && pop(s,&x)==0) {

            if (x.t == INT && y.t == INT) {
                ret = intF(*(long *) x.elem + *(long *) y.elem);
                push(ret,s);
            }

            else if (x.t==DBL && y.t==DBL) {
                ret = doubleF(*(double *) x.elem + *(double *) y.elem);
                push(ret,s);
            }
            else if (x.t==DBL && y.t==INT ) {
                ret = doubleF(*(double *) x.elem + ((double) *(long *) y.elem));
                push(ret,s);
            }
            else if (y.t==DBL && x.t==INT ) {
                ret = doubleF(*(double *) y.elem + ((double) *(long *) x.elem));
                push(ret,s);
            }
            else if (x.t==ARR || y.t==ARR){
                concatArray(s,x,y);
            }
            else if (x.t==STR || y.t==STR)
                concatString(s,x,y);
        }
        return 1;
    }
    return 0;
}

//!Subtrai os dois primeiros numeros do topo da stack (o segundo pelo primeiro),caso o token seja igual a "-".

int sub(STACK*s,char *token){
    if(strcmp(token,"-")==0) {
        STACK_ELEM x,y,ret;

        if(pop(s,&x)==0 && pop(s,&y)==0) {

            if (x.t == INT && y.t == INT)
                ret = intF(*(long *) y.elem - *(long *) x.elem);

            else if (x.t==DBL && y.t==DBL)
                ret = doubleF(*(double *)y.elem - *(double *)x.elem);

            else if (x.t==DBL)
                ret = doubleF((double )*(long *) y.elem - *(double *)x.elem);

            else
                ret = doubleF((double )(*(double *)y.elem - *(long *)x.elem));
        }
        push(ret,s);
        return 1;
    }
    return 0;
}

//!Eleva o segundo numero do topo da stack ao primeiro, caso o token seja igual a "#".

int myExp(STACK*s,char *token) {
    if(strcmp(token,"#")==0) {
        STACK_ELEM x,y,ret;

        if(pop(s,&x)==0 && pop(s,&y)==0){

            if (x.t==INT && y.t==INT)
                ret = intF(((long )(pow(*(long *)y.elem , *(long *)x.elem))));

            else if (x.t==DBL && y.t==DBL)
                ret = doubleF(pow(*(double *)y.elem , *(double *)x.elem));

            else if (x.t==DBL)
                ret = doubleF(pow(*(long *)y.elem , *(double *)x.elem));

            else
                ret = doubleF(pow(*(double *)y.elem , *(long *)x.elem));
        }
        push(ret, s);
        return 1;
    }
    return 0;
}

//!Faz o resto entre o segundo numero do topo da stack com o primeiro, caso os valor do token seja igual a "%".

int resto(STACK*s,char *token) {
    if(strcmp(token,"%")==0) {
        STACK_ELEM x,y,ret;

        if(pop(s,&x)==0 && pop(s,&y)==0) {

            if (x.t == INT && y.t == INT)
                ret = intF(*(long *) y.elem % *(long *) x.elem);
        }
        push(ret, s);
        return 1;
    }
    return 0;
}

//!Multiplica os dois primeiros dois numeros do topo da stack,caso o valor do token seja igual a "*".

int mult(STACK*s,char *token) {
    if(strcmp(token,"*")==0) {
        STACK_ELEM x,y,ret;
        if(pop(s,&y)==0 && pop(s,&x)==0) {
            if (x.t==ARR && y.t==INT) {
                int h = (*(int *) y.elem);
                multConcatArray(s, x.elem, h);
            }
            if (x.t==STR)
                multConcatString(s,x,*(long *)y.elem);
            else if (x.t == INT && y.t == INT)
                ret = intF((*(long *) x.elem) * (*(long *) y.elem));

            else if (x.t==DBL && y.t==DBL)
                ret = doubleF((*(double *)x.elem) * (*(double *)y.elem));

            else if (x.t==DBL)
                ret = doubleF((*(double *)x.elem) * (*(long *) y.elem));

            else
                ret = doubleF((*(long *)x.elem) * (*(double *)y.elem));
        }
        push(ret,s);
        return 1;
    }
    return 0;
}


//!Divide os dois primeiros numeros do topo da stack (o segundo pelo primeiro),caso o token seja igual a "/".

int div1(STACK*s,char *token) {
    if(strcmp(token,"/")==0) {
        STACK_ELEM x,y,ret;

        if(pop(s,&x)==0 && pop(s,&y)==0){

            if (x.t==STR || y.t==ARR){
                separaString(s,&x,&y);
            }
            else if (x.t == INT && y.t == INT)
                ret = intF((*(long *) y.elem) / (*(long *) x.elem));

            else if (x.t==DBL && y.t==DBL)
                ret = doubleF((*(double *)y.elem) / (*(double *)x.elem));

            else if (x.t==DBL)
                ret = doubleF((*(long *)y.elem) / (*(double *) x.elem));

            else
                ret = doubleF((*(double *)y.elem) / (*(long *)x.elem));
        }
        push(ret, s);
        return 1;
    }
    return 0;
}

//!Pega os dois primeiros do topo das stack e compara-os bit a bit , na ocorrencia do valor do token seja igual a "&".
//!Caso ambos os bit sejam 1 retorna 1 caso contrario retorna 0.

int and(STACK*s,char *token){
    if (strcmp(token,"&")==0){
        STACK_ELEM x,y,ret;

        if(pop(s,&x)==0 && pop(s,&y)==0) {
            if (x.t == INT && y.t == INT)
                ret = intF(*(long *)x.elem & *(long *) y.elem);
        }
        push(ret,s);
        return 1;
    }
    return 0;
}
//!Pega os dois primeiros do topo das stack e compara-os bit a bit , na ocorrencia do valor do token seja igual a "|".
//!Caso um dos bit seja 1 retorna 1, senão retorna 0.

int or(STACK*s,char *token){
    if (strcmp(token,"|")==0){
        STACK_ELEM x,y,ret;

        if(pop(s,&x)==0 && pop(s,&y)==0) {
            if (x.t == INT && y.t == INT)
                ret = intF(*(long *)x.elem | *(long *) y.elem);
        }
        push(ret,s);
        return 1;
    }
    return 0;
}

//!Pega os dois primeiros do topo das stack e compara-os bit a bit , na ocorrencia do valor do token seja igual a "^".
//!Caso os bits sejam diferentes retorna 1, senão retorna 0.

int xor(STACK *s,char *token){
    if (strcmp(token,"^")==0){
        STACK_ELEM x,y,ret;

        if(pop(s,&x)==0 && pop(s,&y)==0) {
            if (x.t == INT && y.t == INT)
                ret = intF(*(long *)x.elem ^ *(long *) y.elem);
        }
        push(ret,s);
        return 1;
    }
    return 0;
}

//!Pega no numero do topo da stack e nega-o bit a bit, caso o valor token seja igual "~".
//!Caso o bit seja 1 retorna 0, e vise-versa.

int neg(STACK*s,char*token){
    if (strcmp(token,"~")==0){
        STACK_ELEM x,ret;

        if(pop(s,&x)==0) {
            if (x.t == INT) {
                ret = intF(~*(long *) x.elem);
                push(ret, s);
            }
            else if (x.t==ARR) {
                pushArrayS(s,x.elem);
            }
        }
        return 1;
    }
    return 0;
}