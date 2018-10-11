#include "palabra.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
        Palabra * pal;

        pal = palabraNueva();

        palabraElimina(pal);

        return 0;
}
