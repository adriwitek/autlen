#ifndef AFND_H
#define AFND_H

#include "alfabeto.h"
#include "estado.h"
#include "palabra.h"
#include "vector.h"
#include "relacion.h"

typedef struct _AFND 
{
    char * nombre;
    Alfabeto * alfabeto;
    int num_estados;
    int num_estados_actual; /*numero de estados INSERTADOS en el afnd*/
    int num_estados_actuales_paralelos; /* num estados en los que se esta actualmente*/
    int num_simbolos;
    Estado ** estados;
    Estado ** estado_actuales; /*  estados en los que se esta actualmente*/
    Palabra * cadena_actual;
    VectorIndices ** ftransicion;
    Relacion * lambdaTransiciones;
}AFND;

AFND * AFNDNuevo(char * nombre, int num_estados, int num_simbolos);
void AFNDElimina(AFND * p_afnd);
void AFNDImprime(FILE * fd, AFND* p_afnd);

/*FUNCIONES AUXILIARES*/
int AFNDIndiceDeEstado(AFND * p_afnd,char * nombre);
int AFNDIndiceDeSimbolo(AFND * p_afnd,char * nombre_simbolo_entrada);

AFND * AFNDInsertaSimbolo(AFND * p_afnd, char * simbolo);
AFND * AFNDInsertaEstado(AFND * p_afnd, char * nombre, int tipo);
AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra);
AFND * AFNDInsertaTransicion(AFND * p_afnd, char * nombre_estado_i, char * nombre_simbolo_entrada, char * nombre_estado_f );
void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd);

AFND * AFNDInicializaCadenaActual (AFND * p_afnd );
AFND * AFNDInicializaEstado (AFND * p_afnd);

void AFNDInsertaEstado_Actual(AFND * p_afnd, int indice);
void AFNDTransita(AFND * p_afnd);
int AFND_VectorIndicesVacio(AFND * p_afnd );
void AFNDImprimeConjuntoEstadosActual(FILE * fd, AFND * p_afnd);
void AFNDImprimeCadenaActual(FILE *fd, AFND * p_afnd);

/*LAMBDA TRANSICIONES*/
AFND * AFNDInsertaLTransicion(AFND * p_afnd, char * nombre_estado_i, char * nombre_estado_f );
int AFNDLTransicionIJ(AFND * p_afnd, int i , int j);
AFND * AFNDCierraLTransicion (AFND * p_afnd);

#endif //AFND_H