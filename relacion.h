#ifndef RELACION_H
#define RELACION_H

typedef struct _Relacion
{
    char * nombre;
    int ** relacion;
    int ** cierre_relacion;
    int num_elementos;
}Relacion;

Relacion * relacionNueva(char * nombre, int num_elementos);
int ** matrizInit(int n);
void matrizElimina(int** matriz, int n);
void relacionElimina(Relacion * p_r);
Relacion * relacionInserta(Relacion * p_r, int i, int j);
void relacionImprime(FILE * fd, Relacion * p_r);
int ** matrizCopia(int** matriz, int n);
int ** matrizMultiplica(int** m1, int** m2, int n);
int ** matrizSuma(int** m1, int** m2, int n);
void matrizImprime(FILE * fd, int** m, int n);
int matrizCompara(int** m1, int** m2, int n);
int matrizVacia(int** m1, int n);
Relacion * relacionCierreTransitivo(Relacion * p_r);
void matrizArreglarUnos(int** matriz, int n);

#endif //RELACION_H