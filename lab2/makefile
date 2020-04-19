# Name: Geoffrey Kerr
# Project: Launch-Tube

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.


# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXECUTABLES=launch
SRC=launch.c
OBJ=launch.o

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC=gcc
CFLAGS=-g

# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables
all: launch tube clean
.PHONY: all

launch:
	gcc -g -c launch.c -Wall -Wextra
	gcc -g -o launch launch.o

tube:
	gcc -g -c tube.c -Wall -Wextra
	gcc -g -o tube tube.o

clean:
	rm -f launch.o tube.o *~


a:
	vim launch.c

s:
	vim tube.c
