#include "palabra.h"


Palabra * palabraNueva(){
    Palabra *p;
    p = (Palabra*)malloc(sizeof(Palabra));
    if(p == NULL){
        return NULL;
    }
    p->tam = 0;
    p->letras =  (char**)   malloc(TAM_MAX * sizeof(char*)); 
    if(! p->letras){
        return NULL;
        }
     for(int i = 0;   i<=TAM_MAX;i++)  {
         p->letras[i] = (char *)malloc(sizeof(char));
         if( p->letras[i] == NULL){
             for(j=0;j<i;j++){
                 free(p->letras[i]);
             }
             free(p->letras);
             return NULL;
         }
     }
    return p;
}




void palabraElimina(Palabra * p_p){
    if(p_p == NULL){
        return;
    }

    for(int i = 0 ;i< p_p->tam ;i++){
        free(p_p->letas[i]);
    }
    free(p_p->letras);
    free(p_p);
    return;

}

Palabra * palabraInsertaLetra(Palabra * p_p, char * letra){
    char *copia;

    if(    p_p->tam >= TAM_MAX){
      
      p_p->letras = (char **) realloc(p_p->letras, p_p->tam + 1);
       p_p->tam++;
       p_p->letras[ p_p->tam - 1] = (char*)malloc(sizeof(char) );
       if( p_p->letras[ p_p->tam - 1] == NULL){return NULL;}

    }

    /*movemos cda letra una posicion a la derecha en el array*/
    for(j = p_p->tam - 1; j>=0 ;j--){
        if(j != 0){
             p_p->letras[j] =  p_p->letras[j -1]
        }
    }

    copia = (char*) malloc(sizeof(char));
    if(!copia){
        return NULL;
    }

    *copia = *letra;
    p_p->letras[0] = copia; /*Insetamos en la primera posicion*/
    return p_p;

}

void palabraImprime(FILE * fd, Palabra * p_p){
    if(!fd || p_p){
        return;
    }
    for(i=0;i< p_p->tam ;i++){
        fprintf(fd,"%c",p_p->letras[i]);
    }
    fprintf(fd,"\n");
    return;
    
}

char * palabraQuitaInicio(Palabra * p_p){
    char *copia;
    if(!p_p){
        return NULL;
    }
     copia = p_p->letras[0];
    for(i=0;i<p_p->tam;i++){
        p_p->letras[i] = p_p->letras[i+1];
    }
    
    p_p->letras[p_p->tam - 1] = '/n';


     p_p->tam--;
    return copia;

}
int palabraTamano(Palabra * p_p){
    if(!p_p){
        return -1;
    }
    return p_p->tam;
}
