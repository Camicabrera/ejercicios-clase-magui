/**
 * Framework de pruebas - Práctica 5
 */

#ifndef TESTING_H
#define TESTING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================
 * FRAMEWORK DE PRUEBAS
 * ======================================================================== */

extern int tests_total;
extern int tests_ok;
extern int tests_fail;

#define TEST(nombre) do { \
    tests_total++; \
    printf("  [TEST] %-50s ", nombre); \
} while(0)

#define ASSERT_EQ_INT(expected, got) do { \
    int _e = (expected), _o = (got); \
    if (_e == _o) { \
        printf("OK\n"); tests_ok++; \
    } else { \
        printf("FAIL (esperado: %d, obtenido: %d)\n", _e, _o); \
        tests_fail++; \
    } \
} while(0)

#define ASSERT_TRUE(cond) do { \
    if (cond) { \
        printf("OK\n"); tests_ok++; \
    } else { \
        printf("FAIL (condicion falsa)\n"); \
        tests_fail++; \
    } \
} while(0)

#define ASSERT_NULL(ptr) do { \
    if ((ptr) == NULL) { \
        printf("OK\n"); tests_ok++; \
    } else { \
        printf("FAIL (esperado NULL, obtenido %p)\n", (void*)(ptr)); \
        tests_fail++; \
    } \
} while(0)

#define ASSERT_NOT_NULL(ptr) do { \
    if ((ptr) != NULL) { \
        printf("OK\n"); tests_ok++; \
    } else { \
        printf("FAIL (esperado no-NULL, obtenido NULL)\n"); \
        tests_fail++; \
    } \
} while(0)

#define SECCION(nombre) printf("\n=== %s ===\n", nombre)

/* ========================================================================
 * DECLARACIONES DE TESTS (implementados en testing.c)
 * ======================================================================== */

void test_ejercicio_1(void);
void test_ejercicio_2(void);
void test_ejercicio_3(void);
void test_ejercicio_4(void);
void test_ejercicio_5(void);
void test_ejercicio_6(void);

static inline void print_results(void) {
    printf("\n==================================\n");
    printf("Resultados: %d/%d tests pasaron", tests_ok, tests_total);
    if (tests_fail > 0) {
        printf(" (%d fallaron)", tests_fail);
    }
    printf("\n");

    if (tests_fail > 0) {
        printf("Ejecutá con valgrind para verificar memoria:\n");
        printf("  valgrind --leak-check=full ./ejercicios\n");
    } else {
        printf("Todos los tests pasaron! Verificá con valgrind:\n");
        printf("  valgrind --leak-check=full ./ejercicios\n");
    }
}

#endif
