#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "alfabeto.h"
#include "estado.h"
#include "afnd.h"
#include "palabra.h"


int main(int argc, char ** argv)
{
/*
    AFND * p_afnd_l;



    p_afnd_l = AFNDNuevo("afl1",8,2);

    AFNDInsertaSimbolo(p_afnd_l,"0");
    AFNDInsertaSimbolo(p_afnd_l,"1");

    AFNDInsertaEstado(p_afnd_l,"q0",INICIAL);
    AFNDInsertaEstado(p_afnd_l,"q1",NORMAL);
    AFNDInsertaEstado(p_afnd_l,"q2",NORMAL);
    AFNDInsertaEstado(p_afnd_l,"q3",NORMAL);
    AFNDInsertaEstado(p_afnd_l,"q4",FINAL);
    AFNDInsertaEstado(p_afnd_l,"q5",NORMAL);
    AFNDInsertaEstado(p_afnd_l,"q6",NORMAL);
    AFNDInsertaEstado(p_afnd_l,"q7",FINAL);


    AFNDInsertaTransicion(p_afnd_l, "q1", "1", "q1");
    AFNDInsertaTransicion(p_afnd_l, "q2", "0", "q3");
    AFNDInsertaTransicion(p_afnd_l, "q3", "0", "q4");
    AFNDInsertaTransicion(p_afnd_l, "q5", "1", "q6");
    AFNDInsertaTransicion(p_afnd_l, "q6", "1", "q7");
    AFNDInsertaTransicion(p_afnd_l, "q7", "0", "q7");
    AFNDInsertaTransicion(p_afnd_l, "q7", "1", "q7");


    AFNDInsertaLTransicion(p_afnd_l, "q0", "q1");
    AFNDInsertaLTransicion(p_afnd_l, "q0", "q5");
    AFNDInsertaLTransicion(p_afnd_l, "q1", "q2");
    AFNDInsertaLTransicion(p_afnd_l, "q4", "q2");

    

    AFNDCierraLTransicion(p_afnd_l);

    //relacionImprime(stdout,p_afnd_l->lambdaTransiciones  );
    relacionImprime_teorico(stdout,p_afnd_l->lambdaTransiciones  );
*/


        AFND * p_afnd_l0;
        AFND * p_afnd_l1;
        AFND * p_afnd_l2;
        AFND * p_afnd_l3;
        AFND * p_afnd_l4;
        AFND * p_afnd_l5;/*
        AFND * p_afnd_l6;*/




        p_afnd_l0 = AFND1ODeSimbolo("1");
        AFNDImprime(stdout,p_afnd_l0);


       // p_afnd_l1 = AFND1ODeLambda();
        //AFNDImprime(stdout,p_afnd_l1);

        //p_afnd_l2 = AFND1ODeVacio();
        //AFNDImprime(stdout,p_afnd_l2);







    p_afnd_l3 = AFND1ODeSimbolo("3");
    AFNDImprime(stdout,p_afnd_l3);

    AFND1OInsertaSimbolosAFND(p_afnd_l3, p_afnd_l0);
    AFNDImprime(stdout,p_afnd_l3);
   
    /*esta func esta del reves destino-origen*/
    AFND1OInsertaEstadosTransicionesAFND(p_afnd_l0, p_afnd_l3, "prefijo");
    AFNDImprime(stdout,p_afnd_l3);

    printf("\n\n\nImprimimos el AFND UNION:\n ");
    AFND1OUneLTransicion( p_afnd_l3,  p_afnd_l0,
                             "nombre_nuevo_estado_inicial",  "nombre_nuevo_estado_final");

   //relacionImprime_teorico(stdout, p_afnd_l3->lambdaTransiciones);
    AFNDImprime(stdout,p_afnd_l3);








    /**/
    printf("Probando la funcion AFNDAAFND1O: \n\n");
    //p_afnd_l4 = AFND1ODeSimbolo("4");
    p_afnd_l4 = AFNDNuevo("numero4",8,2);

    AFNDInsertaSimbolo(p_afnd_l4,"0");
    AFNDInsertaSimbolo(p_afnd_l4,"1");

    AFNDInsertaEstado(p_afnd_l4,"q0",INICIAL);
    AFNDInsertaEstado(p_afnd_l4,"q1",NORMAL);
    AFNDInsertaEstado(p_afnd_l4,"q2",NORMAL);
    AFNDInsertaEstado(p_afnd_l4,"q3",NORMAL);
    AFNDInsertaEstado(p_afnd_l4,"q4",FINAL);
    AFNDInsertaEstado(p_afnd_l4,"q5",NORMAL);
    AFNDInsertaEstado(p_afnd_l4,"q6",NORMAL);
    AFNDInsertaEstado(p_afnd_l4,"q7",FINAL);


    AFNDInsertaTransicion(p_afnd_l4, "q1", "1", "q1");
    AFNDInsertaTransicion(p_afnd_l4, "q2", "0", "q3");
    AFNDInsertaTransicion(p_afnd_l4, "q3", "0", "q4");
    AFNDInsertaTransicion(p_afnd_l4, "q5", "1", "q6");
    AFNDInsertaTransicion(p_afnd_l4, "q6", "1", "q7");
    AFNDInsertaTransicion(p_afnd_l4, "q7", "0", "q7");
    AFNDInsertaTransicion(p_afnd_l4, "q7", "1", "q7");









    AFNDImprime(stdout,p_afnd_l4);
    printf("---->>>>  Resultado tras la llamada: \n\n");
    p_afnd_l5 =AFNDAAFND1O(p_afnd_l4);
    AFNDImprime(stdout,p_afnd_l5);
    relacionImprime_teorico(stdout, p_afnd_l5->lambdaTransiciones);
   
/*
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");


    p_afnd_l = AFNDInicializaEstado(p_afnd_l);

    fprintf(stdout,"\n**************** PROCESA CADENA *************\n");
    AFNDImprimeCadenaActual(stdout,p_afnd_l);
    fprintf(stdout,"\n*********************************************\n");

    AFNDProcesaEntrada(stdout,p_afnd_l);

/******************************************************************************** */
/*
    p_afnd_l = AFNDInicializaCadenaActual(p_afnd_l);
    AFNDInsertaLetra(p_afnd_l,"1");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");
    AFNDInsertaLetra(p_afnd_l,"0");

    p_afnd_l = AFNDInicializaEstado(p_afnd_l);

    fprintf(stdout,"\n**************** PROCESA CADENA *************\n");
    AFNDProcesaEntrada(stdout,p_afnd_l);
    fprintf(stdout,"\n*********************************************\n");



    AFNDElimina(p_afnd_l);
*/
/********************************************************************************/


    return 0;

}
