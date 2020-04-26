# Name:Geoffrey Kerr
# Lab 3

all:
	gcc -g -c catcher.c -Wall -Wextra
	gcc -g -o catcher catcher.o

catcher:
	gcc -g -c catcher.c -Wall -Wextra
	gcc -g -o catcher catcher.o

clean:
	rm -f catcher catcher.o *~

a:
	vim catcher.c

s:
	./catcher TERM USR1 USR2

d:
	./catcher TERM USR1 USR2 >/dev/null
