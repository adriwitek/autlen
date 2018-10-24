#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "afnd.h"

#define ERR(source) (perror(source),\
		     fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
		     exit(EXIT_FAILURE))

AFND* AFNDNuevo(char * nombre, int num_estados, int num_simbolos)
{
    if (!nombre || num_estados<=0 || num_simbolos<=0) ERR("bad arguments");
    AFND* a;
    a = (AFND*)malloc(sizeof(AFND));
    if (!a) ERR("malloc");
    a->nombre=(char*)malloc(strlen(nombre)*sizeof(char));
    if (!a->nombre) ERR("malloc");
    strcpy(a->nombre,nombre);
    a->alfabeto = alfabetoNuevo(nombre, num_simbolos);
    a->num_estados = num_estados;
    a->num_simbolos = num_simbolos;

    a->estados = (Estado**)malloc(sizeof(Estado*)*num_estados);
    if (!a->estados) ERR("malloc");

    a->cadena_actual = palabraNueva();

    // for (int i=0; i<num_estados; i++)
    // {
    //     a->estados[i]=estadoNuevo("test",3);
    // }
    return a;
}

void AFNDElimina(AFND * p_afnd)
{
    free(p_afnd->nombre);
    alfabetoElimina(p_afnd->alfabeto);
    for (int i=0; i<p_afnd->num_estados; i++) 
    {
        estadoElimina(p_afnd->estados[i]);
    }
    palabraElimina(p_afnd->cadena_actual);
    free(p_afnd->estados);
    free(p_afnd);
}

AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra)
{
    if (!p_afnd) ERR("afnd is null");
    if (!letra) ERR("letra is null");

    p_afnd->cadena_actual = palabraInsertaLetra(p_afnd->cadena_actual, letra);

    return p_afnd;
}

void AFNDImprime(FILE * fd, AFND* p_afnd)
{
    if (!fd) ERR("problem with file descriptor");
    if (!p_afnd) ERR("AFND is NULL");

    fprintf(fd,"%s={\n",p_afnd->nombre);
    fprintf(fd,"\tnum_simbolos = %d\n\n",p_afnd->num_simbolos);
    fprintf(fd,"\tA=");
    alfabetoImprime(fd, p_afnd->alfabeto);
    fprintf(fd,"\n\tnum_estados = %d\n\n",p_afnd->num_estados);
    fprintf(fd,"\tQ={");
    // for (int i=0; i<p_afnd->num_estados; i++)
    // {
    //     estadoImprime(fd, p_afnd->estados[i]);
    // }
    // fprintf(fd,"}\n\n\tFuncion de Transicion ={\n\n");
    // fprintf(fd,"\t\tnot implemented yet\n\n\n");
    fprintf(fd,"\t}\n}\n\n");
}