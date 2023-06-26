#include <stdio.h>
#include "operacoes.h"

int main() {
    STACK *s =initStack();
    STACK_ELEM vars[26];
    initVariaveis(vars);

    char line[BUFSIZ];
    char token [BUFSIZ];

    if(fgets(line,BUFSIZ,stdin)!=NULL){
        while(sscanf(line,"%s%[^\n]",token,line)==2){
            handle(s,token,vars);
        }
        handle (s,token,vars);

        printStack(s);
        printf("\n");
    }
    return 0;
}