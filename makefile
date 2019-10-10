CFLAGS=-ansi -Wall -pedantic
LFLAGS=-std=gnu11 -lm 
CC=gcc

all: RBC EVC

RBC: RBC.c
	gcc -o RBC RBC.c

EVC: EVC.c
	gcc -o EVC EVC.c

force:
	touch RBC.c
	touch EVC.c
	make