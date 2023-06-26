
/**
 * Serve identificar o tipo de dados no elementos da stack.
 * O TYPE é um identificador (funciona como uma assinatura para cada elemento).
 **/

typedef enum {
    //!Tipo caracter.
    CHAR,
    //!Tipo inteiro.
    INT,
    //!Tipo double.
    DBL,
    //!Tipo string.
    STR,
    //!Tipo array.
    ARR,
    //!Tipo bloco.
    BLK
} TYPE;

/**
 * O STACK_ELEM é um tipo de dados que contem o TYPE que identifica o valor do elemento armazenado.
 * E um apontador que serve para amazenar qualquer valor.
 */

typedef struct stack_elementos {
    //! Serve para indentificar o elemento.
    TYPE t;
    //! Apontador que armazena qualquer valor.
    void *elem;
} STACK_ELEM;

/*!
 * Armazena todos os elememtos da stack, a posiçao atual (stack pointer) e a capacidade atual do array.
 *
  **/

typedef struct stack{
    //! array to store values
    STACK_ELEM *arr;
    //! stack pointer
    int sp;
    //! stack capacity
    int cap;
} STACK;

/*!
 * Esta funçao inicializa a STACK com:
 * Tamanho  incial de 30 numeros inteiros (cap),
 * Como o stack pointer (sp) a 0 (a apontar para ao posisao 0),
 * E com um array de STACK_ELEM.
 * @returns O indereço da STACK.
  **/

STACK *initStack();

/*!
 * Transforma um caracter no tipo CHAR do STACK_ELEM.
 * @param letra O caracter para ser convertido.
 * @return O char na forma CHAR de STACK_ELEM.
 */

STACK_ELEM charF  (char letra);

/*!
 * Transforma um inteiro no tipo INT do STACK_ELEM.
 * @param inteiro O inteiro para ser convertido.
 * @return O inteiro na forma INT do STACK_ELEM.
 */

STACK_ELEM intF   (long inteiro);

/*!
 * Transforma um numero decimal no tipo DBL do STACK_ELEM.
 * @param decimal O numero decimal para ser convertido.
 * @return O numero decimal na forma DBL do STACK_ELEM.
 */

STACK_ELEM doubleF(double decimal);

/*!
 * Transforma uma string no tipo STR do STACK_ELEM.
 * @param letras A string para ser convertida.
 * @return A string na forma STR do STACK_ELEM.
 */

STACK_ELEM stringF(char *letras);

/*!
 * Recebe o indereço de uma STACK e tranforma num elemento do tipo ARR do STACK_ELEM.
 * @param array Indereço de uma STACK.
 * @return Retorna uma STACK na fomra ARR do STACK_ELEM.
 */
STACK_ELEM arrayF (STACK *array);
//!FUnçao por defenir
STACK_ELEM blocoF (char *bloco);

/*!
 * Da print no ecra todos os elementos presentes na STACK.
 * @param s Recebe o indereço da Stack.
 */

void printStack(STACK *s);

/*!
 * Recebe um endereço de uma posiçao da Stack.
 * @param elem e retorna o seu elem.
 */

void auxPrintS(STACK_ELEM elem);

/*!
 * Primeiramente ve se existe espaço disponivel para adicionar o elemento.Caso exista espaço adiciona-o ao topo da STACK,
 * caso nao exista faz realloc (duplica o espaço) e adiciona o elemento de seguida adiciona-o ao topo da STACK.
 * @param x Elemento a ser adicionado a stack,
 * @param s Indereço da stack ao qual o elemento x vai ser adicionado.
 */

void push(STACK_ELEM x, STACK *s);

/*!
 * Caso exista elemento retira o e adicona-o ao elemento x.
 * @param s Indereço da stack ao qual o elemento x vai ser retirado,
 * @param x Indereço ao qual o elemento vai ser popped vai ser adionado.
 * @return Retorna um inteiro, 0 caso exista elemento para retirar , 1 caso a STACK esteja vazia (stack pointer =0)
 */

