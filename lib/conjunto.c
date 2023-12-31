#include "../include/conjunto.h"

/*
##############################################
Biblioteca de operações de conjuntos
Feito em 02/10/2023 para a disciplina de Prog1
Por Eduarda Saibert =D
##############################################
*/

// Retorna uma lista vazia
conjunto_t* inicializaConjunto (void) {
    return NULL;
}

void imprimeConjunto(conjunto_t* l1, bool cont){
    conjunto_t* aux; 
    for (aux = l1; aux != NULL; aux = aux->prox){
        printf("%d ", aux->conteudo);

        // Para o caso das duplicatas
        if (cont)
            printf(": %d vezes / ", aux->cont);
    }
    // printf("\n");
}

// Preferi inserir no início pois não alteraria o exercício
bool insereConjunto(conjunto_t** inicio, int conteudo){
    conjunto_t* novo;
    novo = (conjunto_t*) malloc(sizeof(conjunto_t));

    // Verifica se o malloc foi bem sucedido
    if (novo != NULL){
        novo->conteudo = conteudo;
        novo->prox = *inicio;
        
        *inicio = novo;

        return true;
    }
    return false; 
}

// Conta os elementos de l1
int tamanhoConjunto(conjunto_t* l1){
    conjunto_t* aux;
    int cont = 0;

    for (aux = l1; aux != NULL; aux = aux->prox)
        cont++;

    return cont;
}

// Faz a concatenação das listas l1 e l2
conjunto_t* uniao(conjunto_t* l1, conjunto_t* l2){
    if (l1 == NULL || l2 == NULL) {
        return NULL;
    }

    // Encontra o ultimo nodo de l1 
    conjunto_t* aux = l1;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }

    // Concatena as duas listas 
    aux->prox = NULL;
    
    return l1;
}

// Verifica se determinado conteúdo pertence a l
bool existe(conjunto_t* l, int conteudo){
    conjunto_t* aux;

    for (aux = l; aux != NULL; aux = aux->prox){
        if (aux->conteudo == conteudo)
            return true;
    }

    return false;
}

// Faz a intersecção das listas l1 e l2
bool interseccao(conjunto_t* l1, conjunto_t* l2, conjunto_t** l3){
    conjunto_t* aux = l1;

    if (l1 == NULL || l2 == NULL)
        return false;

    for (aux = l1; aux != NULL; aux = aux->prox) {
    // Verifica se o conteúdo de l1 pertence à l2
        if (existe(l2, aux->conteudo)) 
        // Verifica se esse conteúdo já pertence à l3, para evitar duplicatas
            if (!existe(*l3, aux->conteudo))
                insereConjunto(l3, (aux->conteudo));
    }    

    return true;
}

// Retorna o tamanho de l
int tamanhoLista(conjunto_t* l) {
    conjunto_t* aux = l;
    int cont = 0;

    for (aux = l; aux != NULL; aux = aux->prox)
        cont++;

    return cont;
}

bool contem(conjunto_t* l1, conjunto_t* l2){
    conjunto_t* aux = l1;

    if (l1 == NULL || l2 == NULL)
        return false;

    // Já retorna false caso um elemento de l1 não pertença a l2
    for (aux = l1; aux != NULL; aux = aux->prox){
        if (!existe(l2, aux->conteudo))
            return false;
    }

    return true;
    
}

bool igual(conjunto_t* l1, conjunto_t* l2){
    // Verifica se os tamanhos das listas são iguais
    if (contem(l1, l2) && (tamanhoLista(l1) == tamanhoLista(l2)))
        return true;

    return false;
}

// Retorna em l2 as duplicatas de l1, com a quantidade de vezes que cada aparece
bool duplicados(conjunto_t* l1, conjunto_t** l2){
    conjunto_t* aux, *temp;
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
                insereConjunto(l2, aux->conteudo);
                (*l2)->cont = cont;
            }
        }
   }

    return true;
}

bool retiraConjunto(conjunto_t** l, int conteudo){
    conjunto_t* aux = *l, *ant = NULL;

    if (!existe(*l, conteudo))
        return false;

    // Se o conteúdo estiver no início da lista
    if (aux->conteudo == conteudo){
        *l = aux->prox;
        free(aux);
        return true;
    }

    // Se o conteúdo estiver no meio ou no fim da lista
    while (aux->prox->prox != NULL && aux->prox->conteudo != conteudo){
        aux = aux->prox;
    }

    if (aux->prox->conteudo == conteudo){
        ant = aux->prox;
        aux->prox = aux->prox->prox;
        free(ant);
    }

    return true;
}

bool freeConjunto(conjunto_t* l){
    conjunto_t* aux;

    if (l == NULL)
        return false;

    while (l != NULL){
        aux = l->prox;
        free(l);
        l = aux;
    }

    return true;
}

