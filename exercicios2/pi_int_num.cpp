#include <stdio.h>
#include <omp.h>

int main() {
    int num_pontos = 100000;
    double passo = 1.0 / num_pontos;
    double pi = 0.0;
    double x;

    #pragma omp parallel for private(x) reduction(+:pi)
    for (int i = 0; i < num_pontos; i++) {
        x = (i + 0.5) * passo;
        pi += 4.0 / (1.0 + x * x);
    }

    pi *= passo;
    
    printf("Valor de Pi calculado: %.10f\n", pi);

    return 0;
}