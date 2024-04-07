#include <stdio.h>
#include <string.h>

int main() {
    char str1[10] = "Hello";
    char str2[20] = "Hello, world!";
    
    int len1 = strlen(str1); 
    printf("Length of str1: %d\n", len1);
   
    int len2 = strnlen(str2, sizeof(str2));
    printf("Length of str2: %d\n", len2);
    
    return 0;
}
