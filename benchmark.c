/*
Benchmark developed by Sinan Alkaya
using OpenMP written in C
last change: allowing larger arraytypes through malloc
*/
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define arrValue 300000000
int maxInt = 2147483647;
clock_t begin, end;

int *data = NULL;


double integer(){
    begin = clock();
    int valuetest = 0;
    for(int i = 0; i < maxInt; i++){
        valuetest++;
    }
    end = clock();
    return (double)(end-begin) / CLOCKS_PER_SEC;
}

double integer_parallel(){
    begin = clock();
    int value = 0;
    #pragma omp parallel
    #pragma omp for //private(maxIntm i) reduction(+:value)
    for(int i = 0; i < maxInt; i++){
        value++;
    }
    end = clock();
    maxInt = 0;
    return (double)(end-begin) / CLOCKS_PER_SEC;
}

double init_array(){
    //fill array with random Data
    data = (int *)malloc(arrValue * sizeof(int));
    srand(time(NULL));
    for(int i=0; i< arrValue; i++){
        int r = rand();
        data[i] = r;
    }

}

double sortArray(){
    init_array();
    int i,j,tmp;
    begin = clock();
    for(i=1;i<arrValue;i++)
    {
        for(j=0;j<sizeof(data)-1;j++){
            if(data[j] > data[j+1]){
                tmp = data[j];
                data[j] = data[j+1];
                data[j+1] = tmp;
            }
        }
    }
    end = clock();
    return (double)(end-begin) / CLOCKS_PER_SEC;
}

double sortArray_parallel(){
    //Renew array:
    init_array();
    int i,j,tmp;
    begin = clock();
    #pragma omp parallel shared(tmp) private(i,j)
    {
        #pragma omp for
        for(i=1;i<arrValue;i++)
        {
            for(j=0;j<sizeof(data)-1;j++){
                if(data[j] > data[j+1]){
                    tmp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = tmp;
                }
            }
        }
    }
    end = clock();
    return (double)(end-begin) / CLOCKS_PER_SEC;
}

int main(){
    

    printf("-----Welcome to Turbo-Guacamole-----\n");
    printf("Initializing...\n");
    
    printf("Initialization completed");
    printf("\n--------------------------------\ntesting Integer performance sequentially");
    double value = integer();
    printf("\ntook %f seconds\n", value);

    printf("\n--------------------------------\ntesting Integer performance parallel");
    double value_p = integer_parallel();
    printf("\ntook %f seconds\n",value_p);

    printf("\n--------------------------------\ntesting Sort performance using Bubblesort sequentially");
    double delta_arr_proced = sortArray();
    printf("\ntook %f seconds\n",delta_arr_proced);

    printf("\n--------------------------------\ntesting Sort performance using Bubblesort parallel");
    double delta_arr_paral = sortArray_parallel();
    printf("\ntook %f seconds\n",delta_arr_paral);
    printf("\n------------DONE------------\n");

    //FREE MALLOCS
    free(data);
    return 0;
}

