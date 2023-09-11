#include <stdio.h>
#include <stdlib.h>

int alloc_mem(int **array, int sz) {
    // Alocação dinâmica de memória usando malloc
    *array = (int *) malloc(sz * sizeof(int));
    if (*array == NULL) {
        printf("Falha na alocação de memória.\n");
        return 1;
    }
    return 0;
}

void fill_arr(int **array, int sz) {
    // Preencher o array
    for (int i = 0; i < sz; i++) {
        (*array)[i] = i * 10;
    }
}

void print_arr(int **array, int sz) {
    // Imprimir o array
    printf("Array: ");
    for (int i = 0; i < sz; i++) {
        printf("%d ", (*array)[i]);
    }
}

int main() {
    int *array, n, ret;
    printf("Digite o tamanho do array: ");
    scanf("%d", &n);
    // Alocação dinâmica de memória usando malloc
    ret = alloc_mem(&array, n);
    if (ret != 0) return ret;
    // Preencher o array
    fill_arr(&array, n);
    // Imprimir o array
    print_arr(&array, n);
    // Liberar a memória alocada com malloc
    free(array);
    return 0;
}