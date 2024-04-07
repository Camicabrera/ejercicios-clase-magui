#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void setDiminutivo(const char *nombre, char *diminutivo) {
    if (nombre == NULL) {
        return;
    }
    strcpy(diminutivo, nombre);

    if (diminutivo[strlen(diminutivo) - 1] == 'a') { 
        diminutivo[strlen(diminutivo) - 1] = '\0';
        strcat(diminutivo, "ica");
    } else if (diminutivo[strlen(diminutivo) - 1] == 'o') {
        diminutivo[strlen(diminutivo) - 1] = '\0';
        strcat(diminutivo, "ico");
    }
}

char* getDiminutivo(const char* nombre) {
    // cambie el malloc a +3 ya que con +1 no alcanzaba la memoria.
    char * diminutivo = malloc(sizeof(char) * strlen(nombre) + 3);
    setDiminutivo(nombre, diminutivo);
    if (diminutivo == NULL) {
        free(diminutivo);
        return NULL;
    }

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
    // Cambie los ordenes de los argumentos de testDiminutivo ya que estaban mal en el main.
    // TEST 1
    char* test_1 = "magali";
    char* expected_1 = "magali";
    char* test_1_result = getDiminutivo(test_1);
    testDiminutivo( test_1_result, expected_1);
    free(test_1_result);

    // TEST 2
    char* test_2 = "roberto";
    char* expected_2 = "robertico";
    char* test_2_result = getDiminutivo(test_2);
    testDiminutivo( test_2_result , expected_2);
    free(test_2_result);

    // TEST 3
    char* test_3 = "marta";
    char* expected_3 = "martica";
    char* test_3_result = getDiminutivo(test_3);
    testDiminutivo( test_3_result , expected_3);
    free(test_3_result);
    
    // TEST 4
    char* test_4 = "juan";
    char* expected_4 = "juan";
    char* test_4_result = getDiminutivo(test_4);
    testDiminutivo( test_4_result , expected_4);
    free(test_4_result);

    return 0;
}
