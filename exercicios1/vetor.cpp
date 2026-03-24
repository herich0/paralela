#include <stdio.h>
#include <omp.h>
#define tamanho 80 
#define max_threads 32

int main(){
    int a[tamanho], resultado=0, resultado_local[max_threads]= {0}, num_threads;
    for(int i=0; i<tamanho; i++){
        a[i] = i+1;
    }
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        num_threads = omp_get_num_threads();
        int resultado_temp =0;
        
        int workload = (tamanho + num_threads - 1) / num_threads; 
        int start = id * workload;
        int end = start + workload;

        for(int i=start; i<end && i<tamanho; i++){
            resultado_local[id] += a[i];
        }
    }
    for (int i=0; i<num_threads; i++){
        resultado += resultado_local[i];
    }
    printf("Resultado: %d\n", resultado);
    return 0;
}
