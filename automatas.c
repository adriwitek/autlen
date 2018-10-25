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
    /*
   AFND* p_afnd_l = AFNDNuevo("test",3,5); 
   
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");

    AFNDImprime(stdout, p_afnd_l);

    AFNDProcesaEntrada(stdout, p_afnd_l);
*/
    /**/
    AFND* p_afnd = AFNDNuevo("test",3,5); 
    AFNDInsertaSimbolo(p_afnd,"0");
   AFNDInsertaSimbolo(p_afnd,"1");
    /* DEFINICIÓN DEL CONJUNTO DE ESTADOS */
   AFNDInsertaEstado(p_afnd,"q0",INICIAL);
   AFNDInsertaEstado(p_afnd,"q1",NORMAL);
   AFNDInsertaEstado(p_afnd,"qf",FINAL);
    /* DEFINICIÓN DE LAS TRANSICIONES NO LAMBDA */
   AFNDInsertaTransicion(p_afnd, "q0", "0", "q0");
   AFNDInsertaTransicion(p_afnd, "q0", "1", "q0");
   AFNDInsertaTransicion(p_afnd, "q0", "1", "q1");
   AFNDInsertaTransicion(p_afnd, "q1", "1", "qf");


    AFNDImprime(stdout, p_afnd);

    /* DEFINICIÓN DE LA CADENA DE ENTRADA [ 0 1 0 1 1 ] */
   p_afnd= AFNDInsertaLetra(p_afnd,"0");
   p_afnd= AFNDInsertaLetra(p_afnd,"1");
   p_afnd= AFNDInsertaLetra(p_afnd,"0");
   p_afnd= AFNDInsertaLetra(p_afnd,"1");
   p_afnd= AFNDInsertaLetra(p_afnd,"1");

 AFNDInicializaEstado (p_afnd);


    AFNDElimina(p_afnd);

    return 0;
}


