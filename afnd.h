#ifndef AFND_H
#define AFND_H

#include "alfabeto.h"
#include "estado.h"
#include "palabra.h"
#include "vector.h"
#include "relacion.h"

//Macros para la Practica 3
/*Estas macros son necesarias para las funciones de crear un afnd a partir de un simbolo,lambda o el vacion*/
#define MAX_SIZE_OF_ESTADOS 50
#define MAX_SIZE_OF_SIMBOLOS 50




typedef struct _AFND 
{
    char * nombre;
    Alfabeto * alfabeto;
    int num_estados; /*numero de estados maximos que acepta el automata*/
    int num_estados_actual; /*numero de estados INSERTADOS en el afnd*/
    int num_estados_actuales_paralelos; /* num estados en los que se esta actualmente*/
    int num_simbolos; /*numero MAXIMO de simb. --> NO contabiliza los insertados*/
    Estado ** estados;
    Estado ** estado_actuales; /*  estados en los que se esta actualmente*/
    Palabra * cadena_actual;
    VectorIndices ** ftransicion;
    Relacion * lambdaTransiciones; /*Estructura para gestionar las tansiciones lambda*/
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
int AFNDLTransicionIJ_cierre(AFND * p_afnd, int i , int j);
AFND * AFNDCierraLTransicion(AFND * p_afnd);

int AFND_isInEstadosActuales(AFND * p_afnd,int estado);
void AFNDTransita_Lmabda(AFND * p_afnd);


/*Ampliacion Practica 3 */
AFND * AFND1ODeSimbolo( char * simbolo);
AFND * AFND1ODeLambda();
AFND * AFND1ODeVacio();
AFND * AFNDAAFND1O(AFND * p_afnd);
AFND * AFND1OUne(AFND * p_afnd1O_1, AFND * p_afnd1O_2);
AFND * AFND1OConcatena(AFND * p_afnd_origen1, AFND * p_afnd_origen2);
AFND * AFND1OEstrella(AFND * p_afnd_origen);

//Funciones auxiliares
AFND * AFND1OInsertaSimbolosAFND(AFND * p_afnd_destino, AFND * p_afnd_origen);
AFND * AFND1OInsertaEstadosTransicionesAFND(AFND * p_afnd_destino, AFND * p_afnd_origen, char * prefijo_estados);
AFND * AFND1OUneLTransicion(AFND * p_afnd_destino, AFND * p_afnd_origen, char * nombre_nuevo_estado_inicial, char * nombre_nuevo_estado_final);
AFND * AFNDAAFND1O(AFND * p_afnd);

int aux_hayTransicion(AFND * p_afnd,int estado_origen, int estado_destino ,char * simbolo);

#endif //AFND_H