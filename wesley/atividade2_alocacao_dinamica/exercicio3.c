#include <stdio.h>
#include <stdlib.h>

typedef struct Veiculo {
    char modelo[100];
    char marca[100];
    char chassi[20];
    double preco;
} Veiculo_t;

int alloc_mem(Veiculo_t **array, int sz) {
    // Alocação dinâmica de memória usando malloc
    *array = (Veiculo_t *) malloc(sz * sizeof(Veiculo_t));
    if (*array == NULL) {
        printf("Falha na alocação de memória.\n");
        return 1;
    }
    return 0;
}

int realloc_mem(Veiculo_t **array, int sz) {
    // Alocação dinâmica de memória usando malloc
    *array = (Veiculo_t *) realloc(*array, sz * sizeof(Veiculo_t));
    if (*array == NULL) {
        printf("Falha na realocação de memória.\n");
        return 1;
    }
    return 0;
}

void fill_arr(Veiculo_t **array, int offset, int sz) {
    // Preencher o array
    for (int i = offset; i < sz; i++) {
        Veiculo_t veiculo;
        printf("Informe o modelo:\n");
        scanf("%s", veiculo.modelo);
        printf("Informe a marca:\n");
        scanf("%s", veiculo.marca);
        printf("Informe o chassi:\n");
        scanf("%s", veiculo.chassi);
        printf("Informe o preco:\n");
        scanf("%lf", &veiculo.preco);
        (*array)[i] = veiculo;
    }
}

void print_arr(Veiculo_t **array, int sz) {
    Veiculo_t item;
    // Imprimir o array
    for (int i = 0; i < sz; i++) {
        item = (*array)[i];
        printf("Modelo: %s\n", item.modelo);
        printf("Marca: %s\n", item.marca);
        printf("Chassi: %s\n", item.chassi);
        printf("Preco: %f\n\n", item.preco);
    }
}

int main() {
    Veiculo_t *array;
    int n;
    printf("Digite o tamanho inicial do array: ");
    scanf("%d", &n);
    // Alocação dinâmica de memória usando malloc
    alloc_mem(&array, n);
    // Preencher o array
    fill_arr(&array, 0, n);
    // Imprimir o array
    printf("Array (antes da realocação): \n");
    print_arr(&array, n);
    // Realocar o array para um tamanho maior
    int novo_tamanho = n + 5;
    realloc_mem(&array, novo_tamanho);
    // Preencher os elementos adicionais
    fill_arr(&array, n, novo_tamanho);
    // Imprimir o array após a realocação
    printf("\nArray (após a realocação): \n");
    print_arr(&array, novo_tamanho);
    // Liberar a memória alocada
    free(array);
    return 0;
}