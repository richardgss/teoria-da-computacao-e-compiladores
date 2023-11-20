#include <stdio.h>
#include <stdlib.h>

/**
 *     1) Crie um AFD para reconhecer a linguagem representada pela
 *     expressão regular 0*110*, sabendo que o alfabeto desta linguagem é
 *     {0,1}.
 *
 *     M = (Q,Σ, ꝺ, q0, F)
 *     Q = {q0, q1, q2, q3}
 *     Σ = 0, 1
 *     F = {q2}
 *     ꝺ(q0, 0) = q0
 *     ꝺ(q0, 1) = q1
 *     ꝺ(q1, 1) = q2
 *     ꝺ(q1, 0) = q3
 *     ꝺ(q2, 0) = q2
 *     ꝺ(q2, 1) = q3
 *     ꝺ(q3, 0) = q3
 *     ꝺ(q3, 1) = q3
 */
void automato1() {
  int a, erro;
  char estado = '0';
  char estadoAnt = '0';
  while (1) {
    erro = 0;
    printf("\nEntre com os dados:");
    while ((a = getchar()) != '\n') {
      if (estado == '0' && a == '0') {
        estado = '0';
      } else if (estado == '0' && a == '1') {
        estado = '1';
      } else if (estado == '1' && a == '1') {
        estado = '2';
      } else if (estado == '1' && a == '0') {
        estado = '3';
      } else if (estado == '2' && a == '0') {
        estado = '2';
      } else if (estado == '2' && a == '1') {
        estado = '3';
      } else if (estado == '3' && (a == '0' || a == '1')) {
        estado = '3';
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

/**
 *    2) Para o alfabeto {a, b}, crie um AFD que reconhece todas as palavras que não possuem dois a’s consecutivos.
 *
 *    M = (Q,Σ, ꝺ, q0, F)
 *    Q = {q0, q1, q2, q3, q4, q5}
 *    Σ = a, b
 *    F = {q1, q2, q3, q4}
 *    ꝺ(q0, a) = q1
 *    ꝺ(q0, b) = q3
 *    ꝺ(q1, a) = q5
 *    ꝺ(q1, b) = q2
 *    ꝺ(q2, a) = q1
 *    ꝺ(q2, b) = q2
 *    ꝺ(q3, a) = q4
 *    ꝺ(q3, b) = q3
 *    ꝺ(q4, a) = q5
 *    ꝺ(q4, b) = q3
 *    ꝺ(q5, a) = q5
 *    ꝺ(q5, b) = q5
 */
void automato2() {
  int a, erro;
  char estado = '0';
  char estadoAnt = '0';
  while (1) {
    erro = 0;
    printf("\nEntre com os dados:");
    while ((a = getchar()) != '\n') {
      if (estado == '0' && a == 'a') {
        estado = '1';
      } else if (estado == '0' && a == 'b') {
        estado = '3';
      } else if (estado == '1' && a == 'a') {
        estado = '5';
      } else if (estado == '1' && a == 'b') {
        estado = '2';
      } else if (estado == '2' && a == 'a') {
        estado = '1';
      } else if (estado == '2' && a == 'b') {
        estado = '2';
      } else if (estado == '3' && a == 'a') {
        estado = '4';
      } else if (estado == '3' && a == 'b') {
        estado = '3';
      } else if (estado == '4' && a == 'a') {
        estado = '5';
      } else if (estado == '4' && a == 'b') {
        estado = '3';
      } else if (estado == '5' && (a == 'a' || a == 'b')) {
        estado = '5';
      }
      else {
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

/**
 *    3) Crie um AFD que reconhece todas as palavras que tenham um número par de 0’s, sabendo que o alfabeto desta linguagem é {0,1}.
 *
 *    M = (Q,Σ, ꝺ, q0, F)
 *    Q = {q0, q1, q2}
 *    Σ = 0, 1
 *    F = {q2}
 *    ꝺ(q0, 0) = q1
 *    ꝺ(q0, 1) = q0
 *    ꝺ(q1, 0) = q2
 *    ꝺ(q1, 1) = q1
 *    ꝺ(q2, 0) = q1
 *    ꝺ(q2, 1) = q2
 */
void automato3() {
  int a, erro;
  char estado = '0';
  char estadoAnt = '0';
  while (1) {
    erro = 0;
    printf("\nEntre com os dados:");
    while ((a = getchar()) != '\n') {
      if (estado == '0' && a == '0') {
        estado = '1';
      } else if (estado == '0' && a == '1') {
        estado = '0';
      } else if (estado == '1' && a == '0') {
        estado = '2';
      } else if (estado == '1' && a == '1') {
        estado = '1';
      } else if (estado == '2' && a == '0') {
        estado = '1';
      } else if (estado == '2' && a == '1') {
        estado = '2';
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

/**
 *     4) Dada a expressão regular, crie o grafo que representa o AFD:
 *     L(E) = a(a + b)* ∪ ba(a + b)* ∪ bba(a + b)*
 *     Dica: tente ver a expressão regular como se fosse três partes distintas, assim conseguirá
 *     identificar os elementos em comum.
 */
void automato4() {
  int a, erro;
  char estado = '0';
  char estadoAnt = '0';
  while (1) {
    erro = 0;
    printf("\nEntre com os dados:");
    while ((a = getchar()) != '\n') {
      if (estado == '0' && a == 'a') {
        estado = '1';
      } else if (estado == '0' && a == 'b') {
        estado = '3';
      } else if (estado == '3' && a == 'a') {
        estado = '1';
      } else if (estado == '3' && a == 'b') {
        estado = '2';
      } else if (estado == '2' && a == 'a') {
        estado = '1';
      } else if (estado == '2' && a == 'b') {
        // ??? O grafo do gabarito não é uma função total?
        estado = '1';
      } else if (estado == '1' && (a == 'a' || a == 'b')) {
        estado = '1';
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

/**
 *     5) Crie um AFD que reconheça a linguagem L = {w | w tem um número
 *     par de 0’s e 1’s}, sabendo que o alfabeto Σ = {0, 1} e que o AFD
 *     aceitará uma palavra vazia.
 */
void automato5() {
  int a, erro;
  char estado = '0';
  char estadoAnt = '0';
  while (1) {
    erro = 0;
    printf("\nEntre com os dados:");
    while ((a = getchar()) != '\n') {
      if (estado == '0' && a == '0') {
        estado = '1';
      } else if (estado == '0' && a == '1') {
        estado = '2';
      } else if (estado == '1' && a == '1') {
        estado = '3';
      } else if (estado == '1' && a == '0') {
        estado = '0';
      } else if (estado == '2' && a == '1') {
        estado = '0';
      } else if (estado == '2' && a == '0') {
        estado = '3';
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

//
// Created by Richard on 19/11/2023.
//
int main() {
  // automato1();
  // automato2();
  // automato3();
  // automato4();
  automato5();
}
