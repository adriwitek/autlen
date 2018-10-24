#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palabra.h"

#define ERR(source) (perror(source),\
		     fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
		     exit(EXIT_FAILURE))

Palabra * palabraNueva(){
    Palabra *p;
    p = (Palabra*)malloc(sizeof(Palabra));
    if(p == NULL){
        ERR("malloc");
    }
    p->tam = 0;
    p->letras =  (char**)malloc(sizeof(char*)); 
    if(! p->letras){
        ERR("malloc");
        }
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
       //printf("debug2");
      char** ptr  = (char **) realloc(p_p->letras, (p_p->tam + 1)*sizeof(char*));
      if(!ptr) ERR("malloc");
      p_p->letras = ptr;
      p_p->letras[p_p->tam] = (char*)malloc(strlen(letra) * sizeof(char));
      if(! p_p->letras[p_p->tam] ) ERR("malloc");
      strcpy(p_p->letras[p_p->tam], letra);
      //printf("%s \n",p_p->letras[p_p->tam]);
        p_p->tam++;
   // printf("changing size from %d to %d \n",p_p->tam-1,p_p->tam );
    return p_p;
}

void palabraImprime(FILE * fd, Palabra * p_p){
    if(!fd || !p_p){
        return;
    }
    printf("[(%d)",p_p->tam);
    for(int i=0;i< p_p->tam ;i++){
        fprintf(fd," %s",p_p->letras[i]);
    }
    fprintf(fd,"]\n");
    return;
    
}

char * palabraQuitaInicio(Palabra * p_p){
    char *copia;
    if(!p_p){
        ERR("no palabra");
    }
    if (!p_p->letras)
    {
        ERR("letras uninitialized");
    }
    if (p_p->tam == 0)
    {
        return NULL;
    }
     copia = p_p->letras[0];

    for(int i=0;i<p_p->tam;i++){
        p_p->letras[i] = p_p->letras[i+1];
    }

    p_p->tam--;
    if (p_p->tam>0)
    {
        char** ptr  = (char **) realloc(p_p->letras, (p_p->tam)*sizeof(char*));
        if(!ptr) ERR("malloc");
        p_p->letras = ptr;
    }
    else p_p = palabraNueva();
      
    return copia;
}

// char * palabraQuitaInicio(Palabra * p_p){
//     char *copia;
//     if(!p_p){
//         ERR("no palabra");
//     }
//      copia = p_p->letras[0];
//     for(int i=0;i<p_p->tam;i++){
//         p_p->letras[i] = p_p->letras[i+1];
//     }
    
//     //strcpy(p_p->letras[p_p->tam - 1],"\n");
//     p_p->letras[p_p->tam - 1]='\0';
//      p_p->tam--;
//     return copia;
// }

int palabraTamano(Palabra * p_p){
    if(!p_p){
        return -1;
    }
    return p_p->tam;
}
