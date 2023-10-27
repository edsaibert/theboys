CFLAGS = -Wall# flags de compilacao
CC = gcc -g

INCLUDE = ./include# pasta com .h
LIB = ./lib# pasta com .c (bibliotecas)
OBJ = ./obj# pasta com .o (objetos), dessa forma, a manutenção é mais fácil

all: main.o libed  

libed: fila.o conjunto.o lista.o lef.o vetor.o

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $(OBJ)/$@

%.o: $(LIB)/%.c $(INCLUDE)/%.h
	$(CC) -c $(CFLAGS) $< -I $(INCLUDE) -o $(OBJ)/$@

clean:
	rm -f ./obj/*.o main 