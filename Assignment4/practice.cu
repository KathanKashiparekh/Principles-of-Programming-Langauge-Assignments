#include <stdio.h>
#include <stdlib.h>

__global__ void blur_kernel(int *A,int r,int c)
{
	int row=blockIdx.x*blockDim.x + threadIdx.x
	int col=blockIdx.y*blockDim*y + threadIdx.y

	if(row<r&&col<c)
	{
		A[row*c+col]*=5;
	}
}

int main()
{
	int dimx=5;
	int dimy=4;

	int *A,*res;
	A=(int*)malloc(sizeof(int)*dimx*dimy);
	res=(int*)malloc(sizeof(int)*dimx*dimy);

	for(int i=0;i<5;i++)
	{
		for(int j=0;j<4;j++)
		{
			A[i*4+j]=1;
		}
	}

	int *d_a;
	cudaMalloc((void**)&d_a,sizeof(int)*dimx*dimy);

	cudaMemcpy(d_a,A,sizeof(int)*dimx*dimy,cudaMemcpyHostToDevice);

	dim3 gridDim(3,2);
	dim3 blockDim(2,2);

	blur_kernel<<<gridDim,blockDim>>>(d_a,dimx,dimy);

	cudaMemcpy(res,d_a,sizeof(int)*dimx*dimy,cudaMemcpyDeviceToHost);

	for(int i=0;i<5;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%d ",res[i*4+j]);
		}
		printf("\n");
	}
	printf("\n");
	free(A);
	free(res);
	cudaFree(d_a);

	return 0;
}