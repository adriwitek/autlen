
#include "palabra.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
        Palabra * pal;
        int i;
        char letra [20];
        char * letrai;

        pal = palabraNueva();

        for (i=0; i < argc-1; i++)
        {
                sprintf(letra,"l_%d_%s",i,argv[1+i]);
                palabraInsertaLetra(pal,letra);
                fprintf(stdout,"pal_%d:\n",i);
                palabraImprime(stdout,pal);
                fprintf(stdout,"\n");
        }
        while ( palabraTamano(pal) > 0 )
        {
                fprintf(stdout,
    "QUITAMOS %s DE LA PALABRA QUE QUEDA ASI:\n",letrai=palabraQuitaInicio(pal));
                palabraImprime(stdout,pal);
                free(letrai);
        }

        palabraElimina(pal);

        return 0;
}
