all: clean palabra.o test test_2 test_3



palabra.o: palabra.c 
	gcc -Wall -c palabra.c -o palabra.o
test:  test.c palabra.o
	gcc -Wall palabra.o test.c -o test

test_2:  test_2.c palabra.o
	gcc -Wall palabra.o test_2.c -o test_2

test_3:  test_3.c palabra.o
	gcc -Wall palabra.o test_3.c -o test_3		

clean:
	rm -f *.o	
	rm -f test test_2 test_3