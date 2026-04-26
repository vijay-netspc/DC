#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
int rank,size;
int local,sum,max;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

int data[]={40,30,50,10};

MPI_Scatter(data,1,MPI_INT,&local,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Reduce(&local,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
MPI_Reduce(&local,&max,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);
if(rank==0)
        printf("sum: %d max %d\n",sum,max);
MPI_Finalize();
}
