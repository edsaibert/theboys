#ifndef EVENTOS_H
#define EVENTOS_H

#include "atributos.h"
#include "entidades.h"


bool chega(entidade_t* entidade);       // idFuncao : 0

bool missao(entidade_t* entidade);      // idFuncao : 1

bool espera(entidade_t* entidade);      // idFuncao : 2

bool desiste(entidade_t* entidade);     // idFuncao : 3

bool avisa(entidade_t* entidade);       // idFuncao : 4

bool entra(entidade_t* entidade);       // idFuncao : 5

bool sai(entidade_t* entidade);         // idFuncao : 6

bool viaja(entidade_t* entidade);       // idFuncao : 7

#endif