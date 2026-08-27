# ============================================================================
# Ingeniería en Inteligencia Artificial - Algoritmos y Estructura de Datos
# 2C 2026 | Docente: Ing. Magali Marijuan
# ============================================================================

# Makefile - Tut 03 EXTRA (Lista doble, lista circular e iteradores)
# Flags estrictos de la materia.

CXX      = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -Wconversion -Werror
TARGET   = ejercicios-extra
OBJS     = main.o ejercicios.o

# Compila el ejecutable (target por defecto).
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp ejercicios.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ejercicios.o: ejercicios.cpp ejercicios.h
	$(CXX) $(CXXFLAGS) -c ejercicios.cpp

# Compila (si hace falta) y corre las pruebas.
run: $(TARGET)
	./$(TARGET)

# Compila y corre las pruebas bajo Valgrind, para detectar memory leaks y
# accesos inválidos a memoria (clave en lista doble y, sobre todo, circular).
# Nota: en Mac con Apple Silicon, valgrind no está disponible nativamente.
# Usá `make docker-valgrind` en ese caso.
valgrind: $(TARGET)
	valgrind -s --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Igual que `valgrind`, pero corriendo dentro de un container Linux (vía
# Docker). Sirve para Mac con Apple Silicon, donde valgrind no anda nativo.
docker-valgrind:
	docker build -t tut03-extra-valgrind .
	docker run --rm -v "$(CURDIR)":/app -w /app tut03-extra-valgrind bash -c "make clean && make valgrind"

# Borra los archivos generados.
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run valgrind docker-valgrind clean
