OBJS	= example.o canLinux.o MESCAN1_Utilitaire.o MESCAN1_VarStatusTrain.o MESCAN1_VarTrain.o

SOURCE	= ../example.c ../Libs_Unirail/CAN/canLinux.c ../Libs_Unirail/CAN/MESCAN1_Utilitaire.c ../Libs_Unirail/CAN/MESCAN1_VarStatusTrain.c ../Libs_Unirail/CAN/MESCAN1_VarTrain.c

HEADER	= ../Libs_Unirail/CAN/canLinux.h ../Libs_Unirail/CAN/MESCAN1_Utilitaire.h ../Libs_Unirail/CAN/loco_MAIN_PARAMS.h ../Libs_Unirail/CAN/MESCAN1_DefinitionVariable.h ../Libs_Unirail/CAN/MESCAN1_MAIN_PARAMS.h ../Libs_Unirail/CAN/MESCAN1_VarStatusTrain.h ../Libs_Unirail/CAN/MESCAN1_VarTrain.h

OUT	= example.exe

CC	 = gcc

FLAGS	 = -g -c -Wall

LFLAGS	 = -lpthread -lm -lwiringPi

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

example.o: ../example.c
	$(CC) $(FLAGS) ../example.c 

canLinux.o: ../Libs_Unirail/CAN/canLinux.c
	$(CC) $(FLAGS) ../Libs_Unirail/CAN/canLinux.c 

MESCAN1_Utilitaire.o: ../Libs_Unirail/CAN/MESCAN1_Utilitaire.c
	$(CC) $(FLAGS) ../Libs_Unirail/CAN/MESCAN1_Utilitaire.c 

MESCAN1_VarStatusTrain.o: ../Libs_Unirail/CAN/MESCAN1_VarStatusTrain.c
	$(CC) $(FLAGS) ../Libs_Unirail/CAN/MESCAN1_VarStatusTrain.c 

MESCAN1_VarTrain.o: ../Libs_Unirail/CAN/MESCAN1_VarTrain.c
	$(CC) $(FLAGS) ../Libs_Unirail/CAN/MESCAN1_VarTrain.c 


clean:
	rm -f $(OBJS) $(OUT)