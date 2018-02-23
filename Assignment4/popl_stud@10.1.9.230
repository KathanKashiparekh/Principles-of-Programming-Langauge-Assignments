#include <stdio.h>

__global__ void vecAdd(float *A,float *B,float *C,int n)
{
	int i=blockIdx.x*blockDim.x + threadIdx.x;
	if(i<n)
	{
		C[i]=A[i]+B[i];
	}
}

int main()
{
	int dim=13;
	int dim*sizeof(float)=dim*sizeof(float);
	
	float *h_a=(float*)malloc(dim*sizeof(float));
	float *h_b=(float*)malloc(dim*sizeof(float));
	float *h_c=(float*)malloc(dim*sizeof(float));

	float *d_a,*d_b,*d_c;

	for(int i=0;i<dim;i++)
	{
		h_a[i]=1;
		h_b[i]=2;
	}


	cudaMalloc((void**)&d_a,dim*sizeof(float));
	cudaMalloc((void**)&d_b,dim*sizeof(float));
	cudaMalloc((void**)&d_c,dim*sizeof(float));

	dim3 dimGrid(4,1);
	dim3 dimBlock(4,1,1);

	cudaMemcpy(d_a,h_a,dim*sizeof(float),cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,h_b,dim*sizeof(float),cudaMemcpyHostToDevice);

	vecAdd<<<dimGrid,dimBlock>>>(d_a,d_b,d_c,dim);

	cudaMemcpy(h_c,d_c,dim*sizeof(float),cudaMemcpyDeviceToHost);

	for(int i=0;i<dim;i++)
	{
		printf("%d ",h_c[i]);
	}
	printf("\n");
	free(h_a);
	free(h_b);
	free(h_c);
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);

	return 0;
}