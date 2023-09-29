#include <stdio.h>
#include <darray.h>
#include <dtuple.h>

//typedef struct vets {
//  int vet1[20];
//  int vet2[20];
//} t_vets;
//
//void print_arr(int* array, int len) {
//  printf("{ ");
//  for (int i=0; i<len; i++) {
//    printf("%d%s", array[i], i == len - 1 ? "" :  ", ");
//  }
//  printf(" }");
//}
//
//void write_t_vets(t_vets mVets, const char* fname) {
//  FILE *arq;
//  arq = fopen(fname, "wb");
//
//  if (arq == NULL) {
//    printf("\n Erro ao abrir o arquivo arquivoC.txt.");
//    return;
//  }
//
//  fwrite(&mVets, sizeof(t_vets), 1, arq);
//  fclose(arq);
//}
//
//int arr_len(int* arr, int limit) {
//  int len = 0;
//  while(arr[len] != 0 && len++ < limit) {}
//  return len;
//}
//
//void imprime_combinacao(int tuple[], int input_len, int r, int* data, int index, int i) {
//  if (index == r) {
//    printf("{ ");
//    // Print the combination
//    for (int j = 0; j < r; j++) {
//      printf("%d%s",  data[j], (j == r - 1 ? " " : ", "));
//    }
//    printf("}");
//    printf(" ");
//    return;
//  }
//
//  // When no more elements are there to put in data[]
//  if (i >= input_len)
//    return;
//
//  // Include the current element and recursively generate combinations
//  data[index] = tuple[i];
//  imprime_combinacao(tuple, input_len, r, data, index + 1, i + 1);
//
//  // Exclude the current element (generate combinations without it)
//  imprime_combinacao(tuple, input_len, r, data, index, i + 1);
//}
//
//// Function to print all combinations of 'r' elements from 'n' elements
//void imprime_todas_combinacoes(int* tuple, int input_len, int r) {
//  int data[r];
//  imprime_combinacao(tuple, input_len, r, data, 0, 0);
//}
//
//void a_create_vectors(const char* fname, const int len) {
//  int i;
//  t_vets mVets;
//
//  printf("Primeira sequencia:\n");
//  for (i=0; i<len; i++) {
//    printf("Informe um numero: ");
//    scanf("%d", &mVets.vet1[i]);
//  }
//
//  printf("Segunda sequencia:\n");
//  for (i=0; i<len; i++) {
//    printf("Informe um numero: ");
//    scanf("%d", &mVets.vet2[i]);
//  }
//
//  printf("\nSequencia1: ");
//  print_arr(mVets.vet1, len);
//  printf("\nSequencia2: ");
//  print_arr(mVets.vet2, len);
//
//  write_t_vets(mVets, fname);
//}
//
//void b_read_vectors(t_vets *mVets, const char* fname, const int len) {
//  FILE *arq;
//  arq = fopen(fname, "rb");
//
//  if (arq == NULL) {
//    printf("\n Erro ao abrir o arquivo arquivoC.txt.");
//    return;
//  }
//
//  fread(mVets, sizeof(t_vets), 1, arq);
//
//  fclose(arq);
//
//  printf("\nSequencia1: ");
//  print_arr(mVets->vet1, len);
//  printf("\nSequencia2: ");
//  print_arr(mVets->vet2, len);
//}
//
//int get_conjunto(int* mVet, int len, int* conjunto) {
//  int cur_len = 0;
//  int exists;
//
//  for (int i=0; i<len; i++) {
//    exists = 0;
//    for (int x=0; x<cur_len; x++) {
//      if (conjunto[x] == mVet[i]) {
//        exists = 1;
//        break;
//      }
//    }
//
//    if (exists == 0) {
//      conjunto[cur_len++] = mVet[i];
//    }
//  }
//
//  // Preenche com zero os valores restantes do vetor
//  while(--len >= cur_len) {
//    conjunto[len] = 0;
//  }
//
//  return cur_len;
//}
//
//// Valores de conjunto são unicos
//void c_get_conjuntos(t_vets mVets, const int len, const int input_len, const char* fname, t_vets *mConj) {
//  get_conjunto(mVets.vet1, len, mConj->vet1);
//  get_conjunto(mVets.vet2, len, mConj->vet2);
//
//  printf("\nConjunto A: ");
//  print_arr(mConj->vet1, arr_len(mConj->vet1, input_len));
//  printf("\nConjunto B: ");
//  print_arr(mConj->vet2, arr_len(mConj->vet2, input_len));
//
//  write_t_vets(*mConj, fname);
//}
//
//// Conjunto potência é todos os subconjuntos possíveis de um conjunto
//void d_get_conjunto_potencia(t_vets mConj, int max_len) {
//  t_vets a_conj_pot[10];
//  t_vets b_conj_pot[10];
//
//  const int a_input_len = arr_len(mConj.vet1, max_len);
//  const int b_input_len = arr_len(mConj.vet2, max_len);
//
//  printf("\nConjunto Potencia P(A): ");
//  for (int r = 1; r <= a_input_len; r++) {
//    imprime_todas_combinacoes(mConj.vet1, a_input_len, r);
//  }
//
//  printf("\nConjunto Potencia P(B): ");
//  for (int r = 1; r <= b_input_len; r++) {
//    imprime_todas_combinacoes(mConj.vet2, b_input_len, r);
//  }
//}
//
//void e_get_conjunto_proprio(t_vets mConj, int max_len) {
//  const int a_input_len = arr_len(mConj.vet1, max_len);
//  const int b_input_len = arr_len(mConj.vet2, max_len);
//
//  printf("\nConjunto Próprio A: ");
//  for (int r = 1; r < a_input_len; r++) {
//    imprime_todas_combinacoes(mConj.vet1, a_input_len, r);
//  }
//
//  printf("\nConjunto Próprio B: ");
//  for (int r = 1; r < b_input_len; r++) {
//    imprime_todas_combinacoes(mConj.vet2, b_input_len, r);
//  }
//}

int main() {
//  const char* fname_arr = "vetores.txt";
//  const char* fname_conjuntos = "conjuntos.txt";
//  const char* fname_conjuntos_pot = "conjuntos_pot.txt";
//  const int len = 20;
//  const int input_len = 3;
//  t_vets mVets;
//  t_vets mConj;
//
//  // a_create_vectors(fname_arr, input_len);
//  b_read_vectors(&mVets, fname_arr, input_len);
//  c_get_conjuntos(mVets, len, input_len, fname_conjuntos, &mConj);
//  d_get_conjunto_potencia(mConj, input_len);
//  e_get_conjunto_proprio(mConj, input_len);

  char choice;
  int input;
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
  arr_int_add(&sequencia_A, 3);
  arr_int_add(&sequencia_A, 4);

  arr_int_add(&sequencia_B, 5);
  arr_int_add(&sequencia_B, 6);
  arr_int_add(&sequencia_B, 7);
  arr_int_add(&sequencia_B, 8);

  // Apresenta na tela as sequencias de numeros naturais
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
  arr_int_list_read_file_txt(sequencias_AB, 2, "arquivo.txt");

  printf("\nSequencia A: ");
  arr_int_print(sequencias_AB[0]);
  printf("\nSequencia B: ");
  arr_int_print(sequencias_AB[1]);

  // Libera a alocacao dinamica das listas
  arr_clear(&sequencia_A);
  arr_clear(&sequencia_B);

  // --------------------- ATIVIDADE LETRA C ------------------------


  return 0;
}
