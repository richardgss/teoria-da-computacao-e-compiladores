#include <stdio.h>
#include "darray.h"
#include "dtuple.h"

int main() {
  char choice;
  int input;
  int read_len = 0;
  arr_int sequencia_A = {};
  arr_int sequencia_B = {};
  arr_int sequencias_AB[2] = {};

//  // --------------------- ATIVIDADE LETRA A ------------------------
//  // Recebe os numeros da sequencia A
//  printf("Informe numeros naturais para a sequencia A:\n");
//  do {
//    // Recebe a entrada
//    printf("Sequencia A: ");
//    scanf("%d", &input); // NOLINT(cert-err34-c)
//
//    // Salva o numero na lista A
//    arr_int_add(&sequencia_A, input);
//
//    // Pergunta se o usuario deseja continuar
//    printf("Deseja continuar? (s/n): ");
//    scanf(" %c", &choice);
//  } while (choice == 's' || choice == 'S');
//
//  // Recebe os numeros da sequencia B
//  printf("Informe numeros naturais para a sequencia B:\n");
//  do {
//    // Recebe a entrada
//    printf("Sequencia B: ");
//    scanf("%d", &input); // NOLINT(cert-err34-c)
//
//    // Salva o numero na lista A
//    arr_int_add(&sequencia_B, input);
//
//    // Pergunta se o usuario deseja continuar
//    printf("Deseja continuar? (s/n): ");
//    scanf(" %c", &choice);
//  } while (choice == 's' || choice == 'S');

  // DEBUG ONLY
  arr_int_add(&sequencia_A, 1);
  arr_int_add(&sequencia_A, 2);
  arr_int_add(&sequencia_A, 2);
  arr_int_add(&sequencia_A, 3);
  arr_int_add(&sequencia_A, 8);

  arr_int_add(&sequencia_B, 5);
  arr_int_add(&sequencia_B, 6);
  arr_int_add(&sequencia_B, 7);
  arr_int_add(&sequencia_B, 7);
  arr_int_add(&sequencia_B, 8);

  // Apresenta na tela as sequencias de numeros naturais
  printf("\nSalvando no arquivo.txt as sequencias A e B");
  printf("\nSequencia A: ");
  arr_int_print(sequencia_A);
  printf("\nSequencia B: ");
  arr_int_print(sequencia_B);

  // Salva as duas sequencias no "arquivo.bin"
  sequencias_AB[0] = sequencia_A;
  sequencias_AB[1] = sequencia_B;
  arr_int_list_save_file_txt(sequencias_AB, 2, "arquivo.txt");

  // Libera a alocacao dinamica das listas
  arr_clear(&sequencia_A);
  arr_clear(&sequencia_B);
  // Mantem a sincronia para realocacao posterior
  sequencias_AB[0] = sequencia_A;
  sequencias_AB[1] = sequencia_B;

  // --------------------- ATIVIDADE LETRA B ------------------------
  // Le as sequencias A e B do arquivo no modo texto
  arr_int_list_read_file_txt(sequencias_AB, 2, "arquivo.txt", &read_len);

  printf("\n\nLeitura do arquivo.txt as sequencias A e B");
  printf("\nSequencia A: ");
  arr_int_print(sequencias_AB[0]);
  printf("\nSequencia B: ");
  arr_int_print(sequencias_AB[1]);

  // Salva as sequencias nas variaveis
  sequencia_A = sequencias_AB[0];
  sequencia_B = sequencias_AB[1];

  // --------------------- ATIVIDADE LETRA C ------------------------
  tuple_int conjunto_A = {};
  tuple_int conjunto_B = {};
  tuple_int conjunto_AB[2] = {};

  // Converte as sequencias em tuplas
  tuple_from_arr_int(&conjunto_A, sequencia_A);
  tuple_from_arr_int(&conjunto_B, sequencia_B);

  printf("\n\nImprime os conjuntos A e B");
  printf("\nConjunto A: ");
  tuple_int_print(conjunto_A);
  printf("\nConjunto B: ");
  tuple_int_print(conjunto_B);
  printf("\n");

  // Salva os conjuntos A e B na matriz
  conjunto_AB[0] = conjunto_A;
  conjunto_AB[1] = conjunto_B;

  // Salva os dois conjuntos no arquivo modo texto
  tuple_int_list_save_file_txt(conjunto_AB, 2, "arquivo.txt", "w", 0);

  // --------------------- ATIVIDADE LETRA D ------------------------
  const int conjunto_pot_len = 30;
  tuple_int conjunto_pot_A[conjunto_pot_len];
  tuple_int conjunto_pot_B[conjunto_pot_len];
  // Inicializa os subconjuntos com conjuntos vazios
  for (int i=0; i<conjunto_pot_len; i++) {
    conjunto_pot_A[i] = (tuple_int) {};
    conjunto_pot_B[i] = (tuple_int) {};
  }

  // Gera os conjuntos potencia e salva na lista
  printf("\nImprime os conjuntos potência A e B\n");
  const int conjunto_pot_A_r_len = tuple_int_power_sets(conjunto_pot_A, conjunto_pot_len, 0, conjunto_A, 0);
  const int conjunto_pot_B_r_len = tuple_int_power_sets(conjunto_pot_B, conjunto_pot_len, 0, conjunto_B, 0);

  // Salva a lista de conjuntos potencia A e B no arquivo.txt
  tuple_int_list_save_file_txt(conjunto_pot_A, conjunto_pot_A_r_len, "arquivo.txt", "w", 1);
  tuple_int_list_save_file_txt(conjunto_pot_B, conjunto_pot_B_r_len, "arquivo.txt", "a", 0);

  // --------------------- ATIVIDADE LETRA E ------------------------
  const int conjunto_prop_len = 100;
  tuple_int conjunto_prop_A[conjunto_prop_len];
  tuple_int conjunto_prop_B[conjunto_prop_len];
  // Inicializa os subconjuntos proprios com conjuntos vazios
  for (int i=0; i<conjunto_prop_len; i++) {
    conjunto_prop_A[i] = (tuple_int) {};
    conjunto_prop_B[i] = (tuple_int) {};
  }
  int conjunto_prop_A_r_len = 0;
  int conjunto_prop_B_r_len = 0;

  printf("\nImprime os conjuntos proprios A\n");
  // Para cada subconjunto do conjunto potencia de A
  for (int i=0; i<conjunto_pot_A_r_len; i++) {
    // Gera os conjuntos proprios dos conjuntos potencia de A e salva na lista
    tuple_int_print(conjunto_pot_A[i]);
    printf(" -> ");
    conjunto_prop_A_r_len += tuple_int_power_sets(conjunto_prop_A, conjunto_prop_len, conjunto_prop_A_r_len, conjunto_pot_A[i], 1);
  }

  printf("\nImprime os conjuntos proprios B\n");
  // Para cada subconjunto do conjunto potencia de A
  for (int i=0; i<conjunto_pot_B_r_len; i++) {
    // Gera os conjuntos proprios dos conjuntos potencia de A e salva na lista
    tuple_int_print(conjunto_pot_B[i]);
    printf(" -> ");
    conjunto_prop_B_r_len += tuple_int_power_sets(conjunto_prop_B, conjunto_prop_len, conjunto_prop_B_r_len, conjunto_pot_B[i], 1);
  }

  // Salva a lista de conjuntos potencia A e B no arquivo.txt
  tuple_int_list_save_file_txt(conjunto_prop_A, conjunto_prop_A_r_len, "arquivo.txt", "w", 1);
  tuple_int_list_save_file_txt(conjunto_prop_B, conjunto_prop_B_r_len, "arquivo.txt", "a", 0);

  // Libera a alocacao dinamica dos conjuntos proprios
  tuple_list_clear(conjunto_prop_A, conjunto_prop_A_r_len);
  tuple_list_clear(conjunto_prop_B, conjunto_prop_B_r_len);

  // Libera a alocacao dinamica dos conjuntos potencia
  tuple_list_clear(conjunto_pot_A, conjunto_pot_A_r_len);
  tuple_list_clear(conjunto_pot_B, conjunto_pot_B_r_len);

  // --------------------- ATIVIDADE LETRA F ------------------------
  tuple_int uniao_AB = {};
  // Uniao de A e B
  tuple_int_union(&uniao_AB, conjunto_A, conjunto_B);

  // Exibe na tela a uniao de A e B
  printf("\nUnião de A e B: ");
  tuple_int_print(uniao_AB);

  // Salva no arquivo a uniao de A e B
  tuple_int_save_file_txt(uniao_AB, "arquivo.txt");

  // Libera a alocacao dinamica da tupla uniao A e B
  tuple_clear(&uniao_AB);
  // --------------------- ATIVIDADE LETRA G ------------------------
  tuple_int intersection_AB = {};

  // Intersecao de A e B
  tuple_int_intersection(&intersection_AB, conjunto_A, conjunto_B);

  // Exibe na tela a intersecao de A e B
  printf("\nIntersecao de A e B: ");
  tuple_int_print(intersection_AB);

  // Salva no arquivo a intersecao de A e B
  tuple_int_save_file_txt(intersection_AB, "arquivo.txt");

  // Libera a alocacao dinamica da tupla intersecao A e B
  tuple_clear(&intersection_AB);

  // --------------------- ATIVIDADE LETRA H ------------------------
  tuple_int diff_AB = {};

  // Diferenca de A e B
  tuple_int_diff(&diff_AB, conjunto_A, conjunto_B);

  // Calcula a diferenca de A e B
  printf("\nDiferença de A e B: ");
  tuple_int_print(diff_AB);

  // Salva no arquivo a diferenca de A e B
  tuple_int_save_file_txt(diff_AB, "arquivo.txt");

  // Libera a alocacao dinamica da tupla diferenca A e B
  tuple_clear(&diff_AB);

  // --------------------- ATIVIDADE LETRA I ------------------------
  tuple_int diff_BA = {};

  // Diferenca de B e A
  tuple_int_diff(&diff_BA, conjunto_B, conjunto_A);

  // Exibe na tela a diferenca de B e A
  printf("\nDiferença de B e A: ");
  tuple_int_print(diff_BA);

  // Salva no arquivo a diferenca de B e A
  tuple_int_save_file_txt(diff_BA, "arquivo.txt");

  // Libera a alocacao dinamica da tupla diferenca B e A
  tuple_clear(&diff_BA);

  // --------------------- ATIVIDADE LETRA J ------------------------
  const int cartesian_product_len = 30;
  tuple_int cartesian_product_AB[cartesian_product_len];

  // Inicializa os subconjuntos do conjunto cartesiano com conjuntos vazios
  for (int i=0; i<cartesian_product_len; i++) {
    cartesian_product_AB[i] = (tuple_int) {};
  }

  // Produto cartesiano de A e B
  int cartesian_product_AB_r_len = tuple_int_cartesian_product(cartesian_product_AB, cartesian_product_len, conjunto_A, conjunto_B);

  // Exibe na tela o produto cartesiano de A e B
  printf("\nProduto cartesiano de A e B: ");
  for (int i=0; i < cartesian_product_AB_r_len; i++) {
    tuple_int_print(cartesian_product_AB[i]);
  }

  // Salva a lista de conjuntos do produto cartesiano A e B no arquivo.txt
  tuple_int_list_save_file_txt(cartesian_product_AB, cartesian_product_AB_r_len, "arquivo.txt", "w", 0);

  // Libera a alocacao dinamica do conjunto produto cartesiano
  tuple_list_clear(cartesian_product_AB, cartesian_product_AB_r_len);

  // --------------------- ATIVIDADE LETRA K ------------------------
  tuple_int cartesian_product_BA[cartesian_product_len];

  // Inicializa os subconjuntos do conjunto cartesiano com conjuntos vazios
  for (int i=0; i<cartesian_product_len; i++) {
    cartesian_product_BA[i] = (tuple_int) {};
  }

  // Produto cartesiano de A e B
  int cartesian_product_BA_r_len = tuple_int_cartesian_product(cartesian_product_BA, cartesian_product_len, conjunto_B, conjunto_A);

  // Exibe na tela o produto cartesiano de A e B
  printf("\nProduto cartesiano de B e A: ");
  for (int i=0; i < cartesian_product_BA_r_len; i++) {
    tuple_int_print(cartesian_product_BA[i]);
  }

  // Salva a lista de conjuntos do produto cartesiano A e B no arquivo.txt
  tuple_int_list_save_file_txt(cartesian_product_BA, cartesian_product_BA_r_len, "arquivo.txt", "w", 0);

  // Libera a alocacao dinamica do conjunto produto cartesiano
  tuple_list_clear(cartesian_product_BA, cartesian_product_BA_r_len);

  // Libera a alocacao dinamica das listas
  arr_clear(&sequencia_A);
  arr_clear(&sequencia_B);

  // Libera a alocacao dinamica das tupla
  tuple_clear(&conjunto_A);
  tuple_clear(&conjunto_B);
  // Mantem a sincronia para realocacao posterior
  conjunto_AB[0] = conjunto_A;
  conjunto_AB[1] = conjunto_B;

  return 0;
}
