#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>

int main() {
    int n = 1000;
    bool primo[1001];
    
    memset(primo, true, sizeof(primo));

    for (int p = 2; p * p <= n; p++) {
        if (primo[p]) {
            #pragma omp parallel for schedule(dynamic)
            for (int i = p * p; i <= n; i += p) {
                primo[i] = false;
            }
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