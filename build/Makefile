SOURCE	= ../EVC.c ../Libs_Unirail/CAN/canLinux.c ../Libs_Unirail/CAN/MESCAN1_Utilitaire.c ../Libs_Unirail/CAN/MESCAN1_VarStatusTrain.c ../Libs_Unirail/CAN/MESCAN1_VarTrain.c
CC = gcc
FLAGS=-std=gnu11 -Wall
LFLAGS= -lpthread -lm -lwiringPi -lrt

all: EVC RBC


EVC: $(SOURCE)
	$(CC) $(SOURCE) -o EVC $(LFLAGS) $(FLAGS)
RBC: ../RBC.c
	$(CC) ../RBC.c -o RBC $(LFLAGS) $(FLAGS)

force:
	touch ../RBC.c
	touch ../EVC.c
	make