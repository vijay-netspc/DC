#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
int main(int argc,char *argv[]){
int rank,size;
int local,sum;
int res[4],sq;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);

int data[4]={1,2,3,4};
MPI_Scatter(data,1,MPI_INT,&local,1,MPI_INT,0,MPI_COMM_WORLD);
sq=local*local;
MPI_Reduce(&local,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

MPI_Gather(&sq,1,MPI_INT,res,1,MPI_INT,0,MPI_COMM_WORLD);

if(rank==0){
printf("%d\n",sum);
for(int i=0;i<4;i++)
        printf("%d\n",res[i]);
}

MPI_Finalize();
}
