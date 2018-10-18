Palabra * palabraInsertaLetra(Palabra * p_p, char * letra){
    //char *copia;

    if(    p_p->tam >= TAM_MAX){
      
      p_p->letras = (char **) realloc(p_p->letras, p_p->tam + 1);
       p_p->tam++;
       p_p->letras[ p_p->tam - 1] = (char*)malloc(sizeof(char) );
       if( p_p->letras[ p_p->tam - 1] == NULL){return NULL;}

    }

   

    //copia = (char*) malloc(sizeof(char));
    //if(!copia){
    //    return NULL;
   // }

    //strcpy(copia,letra);
    p_p->letras[p_p->tam]=(char*)malloc(sizeof(char) );
    strcpy(p_p->letras[p_p->tam],letra);
    //printf("%s  ",p_p->letras[p_p->tam]);
    p_p->tam++;
    return p_p;

}