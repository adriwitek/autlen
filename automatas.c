#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alfabeto.h"
#include "estado.h"
#include "palabra.h"
#include "vector.h"
#include "afnd.h"

int main(int argc, char ** argv )
{
    AFND* p_afnd_l = AFNDNuevo("test",3,5); 
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");

    AFNDImprime(stdout, p_afnd_l);

    AFNDElimina(p_afnd_l);

    return 0;
}


