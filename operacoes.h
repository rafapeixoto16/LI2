//
// Created by rafael on 13/04/22.
//



#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define operacao1Matematica add(s,token) || sub(s, token) || div1(s, token) || mult(s, token) || resto(s,token) || des(s, token) || acc(s, token) || myExp(s, token)
#define bool ifThenElse(s,token) || equal(s,token) || negBool(s,token) ||maior(s,token) ||menor(s,token)
#define numero (x.t==INT || x.t==DBL ) && (y.t==INT ||y.t==DBL)
#define numeroChar ((x.t== CHAR && y.t!=CHAR)|| (y.t==CHAR && x.t!=CHAR))
#define variavelV ( ((copia[0]>='A') && (copia[0]<='Z')) && strlen(token)==1) || (copia[0]==':')
#define changeTipe forC(s,token) || forI(s,token) || forS(s,token) ||forDollar(s,token) || lerL(s,token,vars) ||forF(s,token)

/*!
 * Esta funçao vai percurer todas funçoes referentes ao giao 1.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao de cada simbolo da cada operaçao.
 * @return Retorna 1 caso uma da operaçoes do gião 1 tenha sido realizada, caso contraio retorna 0.
 */

int operacao1(STACK *s,char *token);

/*!
 * Esta funçao vai realizar a operaçao de acrementaçao em 1 caso token seja igual ")".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor ")", caso contrario retorna 0.
 */
int acc (STACK *s ,char *token);

/*!
 * Esta funçao vai realizar a operaçao de descrementaçao em 1 caso token seja igual "(".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "(", caso contrario retorna 0.
 */

int des (STACK *s ,char *token);

/*!
 * Esta funçao vai realizar a operaçao de soma caso token seja igual "+".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "+", caso contrario retorna 0.
 */

int add (STACK *s ,char *token);

/*!
 * Esta funçao vai realizar a operaçao de exponenciação caso token seja igual "#".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "#", caso contrario retorna 0.
 */

int myExp(STACK *s,char *token);

/*!
 * Esta funçao vai realizar a operaçao de resto de divisao inteira caso token seja igual "%".
 * @param sIndereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "%", caso contrario retorna 0.
 */

int resto(STACK *s,char *token);

/*!
 * Esta funçao vai realizar a operaçao de multiplição caso token seja igual "*".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "*", caso contrario retorna 0.
 */

int mult(STACK *s ,char *token);

/*!
 * Esta funçao vai realizar a operaçao de subtração caso token seja igual "-".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "-", caso contrario retorna 0.
 */

int sub (STACK *s ,char *token);

/*!
 * Esta funçao vai realizar a operaçao de divisao caso token seja igual "/".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "/", caso contrario retorna 0.
 */

int div1 (STACK *s ,char *token);

/*!
 * Esta funçao vai realizar a operaçao de "bitwise AND" caso token seja igual "&".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "&", caso contrario retorna 0.
 */

int and (STACK *s ,char *token);

/*!
 * Esta funçao vai realizar a operaçao de "bitwise OR" caso token seja igual "|".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "|", caso contrario retorna 0.
 */

int or  (STACK *s ,char *token);

/*!
 * Esta funçao vai realizar a operaçao de "bitwise XOR" caso token seja igual "^".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "^", caso contrario retorna 0.
 */

int xor (STACK *s ,char *token);

/*!
 * Esta funçao vai realizar a operaçao de "bitwise NOT" caso token seja igual "~".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "~", caso contrario retorna 0.
 */

int neg (STACK *s ,char *token);

/*!
 * Esta funçao adiciona o token a STACK.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna valor 1.
 */

int val (STACK *s ,char *token);

/*!
 * Esta função vai percorrer todas as opereçoes do programa.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @param vars Indereço das variaveis.
 */

void handle(STACK *s,char *token,STACK_ELEM vars[]);

/*!
 * Esta funçao vai percurer todas funçoes referentes ao giao 2.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @param vars Indereço das lista das variaveis.
 * @return Retorna 1 caso o token tenha o valor de uma operação do giao 2, caso contrario retorna 0.
 */

int operacao2(STACK *s,char *token,STACK_ELEM vars[]);

/*!
 * Esta funçao vai realizar a operaçao de duplicao (duplica o topo da STACK), caso token seja igual "_".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "_", caso contrario retorna 0.
 */

int dupe (STACK *s ,char *token);

/*!
 * Esta funçao vai realizar a operaçao que troca 3 elementos do topo STACK caso token seja igual "@@".
 * EX: 123 -> 231.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "@@", caso contrario retorna 0.
 */

