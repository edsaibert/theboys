// Arquivo auxiliar (includes e defines)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifndef ATRIBUTOS
#define ATRIBUTOS

#define T_INICIO		0
#define T_FIM_DO_MUNDO	525600
#define N_TAMANHO_MUNDO 200000
#define N_HABILIDADES	10
#define N_HEROIS		N_HABILIDADES * 5
#define N_BASES			(N_HEROIS) / 6
#define N_MISSOES		T_FIM_DO_MUNDO / 100

#define MAX_PACIENCIA	100
#define MAX_VELOCIDADE	5000

#define MIN_VELOCIDADE	50
#define MIN_HAB_MISSAO	6

#endif
