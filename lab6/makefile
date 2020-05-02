# Name: Geoffrey Kerr
# Lab 5

all: clean spiritd mole
.PHONY: all

clean:
	rm -f spiritd spiritd.o *~
	rm -f mole mole.o *~

spiritd:
	gcc -g -c spiritd.c -Wall -Wextra
	gcc -g -o spiritd spiritd.o

mole:
	gcc -g -c mole.c -Wall -Wextra
	gcc -g -o mole mole.o

a:
	vim spiritd.c 

s:
	vim mole.c
