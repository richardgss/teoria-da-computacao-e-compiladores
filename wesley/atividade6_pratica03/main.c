//
// Created by Richard on 03/10/2023.
//
#include <stdio.h>

int get_val(int n) {
  if (n % 2 == 1) {
    // Se impar
    return n / 2 + 1;
  } else {
    return -n / 2;
  }
}

// Relacao entre numeros naturais e inteiros recursiva
void recursive_call(int limit, int n) { // NOLINT(misc-no-recursion)
  if (n > limit || n < limit * -1) {
    return;
  }

  printf("[%d, %d], ", n, get_val(n));

  recursive_call(limit, n + 1);
}

// Relacao entre numeros naturais e inteiros nao recursiva
void non_recursive_call(int limit) {
  for (int n = 0; n <= limit; n++) {
    printf("[%d, %d], ", n, get_val(n));
  }
}

int sucessor(int n) {
  return n + 1;
}

int soma(int m, int n) {
  if (n == 0) {
    return m;
  } else {
    return sucessor(soma(m, n - 1));
  }
}

void menor(int i, int j) {
  if (j > i) {
    return;
  }
  printf("[%d,%d]", j, sucessor(i));
  menor(i, sucessor(j));
}

void sucessor_nr(int n) {
  for(int i = 0; i <= n; i++) {
    for(int j = 0; j <= i; j++)
      printf("[%d, %d] ", j, i + 1);

    printf("\n");
  }
}

void _sucessor_r(int i, int j) {
  if (j < 0) {
    if (i > 0) {
      _sucessor_r(i - 1, i - 1);
      printf("\n");
    }
    return;
  }
  _sucessor_r(i, j - 1);
  printf("[%d, %d] ", j, i + 1);
}

void sucessor_r(int n) {
  _sucessor_r(n, n);
}

// Grafo nao direcionado
void informa_distancias_4x4(int grafo[4][4]) {
  /*
    for(int i=0; i<4; i++) {
        for (int x=0; x<4; x++) {
            printf("Informe a distancia_4x4 entre as cidades [%d, %d]:\n", i, x);
            scanf("%d", &grafo[i][x]);
        }
    }
*/

    // Debug only
    grafo[0][0] = 0;
    grafo[0][1] = 4;
    grafo[0][2] = 0;
    grafo[0][3] = 5;
    grafo[1][0] = 4;
    grafo[1][1] = 0;
    grafo[1][2] = 2;
    grafo[1][3] = 4;
    grafo[2][0] = 0;
    grafo[2][1] = 2;
    grafo[2][2] = 0;
    grafo[2][3] = 3;
    grafo[3][0] = 5;
    grafo[3][1] = 4;
    grafo[3][2] = 3;
    grafo[3][3] = 0;
}

int qtde_estradas_4x4(int grafo[4][4]) {
  int qtd = 0;
  for (int i=0; i<4; i++) {
    for (int x=0; x<4; x++) {
      if (grafo[i][x] > 0) {
        qtd++;
      }
    }
  }
  return qtd;
}

void imprime_matriz_4x4(int grafo[4][4]) {
  for (int i=0; i<4; i++) {
    printf("[");
    for (int x=0; x<4; x++) {
      printf("%d%s", grafo[i][x], x < 4 - 1 ? ", " : "");
    }
    printf("]\n");
  }
}

int distancia_4x4(int grafo[4][4], int c1, int c2) {
  int dist = 0;

  if (c1 < c2 && c2 - c1 > 0) {
    dist += grafo[c2 - 1][c2];
    // printf("dist[%d, %d]: %d\n", c2 - 1, c2, dist);
    dist += distancia_4x4(grafo, c1, c2 - 1);
  } else if (c2 < c1 && c1 - c2 > 0) {
    dist += grafo[c1 - 1][c1];
    // printf("dist[%d, %d]: %d\n", c1 - 1, c2, dist);
    dist += distancia_4x4(grafo, c1 - 1, c2);
  } else {
    dist = grafo[c1][c2];
  }

  return dist;
}


// Grafo direcionado
void informa_distancias_3x3(int grafo[3][3]) {
  /*
    for(int i=0; i<3; i++) {
        for (int x=0; x<3; x++) {
            printf("Informe a distancia_4x4 entre as cidades [%d, %d]:\n", i, x);
            scanf("%d", &grafo[i][x]);
        }
    }
*/

  // Debug only
  grafo[0][0] = 0;
  grafo[0][1] = 450;
  grafo[0][2] = 500;
  grafo[1][0] = 0;
  grafo[1][1] = 0;
  grafo[1][2] = 0;
  grafo[2][0] = 0;
  grafo[2][1] = 600;
  grafo[2][2] = 0;
}

