CFLAGS = -Wall# flags de compilacao
CC = gcc -g

INCLUDE = ./include# pasta com .h
LIB = ./lib# pasta com .c (bibliotecas)
OBJ = ./obj# pasta com .o (objetos), dessa forma, a manutenção é mais fácil

all: main.o libed 
	$(CC) -o main $(OBJ)/*.o

libed: fila.o conjunto.o lista.o vetor.o theboys.o

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $(OBJ)/$@

%.o: $(LIB)/%.c $(INCLUDE)/%.h
	$(CC) -c $(CFLAGS) $< -I $(INCLUDE) -o $(OBJ)/$@

clean:
	rm -f $(OBJ)/*.o $(OBJ)/*.o
