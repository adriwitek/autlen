#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "relacion.h"


int main(int argc, char ** argv)
{
    Relacion * r1;

    int i=0;

    r1 = relacionNueva("grafo1",8);


    relacionInserta(r1,0,1);
    relacionInserta(r1,0,2);
    relacionInserta(r1,1,4);
    relacionInserta(r1,2,3);
    relacionInserta(r1,3,0);
    relacionInserta(r1,4,6);
    relacionInserta(r1,5,4);
    relacionInserta(r1,5,7);
    relacionInserta(r1,6,5);

    r1 = relacionCierreTransitivo(r1);

    fprintf(stdout,"R1\n");
    relacionImprime(stdout,r1);
    relacionElimina(r1);

    return 0;
}