int ord3 (STACK *s ,char *token);

/*!
 * Esta funçao vai dar da pop ao topo da STACK caso token seja igual ";".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor ";", caso contrario retorna 0.
 */

int pops (STACK *s ,char *token);

/*!
 * Esta funçao vai trocar dois elementos do topo da STACK caso token seja igual "\\".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "\\", caso contrario retorna 0.
 */

int ord2 (STACK *s ,char *token);

/*!
 * Esta funçao vai converter o elemento do topo da STACK para um caracter ,caso token seja igual "c".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "c", caso contrario retorna 0.
 */

int forC (STACK *s ,char *token);

/*!
 * Esta funçao vai converter o elemento do topo da STACK para um inteiro ,caso token seja igual "i".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "i", caso contrario retorna 0.
 */

int forI (STACK *s ,char *token);

/*!
 * Esta funçao vai converter o elemento do topo da STACK para uma string ,caso token seja igual "s".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "s", caso contrario retorna 0.
 */

int forS (STACK *s ,char *token);

/*!
 * Esta funçao vai converter o topo da STACK para um numero decimal ,caso token seja igual "f".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "f", caso contrario retorna 0.
 */
int forF (STACK *s ,char *token);

/*!
 * Esta funçao vai n elemento da STACK onde n é o elemento do topo da STACK ,caso token seja igual "$".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "$", caso contrario retorna 0.
 */

int forDollar(STACK *s ,char *token);

/*!
 * Esta funçao vai a proxima linha do ficheiro caso nao seja null e adiciona a STACk ,caso o token seja "l".
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @param vars Indereço das lista de variaveis.
 * @return Retorna 1 caso o token tenha o valor "l", caso contrario retorna 0.
 */

int lerL(STACK *s ,char *token,STACK_ELEM vars[]);

/*!
 * Esta funçao vai percurer todas funçoes referentes ao giao 3.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @param vars Indereço da lista das variaveis.
 * @return Retorna 1 caso o token tenha o valor de uma operação do giao 2, caso contrario retorna 0.
 */

int operacao3 (STACK *s,char *token,STACK_ELEM *vars);

/*!
 * Esta funçao vai dar pop de 3 elemento do topo da STACK e compara-o o 3 ( do topo).Caso esse elemento seja
 * diferente de 0 retorna o primeiro,caso contrario retorna segundo. EX 7 2 3 ? -> 2
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "?", caso contrario retorna 0.
 */

int ifThenElse(STACK *s ,char *token);

/*!
 * Esta funçao vai dar pop a 2 elementos.Caso sejam iguais os dois elemento vai dar push do numero 1 para a STACK,
 * caso contrario retorna o numero 0.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "=", caso contrario retorna 0.
 */

int equal (STACK *s,char *token);

/*!
 * Esta funçao vai troca o "valor do elemento" .Caso o elemento seja igual ao valor 0 retorna o numero 1,
 * caso contrario retorna para a STACK o numero 0.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "!", caso contrario retorna 0.
 */

int negBool (STACK *s,char *token);

/*!
 * Esta funçao vai dar pop a dois elementos e vai retornar 1 caso o primeiro elemento seja maior que segundo, e 0
 * caso contrario. EX 1 2 >  -> 0.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor ">", caso contrario retorna 0.
 */

int maior (STACK *s,char *token);

/*!
 * Esta funçao vai dar pop a dois elementos e vai retornar 1 caso o primeiro elemento seja menor que segundo, e 0
 * caso contrario. EX 1 2 >  -> 1.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "<", caso contrario retorna 0.
 */

int menor (STACK *s,char *token);

/*!
 * Esta funçao vai dar pop a 2 elementos e vai retornar o maior. EX 2 3 e>  -> 3.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "e>", caso contrario retorna 0.
 */

int maiorElem (STACK *s,char *token);

/*!
 * Esta funçao vai dar pop a 2 elementos e vair retornar o menor. EX 2 3 e< -> 2.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "e<", caso contrario retorna 0.
 */

int menorElem (STACK *s,char *token);

/*!
 * Esta funçao vai dar pop a 2 elementos caso um deles seja 0 retorna o outro elemento,
 * caso contraio retorna o primeiro elemento.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "e|", caso contrario retorna 0.
 */

int orElem (STACK *s, char *token);

/*!
 * Esta funçao vai dar pop a 2 elementos caso um deles seja 0 retorna 0, caso nenhum seja 0 retorna o maior entre os
 * 2 elementos.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "e&", caso contrario retorna 0.
 */

