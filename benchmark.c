/*
Benchmark developed by Sinan Alkaya
using OpenMP written in C
*/
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int maxInt = 2147483647;
clock_t begin, end;
int data[199];
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
    return (double)(end-begin) / CLOCKS_PER_SEC;
}

double init_array(){
    //fill array with random Data
    srand(time(NULL));
    for(int i=0; i< sizeof(data); i++){
        int r = rand();
        data[i] = r;
    }

}

double sortArray(){
    
    int i,j,tmp;
    /*
    printf("\nArray before Sort:\n");
    for(int x=0; x<sizeof(data); x++){
        printf("%d,",data[x]);
    }
    */
    clock_t end, begin;
    begin = clock();
    for(i=1;i<sizeof(data);i++)
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
    //useless: double delta = (double)(end-begin) / CLOCKS_PER_SEC;
    //printf("\nArray after Sort:\n");
    /*
    for(int x=0; x<sizeof(data); x++){
        printf("%d,",data[x]);
    }
    */
    return (double)(end-begin) / CLOCKS_PER_SEC;
}

int main(){
    printf("-----Welcome to Turbo-Guacamole-----\n");
    printf("Initializing...\n");
    init_array();
    printf("Initialization completed");
    printf("\n--------------------------------\ntesting Integer Performance Sequentially");
    double value = integer();
    printf("\ntook %f seconds\n", value);

    printf("\n--------------------------------\ntesting Integer Performance Parallel");
    double value_p = integer_parallel();
    printf("\ntook %f seconds\n",value_p);

    printf("\n--------------------------------\ntesting Sort performance using Bubblesort");
    double delta_arr_proced = sortArray();
    printf("\ntook %f seconds\n",delta_arr_proced);
    printf("\n------------DONE------------\n");
    return 0;
}

