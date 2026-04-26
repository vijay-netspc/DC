#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
int size,rank;
int local,sum;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);
int data[]={10,20,30,40};
MPI_Scatter(data,1,MPI_INT,&local,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Reduce(&local,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

if(rank==0)
        printf("Sum:%d",sum);
MPI_Finalize();

}
