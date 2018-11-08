#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relacion.h"

#define ERR(source) (perror(source),\
		     fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
		     exit(EXIT_FAILURE))

int ** matrizInit(int n)
{
    int ** matriz;

    matriz = (int**) malloc (n *sizeof(int*));
    if (!matriz) ERR("malloc");

    for (int i=0; i<n; i++)
    {
        matriz[i] = (int*) malloc (n*sizeof(int));
        if (!matriz[i]) ERR("malloc");
    }

    for (int i=0; i < n ; i++)
    {
        for (int j=0; j < n; j++)
        {
            matriz[i][j]=0;
        }
    }
    return matriz;
}

Relacion * relacionNueva(char * nombre, int num_elementos)
{
    if (!nombre || num_elementos<=0) ERR("bad args");

    Relacion* r;
    r = (Relacion*)malloc(sizeof(Relacion));
    if (!r) ERR("malloc");
    r->nombre=(char*)malloc(strlen(nombre)*sizeof(char));
    if (!r->nombre) ERR("malloc");
    strcpy(r->nombre,nombre);
    r->relacion = matrizInit(num_elementos);
    r->cierre_relacion = matrizInit(num_elementos);
    r->num_elementos = num_elementos;

    return r;
}

void matrizElimina(int** matriz, int n)
{
     if (matriz != NULL)
    {
        for (int i=0; i<n; i++)
        {
            free (matriz[i]);
        }
    }
    free(matriz);
}

int ** matrizCopia(int** matriz, int n)
{
    if (!matriz) ERR("matriz null");

    int ** matriz2 = matrizInit(n);
    for (int i=0; i < n ; i++)
    {
        for (int j=0; j < n; j++)
        {
            matriz2[i][j]=matriz[i][j];
        }
    }
    return matriz2;
}

int ** matrizMultiplica(int** m1, int** m2, int n)
{
    if (!m1 || !m2) ERR("malas matrices");

    int sum = 0;
    int ** matrizMultiplicada = matrizInit(n);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            for (int k=0; k<n; k++)
            {
                sum += m1[i][k] * m2[k][j];
            }
            matrizMultiplicada[i][j] = sum;
            sum = 0;
        }
    }
    return matrizMultiplicada;
}

int ** matrizSuma(int** m1, int** m2, int n)
{
    if (!m1 || !m2) ERR("malas matrices");

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            m1[i][j] += m2[i][j];
        }
    }
    return m1;
}

void relacionElimina(Relacion * p_r)
{
    if (!p_r) return;
    free(p_r->nombre);
    matrizElimina(p_r->relacion ,p_r->num_elementos);
    matrizElimina(p_r->cierre_relacion ,p_r->num_elementos);
}

Relacion * relacionInserta(Relacion * p_r, int i, int j)
{
    if (!p_r) ERR("relacion null");
    if (i<0 || j<0 || i>=p_r->num_elementos || j>=p_r->num_elementos) ERR("bad indices");

    p_r->relacion[i][j]=1;

    return p_r;
}

void matrizImprime(FILE * fd, int** m, int n)
{
    if (!m) ERR("matriz null");

    for (int i=0; i<n; i++)
    {
        fprintf(fd, "\t[%d]",i);
        for (int j=0; j<n; j++)
        {
            fprintf(fd, "\t%d",m[i][j]);
        }
        fprintf(fd, "\n");
    }
    fprintf(fd, "\n");
}

void relacionImprime(FILE * fd, Relacion * p_r)
{
    if (!fd) ERR("fd null");
    if (!p_r) ERR("p_r null");

    fprintf(fd, "%s={\n\t   ",p_r->nombre);
    for (int i=0; i<p_r->num_elementos; i++)
    {
        fprintf(fd, "\t[%d]",i);
    }
    fprintf(fd, "\n");

    fprintf(fd, "\t\tCIERRE\n");
    matrizImprime(fd, p_r->relacion, p_r->num_elementos);
    fprintf(fd, "}");
}