//
// Created by Richard on 19/11/2023.
//

#include <stdio.h>
#include <stdlib.h>

//
// Created by Richard on 19/11/2023.
//
int main() {
  int a, erro;
  char estado = '1';
  char estadoAnt = '1';
  while (1) {
    erro = 0;
    printf("\nEntre com os dados:");
    while ((a = getchar()) != '\n') {
      if (estado == '1' && a == 'a') {
        estado = '2';
      } else if (estado == '1' && a == 'b') {
        estado = '4';
      } else if (estado == '2' && a == 'a') {
        estado = '5';
      } else if (estado == '2' && a == 'b') {
        estado = '6';
      } else if (estado == '3' && a == 'a') {
        estado = '5';
      } else if (estado == '3' && a == 'b') {
        estado = '6';
      } else if (estado == '4' && a == 'a') {
        estado = '7';
      } else if (estado == '4' && a == 'b') {
        estado = '8';
      } else if (estado == '5' && a == 'a') {
        estado = '6';
      } else if (estado == '5' && a == 'b') {
        estado = '8';
      } else if (estado == '6' && a == 'a') {
        estado = '8';
      } else if (estado == '6' && a == 'b') {
        estado = '7';
      } else if (estado == '7' && a == 'a') {
        estado = '3';
      } else if (estado == '7' && a == 'b') {
        estado = '8';
      } else if (estado == '8' && (a == 'a' || a == 'b')) {
        estado = '8';
      } else {
        // Dados informados inválidos
        erro = 1;
      }
    }

    if (erro == 0) {
      printf("\nTransicao de estado de q%c -> q%c", estadoAnt, estado);
    } else {
      printf("\nEstado de erro.");
    }
    printf("\n\nTecle <ENTER> para continuar.");
    getchar();
    system("clear || cls");

    estadoAnt = estado;
  }
}
