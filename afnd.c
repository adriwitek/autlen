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

    for (int i=0; i<num_estados; i++)
    {
        a->estados[i]=estadoNuevo("test",3);
    }
    return a;
}