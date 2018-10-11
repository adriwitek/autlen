#ifndef ESTADO_H
#define ESTADO_H

#define INICIAL 0
#define FINAL   1
#define INICIAL_Y_FINAL 2
#define NORMAL 3

typedef struct
{
    char* nombre;
    int tipo;
}Estado;

Estado * estadoNuevo( char * nombre, int tipo);
void estadoElimina( Estado * p_s);
void estadoImprime( FILE * fd, Estado * p_s);
int estadoEs(Estado * p_s, char * nombre);
char * estadoNombre(Estado * p_s);
int estadoTipo(Estado * p_s);

#endif //ESTADO_H