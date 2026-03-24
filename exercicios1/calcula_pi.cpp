#include <stdio.h>
#include <omp.h>

#define num_pontos 100000
#define max_threads 32

int main() {
    double resultado_local[max_threads] = {0.0};
    double passo = 1.0 / (double)num_pontos;
    double pi = 0.0;
    int num_threads_exec;

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int n_threads = omp_get_num_threads();
        
        if (id == 0) {
            num_threads_exec = n_threads;
        }

        int workload = (num_pontos + n_threads - 1) / n_threads;
        int start = id * workload;
        int end = start + workload;

        double x;
        double soma_local = 0.0;

        for(int i = start; i < end && i < num_pontos; i++) {
            x = (i + 0.5) * passo;
            soma_local += 4.0 / (1.0 + x * x);
        }

        resultado_local[id] = soma_local;
    }

    for (int i = 0; i < num_threads_exec; i++) {
        pi += resultado_local[i];
    }
    
    pi = pi * passo;

    printf("Valor de Pi calculado: %.10f\n", pi);

    return 0;
}