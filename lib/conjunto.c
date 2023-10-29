#include "../include/conjunto.h"

/*
##############################################
Biblioteca de operações de conjuntos
Feito em 02/10/2023 para a disciplina de Prog1
Por Eduarda Saibert =D
##############################################
*/

// Retorna uma lista vazia
lista_t* inicializa (void) {
    return NULL;
}

void imprimeLista(lista_t* l1, bool cont){
    lista_t* aux; 
    for (aux = l1; aux != NULL; aux = aux->prox){
        printf("%d ", aux->conteudo);

        // Para o caso das duplicatas
        if (cont)
            printf(": %d vezes / ", aux->cont);
    }
    printf("\n");
}

// Preferi inserir no início pois não alteraria o exercício
bool insereInicio(lista_t** inicio, int conteudo){
    lista_t* novo;
    novo = (lista_t*) malloc(sizeof(lista_t));

    // Verifica se o malloc foi bem sucedido
    if (novo != NULL){
        novo->conteudo = conteudo;
        novo->prox = *inicio;
        
        *inicio = novo;

        return true;
    }
    return false; 
}

// Faz a concatenação das listas l1 e l2
bool uniao(lista_t* l1, lista_t* l2, lista_t** l3){
    // Vincula o endereço de l3 à l1
    *l3 = l1;

    if (l1 == NULL || l2 == NULL) {
        return false;
    }
    
    // aux recebe o endereço de l1
    lista_t* aux = l1;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    // aux concatena as duas listas
    aux->prox = l2;
    
    return true;
}

// Verifica se determinado conteúdo pertence a l
bool existe(lista_t* l, int conteudo){
    lista_t* aux;

    for (aux = l; aux != NULL; aux = aux->prox){
        if (aux->conteudo == conteudo)
            return true;
    }

    return false;
}

// Faz a intersecção das listas l1 e l2
bool interseccao(lista_t* l1, lista_t* l2, lista_t** l3){
    lista_t* aux = l1;

    if (l1 == NULL || l2 == NULL)
        return false;

    for (aux = l1; aux != NULL; aux = aux->prox) {
    // Verifica se o conteúdo de l1 pertence à l2
        if (existe(l2, aux->conteudo)) 
        // Verifica se esse conteúdo já pertence à l3, para evitar duplicatas
            if (!existe(*l3, aux->conteudo))
                insereInicio(l3, (aux->conteudo));
    }    

    return true;
}

// Retorna o tamanho de l
int tamanhoLista(lista_t* l) {
    lista_t* aux = l;
    int cont = 0;

    for (aux = l; aux != NULL; aux = aux->prox)
        cont++;

    return cont;
}

bool contem(lista_t* l1, lista_t* l2){
    lista_t* aux = l1;

    if (l1 == NULL || l2 == NULL)
        return false;

    // Já retorna false caso um elemento de l1 não pertença a l2
    for (aux = l1; aux != NULL; aux = aux->prox){
        if (!existe(l2, aux->conteudo))
            return false;
    }

    return true;
    
}

bool igual(lista_t* l1, lista_t* l2){
    // Verifica se os tamanhos das listas são iguais
    if (contem(l1, l2) && (tamanhoLista(l1) == tamanhoLista(l2)))
        return true;

    return false;
}

// Retorna em l2 as duplicatas de l1, com a quantidade de vezes que cada aparece
bool duplicados(lista_t* l1, lista_t** l2){
    lista_t* aux, *temp;
    int cont;

    if (l1 == NULL)
        return false;

    for (aux = l1; aux != NULL; aux = aux->prox){
        cont = 0;

        if (!existe(*l2, aux->conteudo)){
            for (temp = l1; temp != NULL; temp = temp->prox)
            {
                if (temp->conteudo == aux->conteudo)
                    cont++;
            }

            if (cont > 1)
            {
                insereInicio(l2, aux->conteudo);
                (*l2)->cont = cont;
            }
        }
   }

    return true;
}

