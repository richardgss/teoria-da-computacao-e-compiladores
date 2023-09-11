#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int potencia(int base, int expoente) {
    if (base == 0) {
        return 0;
    } else if (expoente == 0) {
        return 1;
    }
    
    printf("%d", base);
    
    if (expoente > 1) {
        printf("*");
    }
    
    return base * potencia(base, expoente - 1);
}

int main() {
    printf("potencia de 5^5 = ");
    int pot = potencia(5, 5);
    printf(" = %d", pot);
    return 0;
}