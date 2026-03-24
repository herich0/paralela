#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>
#include <math.h>

int main() {
    int n = 1000;
    bool primo[1001];
    memset(primo, true, sizeof(primo));

    int limite = (int)sqrt(n);

    for (int p = 2; p * p <= limite; p++) {
        if (primo[p]) {
            for (int i = p * p; i <= limite; i += p) {
                primo[i] = false;
            }
        }
    }

    int primos_base[limite + 1];
    int cont_base = 0;
    for (int p = 2; p <= limite; p++) {
        if (primo[p]) {
            primos_base[cont_base] = p;
            cont_base++;
        }
    }

    #pragma omp parallel for schedule(dynamic)
    for (int k = 0; k < cont_base; k++) {
        int p = primos_base[k];
        for (int i = p * p; i <= n; i += p) {
            primo[i] = false;
        }
    }

    printf("Numeros primos ate %d:\n", n);
    for (int p = 2; p <= n; p++) {
        if (primo[p]) {
            printf("%d ", p);
        }
    }
    printf("\n");

    return 0;
}