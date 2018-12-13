#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alfabeto.h"

#define ERR(source) (perror(source),\
		     fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
		     exit(EXIT_FAILURE))

Alfabeto* alfabetoNuevo(char* nombre, int tamano)
{
    if (!nombre) ERR("nombre error");
    if (tamano<=0) ERR("tamano should be >0");

    Alfabeto* a;
    a = (Alfabeto*)malloc(sizeof(Alfabeto));
    if (!a) ERR("malloc");
    a->nombre=(char*)malloc(strlen(nombre)*sizeof(char));
    if (!a->nombre) ERR("malloc");
    strcpy(a->nombre,nombre);
    a->tamano=tamano;
    a->simbolos=(char**)malloc(tamano*sizeof(char*));
    if (!a->simbolos) ERR("malloc");
    a->no_simbolos_actual=0;

    return a;
}

void alfabetoElimina(Alfabeto* p_alfabeto)
{
    if (!p_alfabeto) ERR("alfabeto is NULL");

    int len=p_alfabeto->no_simbolos_actual;

    free(p_alfabeto->nombre);
    for (int i=0; i<len; i++)
    {
        free(p_alfabeto->simbolos[i]);
    }
    free(p_alfabeto->simbolos);
    free(p_alfabeto);
}

Alfabeto * alfabetoInsertaSimbolo(Alfabeto * p_alfabeto, char * simbolo)
{
    if (!p_alfabeto) ERR("alfabeto is NULL");

    int len=p_alfabeto->no_simbolos_actual;
    if (len<p_alfabeto->tamano)
    {
        p_alfabeto->simbolos[len]=(char*)malloc(sizeof(simbolo));
        if (!p_alfabeto->simbolos[len]) ERR("malloc");
        strcpy(p_alfabeto->simbolos[len],simbolo);
        p_alfabeto->no_simbolos_actual++;
    }
    else{
        ERR("coleccion de simbolos lleno");
        return NULL;
    } 
    return p_alfabeto;
}

void alfabetoImprime(FILE * fd, Alfabeto * p_alf)
{
    if (!fd) ERR("problem with file descriptor");
    if (!p_alf) ERR("alfabeto is NULL");

    fprintf(fd,"%s={ ",p_alf->nombre);
    for (int i=0; i<p_alf->no_simbolos_actual; i++)
    {
        fprintf(fd,"%s ",p_alf->simbolos[i]);
    }
    fprintf(fd,"}\n");
}

char* alfabetoSimboloEn(Alfabeto * p_alf, int i)
{
    if (!p_alf) ERR("alfabeto is NULL");
    if (i<0||i>p_alf->tamano) ERR("wrong index");

    return p_alf->simbolos[i]==NULL?NULL:p_alf->simbolos[i];
}

int alfabetoIndiceDeSimbolo(Alfabeto * p_alf, char * simbolo)
{
    if (!p_alf) ERR("alfabeto is NULL");

    for (int i=0; i<p_alf->no_simbolos_actual; i++)
    {
        if (!strcmp(p_alf->simbolos[i],simbolo)) return i;
    }
    return -1;
}

int alfabetoTamano(Alfabeto * p_alf)
{
    if (!p_alf) ERR("alfabeto is NULL");

    return p_alf->tamano;
}


int alfabeto_get_numSimbolosActual(Alfabeto * p_alf){
    if (!p_alf) ERR("alfabeto is NULL");
    return p_alf->no_simbolos_actual;

}