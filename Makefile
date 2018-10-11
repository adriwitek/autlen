all: automatas
automatas: automatas.c	
	gcc -Wall -o automatas automatas.c alfabeto.c estado.c vector.c afnd.c
.PHONY: clean all
clean:
	rm automatas
