
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"palabra.h"
int main (int argc, char **argv)
{
        Palabra * pal;

        pal = palabraNueva();

        palabraElimina(pal);

        return 0;
}
