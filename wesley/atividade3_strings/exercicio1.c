#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* yes_or_no(int val) {
    return val == 0 ? "NAO" : "SIM";
}

void exemplo_isalpha(char c) {
    printf("O caracter '%c' e uma letra? %s\n", c, yes_or_no(isalpha(c)));
}

void exemplo_isdigit(char c) {
    printf("O caracter '%c' e um digito? %s\n", c, yes_or_no(isdigit(c)));
}

void exemplo_isupper(char c) {
    printf("O caracter '%c' e maiusculo? %s\n", c, yes_or_no(isupper(c)));
}

void exemplo_islower(char c) {
    printf("O caracter '%c' e minusculo? %s\n", c, yes_or_no(islower(c)));
}

void exemplo_isalnum(char c) {
    printf("O caracter '%c' e letra ou digito? %s\n", c, yes_or_no(isalnum(c)));
}

void exemplos(char c) {
    exemplo_isalpha(c);
    exemplo_isdigit(c);
    exemplo_isupper(c);
    exemplo_islower(c);
    exemplo_isalnum(c);
}

int main() {
    char c;
    
    c = 'A';
    exemplos(c);
    
    c = '!';
    exemplos(c);
    return 0;
}