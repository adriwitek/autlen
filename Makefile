all: clean automatas
automatas: automatas.c	
	gcc -Wall -g -o automatas automatas.c alfabeto.c estado.c palabra.c vector.c afnd.c relacion.c



palabra.o: palabra.c 
	gcc -Wall -c palabra.c -o palabra.o	
run:
	./automatas	
.PHONY: clean all
clean:
	rm -f *.o	
	rm -f automatas
