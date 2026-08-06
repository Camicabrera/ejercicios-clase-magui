# ============================================================================
# Ingeniería en Inteligencia Artificial - Algoritmos y Estructura de Datos
# 2C 2026 | Docente: Magali Marijuan
# ============================================================================

# Makefile - Tut 01 (Introducción a C++)
# Flags estrictos de la materia.

CXX      = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -Wconversion -Werror
TARGET   = ejercicios
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

# Borra los archivos generados.
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
