#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int somaNaturais(int numero) {
    if (numero == 1 || numero == 0) {
        printf("%d", numero);
        return numero;
    }
    
    printf("%d", numero);
    
    if (numero > 1) {
        printf("+");
    }
    
    return numero + somaNaturais(numero - 1);
}

int main() {
    printf("somaNaturais: ");
    int soma = somaNaturais(5);
    printf(" = %d", soma);
    return 0;
}