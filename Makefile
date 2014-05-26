CC = gcc
HEAD = estructuras.h entrada.h tiempo.h
OBJ = main_con_hilos.o
OBJ2 = main_con_procesos.o
OPT = -std=c99
PROG = toyx_con_hilos
PROG2 = toyx_con_procesos

all: $(PROG) $(PROG2) 

$(PROG2): $(HEAD) $(OBJ2)
	$(CC) $(OBJ2) -o $(PROG2) $(OPT)

$(PROG): $(HEAD) $(OBJ)
	$(CC) $(OBJ) -o $(PROG) $(OPT) -lpthread

main_con_procesos.o: $(HEAD) main_con_procesos.c
	$(CC) -c main_con_procesos.c $(OPT)
	
main_con_hilos.o: $(HEAD) main_con_hilos.c
	$(CC) -c main_con_hilos.c $(OPT) -lpthread

clean:
	rm $(OBJ) $(PROG) $(OBJ2) $(PROG2) Part.*
