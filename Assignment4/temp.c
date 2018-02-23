#include <stdio.h>
#include <stdlib.h>

int main()
{
	float *a;
	a=(float*)malloc(10*sizeof(float));
	for(int i=0;i<10;i++)
	{
		a[i]=1;
	}
	for(int i=0;i<10;i++)
	{
		printf("%f ",a[i]);
	}
	
	return 0;
}