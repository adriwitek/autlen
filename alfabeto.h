#ifndef ALFABETO_H
#define ALFABETO_H

typedef struct
{
    char* nombre;
    int tamano; /*numero max si de simbolos que admite*/
    char** simbolos;
    int no_simbolos_actual;
}Alfabeto;

Alfabeto* alfabetoNuevo(char* nombre, int tamano);
void alfabetoElimina(Alfabeto* p_alfabeto);
Alfabeto * alfabetoInsertaSimbolo(Alfabeto * p_alfabeto, char * simbolo);
void alfabetoImprime(FILE * fd, Alfabeto * p_alf);
char* alfabetoSimboloEn(Alfabeto * p_alf, int i);
int alfabetoIndiceDeSimbolo(Alfabeto * p_alf, char * simbolo);
int alfabetoTamano(Alfabeto * p_alf);

int alfabeto_get_numSimbolosActual(Alfabeto * p_alf);

#endif //ALFABETO_H