int andElem (STACK *s, char *token);

/*!
 * Esta funçao vai dar push a um elemento caso o token seja um letra maiuscula ou vai dar pop ao topo da stack e atribuir
 * esse elemento a variavel EX A -> 10, 10 :D D -> 1010.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @param vars Indereço da lista de variaveis.
 * @return Retorna 1 caso o token tenha o valor na primeira posiçao ":" ou seja um letra maiuscula,
 * caso contrario retorna 0.
 */

int variavel (STACK *s,char *token,STACK_ELEM *vars);

/*!
 * Esta funçao recebe um elemento e duplica-o.
 * @param x Elemento a ser duplicado.
 * @return Retorna o indereço do elemento duplicado.
 */

STACK_ELEM *dupElem (STACK_ELEM x);

/*!
 * Esta funçao vai percurer todas funçoes referentes ao giao 4.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha sido realizada alguma das operaçoes do giao 4, caso contrario retorna 0.
 */

int operacao4 (STACK *s,char *token);

/*!
 * Esta funçao da pop a 1 elemento caso seja um caracter ou um inteiro vai criar uma ARR desde menor
 * caracter(a)/inteiro(0) , ate chegar ao anterior do elemento. EX 5 , -> 01234
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "," , caso contrario retorna 0.
 */

int range (STACK *s, char *token);

/*!
 * Esta funçao vai criar um elemento do tipo ARR (cria uma STACK).
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "]", caso contrario retorna 0.
 */

int arrayMake (STACK *s ,char *token);

/*!
 * Esta funçao le todas as linhas do terminal enquanto for diferente a NULL.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "t", caso contrario retorna 0.
 */

int leTodasAsLinhas (STACK *s ,char *token);

/*!
 * Esta funçao identifica uma string e da push na STACK.
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor ' " ', caso contrario retorna 0.
 */

int stringMake (STACK* ,char *token);

/*!
 * Esta funçao separa uma STR ou ARR por espaços (' ').
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "S/", caso contrario retorna 0.
 */

int sepWP (STACK* s ,char *token);

/*!
 * Esta funçao separa uma STR ou ARR por "new line" ("\\n")
 * @param s Indereço da STACK.
 * @param token Indereço do token para fazer a comparaçao.
 * @return Retorna 1 caso o token tenha o valor "N/", caso contrario retorna 0.
 */

int sepNL(STACK* s ,char *token);

/*!
 * Recebe dois numeros e compara-os a ver se eles sao iguais.
 * @param x Primeiro numero
 * @param y Segundo numero
 * @return Retorna 1 se forem iguais , 0 caso sejam diferentes.
 */

int equalNum(STACK_ELEM x ,STACK_ELEM y);

/*!
 * Busca na array/string o elemento na posiçao x.
 * @param y Elemento que é array/String.
 * @param x Elemento que é um numero
 * @param s Indereço da STACK.
 */

void pushIndiceArray(STACK_ELEM y , STACK_ELEM x ,STACK *s);

/*!
 * Recebe dois numeros e analisa se x é menor do que y.
 * @param x Primeiro numero
 * @param y Segundo  numero
 * @return Retorna 1 se x menor y ,0 se x maior que y.
 */
int menorNum(STACK_ELEM x ,STACK_ELEM y);

/*!
 * Recebe dois STACK_ELEM's ( um deles é um char)  e analisa se x é menor do que y.
 * @param x Primeiro elemento
 * @param y Segundo elemento
 * @return Retorna 1 se x menor y ,0 se x maior que y.
 */

int menorChar (STACK_ELEM x ,STACK_ELEM y);

/*!
 * Esta funçao recebe dois STACK_ELEM e retorna o maior.
 * @param x Primeiro STACK_ELEM
 * @param y Segundo STACK_ELEM
 * @return Retorna o maior entre os dois.
 */

STACK_ELEM maiorEntre2 (STACK_ELEM x , STACK_ELEM y);

/*!
 * Esta funçao recebe dois STACK_ELEM e retorna o menor.
 * @param x Primeiro STACK_ELEM
 * @param y Segundo STACK_ELEM
 * @return Retorna o menor entre os dois.
 */

STACK_ELEM menorEntre2 (STACK_ELEM x , STACK_ELEM y);

/*!
 * Compara o elemento com 0.
 * @param x Elemento a ser comparado
 * @return Se o elemento for igual a 0 retorna 1 ,caso contrario retorna 0.
 */

int elemtZero (STACK_ELEM x);