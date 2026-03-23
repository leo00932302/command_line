CC = gcc
FLAG = -Wall -Wextra

main : main.o function.o
	$(CC) $(FLAG) main.c -o main

function : function.o
	$(CC) $(FLAG) function.c -o function.o
	
.PHONY = clean
clean :
	rm -rf *.o main