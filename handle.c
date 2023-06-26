//
// Created by rafael on 11-05-2022.

#include "operacoes.h"

void handle(STACK *s,char *token,STACK_ELEM vars[]) {
    if (operacao1(s, token) || operacao2(s, token,vars) || operacao3(s,token,vars) || operacao4(s,token) || val(s, token)) {}
}

int val(STACK*s,char*token) {
    addStack(token,s);
    return 1;
}