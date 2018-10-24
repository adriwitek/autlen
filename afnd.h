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
    Estado * estado_actual;
    Palabra * cadena_actual;
    //int contador;
    VectorIndices ** ftransicion;

}AFND;

AFND * AFNDNuevo(char * nombre, int num_estados, int num_simbolos);
void AFNDElimina(AFND * p_afnd);
AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra);
void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd);
void AFNDImprime(FILE * fd, AFND* p_afnd);
AFND * AFNDInsertaTransicion(AFND * p_afnd,
                            char * nombre_estado_i,
                            char * nombre_simbolo_entrada,
                            char * nombre_estado_f );


/*FUNCIONES AUXILIARES*/
int AFNDIndiceDeEstado(AFND * p_afnd,char * nombre);
int AFNDIndiceDeSimbolo(AFND * p_afnd,char * nombre_simbolo_entrada);


#endif //AFND_H