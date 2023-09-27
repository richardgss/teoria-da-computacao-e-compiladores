#include <stdio.h>

typedef struct vets {
  int vet1[20];
  int vet2[20];
} t_vets;

typedef struct pot_vet {
    int vet[20];
} t_pot_vet;

int arr_len(int* arr, int limit) {
  int len = 0;
  while(arr[len] != 0 && len++ < limit) {}
  return len;
}


void print_arr(int* array, int len) {
  printf("{ ");
  for (int i=0; i<len; i++) {
    printf("%d%s", array[i], i == len - 1 ? "" :  ", ");
  }
  printf(" }");
}

void print_conjs_pot(t_pot_vet* s_vet, int len, int max_vet_len) {
    int vet_len = 0;
    for (int i=0; i<len; i++) {
        int* vet = s_vet[i].vet;
        vet_len = arr_len(vet, max_vet_len);
        printf("{");
        for (int x=0; x<vet_len; x++) {
            printf("%d%s", vet[x], x == vet_len -1 ? "" : ", ");
        }
        printf("}");
    }
}

void write_t_vets(t_vets mVets, const char* fname) {
  FILE *arq;
  arq = fopen(fname, "wb");

  if (arq == NULL) {
    printf("\n Erro ao abrir o arquivo %s.", fname);
    return;
  }

  fwrite(&mVets, sizeof(t_vets), 1, arq);
  fclose(arq);
}

void imprime_combinacao(
    int tuple[], int input_len, int r, int* data, int index, int i, t_pot_vet* s_vet, int s_vet_len
) {
  if (index == r) {
    int* m_s_vet = s_vet[index - 1].vet;
    int j;
    
    printf("{ ");
    // Printa a combinacao do vetor
    for (j = 0; j < r; j++) {
      // Salva o elemento na posicao do vetor atual da lista de conjuntos potencia
      m_s_vet[j] = data[j];
      // Printa o subconjunto do conjunto potencia
      printf("%d%s",  data[j], (j == r - 1 ? " " : ", "));
    }
    // Preenche restante do vetor com zero.
    while(j++ < s_vet_len) {
        m_s_vet[j] = 0;
    }
    printf("}");
    printf(" ");
    return;
  }

  // When no more elements are there to put in data[]
  if (i >= input_len)
    return;

  // Include the current element and recursively generate combinations
  data[index] = tuple[i];
  imprime_combinacao(tuple, input_len, r, data, index + 1, i + 1, s_vet, s_vet_len);

  // Exclude the current element (generate combinations without it)
  imprime_combinacao(tuple, input_len, r, data, index, i + 1, s_vet, s_vet_len);
}

// Function to print all combinations of 'r' elements from 'n' elements
void imprime_todas_combinacoes(int* tuple, int input_len, int r, t_pot_vet* s_vet, int s_vet_len) {
  int data[r];
  imprime_combinacao(tuple, input_len, r, data, 0, 0, s_vet, s_vet_len);
}

void a_create_vectors(const char* fname, const int len) {
  int i;
  t_vets mVets;

  printf("Primeira sequencia:\n");
  for (i=0; i<len; i++) {
    printf("Informe um numero: ");
    scanf("%d", &mVets.vet1[i]);
  }

  printf("Segunda sequencia:\n");
  for (i=0; i<len; i++) {
    printf("Informe um numero: ");
    scanf("%d", &mVets.vet2[i]);
  }

  printf("\nSequencia1: ");
  print_arr(mVets.vet1, len);
  printf("\nSequencia2: ");
  print_arr(mVets.vet2, len);

  write_t_vets(mVets, fname);
}

void b_read_vectors(t_vets *mVets, const char* fname, const int len) {
  FILE *arq;
  arq = fopen(fname, "rb");

  if (arq == NULL) {
    printf("\n Erro ao abrir o arquivo arquivoC.txt.");
    return;
  }

  fread(mVets, sizeof(t_vets), 1, arq);

  fclose(arq);

  printf("\nSequencia1: ");
  print_arr(mVets->vet1, len);
  printf("\nSequencia2: ");
  print_arr(mVets->vet2, len);
}

