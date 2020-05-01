# Name:Geoffrey Kerr
# Lab 4

all: clean dining-p
.PHONY: all

clean:
	rm -f dining-p dining-p.o *~

dining-p:
	gcc -g -c dining-p.c -Wall -Wextra
	gcc -g -o dining-p dining-p.o -lpthread -lrt

a:
	vim dining-p.c

s: 
	vim launch-philosophers.sh

d:
	./launch-philosophers.sh 5

