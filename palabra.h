#ifndef PALABRA_H
#define PALABRA_H

#define TAM_MAX 50
typedef struct _Palabra{
    int tam;
    char** letras;
}Palabra;

Palabra * palabraNueva();
void palabraElimina(Palabra * p_p);
Palabra * palabraInsertaLetra(Palabra * p_p, char * letra);
void palabraImprime(FILE * fd, Palabra * p_p);
char * palabraQuitaInicio(Palabra * p_p);
int palabraTamano(Palabra * p_p);

#endif //PALABRA_H