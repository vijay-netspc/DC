#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 
#define N 3 // Matrix size (NxN) 
int main() 
{ 
int i, j, k; 
int A[N][N], B[N][N], C[N][N]; 
int global_count = 0; 
printf("Matrix size: %d x %d\n", N, N); 
printf("\nInitializing matrices...\n"); 
for(i = 0; i < N; i++) 
for(j = 0; j < N; j++) 
{ 
A[i][j] = i + j; 
B[i][j] = i * j; 
C[i][j] = 0; 
} 
omp_set_dynamic(0); 
omp_set_num_threads(4); 
printf("\nMaximum threads available: %d\n", omp_get_max_threads()); 
#pragma omp parallel private(i,j,k) shared(A,B,C) reduction(+:global_count) 
{ 
int tid = omp_get_thread_num(); 
#pragma omp single 
printf("\nTotal threads working: %d\n", omp_get_num_threads()); 
#pragma omp for schedule(dynamic) 
for(i = 0; i < N; i++) 
{ 
for(j = 0; j < N; j++) 
{ 
for(k = 0; k < N; k++) 
{ 
C[i][j] += A[i][k] * B[k][j]; 
global_count++; 
} 
} 
printf("Thread %d completed row %d\n", tid, i); 
} 
} 
printf("\nResult Matrix C:\n"); 
for(i = 0; i < N; i++) 
{ 
for(j = 0; j < N; j++) 
printf("%4d ", C[i][j]); 
printf("\n"); 
} 
printf("\nTotal multiplication operations = %d\n", global_count); 
return 0; 
}  
 
###################
#gcc openmp.c -o openmp -fopenmp
