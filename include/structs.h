#ifndef STRUCTS_H
#define STRUCTS_H

#include "fila.h"
#include "conjunto.h"

typedef struct heroi {
	int id;
	int experiencia;
	int paciencia;
	int velocidade;
	conjunto_t* habilidades;	
} heroi_t;

typedef struct base {
	int id;
	int local[2];
	int lotação;
	conjunto_t* presentes;
	fila_t* espera; // incluir bib separada para fila
} base_t;

typedef struct missao {
	int id;
	int local[2];
	conjunto_t* habilidades; 
} missao_t;

#endif



