int get_conjunto(int* mVet, int len, int* conjunto) {
  int cur_len = 0;
  int exists;

  for (int i=0; i<len; i++) {
    exists = 0;
    for (int x=0; x<cur_len; x++) {
      if (conjunto[x] == mVet[i]) {
        exists = 1;
        break;
      }
    }

    if (exists == 0) {
      conjunto[cur_len++] = mVet[i];
    }
  }

  // Preenche com zero os valores restantes do vetor
  while(--len >= cur_len) {
    conjunto[len] = 0;
  }

  return cur_len;
}

// Valores de conjunto são unicos
void c_get_conjuntos(t_vets mVets, const int len, const int input_len, const char* fname, t_vets *mConj) {
  get_conjunto(mVets.vet1, len, mConj->vet1);
  get_conjunto(mVets.vet2, len, mConj->vet2);

  printf("\nConjunto A: ");
  print_arr(mConj->vet1, arr_len(mConj->vet1, input_len));
  printf("\nConjunto B: ");
  print_arr(mConj->vet2, arr_len(mConj->vet2, input_len));

  write_t_vets(*mConj, fname);
}

// Conjunto potência é todos os subconjuntos possíveis de um conjunto
void d_get_conjunto_potencia(t_vets mConj, int max_len, const char* fname_conjuntos_pot) {
  const int conj_pot_len = 10;
  t_pot_vet a_conj_pot[conj_pot_len];
  t_pot_vet b_conj_pot[conj_pot_len];

  const int a_input_len = arr_len(mConj.vet1, max_len);
  const int b_input_len = arr_len(mConj.vet2, max_len);

  printf("\nConjunto Potencia P(A): ");
  for (int r = 1; r <= a_input_len; r++) {
    imprime_todas_combinacoes(mConj.vet1, a_input_len, r, a_conj_pot, conj_pot_len);
  }

  printf("\nConjunto Potencia P(B): ");
  for (int r = 1; r <= b_input_len; r++) {
    imprime_todas_combinacoes(mConj.vet2, b_input_len, r, b_conj_pot, conj_pot_len);
  }
  
  print_conjs_pot(a_conj_pot, 3, 20);
}

void e_get_conjunto_proprio(t_vets mConj, int max_len) {
  const int conj_prop_len = 10;
  t_pot_vet a_conj_prop[conj_prop_len];
  t_pot_vet b_conj_prop[conj_prop_len];
  
  const int a_input_len = arr_len(mConj.vet1, max_len);
  const int b_input_len = arr_len(mConj.vet2, max_len);

  printf("\nConjunto Próprio A: ");
  for (int r = 1; r < a_input_len; r++) {
    imprime_todas_combinacoes(mConj.vet1, a_input_len, r, a_conj_prop, conj_prop_len);
  }

  printf("\nConjunto Próprio B: ");
  for (int r = 1; r < b_input_len; r++) {
    imprime_todas_combinacoes(mConj.vet2, b_input_len, r, b_conj_prop, conj_prop_len);
  }
}

int main() {
  const char* fname_arr = "vetores.txt";
  const char* fname_conjuntos = "conjuntos.txt";
  const char* fname_conjuntos_pot = "conjuntos_pot.txt";
  const int len = 20;
  const int input_len = 3;
  t_vets mVets;
  t_vets mConj;

  // a_create_vectors(fname_arr, input_len);
  b_read_vectors(&mVets, fname_arr, input_len);
  c_get_conjuntos(mVets, len, input_len, fname_conjuntos, &mConj);
  d_get_conjunto_potencia(mConj, input_len, fname_conjuntos_pot);
  // e_get_conjunto_proprio(mConj, input_len);

  return 0;
}
