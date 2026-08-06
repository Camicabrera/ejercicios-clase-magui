CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g

all: ejercicios

ejercicios: ejercicios.c testing.c testing.h
	$(CC) $(CFLAGS) -o ejercicios ejercicios.c testing.c

resuelto: resuelto.c testing.c testing.h
	$(CC) $(CFLAGS) -o resuelto resuelto.c testing.c

valgrind: ejercicios
	valgrind --leak-check=full --error-exitcode=1 ./ejercicios

valgrind-resuelto: resuelto
	valgrind --leak-check=full --error-exitcode=1 ./resuelto

docker:
	docker build -t practica5 .
	docker run --rm practica5

clean:
	rm -f ejercicios resuelto

.PHONY: all clean valgrind valgrind-resuelto docker
