#include "stack.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//!Esta funçao inicializa a STACK:
STACK *initStack()
{
    STACK *s = malloc (sizeof (STACK));
    s->sp = 0;
    s->cap =50;
    s->arr =(STACK_ELEM*)malloc((s->cap) * sizeof(STACK_ELEM));
    return s;
}

//!Insere o numero na STACK
void push(STACK_ELEM x, STACK *s){
    if (s->sp == s->cap)
    {
        s->arr = (STACK_ELEM*) realloc(s->arr, 2 * s->cap*sizeof (STACK_ELEM));
        s->cap *= 2;
    }
    s->arr[s->sp] = x;
    s->sp += 1;
}

//!Tira o elemento da stack e coloca-o no endereço x
int pop(STACK *s, STACK_ELEM *x){

    if (s->sp == 0)
        return 1;
    s->sp -= 1;
    *x = s->arr[s->sp];
    return 0;
}

//! Retorna um char na forma CHAR
STACK_ELEM charF (char letra){
    char *arrChar=(char*)malloc(sizeof (char));
    *arrChar = letra;
    STACK_ELEM elem ={CHAR,arrChar};
    return elem;
}

//!Retorna um inteiro na forma INT.
STACK_ELEM intF (long inteiro){
    long *arrInt =(long *) malloc(sizeof (long ));
    *arrInt = inteiro;
    STACK_ELEM elem={INT,arrInt};
    return elem;
}

//!Retorna um double na forma DBL.
STACK_ELEM doubleF(double decimal){
    double *arrDouble =(double *) malloc(sizeof (double));
    *arrDouble=decimal;
    STACK_ELEM elem={DBL,arrDouble};
    return elem;
}

//!Retorna uma array de caracters na forma de STR.
STACK_ELEM stringF(char *letras){
    char *arrStr =strdup(letras);
    STACK_ELEM elem ={STR,arrStr};
    return elem;
}

STACK_ELEM arrayF(STACK *array){
    STACK_ELEM elem={ARR,array};
    return elem;
}

//!Print dos elemento da Stack.
void printStack(STACK *s){

    for (int i=0; i<s->sp;i++){
        auxPrintS(s->arr[i]);

    }
}

//!Auxiliar ao printStack.
void auxPrintS(STACK_ELEM elem){

    if (elem.t == INT)
        printf("%ld",*(long *)elem.elem);

    else if (elem.t == DBL)
        printf("%g",*(double *)elem.elem);

    else if (elem.t == CHAR)
        putchar(*(char *)elem.elem);

    else if (elem.t == STR)
        printf("%s",(char *)elem.elem);

    else if (elem.t==ARR)
        printStack((STACK*)elem.elem);
}

//!Adiciona uma string a Stack conforma seja int,char...
void addStack(char *token,STACK *s){
    char *string=strdup(token);
    if (eInt(string)){
        int i;
        sscanf(token, "%dl",&i);
        push(intF(i),s);

    } else if (eDouble(string)){
        float i;
        sscanf(token,"%g",&i);
        push(doubleF(i),s);

    }else if (eChar(string)){
        char i ;
        sscanf(token,"%c",&i);
        push(charF(i),s);

    }
    else {
        push(stringF(string),s);
    }
}

//!Compara uma string e ve se ela é um char.
int eChar(char *string){
    int i =0;
    if (isalpha(string[i])&&string[i+1]=='\0')
        return 1;
    else
        return 0;
}

//!Compara uma string e ve se ela é um double.
int eDouble(char *string){
    for (int i = 0; string[i]!= '\0'; i++)
    {
        if (string[i]=='-' && (isdigit(string[i+1]))){}

        else if (string[i]=='.')
            return 1;
        else if (isdigit(string[i]) == 0)
            return 0;
    }
    return 0;
}

//!Compara uma string e ve se ela é um inteiro.
int eInt (char *string){
    for (int i = 0; string[i]!= '\0'; i++)
    {
        if (string[i]=='-' && (isdigit(string[i+1]))){}

        else if (isdigit(string[i]) == 0)
            return 0;
    }
    return 1;
}

void initVariaveis(STACK_ELEM vars[]){;
    for (int i = 0; i < 25; i++) {
        vars[i] = intF(i + 10);
    }

    free(vars[13].elem);
    free(vars[18].elem);
    free(vars[23].elem);
    free(vars[24].elem);
    free(vars[25].elem);
    vars[13] = charF('\n');
    vars[18] = charF(' ');
    vars[23] = intF(0);
    vars[24] = intF(1);
    vars[25] = intF(2);

}

void pushArrayS(STACK * s,STACK *array){
    int i =0;

    for (; i < array->sp;i++) {
        push(array->arr[i],s);
    }
}

void concatArray (STACK *s, STACK_ELEM x,STACK_ELEM y){
    if (x.t==ARR && y.t==ARR){
        pushArrayS(x.elem,y.elem);
        push(arrayF(x.elem),s);
    }
    else if (x.t==ARR){
        push(y,x.elem);
        push(x,s);
    }
    else{
        push(intF(1),y.elem);
        int i = 0,spArray=((STACK *)(y.elem))->sp-1;

        for (;i<((STACK *)(y.elem))->sp;i++) {
            ((STACK*)(y.elem))->arr[spArray]=((STACK *)y.elem)->arr[spArray-1];
            spArray--;
        }
        ((STACK*)(y.elem))->arr[0]=x;
        push(arrayF(y.elem),s);
    }
}

void concatString (STACK *s, STACK_ELEM x,STACK_ELEM y) {

    if (x.t==STR && y.t==STR){
        strcat(x.elem,y.elem);
        push(x,s);
    }
    else if (x.t==STR){
        char string;
        string=*(char *)y.elem;
        strcat(x.elem,&string);
        push(x,s);
    }
    else{
        char string[strlen(y.elem)+1];
        string[0]=*(char *)x.elem;
        char *stack =y.elem;

        int i=1;
        for (;i<=(int) strlen(y.elem);i++){
            string[i]=stack[i-1];
        }
        string[strlen(y.elem)+1]='\0';
        push(stringF(string),s);
    }

}

void multConcatArray (STACK *s, STACK *x, int rep){
    STACK *mult=initStack();
    pushArrayS(mult,x);

    for (int i = 0;i<rep-1;i++)
        pushArrayS(mult,x);

    STACK_ELEM elemento = arrayF(mult);
    push(elemento,s);
}

void multConcatString (STACK *s, STACK_ELEM x, int rep){
    char mult[strlen(x.elem)*rep];
    strcpy(mult,x.elem);
    int l = strlen(x.elem)*rep;
    int i=0;

    for(;i<rep;i++){
        strcat(mult,x.elem);
    }
    mult[l]='\0';
    push(stringF(mult),s);
    free(x.elem);
}

void separaString(STACK *s,STACK_ELEM *x ,STACK_ELEM *y){
    char *string = x->elem;
    STACK *array = initStack();

    if (strcmp(y->elem,"")==0){
        while (*string != '\0'){
            push(charF(*string),array);
            string++;
        }
    }else{

    }
    push(arrayF(array),s);
}

STACK_ELEM retiraPrimeiroArray(STACK *array){
    STACK_ELEM ret =array->arr[0];
    int i = 0;
    for (; i < array->cap-1; i++) {
        array->arr[i]=array->arr[i+1];
    }
    array->sp--;
    return ret;
}

STACK_ELEM retiraPrimeiroString(STACK_ELEM *string){
    char *s = string->elem;
    STACK_ELEM ret = charF(s[0]);
    s++;
    string->elem=s;
    return ret;
}
