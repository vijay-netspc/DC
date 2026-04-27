/* matrix_server.c */

#include "matrix.h"

output *multiply_1_svc(input *in, struct svc_req *req)
{
	static output out;
	int i,j,k;

	for(i=0;i<in->r1;i++)
	{
		for(j=0;j<in->c2;j++)
		{
			out.c[i][j]=0;

			for(k=0;k<in->c1;k++)
			{
				out.c[i][j] =
				out.c[i][j] +
				in->a[i][k] * in->b[k][j];
			}
		}
	}

	return &out;
}
