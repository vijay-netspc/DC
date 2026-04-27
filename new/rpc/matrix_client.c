/* matrix_client.c */

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	CLIENT *c1;
	input in;
	output *out;
	int i,j;

	c1 = clnt_create(argv[1], MATRIX_PROG, MATRIX_VERS, "tcp");

	printf("Enter rows and cols of Matrix A : ");
	scanf("%d%d",&in.r1,&in.c1);

	printf("Enter rows and cols of Matrix B : ");
	scanf("%d%d",&in.r2,&in.c2);

	if(in.c1 != in.r2)
	{
		printf("Multiplication not possible\n");
		return 0;
	}

	printf("Enter Matrix A elements:\n");
	for(i=0;i<in.r1;i++)
	{
		for(j=0;j<in.c1;j++)
		{
			scanf("%d",&in.a[i][j]);
		}
	}

	printf("Enter Matrix B elements:\n");
	for(i=0;i<in.r2;i++)
	{
		for(j=0;j<in.c2;j++)
		{
			scanf("%d",&in.b[i][j]);
		}
	}

	out = multiply_1(&in,c1);

	printf("Result Matrix:\n");

	for(i=0;i<in.r1;i++)
	{
		for(j=0;j<in.c2;j++)
		{
			printf("%d ",out->c[i][j]);
		}
		printf("\n");
	}

	clnt_destroy(c1);
	return 0;
}
