CC = gcc
HEAD = estructuras.h entrada.h
OBJ = main_con_hilos.o
OPT = -std=c99 -lpthread
PROG = toyx_con_hilos
PROG2 = toyx_con_procesos

$(PROG): $(HEAD) $(OBJ)
	$(CC) $(OBJ) -o $(PROG) $(OPT)

main_con_hilos.o: $(HEAD) main_con_hilos.c
	$(CC) -c main_con_hilos.c $(OPT)

clean:
	rm $(OBJ) $(PROG) Part.*