int pop(STACK *s,STACK_ELEM *x);

/*!
 * Adiciona o token a STACK conforme o tipo do elemento, inteiro e adicionado a STACK com um INT, decimal como um DBL,
 * char como CHARA e caso contraio string.
 * @param token String ao qual vai ser adicionada a stack.
 * @param s Indereço da STACK ao qual o elemento vai ser adicionado.
 */
void addStack(char *token,STACK *s);

/*!
 * Recebe uma string e ve se é composta so por inteiros.
 * @param string Indereço da string ao qual vai comparada.
 * @return Retorna 1 caso a string seja composta por numeros inteiros, 0 caso contrario.
 */
int eInt (char *string);
/*!
 * Recebe uma string e ve se é composta por numeros decimais.
 * @param string Indereço da string ao qual vai comparada.
 * @return Retorna 1 caso a string seja um numeros decimal, 0 caso contrario.
 */

int eDouble(char *string);

/*!
 * Recebe uma string e ve se ela é um unico caracter.
 * @param string Indereço da string ao qual vai ser comparada.
 * @return Retorna 1 caso a string seja um unico cacarter, 0 caso contrario.
 */

int eChar(char *string);

/*!
 * Adiciona um o conteudo da array a STACK.
 * @param s Indereço da STACK ao qual o array vai ser adicionado.
 * @param array Indereço do array.
 */

void pushArrayS(STACK * s,STACK *array);

/*!
 * Inicializa os valores pre-defenidos das variaveis.
 * @param vars Indereço da lista de variavies.
 */

void initVariaveis(STACK_ELEM vars[]);

/*!
 * Caso ambos elemento sejam ARR adiciona y em x , caso so o elemento x seja ARR entao adiciona y na ultima posiçao do ARR
 * caso y seja ARR adiciona x na primeira posiçao do ARR y.
 * @param s Indereço da STACK.
 * @param x Primeiro elemento.
 * @param y Segundo elemento.
 */

void concatArray (STACK *s, STACK_ELEM x,STACK_ELEM y);

/*!
 * Caso ambos elemento sejam STR adiciona y em x , caso so o elemento x seja STR entao adiciona y na ultima posiçao da STR
 * caso y seja STR adiciona x na primeira posiçao do STR y.
 * @param s Indereço da STACK.
 * @param x Primeiro elemento.
 * @param y Segundo elemento.
 */


void concatString (STACK *s, STACK_ELEM x,STACK_ELEM y);

/*!
 * Multiplica a STR x rep vezes e da push na STACK. EX "olaBomdia" 2 * -> "olaBomdiaolaBomdia".
 * @param s Indereço da STACK.
 * @param x String a ser multiplicada.
 * @param rep Numero de repetiçoes.
 */

void multConcatString (STACK *s, STACK_ELEM x, int rep);

/*!
 * Repete o conteudo do array x rep vezes da push do array na STACK.
 * @param s Indereço da STACK
 * @param x Conteudo do array.
 * @param rep Numero de repetiçoes.
 */

void multConcatArray (STACK *s, STACK *x, int rep);

/*!
 * \brief Separa uma STR em substrings e da push na STACK,
 * @param s Indereço da STACK.
 * @param x Indereço do primeiro elemento.
 * @param y Indereço do segundo elemento.
 */

void separaString(STACK *s,STACK_ELEM *x ,STACK_ELEM *y);

/*!
 * Recebe um array e retira o primeiro elemento.
 * @param array Indereço do array.
 * @return Retorna o elemento retirado.
 */

STACK_ELEM retiraPrimeiroArray(STACK *array);

/*!
 * Recebe uma string e retira o primeiro caracter.
 * @param string Indereço da string
 * @return Retorna o caracter retirado.
 */

STACK_ELEM retiraPrimeiroString(STACK_ELEM *string);
