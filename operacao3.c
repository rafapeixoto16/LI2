//
// Created by rafael on 22-04-2022.
//

#include "operacoes.h"

int operacao3(STACK *s,char *token,STACK_ELEM vars[]) {
    if(bool|| maiorElem(s,token) || menorElem(s,token)|| andElem(s,token) || variavel(s,token,vars))
        return 1;
    else
        return 0;
}

int ifThenElse (STACK *s, char *token){

    if (strcmp(token, "?") == 0) {
        STACK_ELEM x,y,z;

        if (pop(s, &x) == 0 && pop(s, &y) == 0 && pop(s, &z) == 0){
            if (z.t==INT) {
                if (*(long *) z.elem)
                    push(y, s);
                else
                    push(x, s);
            }
            else if (z.t==DBL) {
                if (*(double *) z.elem)
                    push(y, s);
                else
                    push(x,s);
            }
        }

        return 1;
    }
    return 0;
}

int equal (STACK *s, char *token){

    if (strcmp(token, "=") == 0){
        STACK_ELEM x,y;

        if (pop(s, &x) == 0 && pop(s, &y) == 0){
            if(y.t==ARR || (y.t==STR && x.t!=STR))
                pushIndiceArray(y,x,s);

            else if (numero)
                push(intF( equalNum(x,y)),s);

            else
                push(intF(strcmp((char *) x.elem, (char *) y.elem) == 0), s);
        }
        return 1;
    }
    return 0;
}

int negBool (STACK *s,char *token){

    if (strcmp(token, "!") == 0){
        STACK_ELEM x;
        STACK_ELEM ret;

        if (pop(s, &x) == 0){
            if (x.t == INT)
                ret = intF(*(long *) x.elem==0);

            else if (x.t == DBL)
                ret = intF(*(double *) x.elem == 0);

            else if (x.t == CHAR)
                ret = intF(*(char *) x.elem == 0);

            else if (x.t)
                ret = intF(strlen(x.elem) == 0);

            push(ret, s);
            return 1;
        }
    }
    return 0;
}

int menor (STACK *s, char *token){

    if (strcmp(token, "<") == 0){
        STACK_ELEM x,y;
        STACK_ELEM ret;

        if (pop(s, &x) == 0 && pop(s, &y) == 0){
            if (numero){
                int i = menorNum(x,y);
                ret = intF(i);
            }
            else if (numeroChar){
                int i = menorChar(x,y);
                ret = intF(i);
            }
            else
                ret = intF(strcmp((char *)x.elem,(char *)y.elem)>0);

        }
        push(ret,s);
        return 1;
    }
    return 0;
}

//! Vẽ se o penúltimo da STACK é maior do que o último da STACK caso o token seja ">".
int maior (STACK *s, char *token){

    if (strcmp(token, ">") == 0){
        STACK_ELEM x,y;
        STACK_ELEM ret;

        if (pop(s, &x) == 0 && pop(s, &y) == 0){
            if (numero){
                int i = menorNum(y,x);
                ret = intF(i);
            }
            else if (numeroChar){
                int i = menorChar(y,x);
                ret = intF(i);
            }
            else
                ret = intF(strcmp((char *)x.elem,(char *)y.elem)<0);
        }
        push(ret,s);
        return 1;
    }
    return 0;
}


int maiorElem (STACK *s, char *token){

    if (strcmp(token, "e>") == 0) {
        STACK_ELEM x, y;
        STACK_ELEM ret;
        if (pop(s, &x) == 0 && pop(s, &y) == 0) {
            if (numero)
                ret = maiorEntre2(x, y);
            else
                ret = strcmp((char *) x.elem, (char *) y.elem) < 0 ? y : x;
        }
        push(ret,s);
        return 1;
    }
    return 0;
}


int menorElem (STACK *s, char *token){

    if (strcmp(token, "e<") == 0) {
        STACK_ELEM x, y;
        STACK_ELEM ret;
        if (pop(s, &y) == 0 && pop(s, &x) == 0) {
            if (numero)
                ret = menorEntre2(x,y);
            else
                ret = strcmp((char *) x.elem, (char *) y.elem) < 0 ? x :y;
        }
        push(ret,s);
        return 1;
    }
    return 0;
}

int orElem (STACK *s, char *token){
    if (strcmp(token, "e|") == 0) {
        STACK_ELEM x, y;
        STACK_ELEM ret;

        if (pop(s, &y) == 0 && pop(s, &x) == 0) {
            int vX = elemtZero(x);

            if (vX)
                ret=y;
            else
                ret = x;
        }
        push(ret,s);
        return 1;
    }
    return 0;
}

int andElem (STACK *s, char *token){
    if (strcmp(token, "e&") == 0) {
        STACK_ELEM x, y;
        STACK_ELEM ret;

        if (pop(s, &y) == 0 && pop(s, &x) == 0) {
            int vX = elemtZero(x);

            if (vX)
                ret=x;
            else
                ret=y;
        }
        push(ret,s);
        return 1;
    }
    return 0;
}



