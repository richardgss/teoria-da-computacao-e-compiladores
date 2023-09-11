#include <stdio.h>
#include <stdlib.h>

typedef struct Pessoa {
  char cpf[11];
  char nome[100];
  double salario;
} Pessoa_t;

int alloc_mem(Pessoa_t **array, int sz) {
    // Alocação dinâmica de memória usando calloc
    *array = (Pessoa_t *) calloc(sz, sizeof(Pessoa_t));
    if (*array == NULL) {
        printf("Falha na alocação de memória.\n");
        return 1;
    }
    return 0;
}

void fill_arr(Pessoa_t **array, int sz) {
    // Preencher o array
    for (int i = 0; i < sz; i++) {
        Pessoa_t pessoa;
        printf("Informe o nome:\n");
        scanf("%s", pessoa.nome);
        printf("Informe o cpf:\n");
        scanf("%s", pessoa.cpf);
        printf("Informe o salario:\n");
        scanf("%lf", &pessoa.salario);
        (*array)[i] = pessoa;
    }
}

void print_arr(Pessoa_t **array, int sz) {
    Pessoa_t item;
    // Imprimir o array
    printf("Array:\n");
    for (int i = 0; i < sz; i++) {
        item = (*array)[i];
        printf("Nome: %s\n", item.nome);
        printf("CPF: %s\n", item.cpf);
        printf("Salario: %f\n\n", item.salario);
    }
}

int main() {
    Pessoa_t *array;
    int n, ret;
    printf("Digite o tamanho do array: ");
    scanf("%d", &n);
    // Alocação dinâmica de memória usando calloc
    ret = alloc_mem(&array, n);
    if (ret != 0) return ret;
    // Preenche o array
    fill_arr(&array, n);
    // Imprimir o array
    print_arr(&array, n);
    // Liberar a memória alocada com calloc
    free(array);
    return 0;
}