CC = gcc
HEAD = estructuras.h
OBJ = main.o
OPT = -std=c99
PROG = troyx

$(PROG): $(OBJ)
	$(CC) $(OBJ) -o $(PROG) $(OPT)

main.o: estructuras.h main.c $(HEAD)
	$(CC) -c main.c $(OPT)

clean:
	rm $(OBJ) $(PROG)
