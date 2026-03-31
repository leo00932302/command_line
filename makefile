CC = gcc
FLAG = -Wall -Wextra

main : main.o function.o
	$(CC) $(FLAG) main.o function.o -o main

main.o : main.c function.h
	$(CC) $(FLAG) -c main.c -o main.o

function.o : function.c function.h
	$(CC) $(FLAG) -c function.c -o function.o


.PHONY = clean
clean :
	rm -rf *.o main