# Name: Geoffrey Kerr
# Lab 7

all: clean matrix_gen matrix_add
.PHONY: all

clean:
	rm -f matrix_gen matrix_gen.o *~
	rm -f matrix_add matrix_add.o *~

matrix_gen:
	gcc -g -c matrix_gen.c -Wall -Wextra 
	gcc -g -o matrix_gen matrix_gen.o -lrt

matrix_add:
	gcc -g -c matrix_add.c -Wall -Wextra 
	gcc -g -o matrix_add matrix_add.o -lrt

a:
	vim matrix_gen.c

s:
	vim matrix_add.c
