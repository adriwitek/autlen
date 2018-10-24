#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "afnd.h"

#define ERR(source) (perror(source),\
		     fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
		     exit(EXIT_FAILURE))

AFND* AFNDNuevo(char * nombre, int num_estados, int num_simbolos){
    int i,j;
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
    if(!a->cadena_actual) ERR("error al reservar la palabra nueva");
    //a->contador = 0;
    // for (int i=0; i<num_estados; i++)
    // {
    //     a->estados[i]=estadoNuevo("test",3);
    // }
    

    /* MATRIZ DE TRANSICCION */
    a->ftransicion = (VectorIndices **)malloc(sizeof(VectorIndices*)*num_simbolos);
    for (i=0; i<num_estados; i++){
		a->ftransicion[i] = (VectorIndices*) malloc (num_estados*sizeof(VectorIndices)); 
	}
	for (i=0; i < num_estados ; i++){
		for (j=0; j < num_simbolos; j++){
			a->ftransicion[i][j]= VectorIndicesNuevo(num_estados);
		}
	}


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
    if(!p_afnd){
        return NULL;
    }
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

void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd){
    
    int i = 0;
    int size;
    char *letraux;
    
    if(  fd == NULL || p_afnd == NULL ){
        ERR("ANFDProcesarEntrada");
    }
    
    size = palabraTamano(p_afnd->cadena_actual);
    
    fprintf(fd, "\n\n");
    fprintf(fd, ">>>>PROCESANDO CADENA: \n \n");
    fprintf(fd, "\t");
    palabraImprime(fd,p_afnd->cadena_actual);
    fprintf(fd, "\n \n \n");
    
    for(i=0; i<=size; i++){
        
        fprintf(fd,"----Poscion Numero: %d  \n", i);
        fprintf(fd, "\t");
        palabraImprime(fd,p_afnd->cadena_actual);
        fprintf(fd, "\n ");
        
        letraux = palabraQuitaInicio(p_afnd->cadena_actual);
        free(letraux);
    }
    
}


int AFNDIndiceDeEstado(AFND * p_afnd,char * nombre){
    if(!p_afnd || !nombre) ERR("mal indice");
    for(int i =0;i <p_afnd->num_estados ;i++){
        if(strcmp(nombre, estadoNombre(p_afnd->estados[i])  ) == 0 ){
            return i;
        }
    }
    return -1;
}
int AFNDIndiceDeSimbolo(AFND * p_afnd,char * nombre){
     if(!p_afnd || !nombre) ERR("mal indice");
     return alfabetoIndiceDeSimbolo(p_afnd->alfabeto,  nombre);
}

AFND * AFNDInsertaTransicion(AFND * p_afnd, char * nombre_estado_i,  char * nombre_simbolo_entrada,  char * nombre_estado_f ){
    int pos_qi,pos_qf,pos_simbolo;
    if(!p_afnd || nombre_estado_f || nombre_estado_i || nombre_estado_f ) ERR("error al insertar transiccion");
    pos_qi= AFNDIndiceDeEstado( p_afnd,nombre_estado_i);
    pos_qf= AFNDIndiceDeEstado( p_afnd,nombre_estado_f);
    pos_simbolo = AFNDIndiceDeSimbolo(p_afnd,nombre_simbolo_entrada);
    if(pos_qi == -1 || pos_qf == -1 || pos_simbolo == -1) ERR("ERRO AL INSETAR LA TRANSICION");
    (p_afnd->ftransicion[pos_qi][pos_simbolo])[pos_qf]=1;
}
