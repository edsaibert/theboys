#ifndef EVENTOS_H
#define EVENTOS_H

#include "atributos.h"
#include "entidades.h"
#include "lista.h"

bool chega(lista_t** inicio);       // idFuncao : 0

bool missao(lista_t** inicio);      // idFuncao : 1

bool espera(lista_t** inicio);      // idFuncao : 2

bool desiste(lista_t** inicio);     // idFuncao : 3

bool avisa(lista_t** inicio);       // idFuncao : 4

bool entra(lista_t** inicio);       // idFuncao : 5

bool sai(lista_t** inicio);         // idFuncao : 6

bool viaja(lista_t** inicio);       // idFuncao : 7

void fim(lista_t* inicio, int numMissao);

#endif