CFLAGS=-ansi -Wall -pedantic
LFLAGS=-std=gnu11 -lm
LDFLAGS=-pthread
CC=gcc

all: RBC EVC

RBC: RBC.c
	$(CC) -o RBC RBC.c $(CFLAGS) $(LFLAGS) $(LDFLAGS)

EVC: EVC.c
	$(CC) -o EVC EVC.c $(CFLAGS) $(LFLAGS) $(LDFLAGS)

force:
	touch RBC.c
	touch EVC.c
	make