void imprime_matriz_3x3(int grafo[3][3]) {
  for (int i=0; i<3; i++) {
    printf("[");
    for (int x=0; x<3; x++) {
      printf("%d%s", grafo[i][x], x < 3 - 1 ? ", " : "");
    }
    printf("]\n");
  }
}

int distancia_3x3(int grafo[3][3], int origem, int destino) {
  if (origem < 0 || origem >= 3 || destino < 0 || destino >= 3) {
    return 0;
  }

  if (grafo[origem][destino] > 0) {
    return grafo[origem][destino];
  }

  return 0;
}

int tem_ciclo_3x3(int visitados[3], int grafo[3][3], int vertice, int pai) {
  visitados[vertice] = 1;

  for (int i = 0; i < 3; i++) {
    if (grafo[vertice][i]) {
      if (!visitados[i]) {
        if (tem_ciclo_3x3(visitados, grafo, i, vertice))
          return 1;
      } else if (i != pai) {
        return 1;
      }
    }
  }

  return 0;
}

int verifica_ciclo_3x3(int grafo[3][3]) {
  int visitados[3];
  for (int i = 0; i < 3; i++) {
    if (!visitados[i]) {
      if (tem_ciclo_3x3(visitados, grafo, i, -1)) {
        return 1;
      }
    }
  }

  return 0;
}

void grau_entrada_3x3(int grau_entrada[3], int grafo[3][3]) {
  for (int i=0; i<3; i++) {
    grau_entrada[i] = 0;
  }
  // Calcula o grau de entrada para cada nó
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      grau_entrada[j] += grafo[i][j];
    }
  }
}

void grau_saida_3x3(int grau_saida[3], int grafo[3][3]) {
  for (int i=0; i<3; i++) {
    grau_saida[i] = 0;
  }
  // Calcula o grau de entrada para cada nó
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      grau_saida[i] += grafo[i][j];
    }
  }
}

int main() {
  int limit;
  int s1, s2, st;
  int i;
  int grafo1[4][4];
  int grafo2[3][3];

  limit = 5;
//  printf("Informe o limite:");
//  scanf("%d", &limit);
  recursive_call(limit, 0);
  printf("\n");
  non_recursive_call(limit);

  s1 = 2;
  s2 = 3;
//  printf("\nInforme o primeiro numero:");
//  scanf("%d", &s1);
//  printf("Informe o segundo numero:");
//  scanf("%d", &s2);
  st = soma(s1, s2);
  printf("\nSoma: %d", st);

  printf("\nMenor que:\n");
  // menor(0, 0);
  menor(1, 0);


  i = 3;
  // printf("Informe o valor de i:");
  // scanf("%d", &i);
  printf("\nSucessor não recursivo:\n");
  sucessor_nr(i);

  printf("\nSucessor recursivo:\n");
  sucessor_nr(i);


  printf("\nGrafo não direcionado rotulado:\n");
  informa_distancias_4x4(grafo1);
  int qtd = qtde_estradas_4x4(grafo1);
  imprime_matriz_4x4(grafo1);
  int c1 = 3;
  int c2 = 0;
  int dist = distancia_4x4(grafo1, c1, c2);

  printf("Qtde de estradas: %d\n", qtd);
  printf("Distancia [%d, %d]: %d", c1, c2, dist);

  printf("\n\nGrafo direcionado rotulado:\n");
  informa_distancias_3x3(grafo2);
  imprime_matriz_3x3(grafo2);

  dist = 0;
  c1 = 0;
  c2 = 2;
  dist = distancia_3x3(grafo2, c1, c2);
  if (dist == 0) {
    printf("Não há caminho entre as cidades.\n");
  } else {
    printf("Distancia: [%d, %d]: %d\n", c1, c2, dist);
  }

  if (verifica_ciclo_3x3(grafo2)) {
    printf("O grafo tem ciclos.\n");
  } else {
    printf("O grafo não tem ciclos.\n");
  }

  int grau_entrada[3];
  grau_entrada_3x3(grau_entrada, grafo2);

  for (int z=0; z<3; z++) {
    printf("Grau de entrada grafo[%d] = %d\n", z, grau_entrada[z]);
  }

  int grau_saida[3];
  grau_saida_3x3(grau_saida, grafo2);

  for (int z=0; z<3; z++) {
    printf("Grau de saida grafo[%d] = %d\n", z, grau_saida[z]);
  }

  return 0;
}
