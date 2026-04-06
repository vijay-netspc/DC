#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h> 
#define N 8   
void api_init(int *argc, char ***argv, int *rank, int *size) { 
 MPI_Init(argc, argv); 
 MPI_Comm_rank(MPI_COMM_WORLD, rank); 
 MPI_Comm_size(MPI_COMM_WORLD, size); 
} 
int api_distributed_sum(int *data, int n) { 
 int rank, size; 
 MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
 MPI_Comm_size(MPI_COMM_WORLD, &size); 
 int local_value = 0; 
 int result = 0; 
 MPI_Scatter(data, 1, MPI_INT, 
             &local_value, 1, MPI_INT, 
             0, MPI_COMM_WORLD); 
 
 printf("[Rank %d] Received %d\n", rank, local_value); 
 
 MPI_Reduce(&local_value, &result, 1, 
            MPI_INT, MPI_SUM, 
            0, MPI_COMM_WORLD); 
 return result; 
} 
int api_distributed_max(int *data, int n) { 
 int rank; 
 MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
 
 int local_value = 0; 
 int result = 0; 
 
 MPI_Scatter(data, 1, MPI_INT, 
             &local_value, 1, MPI_INT, 
             0, MPI_COMM_WORLD); 
 
 MPI_Reduce(&local_value, &result, 1, 
            MPI_INT, MPI_MAX, 
            0, MPI_COMM_WORLD); 
 
 return result; | 
void api_finalize() { 
 MPI_Finalize(); 
} 
int main(int argc, char *argv[]) { 
 
 int rank, size; 
 int data[N] = {10, 20, 30, 40, 50, 60, 70, 80}; 
 
 api_init(&argc, &argv, &rank, &size); 
 
 if (size > N) { 
     if (rank == 0) 
         printf("Number of processes must be <= %d\n", N); 
     api_finalize(); 
     return 0; 
 } 
 int sum = api_distributed_sum(data, N); 
 if (rank == 0) 
     printf("\nDistributed SUM = %d\n", sum); 
 int max = api_distributed_max(data, N); 
 if (rank == 0) 
     printf("Distributed MAX = %d\n", max); 
 api_finalize(); 
 return 0; 
}