int variavel(STACK *s,char *token,STACK_ELEM vars[26]) {
    char *copia= strdup(token);
    STACK_ELEM x;

    if (variavelV) {
        if (copia[0] == ':') {
            if (pop(s, &x)==0)
            {
                free(vars[(int )copia[1]-65].elem);
                vars[(int )copia[1]-65] = *dupElem(x);
                push(x,s);
            }

        }
        else{
            if (vars[copia[0] - 'A'].t == INT){
                push(intF(*(int *) vars[copia[0] - 'A'].elem), s);
            }
            else if (vars[copia[0] - 'A'].t == CHAR){
                push(charF(*(char *) vars[copia[0] - 'A'].elem), s);
            }
            else if (vars[copia[0] - 'A'].t == DBL){
                push(doubleF(*(double *) vars[copia[0] - 'A'].elem), s);
            }
            else if (vars[copia[0] - 'A'].t == ARR) {
                push(vars[copia[0] - 'A'],s);
            }
            else if (vars[copia[0] - 'A'].t == STR){
                push(vars[copia[0] - 'A'],s);
            }

        }
        return 1;
    }
    return 0;
}

STACK_ELEM *dupElem (STACK_ELEM x) {
    STACK_ELEM *dup =(STACK_ELEM *) malloc(sizeof (STACK_ELEM));

    if (x.t==INT)
        *dup = intF(*(long *)x.elem);

    else if (x.t==DBL)
        *dup = doubleF(*(double *)x.elem);

    else if (x.t==CHAR)
        *dup = charF(*(char *)x.elem);

    else if (x.t==STR)
        *dup = stringF((char *)x.elem);

    else if (x.t==ARR) {
        STACK *temp =initStack();
        pushArrayS(temp,x.elem);
        *dup= arrayF(temp);
    }
    return dup;
}

int equalNum(STACK_ELEM x ,STACK_ELEM y){
    int ret;

    if (x.t==INT){
        if (y.t==INT )
            ret = *(long *) x.elem == *(long *) y.elem ? 1 : 0;

        else
            ret = (double )*(long *)x.elem == *(double *)y.elem ? 1 : 0;
    }

    else {
        if (y.t==INT )
            ret = * (double *) x.elem == (double ) *(long *) y.elem ? 1: 0;

        else
            ret = *(double *)x.elem == *(double *)y.elem ? 1 : 0 ;
    }
    return ret;
}

void pushIndiceArray(STACK_ELEM y , STACK_ELEM x ,STACK *s){
    STACK_ELEM ret;

    if(y.t==ARR && x.t==INT){
        STACK *temp=y.elem;
        ret =temp->arr[*(long *)x.elem];
        push(ret,s);
    }
    else if(y.t==STR && x.t==INT){
        char *temp = y.elem;
        push(charF(*(char *) (temp + *(long *) x.elem)), s);
    }
}
int menorNum (STACK_ELEM x ,STACK_ELEM y){
    int ret=0;

    if (x.t==INT){
        if (y.t==INT )
            ret = *(long *) x.elem > *(long *) y.elem ? 1 : 0;

        else if(y.t==DBL)
            ret = (double )*(long *)x.elem > *(double *)y.elem ? 1 : 0;
    }

    else {
        if (y.t==INT )
            ret = * (double *) x.elem > (double ) *(long *) y.elem ? 1: 0;

        else if (y.t==DBL)
            ret = *(double *)x.elem >*(double *)y.elem ? 1 : 0 ;
    }
    return ret;
}

int menorChar (STACK_ELEM x ,STACK_ELEM y){
    int ret;
    if (x.t==CHAR){
        if (y.t==INT)
            ret = *(char *) x.elem < *(long *) y.elem ? 0 : 1;

        else
            ret = *(char *)x.elem < *(double *)y.elem ? 0 : 1;
    }
    else{
        if (x.t==INT)
            ret = *(long *) x.elem < *(char *) y.elem ? 0 : 1;
        else
            ret = *(double *)x.elem < *(char *)y.elem ? 0 : 1;

    }return ret;
}

STACK_ELEM maiorEntre2 (STACK_ELEM x , STACK_ELEM y){
    STACK_ELEM ret;

    if (x.t==INT){
        if (y.t==INT )
            ret = *(long *) x.elem < *(long *) y.elem ? y : x;

        else
            ret = (double )*(long *)x.elem < *(double *)y.elem ? y : x;
    }

    else {
        if (y.t==INT )
            ret = * (double *) x.elem <(double ) *(long *) y.elem ? y : x;

        else
            ret = *(double *)x.elem < *(double *)y.elem ? y : x;
    }
    return ret;
}

int elemtZero (STACK_ELEM x){
    int ret;
    if (x.t==INT)
        ret = *(long *) x.elem == 0 ? 1 : 0;
    else if (x.t==DBL)
        ret = *(double *) x.elem == 0 ? 1 : 0;
    else if (x.t==CHAR)
        ret = *(char *)x.elem == 0 ? 1 : 0;
    else
        ret = strcmp((char *)x.elem,"\0") == 0 ? 1 : 0;
    return ret;
}

STACK_ELEM menorEntre2 (STACK_ELEM x , STACK_ELEM y){
    STACK_ELEM ret;

    if (x.t==INT){
        if (y.t==INT )
            ret = *(long *) x.elem < *(long *) y.elem ? x : y;

        else
            ret = (double )*(long *)x.elem < *(double *)y.elem ? x : y;
    }

    else {
        if (y.t==INT )
            ret = * (double *) x.elem <(double ) *(long *) y.elem ? x : y;

        else
            ret = *(double *)x.elem < *(double *)y.elem ? x : y;
    }
    return ret;
}