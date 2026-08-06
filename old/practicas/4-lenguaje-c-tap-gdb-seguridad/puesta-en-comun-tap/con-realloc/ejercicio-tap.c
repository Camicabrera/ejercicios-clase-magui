#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setDiminutivo(const char *nombre, char **diminutivo) {

    strcpy(*diminutivo, nombre);
    size_t newLength = strlen(*diminutivo) + 3;

    char *try = realloc(*diminutivo, newLength);

    if (!try)return;

    *diminutivo = try;

    unsigned long len = strlen(*diminutivo);

    ((*diminutivo)[len-1]) = 'i';
    ((*diminutivo)[len]) = 'c';
    ((*diminutivo)[len+1]) = nombre[len - 1];
    ((*diminutivo)[len+2]) = '\0';
}


char* getDiminutivo(const char* nombre) {

    if(!nombre) return NULL;

    char lastChar = nombre[strlen(nombre)-1];
    char * diminutivo = malloc(sizeof(char) * (strlen(nombre) + 1));

    if(!diminutivo) return NULL;

    if(lastChar == 'a' || lastChar == 'o')
        setDiminutivo(nombre, &diminutivo);
    else
        strcpy(diminutivo, nombre);

    return diminutivo;
}

void testDiminutivo(char* actual, char* expected) {
    if(strcmp(actual, expected)){
        printf("TEST FAILED | Actual: %s Expected: %s \n", actual, expected);
    }
    else {
        printf("TEST PASSED |  Actual: %s Expected: %s \n", actual, expected);
    }
}

int main() {

    // TEST 1
    char* test_1 = "magali";
    char* expected_1 = "magali";
    char* test_1_result = getDiminutivo(test_1);
    testDiminutivo(expected_1, test_1_result);
    free(test_1_result);

    // TEST 2
    char* test_2 = "roberto";
    char* expected_2 = "robertico";
    char* test_2_result = getDiminutivo(test_2);
    testDiminutivo(expected_2, test_2_result);
    free(test_2_result);

    // TEST 3
    char* test_3 = "marta";
    char* expected_3 = "martica";
    char* test_3_result = getDiminutivo(test_3);
    testDiminutivo(expected_3, test_3_result);
    free(test_3_result);
    
    // TEST 4
    char* test_4 = "juan";
    char* expected_4 = "juan";
    char* test_4_result = getDiminutivo(test_4);
    testDiminutivo(expected_4, test_4_result);
    free(test_4_result);

    return 0;
}
