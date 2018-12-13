#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estado.h"

#define ERR(source) (perror(source),\
		     fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
		     exit(EXIT_FAILURE))

Estado * estadoNuevo( char * nombre, int tipo)
{
    if (!nombre) ERR("nombre error");
    if (tipo<0||tipo>3) ERR("incorrecto tipo de estado");

    Estado* e;
    e = (Estado*)malloc(sizeof(Estado));
    if (!e) ERR("malloc");
    e->nombre=(char*)malloc(strlen(nombre)*sizeof(char));
    if (!e->nombre) ERR("malloc");
    strcpy(e->nombre,nombre);
    e->tipo=tipo;

    return e;
}

void estadoElimina( Estado * p_s)
{
    if (!p_s) return;

    free(p_s->nombre);
    free(p_s);
}

void estadoImprime( FILE * fd, Estado * p_s)
{
    if (!fd) ERR("problem with file descriptor");
    //if (!p_s) ERR("estado is NULL");
    if (!p_s) return;

    switch(p_s->tipo)
    {
        case INICIAL:
            fprintf(fd,"->%s ",p_s->nombre);
            break;
        case FINAL:
            fprintf(fd,"%s* ",p_s->nombre);
            break;
        case INICIAL_Y_FINAL:
            fprintf(fd,"->%s* ",p_s->nombre);
            break;         
        case NORMAL:
            fprintf(fd,"%s ",p_s->nombre);
            break;
        default:
            fprintf(fd,"HA OCURRIDO UN ERROR ");    
    }
}

int estadoEs(Estado * p_s, char * nombre)
{
    if (!p_s) ERR("estado is NULL");
    if (!nombre) ERR("nombre error");

    if(!strcmp(p_s->nombre,nombre)) return 1;
    else return 0;
}

char * estadoNombre(Estado * p_s)
{
    if (!p_s) ERR("estado is NULL");
    return p_s->nombre;
}

int estadoTipo(Estado * p_s)
{
    if (!p_s) ERR("estado is NULL");
    return p_s->tipo;
}

/*Funciones auxiliares Practica 3*/

/*Quita a un estado su prpiedad de Inicial,final o inicial-final*/
void quitar_tipoIni_FinalEstado(Estado * p_s){
    if (!p_s) ERR("estado is NULL");
    p_s->tipo = NORMAL;
}

/*anniade un sufijo al nombre del estado*/
void annide_sufijoEstado(Estado * p_s,char * sufijo){
    
    if (!p_s || sufijo == NULL) ERR("estado o sufijo es NULL");
    free( p_s->nombre);
    /* strcat(dest, src);*/
    strcat(p_s->nombre, sufijo);
}

/*quita el sufijo al nombre del estado*/
void quita_sufijoEstado(Estado * p_s,char * sufijo){
    char * tmp;
    if (!p_s || sufijo == NULL) ERR("estado o sufijo es NULL");
    
    tmp = strtok(p_s->nombre, sufijo);
    free( p_s->nombre);
    p_s->nombre = tmp;
}