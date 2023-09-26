/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

typedef struct vets {
    int vet1[3];
    int vet2[3];
} t_vets;

void print_arr(int* array, int len) {
    for (int i=0; i<len; i++) {
        printf("%d, ", array[i]);
    }
}

void write_t_vets(t_vets mVets, const char* fname) {
    FILE *arq;
    arq = fopen(fname, "wb");
    
    if (arq == NULL) {
        printf("\n Erro ao abrir o arquivo arquivoC.txt.");
        return;
    }
    
    fwrite(&mVets, sizeof(t_vets), 1, arq);
    fclose(arq);
}

void a_create_vectors(const char* fname) {
    const int len = 3;
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

void b_read_vectors(t_vets *mVets, const char* fname) {
    const int len=3;
    
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

void c_get_conjuntos(t_vets mVets, const int len, const char* fname) {
    t_vets mConj;
    
    get_conjunto(mVets.vet1, len, mConj.vet1);
    get_conjunto(mVets.vet2, len, mConj.vet2);
    
    printf("\nConjunto A: ");
    print_arr(mConj.vet1, len);
    printf("\nConjunto B: ");
    print_arr(mConj.vet2, len);
    
    write_t_vets(mConj, fname);
}


int main() {
    const char* fname_arr = "vetores.txt";
    const char* fname_conjuntos = "conjuntos.txt";
    const int len = 3;
    t_vets mVets;

    // a_create_vectors(fname_arr);
    b_read_vectors(&mVets, fname_arr);
    c_get_conjuntos(mVets, len, fname_conjuntos);
    
    return 0;
}
