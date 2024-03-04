#include <stdlib.h>
#include <stdio.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    
    *ptr = 10;

    printf("%d", *ptr);
    
    return 0;
}