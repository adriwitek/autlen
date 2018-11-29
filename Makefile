all: clean automatas
automatas: automatas.c	
	gcc -Wall -g -o automatas automatas.c alfabeto.c estado.c palabra.c vector.c afnd.c relacion.c
test3: test3.c
	gcc -Wall -g -o test3 test3.c alfabeto.c estado.c palabra.c vector.c afnd.c relacion.c

palabra.o: palabra.c 
	gcc -Wall -c palabra.c -o palabra.o	


test_relacion:
	gcc -Wall -g -o test_relacion test_relacion.c alfabeto.c estado.c palabra.c vector.c afnd.c relacion.c

run:
	./automatas	
.PHONY: clean all
clean:
	rm -f *.o	
	rm -f automatas
