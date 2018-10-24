#include <stdio.h>
#include <stdlib.h>
#include<string.h>


typedef struct _Palabra{
    int tam;
    char** letras;
}Palabra;

Palabra * palabraNueva();
void palabraElimina(Palabra * p_p);
Palabra * palabraInsertaLetra(Palabra * p_p, char * letra);
void palabraImprime(FILE * fd, Palabra * p_p);
char * palabraQuitaInicio(Palabra * p_p);
int palabraTamano(Palabra * p_p);