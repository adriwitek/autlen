#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alfabeto.h"
#include "estado.h"
// #include "palabra.h"
#include "vector.h"
#include "afnd.h"

int main (int argc, char **argv)
{
    AFND* test = AFNDNuevo("test",10,10);
    printf("%s %d %d\n",test->nombre, test->num_estados, test->num_simbolos);  
    test->alfabeto = alfabetoInsertaSimbolo(test->alfabeto, "0");
    test->alfabeto = alfabetoInsertaSimbolo(test->alfabeto, "1");
    test->alfabeto = alfabetoInsertaSimbolo(test->alfabeto, "2");
    test->alfabeto = alfabetoInsertaSimbolo(test->alfabeto, "3");
    alfabetoImprime(stdout, test->alfabeto);
    //free afnd
    
    return 0;
}