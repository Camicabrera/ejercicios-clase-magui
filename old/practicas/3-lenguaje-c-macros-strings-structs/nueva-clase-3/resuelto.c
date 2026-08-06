/**
 * Práctica 3 - Lenguaje C: Macros, Strings y Structs (RESUELTO)
 * ==============================================================
 *
 * Compilar:  gcc -std=c99 -Wall -Wextra -g -o resuelto resuelto.c
 * Ejecutar:  ./resuelto
 * Valgrind:  valgrind --leak-check=full ./resuelto
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================
 * FRAMEWORK DE PRUEBAS
 * ======================================================================== */

static int tests_totales = 0;
static int tests_ok = 0;
static int tests_fail = 0;

#define TEST(nombre) do { \
    tests_totales++; \
    printf("  [TEST] %-50s ", nombre); \
} while(0)

#define ASSERT_EQ_INT(esperado, obtenido) do { \
    int _e = (esperado), _o = (obtenido); \
    if (_e == _o) { \
        printf("OK\n"); tests_ok++; \
    } else { \
        printf("FAIL (esperado: %d, obtenido: %d)\n", _e, _o); \
        tests_fail++; \
    } \
} while(0)

#define ASSERT_EQ_STR(esperado, obtenido) do { \
    const char* _e = (esperado); \
    const char* _o = (obtenido); \
    if (_e == NULL && _o == NULL) { \
        printf("OK\n"); tests_ok++; \
    } else if (_e && _o && strcmp(_e, _o) == 0) { \
        printf("OK\n"); tests_ok++; \
    } else { \
        printf("FAIL (esperado: \"%s\", obtenido: \"%s\")\n", \
               _e ? _e : "NULL", _o ? _o : "NULL"); \
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
 * ESTRUCTURAS
 * ======================================================================== */

typedef struct {
    char* nombre;
    char* telefono;
    char* email;
} Contacto;

typedef struct {
    Contacto** contactos;
    int cantidad;
    int capacidad;
} Agenda;

/* ========================================================================
 * EJERCICIO 1: Funciones de strings desde cero
 * ======================================================================== */

/*
 * mi_strlen: recorremos el string hasta encontrar '\0'.
 * Cada carácter que NO es '\0' suma 1 a la longitud.
 *
 *   "hola"  en memoria es: ['h']['o']['l']['a']['\0']
 *                            ^0   ^1   ^2   ^3   ^4
 *   Longitud = 4 (el '\0' no cuenta)
 */
int mi_strlen(const char* str) {
    if (str == NULL) return -1;

    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

/*
 * mi_strcpy: copiamos carácter por carácter, INCLUYENDO el '\0'.
 * El '\0' es lo que le dice a todas las funciones de C dónde termina
 * el string. Si no lo copiamos, dst queda con basura al final.
 */
char* mi_strcpy(char* dst, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';  // CRUCIAL: sin esto, dst no es un string válido
    return dst;
}

/*
 * mi_strcmp: comparamos carácter a carácter.
 * Si ambos caracteres son iguales y no son '\0', avanzamos.
 * Si encontramos una diferencia o el '\0', la resta nos da el resultado.
 */
int mi_strcmp(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) {
        i++;
    }
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

void test_ejercicio_1(void) {
    SECCION("EJERCICIO 1: Funciones de strings");

    TEST("mi_strlen de string vacío");
    ASSERT_EQ_INT(0, mi_strlen(""));

    TEST("mi_strlen de \"hola\"");
    ASSERT_EQ_INT(4, mi_strlen("hola"));

    TEST("mi_strlen de string con espacios");
    ASSERT_EQ_INT(11, mi_strlen("hola mundo!"));

    TEST("mi_strlen con NULL devuelve -1");
    ASSERT_EQ_INT(-1, mi_strlen(NULL));

    char buffer[20];
    memset(buffer, 'X', sizeof(buffer));

    TEST("mi_strcpy copia contenido");
    mi_strcpy(buffer, "test");
    ASSERT_EQ_STR("test", buffer);

    TEST("mi_strcpy pone \\0 al final");
    ASSERT_EQ_INT('\0', buffer[4]);

    TEST("mi_strcpy de string vacío");
    mi_strcpy(buffer, "");
    ASSERT_EQ_INT('\0', buffer[0]);

    TEST("mi_strcmp iguales");
    ASSERT_EQ_INT(0, mi_strcmp("abc", "abc"));

    TEST("mi_strcmp primero menor");
    ASSERT_TRUE(mi_strcmp("abc", "abd") < 0);

    TEST("mi_strcmp primero mayor");
    ASSERT_TRUE(mi_strcmp("abd", "abc") > 0);

    TEST("mi_strcmp distinta longitud");
    ASSERT_TRUE(mi_strcmp("ab", "abc") < 0);
}

/* ========================================================================
 * EJERCICIO 2: Duplicar y concatenar strings con memoria dinámica
 * ======================================================================== */

/*
 * mi_strdup: necesitamos strlen + 1 bytes.
 * El +1 es para el '\0'. Este es el error más común en C:
 *
 *   "hola" necesita 5 bytes: h, o, l, a, \0
 *   Si hacemos malloc(4), el '\0' se escribe fuera del bloque → UB
 */
char* mi_strdup(const char* str) {
    if (str == NULL) return NULL;

    int len = mi_strlen(str);
    char* copia = malloc(len + 1);  // +1 para el '\0'
    if (copia == NULL) return NULL;

    mi_strcpy(copia, str);
    return copia;
}

/*
 * mi_strconcat: hay que sumar las longitudes + 1 '\0' al final.
 *
 *   "hola" (4) + " mundo" (6) + '\0' (1) = 11 bytes
 *
 * Tratamos NULL como "": esto simplifica la lógica y evita segfaults.
 */
char* mi_strconcat(const char* s1, const char* s2) {
    if (s1 == NULL) s1 = "";
    if (s2 == NULL) s2 = "";

    int len1 = mi_strlen(s1);
    int len2 = mi_strlen(s2);
    char* resultado = malloc(len1 + len2 + 1);
    if (resultado == NULL) return NULL;

    mi_strcpy(resultado, s1);
    mi_strcpy(resultado + len1, s2);  // Copiamos s2 a partir de donde termina s1
    return resultado;
}

void test_ejercicio_2(void) {
    SECCION("EJERCICIO 2: Duplicar y concatenar strings");

    TEST("mi_strdup copia el contenido");
    char* dup = mi_strdup("hola");
    ASSERT_EQ_STR("hola", dup);

    TEST("mi_strdup devuelve memoria nueva (no el mismo puntero)");
    ASSERT_TRUE(dup != "hola");
    free(dup);

    TEST("mi_strdup de string vacío");
    dup = mi_strdup("");
    ASSERT_EQ_STR("", dup);

    TEST("mi_strdup de string vacío: \\0 presente");
    ASSERT_EQ_INT('\0', dup[0]);
    free(dup);

    TEST("mi_strdup de NULL devuelve NULL");
    ASSERT_NULL(mi_strdup(NULL));

    TEST("mi_strconcat de dos strings");
    char* concat = mi_strconcat("hola", " mundo");
    ASSERT_EQ_STR("hola mundo", concat);
    free(concat);

    TEST("mi_strconcat con primer NULL");
    concat = mi_strconcat(NULL, "mundo");
    ASSERT_EQ_STR("mundo", concat);
    free(concat);

    TEST("mi_strconcat con segundo NULL");
    concat = mi_strconcat("hola", NULL);
    ASSERT_EQ_STR("hola", concat);
    free(concat);

    TEST("mi_strconcat con ambos vacíos");
    concat = mi_strconcat("", "");
    ASSERT_EQ_STR("", concat);
    free(concat);
}

/* ========================================================================
 * EJERCICIO 3: Crear y destruir un Contacto
 * ======================================================================== */

/*
 * crear_contacto: hacemos 4 mallocs (1 struct + hasta 3 strings).
 * Si algún malloc falla, hay que liberar todo lo que ya pedimos.
 *
 * Layout en memoria de un Contacto con email:
 *
 *   [Contacto]  →  nombre → [A][n][a][\0]
 *               →  telefono → [1][2][3][4][\0]
 *               →  email → [a][n][a][@][m][a][i][l][.][c][o][m][\0]
 *
 * Son 4 bloques independientes. Todos deben ser liberados.
 */
Contacto* crear_contacto(const char* nombre, const char* telefono, const char* email) {
    if (nombre == NULL || telefono == NULL) return NULL;

    Contacto* c = malloc(sizeof(Contacto));
    if (c == NULL) return NULL;

    c->nombre = mi_strdup(nombre);
    if (c->nombre == NULL) {
        free(c);
        return NULL;
    }

    c->telefono = mi_strdup(telefono);
    if (c->telefono == NULL) {
        free(c->nombre);
        free(c);
        return NULL;
    }

    if (email != NULL) {
        c->email = mi_strdup(email);
        if (c->email == NULL) {
            free(c->telefono);
            free(c->nombre);
            free(c);
            return NULL;
        }
    } else {
        c->email = NULL;
    }

    return c;
}

/*
 * destruir_contacto: liberar en cualquier orden, pero no olvidar nada.
 * Importante: free(NULL) es seguro en C, así que no hace falta chequear
 * email antes de liberarlo.
 */
void destruir_contacto(Contacto* c) {
    if (c == NULL) return;
    free(c->nombre);
    free(c->telefono);
    free(c->email);    // free(NULL) es válido, no necesita if
    free(c);
}

void test_ejercicio_3(void) {
    SECCION("EJERCICIO 3: Crear y destruir Contacto");

    TEST("crear_contacto devuelve no-NULL");
    Contacto* c = crear_contacto("Ana", "1234", "ana@mail.com");
    ASSERT_NOT_NULL(c);

    if (c) {
        TEST("nombre se copió correctamente");
        ASSERT_EQ_STR("Ana", c->nombre);

        TEST("teléfono se copió correctamente");
        ASSERT_EQ_STR("1234", c->telefono);

        TEST("email se copió correctamente");
        ASSERT_EQ_STR("ana@mail.com", c->email);

        const char* nombre_orig = "Ana";
        TEST("nombre es una copia (distinto puntero)");
        ASSERT_TRUE(c->nombre != nombre_orig);

        destruir_contacto(c);
    }

    TEST("crear_contacto con email NULL");
    c = crear_contacto("Bob", "5678", NULL);
    ASSERT_NOT_NULL(c);
    if (c) {
        TEST("email es NULL cuando se pasa NULL");
        ASSERT_NULL(c->email);
        destruir_contacto(c);
    }

    TEST("crear_contacto con nombre NULL devuelve NULL");
    ASSERT_NULL(crear_contacto(NULL, "1234", "x@y.com"));

    TEST("crear_contacto con teléfono NULL devuelve NULL");
    ASSERT_NULL(crear_contacto("Ana", NULL, "x@y.com"));

    TEST("destruir_contacto(NULL) no crashea");
    destruir_contacto(NULL);
    ASSERT_TRUE(1);
}

/* ========================================================================
 * EJERCICIO 4: Agenda - agregar y buscar contactos
 * ======================================================================== */

/*
 * crear_agenda: dos mallocs: la Agenda y el array de punteros.
 *
 *   [Agenda] → contactos → [ptr][ptr][...][capacidad slots]
 *              cantidad = 0
 *              capacidad = capacidad_inicial
 */
Agenda* crear_agenda(int capacidad_inicial) {
    if (capacidad_inicial <= 0) return NULL;

    Agenda* ag = malloc(sizeof(Agenda));
    if (ag == NULL) return NULL;

    ag->contactos = malloc(sizeof(Contacto*) * capacidad_inicial);
    if (ag->contactos == NULL) {
        free(ag);
        return NULL;
    }

    ag->cantidad = 0;
    ag->capacidad = capacidad_inicial;
    return ag;
}

/*
 * agenda_agregar: si está llena, duplicamos con realloc.
 *
 * realloc puede:
 *   1. Expandir el bloque in-place (rápido)
 *   2. Pedir un bloque nuevo, copiar, y liberar el viejo
 *   3. Fallar → devuelve NULL, el bloque original sigue válido
 *
 * Por eso guardamos el resultado de realloc en un temporal:
 * si falla, no perdemos el puntero original.
 */
int agenda_agregar(Agenda* agenda, const char* nombre, const char* telefono, const char* email) {
    if (agenda == NULL) return -1;

    // ¿Necesitamos más espacio?
    if (agenda->cantidad >= agenda->capacidad) {
        int nueva_cap = agenda->capacidad * 2;
        Contacto** nuevo_array = realloc(agenda->contactos, sizeof(Contacto*) * nueva_cap);
        if (nuevo_array == NULL) return -1;
        agenda->contactos = nuevo_array;
        agenda->capacidad = nueva_cap;
    }

    Contacto* nuevo = crear_contacto(nombre, telefono, email);
    if (nuevo == NULL) return -1;

    agenda->contactos[agenda->cantidad] = nuevo;
    agenda->cantidad++;
    return 0;
}

/*
 * agenda_buscar: recorremos y comparamos nombres con mi_strcmp.
 * Devolvemos el puntero directo (no una copia), así el caller
 * puede leer los datos pero no debería liberar la memoria.
 */
Contacto* agenda_buscar(Agenda* agenda, const char* nombre) {
    if (agenda == NULL || nombre == NULL) return NULL;

    for (int i = 0; i < agenda->cantidad; i++) {
        if (mi_strcmp(agenda->contactos[i]->nombre, nombre) == 0) {
            return agenda->contactos[i];
        }
    }
    return NULL;
}

void test_ejercicio_4(void) {
    SECCION("EJERCICIO 4: Agenda - agregar y buscar");

    TEST("crear_agenda devuelve no-NULL");
    Agenda* ag = crear_agenda(2);
    ASSERT_NOT_NULL(ag);

    if (!ag) return;

    TEST("agenda vacía tiene cantidad 0");
    ASSERT_EQ_INT(0, ag->cantidad);

    TEST("capacidad inicial correcta");
    ASSERT_EQ_INT(2, ag->capacidad);

    TEST("agregar primer contacto");
    ASSERT_EQ_INT(0, agenda_agregar(ag, "Ana", "1111", "ana@mail.com"));

    TEST("cantidad después de agregar");
    ASSERT_EQ_INT(1, ag->cantidad);

    TEST("agregar segundo contacto");
    ASSERT_EQ_INT(0, agenda_agregar(ag, "Bob", "2222", NULL));

    TEST("agregar tercero (requiere realloc)");
    ASSERT_EQ_INT(0, agenda_agregar(ag, "Carlos", "3333", "carlos@mail.com"));

    TEST("capacidad creció después de realloc");
    ASSERT_TRUE(ag->capacidad >= 3);

    TEST("buscar contacto existente");
    Contacto* encontrado = agenda_buscar(ag, "Bob");
    ASSERT_NOT_NULL(encontrado);

    if (encontrado) {
        TEST("contacto encontrado tiene datos correctos");
        ASSERT_EQ_STR("2222", encontrado->telefono);
    }

    TEST("buscar contacto inexistente");
    ASSERT_NULL(agenda_buscar(ag, "Zoe"));

    for (int i = 0; i < ag->cantidad; i++) {
        destruir_contacto(ag->contactos[i]);
    }
    free(ag->contactos);
    free(ag);
}

/* ========================================================================
 * EJERCICIO 5: Destruir y duplicar la agenda completa
 * ======================================================================== */

/*
 * destruir_agenda: hay que liberar en orden inverso a la construcción.
 * Primero cada contacto (con sus strings), después el array, y por
 * último la agenda.
 */
void destruir_agenda(Agenda* agenda) {
    if (agenda == NULL) return;

    for (int i = 0; i < agenda->cantidad; i++) {
        destruir_contacto(agenda->contactos[i]);
    }
    free(agenda->contactos);
    free(agenda);
}

/*
 * duplicar_agenda: deep copy = copiar TODOS los niveles.
 *
 * Original:                          Copia:
 * [Agenda]─→[*ptr1][*ptr2][*ptr3]    [Agenda]─→[*ptr1'][*ptr2'][*ptr3']
 *             │      │      │                     │       │       │
 *             ▼      ▼      ▼                     ▼       ▼       ▼
 *          [Ana]  [Bob]  [Carlos]              [Ana']  [Bob']  [Carlos']
 *           │      │      │                     │       │       │
 *           ▼      ▼      ▼                     ▼       ▼       ▼
 *         "Ana"  "Bob"  "Carlos"              "Ana"   "Bob"   "Carlos"
 *
 * Si falla a mitad de camino, liberamos todo lo que ya copiamos.
 */
Agenda* duplicar_agenda(Agenda* agenda) {
    if (agenda == NULL) return NULL;

    Agenda* copia = crear_agenda(agenda->capacidad);
    if (copia == NULL) return NULL;

    for (int i = 0; i < agenda->cantidad; i++) {
        Contacto* orig = agenda->contactos[i];
        int resultado = agenda_agregar(copia, orig->nombre, orig->telefono, orig->email);
        if (resultado != 0) {
            // Falló: liberar todo lo que ya copiamos
            destruir_agenda(copia);
            return NULL;
        }
    }

    return copia;
}

void test_ejercicio_5(void) {
    SECCION("EJERCICIO 5: Destruir y duplicar agenda");

    Agenda* ag = crear_agenda(2);
    if (!ag) {
        printf("  Skipping: crear_agenda no implementada\n");
        return;
    }

    agenda_agregar(ag, "Ana", "1111", "ana@mail.com");
    agenda_agregar(ag, "Bob", "2222", NULL);
    agenda_agregar(ag, "Carlos", "3333", "carlos@mail.com");

    TEST("duplicar_agenda devuelve no-NULL");
    Agenda* copia = duplicar_agenda(ag);
    ASSERT_NOT_NULL(copia);

    if (copia) {
        TEST("copia tiene misma cantidad");
        ASSERT_EQ_INT(ag->cantidad, copia->cantidad);

        TEST("copia tiene los mismos datos");
        Contacto* c = agenda_buscar(copia, "Ana");
        ASSERT_NOT_NULL(c);

        if (c) {
            TEST("datos del contacto copiado son correctos");
            ASSERT_EQ_STR("ana@mail.com", c->email);

            TEST("contacto copiado es independiente (distinto puntero)");
            Contacto* orig = agenda_buscar(ag, "Ana");
            ASSERT_TRUE(c != orig);

            TEST("string copiado es independiente (distinto puntero)");
            ASSERT_TRUE(c->nombre != orig->nombre);
        }

        TEST("contacto con email NULL se duplica bien");
        Contacto* bob_copia = agenda_buscar(copia, "Bob");
        ASSERT_NOT_NULL(bob_copia);
        if (bob_copia) {
            TEST("email NULL se mantiene NULL en la copia");
            ASSERT_NULL(bob_copia->email);
        }

        destruir_agenda(copia);
    }

    TEST("destruir_agenda no crashea");
    destruir_agenda(ag);
    ASSERT_TRUE(1);

    TEST("destruir_agenda(NULL) no crashea");
    destruir_agenda(NULL);
    ASSERT_TRUE(1);
}

/* ========================================================================
 * MAIN
 * ======================================================================== */

int main(void) {
    printf("Práctica 3: Agenda de Contactos (RESUELTO)\n");
    printf("============================================\n");

    test_ejercicio_1();
    test_ejercicio_2();
    test_ejercicio_3();
    test_ejercicio_4();
    test_ejercicio_5();

    printf("\n============================================\n");
    printf("Resultados: %d/%d tests pasaron", tests_ok, tests_totales);
    if (tests_fail > 0) {
        printf(" (%d fallaron)", tests_fail);
    }
    printf("\n");

    if (tests_fail > 0) {
        printf("Ejecutá con valgrind para verificar memoria:\n");
        printf("  valgrind --leak-check=full ./resuelto\n");
    } else {
        printf("Todos los tests pasaron! Verificá con valgrind:\n");
        printf("  valgrind --leak-check=full ./resuelto\n");
    }

    return tests_fail > 0 ? 1 : 0;
}
