#ifndef VECTOR_H
#define VECTOR_H

typedef int* VectorIndices;

VectorIndices VectorIndicesNuevo(int tamano);
void VectorIndicesElimina(VectorIndices vi);
void VectorIndicesImprime(FILE * fd, VectorIndices vi, int tamano);
void VectorIndicesSetI(VectorIndices vi, int i);
void VectorIndicesUnsetI(VectorIndices vi, int i);
int VectorIndicesGetI(VectorIndices vi, int i);

#endif //VECTOR_H