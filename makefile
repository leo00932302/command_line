CC = gcc
flags = -Wall -Wextra
main : main.o
	$(CC) $(flags) main.c -o main
clean :
	rm -rf *.o main