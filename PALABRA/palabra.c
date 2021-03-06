#include "palabra.h"


Palabra * palabraNueva(){
    Palabra *p;
    p = (Palabra*)malloc(sizeof(Palabra));
    if(p == NULL){
        return NULL;
    }
    p->tam = 0;
    p->letras =  (char**)   malloc(sizeof(char*)); 
    if(! p->letras){
        return NULL;
        }
        //printf("debug1");
    return p;
}




void palabraElimina(Palabra * p_p){
    if(p_p == NULL){
        return;
    }

    for(int i = 0 ;i< p_p->tam ;i++){
        free(p_p->letras[i]);
    }
    free(p_p->letras);
    free(p_p);
    return;

}

Palabra * palabraInsertaLetra(Palabra * p_p, char * letra){
   

  
      
     
      char** ptr  = (char **) realloc(p_p->letras, (p_p->tam + 1)* sizeof(char *) );
      if(!ptr) return NULL;
      p_p->letras = ptr;
      p_p->letras[p_p->tam] = (char*)malloc(strlen(letra) +1 );
      if(! p_p->letras[p_p->tam] ){return NULL;}
      strcpy(p_p->letras[p_p->tam], letra);
      //printf("letra : %s \n",p_p->letras[p_p->tam]);
       p_p->tam++;
   
    return p_p;

}

void palabraImprime(FILE * fd, Palabra * p_p){
    if(fd==NULL || p_p==NULL){
        printf("Error de puntero,funcion imprime_palabra\n");
        return;
    }
    fprintf(fd,"[(%d) ",p_p->tam);
    for(int i=0;i< p_p->tam ;i++){
        fprintf(fd,"%s ",p_p->letras[i]);
        
    }
    fprintf(fd,"] \n");
    return;
    
}

char * palabraQuitaInicio(Palabra * p_p){
    char *copia;
    if(!p_p){
        return NULL;
    }
     copia = p_p->letras[0];
    for(int i=0;i<p_p->tam;i++){
        p_p->letras[i] = p_p->letras[i+1];
    }
    
    //strcpy(p_p->letras[p_p->tam - 1],"\n");
    p_p->letras[p_p->tam - 1]='\0';
     p_p->tam--;
    return copia;

}
int palabraTamano(Palabra * p_p){
    if(!p_p){
        return -1;
    }
    return p_p->tam;
}
