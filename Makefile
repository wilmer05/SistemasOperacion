CC = gcc
HEAD = estructuras.h
OBJ = main.o
OPT = -std=c99
PROG = troyx

$(PROG): $(HEAD) $(OBJ)
	$(CC) $(OBJ) -o $(PROG) $(OPT)

main.o: $(HEAD) main.c
	$(CC) -c main.c $(OPT)

clean:
	rm $(OBJ) $(PROG)
