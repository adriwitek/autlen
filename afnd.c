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
    a->num_estados_actual = 0;
    a->num_simbolos = num_simbolos;

    a->estados = (Estado**)malloc(sizeof(Estado*)*num_estados);
    if (!a->estados) ERR("malloc");


    /*Para el no determinismo:*/
    a->num_estados_actuales_paralelos = 0;
    a->estado_actuales = (Estado**)malloc(sizeof(Estado*)*num_estados);
    if (!a->estado_actuales) ERR("malloc");



    a->cadena_actual = palabraNueva();
    if(!a->cadena_actual) ERR("error al reservar la palabra nueva");
    //a->contador = 0;
    // for (int i=0; i<num_estados; i++)
    // {
    //     a->estados[i]=estadoNuevo("test",3);
    // }
    

    /* MATRIZ DE TRANSICCION */
    a->ftransicion = (VectorIndices**) malloc (num_estados*sizeof(VectorIndices*));
    for (i=0; i<num_estados; i++)
    {
        a->ftransicion[i] = (VectorIndices*) malloc (num_simbolos*sizeof(VectorIndices)); 
    }

    for (i=0; i < num_estados ; i++)
    {
        for (j=0; j < num_simbolos; j++)
        {
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

    for (int i=0; i < p_afnd->num_estados ; i++){
		for (int j=0; j < p_afnd->num_simbolos; j++){
			VectorIndicesElimina(p_afnd->ftransicion[i][j]);
		}
	}

    for (int i=0; i<p_afnd->num_estados; i++){
		free(p_afnd->ftransicion[i]);
	}
    free(p_afnd->ftransicion);

    free(p_afnd->estados);
    free(p_afnd->estado_actuales);
    free(p_afnd);
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
    for (int i=0; i<p_afnd->num_estados; i++)
    {
        estadoImprime(fd, p_afnd->estados[i]);
    }
    fprintf(fd,"}\n\n\tFuncion de Transicion = {\n\n");
    for (int i=0; i < p_afnd->num_estados ; i++){
		for (int j=0; j < p_afnd->num_simbolos; j++){
			fprintf(fd,"\t\t");
            fprintf(fd,"f(%s",p_afnd->estados[i]->nombre);
            //estadoImprime(fd, p_afnd->estados[i]);
            fprintf(fd,",%s)={",p_afnd->alfabeto->simbolos[j]);
           
            for (int k=0;k<p_afnd->num_estados; k++)
            {
                if (VectorIndicesGetI(p_afnd->ftransicion[i][j],k)==1)
                {
                    fprintf(fd," %s",p_afnd->estados[k]->nombre);
                }
            }
            fprintf(fd," }\n");
		}
	}
    fprintf(fd,"\t}\n}\n\n");
}

void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd){
    
    


AFNDImprimeCadenaActual(fd,p_afnd);
while (  (palabraTamano(p_afnd->cadena_actual) > 0) &&  !AFND_VectorIndicesVacio( p_afnd ) ){ /*Minetras queden caracterres y haya estados actuales:*/
        
        AFNDTransita(p_afnd);
       

       /AFNDImprimeConjuntoEstadosActual(fd,p_afnd);
        AFNDImprimeCadenaActual(fd,p_afnd);
    }

    
}



AFND * AFNDInsertaTransicion(AFND * p_afnd, char * nombre_estado_i,  char * nombre_simbolo_entrada,  char * nombre_estado_f ){
    int pos_qi,pos_qf,pos_simbolo;
    if(!p_afnd || !nombre_estado_f || !nombre_estado_i || !nombre_estado_f ) ERR("error al insertar transiccion");
    pos_qi= AFNDIndiceDeEstado( p_afnd,nombre_estado_i);
    pos_qf= AFNDIndiceDeEstado( p_afnd,nombre_estado_f);
    pos_simbolo = AFNDIndiceDeSimbolo(p_afnd,nombre_simbolo_entrada);
    if(pos_qi == -1 || pos_qf == -1 || pos_simbolo == -1) ERR("ERRO AL INSETAR LA TRANSICION");
    VectorIndicesSetI(p_afnd->ftransicion[pos_qi][pos_simbolo],pos_qf);
    return p_afnd;
}
AFND * AFNDInsertaSimbolo(AFND * p_afnd, char * simbolo)
{
    if (!p_afnd) ERR("AFND is null");
    if (!simbolo) ERR("inserted symbol is null");

    p_afnd->alfabeto = alfabetoInsertaSimbolo(p_afnd->alfabeto, simbolo);

    return p_afnd;
}

AFND * AFNDInsertaEstado(AFND * p_afnd, char * nombre, int tipo){
    if (!p_afnd) ERR("AFND is null");
    if (!nombre) ERR("nombre is null");

    int len = p_afnd->num_estados_actual;
    if (len<p_afnd->num_estados){
        p_afnd->estados[len] = estadoNuevo(nombre, tipo);
        p_afnd->num_estados_actual++;
    }
    else ERR("exceeded number of possible states");
    return p_afnd;
}

AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra){
    if (!p_afnd) ERR("afnd is null");
    if (!letra) ERR("letra is null");

    p_afnd->cadena_actual = palabraInsertaLetra(p_afnd->cadena_actual, letra);

    return p_afnd;
}

/*Reset of the machine*/
AFND * AFNDInicializaCadenaActual (AFND * p_afnd ){
     if(!p_afnd)ERR("error");
     if(p_afnd->cadena_actual){
          palabraElimina(p_afnd->cadena_actual);
     }
    p_afnd->cadena_actual = palabraNueva();
    for(int i = 0;i<p_afnd->num_estados_actuales_paralelos   ;i++){
        p_afnd->estado_actuales = NULL;
    }

    return p_afnd;
}
/*Inicializamos TODOS los estados de tipo INICIAL*/
AFND * AFNDInicializaEstado (AFND * p_afnd){
    if(!p_afnd)ERR("inicializando estado");

     for(int i = 0; i < p_afnd->num_estados; i++){

        if(estadoTipo(p_afnd->estados[i]) == INICIAL){
        
            p_afnd->estado_actuales[p_afnd->num_estados_actuales_paralelos] = p_afnd->estados[i];
            p_afnd->num_estados_actuales_paralelos ++;
        }
    }
    return p_afnd;
}



/*******FUNCIONES AUXILIARES PARA TRANSITA*****/



void AFNDInsertaEstado_Actual(AFND * p_afnd, int indice){
    if (!p_afnd) ERR("AFND is null");

    for(int k=0;  k<p_afnd->num_estados;  k++){
        if(p_afnd->estado_actuales[k] == NULL){
            p_afnd->estado_actuales[k] = p_afnd->estados[indice];
            p_afnd->num_estados_actuales_paralelos++;
            return;
        }
    }
}




/*Comprobamos que haya algun estado actual*/
int AFND_VectorIndicesVacio(AFND * p_afnd ){
    if(!p_afnd)ERR("error de puntero");
    if(p_afnd->num_estados_actuales_paralelos <= 0){    /*Esta varaible la modificamos desde AFND_transita*/
        return 1;
    }else{
        return 0;
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



void AFNDTransita(AFND * p_afnd){
    char * entrada;
    int num_transiciones;
    int indice_fila,indice_col;
    if(!p_afnd)ERR("error al transitar");

    entrada = palabraQuitaInicio(p_afnd->cadena_actual);
    if(!entrada)ERR("error al transitar");

    num_transiciones = p_afnd->num_estados_actuales_paralelos;
    for(int i = 0 ;i< num_transiciones;i++){


        
        
        indice_fila = AFNDIndiceDeEstado(p_afnd,estadoNombre(   p_afnd->estado_actuales[i]   ));
        indice_col  = AFNDIndiceDeSimbolo(p_afnd,entrada);
        p_afnd->estado_actuales[i] = NULL; /*Lo saco ya que al transitar saldre de ese estado(si no asi se inserta a si mismo en el bucle de abajo)*/
        p_afnd->num_estados_actuales_paralelos--;


        for(int j=0;j < p_afnd->num_estados_actual;j++){
            
            if( 1 ==  VectorIndicesGetI(p_afnd->ftransicion[indice_fila][indice_col], j)   ){/*Transitamos*/ /*j es el indice del estadoa  transitar*/
                 //AFNDInsertaEstado_Actual( p_afnd, j);
                  p_afnd->estado_actuales[p_afnd->num_estados_actuales_paralelos  ] = p_afnd->estados[j];
                  p_afnd->num_estados_actuales_paralelos++;
            }  
        }
    }
    
    /*Recolocamos  p_afnd->estado_actuales para que no queden nulls arriba*/
    Estado ** estado_actuales_copy;
    p_afnd->estado_actuales = (Estado**)malloc(sizeof(Estado*)* p_afnd->num_estados);
    if (!p_afnd->estado_actuales) ERR("malloc");

    for(int h = 0,g=0;  h < p_afnd->num_estados ;h++){
        if(p_afnd->estado_actuales[h] != NULL){
            estado_actuales_copy[g] =  p_afnd->estado_actuales[h];
            g++;
        }
    }
    free(p_afnd->estado_actuales);
    p_afnd->estado_actuales = estado_actuales_copy;
    return;

}





void AFNDImprimeConjuntoEstadosActual(FILE * fd, AFND * p_afnd)
{
    if (!fd) ERR("problem with file descriptor");
    if (!p_afnd) ERR("AFND is NULL");

    for (int i=0; i<p_afnd->num_estados_actual;i++)
    {
        //if(p_afnd->estado_actuales[i] != NULL){
        //     estadoImprime(fd, p_afnd->estado_actuales[i]);
        //}
       
       
    }
}

void AFNDImprimeCadenaActual(FILE *fd, AFND * p_afnd)
{
    if (!fd) ERR("problem with file descriptor");
    if (!p_afnd) ERR("AFND is NULL");

    palabraImprime(fd, p_afnd->cadena_actual);
}
