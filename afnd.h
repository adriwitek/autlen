#ifndef AFND_H
#define AFND_H

#include "alfabeto.h"
#include "estado.h"
#include "palabra.h"
#include "vector.h"

typedef struct _AFND 
{
    char * nombre;
    Alfabeto * alfabeto;
    int num_estados;
    int num_estados_actual;
    int num_simbolos;
    Estado ** estados;
    Palabra * cadena_actual;
}AFND;

AFND * AFNDNuevo(char * nombre, int num_estados, int num_simbolos);
void AFNDElimina(AFND * p_afnd);
void AFNDImprime(FILE * fd, AFND* p_afnd);

AFND * AFNDInsertaSimbolo(AFND * p_afnd, char * simbolo);
AFND * AFNDInsertaEstado(AFND * p_afnd, char * nombre, int tipo);
AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra);
AFND * AFNDInsertaTransicion(AFND * p_afnd, char * nombre_estado_i, char * nombre_simbolo_entrada, char * nombre_estado_f );


#endif //AFND_H