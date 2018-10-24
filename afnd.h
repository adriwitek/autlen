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
    int num_simbolos;
    Estado ** estados;
    Palabra * cadena_actual;
}AFND;

AFND * AFNDNuevo(char * nombre, int num_estados, int num_simbolos);
void AFNDElimina(AFND * p_afnd);
AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra);
void AFNDImprime(FILE * fd, AFND* p_afnd);

#endif //AFND_H