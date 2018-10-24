#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define ERR(source) (perror(source),\
		     fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
		     exit(EXIT_FAILURE))

VectorIndices VectorIndicesNuevo(int tamano)
{
    VectorIndices a;
	a = (VectorIndices)calloc(sizeof(int),tamano);
	if (!a) ERR("malloc");

	return a;
}

void VectorIndicesElimina(VectorIndices vi)
{
	free(vi);
}

void VectorIndicesImprime(FILE * fd, VectorIndices vi, int tamano)
{
	if (!vi || !fd) ERR("null arguments");

	for (int i=0;i<tamano;i++)
	{
		fprintf(fd,"%d", vi[i]);
	}
	fprintf(fd,"\n");
}

void VectorIndicesSetI(VectorIndices vi, int i)
{
	if (!vi) ERR("null argument");
	vi[i]=1;
}

void VectorIndicesUnsetI(VectorIndices vi, int i)
{
	if (!vi) ERR("null argument");
	vi[i]=0;
}

int VectorIndicesGetI(VectorIndices vi, int i)
{
	if (!vi) ERR("null argument");
	return vi[i];
}