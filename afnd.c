#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "afnd.h"
#include <time.h>

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

    a->lambdaTransiciones = relacionNueva("lambda_relacion",num_estados);

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

    relacionElimina(p_afnd->lambdaTransiciones);

    free(p_afnd->ftransicion);

    free(p_afnd->estados);
    //free(p_afnd->estado_actuales);
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
    
     AFNDImprimeConjuntoEstadosActual(fd,p_afnd);
    AFNDImprimeCadenaActual(fd,p_afnd);
while (  (palabraTamano(p_afnd->cadena_actual) > 0) &&  !AFND_VectorIndicesVacio( p_afnd ) ){ /*Minetras queden caracterres y haya estados actuales:*/
       // printf("vamos a transitar \n");
        AFNDTransita(p_afnd);
        AFNDTransita_Lmabda( p_afnd);
      // printf("hemos transitado \n");

       AFNDImprimeConjuntoEstadosActual(fd,p_afnd);
        AFNDImprimeCadenaActual(fd,p_afnd);
    }

    AFNDInicializaCadenaActual(p_afnd);
    AFNDInicializaEstado(p_afnd);
    
  
}



AFND * AFNDInsertaTransicion(AFND * p_afnd, char * nombre_estado_i,  char * nombre_simbolo_entrada,  char * nombre_estado_f ){
    int pos_qi,pos_qf,pos_simbolo;
    if(!p_afnd || !nombre_estado_f || !nombre_estado_i || !nombre_estado_f ) ERR("error al insertar transiccion");
    pos_qi= AFNDIndiceDeEstado( p_afnd,nombre_estado_i);
    pos_qf= AFNDIndiceDeEstado( p_afnd,nombre_estado_f);
    pos_simbolo = AFNDIndiceDeSimbolo(p_afnd,nombre_simbolo_entrada);
    if(pos_qi == -1 || pos_qf == -1 || pos_simbolo == -1) ERR("ERROR AL INSETAR LA TRANSICION");
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
    
    /*Estado ** estado_actuales_copy;
    estado_actuales_copy = (Estado**)malloc(sizeof(Estado*)* p_afnd->num_estados);
    if (!p_afnd->estado_actuales) ERR("malloc");
    free(p_afnd->estado_actuales);
    p_afnd->estado_actuales = estado_actuales_copy;
    p_afnd->num_estados_actuales_paralelos = 0;*/
    return p_afnd;
}
/*Inicializamos TODOS los estados de tipo INICIAL*/
AFND * AFNDInicializaEstado (AFND * p_afnd){
    if(!p_afnd){ERR("inicializando estado");}
    

    free(p_afnd->estado_actuales);
    Estado ** estado_actuales_copy;
    estado_actuales_copy = (Estado**)calloc(p_afnd->num_estados, sizeof(Estado*) );
    if (estado_actuales_copy == NULL) {
        ERR("malloc");
    }

    
    p_afnd->estado_actuales = estado_actuales_copy;
    
    
    p_afnd->num_estados_actuales_paralelos =0;
    for(int i = 0; i < p_afnd->num_estados; i++){
        if(estadoTipo(p_afnd->estados[i]) == INICIAL){
            p_afnd->estado_actuales[p_afnd->num_estados_actuales_paralelos] = p_afnd->estados[i];
            p_afnd->num_estados_actuales_paralelos ++;

            
            for(int j = 0;j  < p_afnd->num_estados ;j++){   
                if(AFNDLTransicionIJ_cierre(p_afnd,i,j) != 0 &&  (  AFND_isInEstadosActuales( p_afnd,j) == 0 )  ){
                    p_afnd->estado_actuales[p_afnd->num_estados_actuales_paralelos] = p_afnd->estados[j];
                    p_afnd->num_estados_actuales_paralelos ++;
                }

            }



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

/*Funcion auxiliar para AFNDTransita*/
void procesa_transicion_estado(AFND * p_afnd,int i,char* entrada,Estado** estado_actuales_copy,int *n){/*i = indice*/
    int indice_fila,indice_col;

    
        indice_fila = AFNDIndiceDeEstado(p_afnd,estadoNombre(   p_afnd->estado_actuales[i]   ));/* i :estado en el que esta la maquina*/
        
        indice_col  = AFNDIndiceDeSimbolo(p_afnd,entrada); /*simbolo de entrada*/
        if (indice_fila==-1 || indice_col == -1){
            fprintf(stdout, "indice = -1 !!\n");
        }

       
        for(int j=0;j < p_afnd->num_estados_actual;j++){/*Recorremos TODOS los estados INSERTADOS en el AFND : j es el indice del estado destino*/
            //fprintf(stdout,"fila: %d, col: %d, j: %d\n",indice_fila,indice_col,j);
            /*Transicion normal:*/
            if( 1 ==  (p_afnd->ftransicion[indice_fila][indice_col])[j]   ){/*Transitamos*/ /*j es el indice del estadoa  transitar*/
                 //fprintf(stdout,"transito aqui\n");
                 estado_actuales_copy[*n] = p_afnd->estados[j];
                 *n = *n +1;
                 if(!p_afnd->estados[j]) printf("el estado el null \n");
                 
            }  

        }


}

void AFNDTransita(AFND * p_afnd){
   int n = 0;
    char * entrada;
    int num_transiciones;
    
    if(!p_afnd)ERR("error al transitar");

    entrada = palabraQuitaInicio(p_afnd->cadena_actual);
    if(!entrada)ERR("error al transitar");
    

    num_transiciones = p_afnd->num_estados_actuales_paralelos;
    /**/
    /*printf("---n. estados_actuales_paralelos: %d\n\n",num_transiciones);*/
    /**/

    Estado ** estado_actuales_copy;
    estado_actuales_copy = (Estado**)calloc( p_afnd->num_estados,sizeof(Estado*));
    if (p_afnd->estado_actuales == NULL) {ERR("malloc");}

    for(int i = 0 ;i< num_transiciones;i++){/*Procesamos todos los estados actuales*/
        procesa_transicion_estado( p_afnd, i,entrada, estado_actuales_copy,&n);/*para cada estado*/
    }
    

     free(p_afnd->estado_actuales);
    p_afnd->estado_actuales= estado_actuales_copy;
    p_afnd->num_estados_actuales_paralelos = n;
    
    return;

}


void AFNDTransita_Lmabda(AFND * p_afnd){

    // printf("eee\n");
     //printf("aaaaa :  EL ESTADO %d esta en e. actuales\n",i);
   
    
    int * estados_en_maquina;
    int num = 0;
    estados_en_maquina = calloc(p_afnd->num_estados,sizeof(int));
    if(!estados_en_maquina){ERR("reservando memoria");}       

    for(int i = 0;i  < p_afnd->num_estados ;i++){ 
        for(int k =0;k< p_afnd->num_estados_actuales_paralelos;k++){
             if(p_afnd->estado_actuales[k] == p_afnd->estados[i]){
                estados_en_maquina[num] = i;
                //aaa
                //printf("estados_en_maquina:%d\n",i);
                num ++;

            }

        }  
       

    }    




    for(int u =0;u < num;u++){
        for(int j = 0;j  < p_afnd->num_estados ;j++){   
            if(AFNDLTransicionIJ_cierre(p_afnd,estados_en_maquina[u],j) != 0  ){
               // printf("TESTTT\n");
                //printf("el estado que voy a meter debria ser el: %d\n",estados_en_maquina[u]);
                    p_afnd->estado_actuales[p_afnd->num_estados_actuales_paralelos] = p_afnd->estados[j];
                    p_afnd->num_estados_actuales_paralelos ++;
        }

        }


    }
        



        

       
        



    
    
    
}




void AFNDImprimeConjuntoEstadosActual(FILE * fd, AFND * p_afnd)
{
    if (!fd) ERR("problem with file descriptor");
    if (!p_afnd) ERR("AFND is NULL");


    fprintf(fd, "ACTUALMENTE EN {");
    for (int i=0; i<p_afnd->num_estados_actual;i++){
        if(p_afnd->estado_actuales[i] != NULL){
             estadoImprime(fd, p_afnd->estado_actuales[i]);
        }
       
       
    }
    fprintf(fd, "} \n");
}

void AFNDImprimeCadenaActual(FILE *fd, AFND * p_afnd)
{
    if (!fd) ERR("problem with file descriptor");
    if (!p_afnd) ERR("AFND is NULL");
   
    palabraImprime(fd, p_afnd->cadena_actual);
}

AFND * AFNDInsertaLTransicion(AFND * p_afnd, char * nombre_estado_i, char * nombre_estado_f )
{
    if (!p_afnd) ERR("AFND is null");
    if (!nombre_estado_i || !nombre_estado_f) ERR("bad arguments");

    int i= AFNDIndiceDeEstado( p_afnd,nombre_estado_i);
    int j= AFNDIndiceDeEstado( p_afnd,nombre_estado_f);
    if(i == -1 || j == -1) ERR("mal indice");

    p_afnd->lambdaTransiciones->relacion[i][j] = 1;

    return p_afnd;
}

int AFNDLTransicionIJ(AFND * p_afnd, int i , int j)
{
    if (!p_afnd) ERR("AFND is null");
    if (i<0 || j<0 || i>=p_afnd->num_estados || j>=p_afnd->num_estados) ERR("indices malos");
    
    return p_afnd->lambdaTransiciones->relacion[i][j];
}



int AFNDLTransicionIJ_cierre(AFND * p_afnd, int i , int j)
{
    if (!p_afnd) ERR("AFND is null");
    if (i<0 || j<0 || i>=p_afnd->num_estados || j>=p_afnd->num_estados) ERR("indices malos");
    
    return p_afnd->lambdaTransiciones->cierre_relacion[i][j];
}


AFND * AFNDCierraLTransicion (AFND * p_afnd)
{
    if (!p_afnd) ERR("AFND is null");

    p_afnd->lambdaTransiciones = relacionCierreTransitivo(p_afnd->lambdaTransiciones);

    return p_afnd;
}



  int AFND_isInEstadosActuales(AFND * p_afnd,int estado){
      int flag = 0;

      for(int i = 0;i < p_afnd->num_estados_actual;i++){
          for(int j;j<p_afnd->num_estados_actuales_paralelos  ;j++){
              if(p_afnd->estados[i] == p_afnd->estado_actuales[j] ){
                  flag = 1;
              }
          }

      }


    return flag; 
  }



  /*Avance Practica 3*/

AFND * AFND1ODeSimbolo( char * simbolo){
        AFND * p_afnd_l;
        
        p_afnd_l = AFNDNuevo(simbolo, 2, 1);
        if(NULL == p_afnd_l){
            return NULL;
        }
        AFNDInsertaSimbolo(p_afnd_l, simbolo);
        AFNDInsertaEstado(p_afnd_l, "q0", INICIAL );
        AFNDInsertaEstado(p_afnd_l, "qf", FINAL );
        AFNDInsertaTransicion(p_afnd_l, "q0", simbolo, "qf");
        return p_afnd_l;
  }


 AFND * AFND1ODeLambda(){
    
    AFND * p_afnd_l;
    int random;
    char str[50];
    srand(time(NULL));   // Initialization, should only be called once.
    random = rand();  
    sprintf(str, "%d", random);
    p_afnd_l = AFNDNuevo(str, 1 , 0);
    if(NULL == p_afnd_l){
            return NULL;
        }
    AFNDInsertaEstado(p_afnd_l, "q0", INICIAL_Y_FINAL );
    return p_afnd_l;
 }



AFND * AFND1ODeVacio( ){
    AFND * p_afnd_l;
    int random;
    char str[50];
    srand(time(NULL));   // Initialization, should only be called once.
    random = rand() + 1;  
    sprintf(str, "%d", random);
    p_afnd_l = AFNDNuevo(str, 1 , 0);
    if(NULL == p_afnd_l){
            return NULL;
        }
    AFNDInsertaEstado(p_afnd_l, "q0", INICIAL );
    AFNDInsertaEstado(p_afnd_l, "qf", FINAL );
    return p_afnd_l;
}


AFND * AFND1OInsertaSimbolosAFND(AFND * p_afnd_destino, AFND * p_afnd_origen){
    
    int i;

    if(NULL == p_afnd_destino || NULL == p_afnd_origen){
        return NULL;
    }

    for(i=0;i<p_afnd_origen-> ;i++){}



}

