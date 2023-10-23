#include <stdio.h>

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

int main() {
    int n = 3;
    
    sucessor_nr(n);
    printf("\n\n");
    sucessor_r(n);
    return 0;
}
