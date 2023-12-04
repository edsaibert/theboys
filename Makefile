CFLAGS = -Wall
CC = gcc -g

INCLUDE = ./include
LIB = ./lib
OBJ = ./obj

all: main

main: main.o libed
	$(CC) -o main $(OBJ)/*.o -lm

libed: fila.o conjunto.o lista.o entidades.o eventos.o

main.o: main.c
	$(CC) -c $(CFLAGS) $< -I $(INCLUDE) -o $(OBJ)/$@

%.o: $(LIB)/%.c $(INCLUDE)/%.h
	$(CC) -c $(CFLAGS) $< -I $(INCLUDE) -o $(OBJ)/$@

clean:
	rm -f $(OBJ)/*.o main
