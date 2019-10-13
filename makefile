CFLAGS=-ansi -Wall -pedantic
LFLAGS=-std=gnu11 -lm 
CC=gcc

all: RBC EVC

RBC: RBC.c
	$(CC) -o RBC RBC.c $(CFLAGS) $(LFLAGS)

EVC: EVC.c
	$(CC) -o EVC EVC.c $(CFLAGS) $(LFLAGS)

force:
	touch RBC.c
	touch EVC.c
	make
