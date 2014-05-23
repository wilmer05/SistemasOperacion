CC = gcc
HEAD = operaciones.h estructura.h lista.h
OBJ = operaciones.o lista.o main.o
OPT = -std=c99
PROG = fileTree

$(PROG): $(OBJ)
	$(CC) $(OBJ) -o $(PROG) $(OPT)

main.o: operaciones.o main.c $(HEAD)
	$(CC) -c main.c $(OPT)

operaciones.o: lista.o operaciones.c $(HEAD)
	$(CC) -c operaciones.c $(OPT)

lista.o: lista.c estructura.h
	$(CC) -c lista.c $(OPT)

clean:
	rm $(OBJ) $(PROG)
