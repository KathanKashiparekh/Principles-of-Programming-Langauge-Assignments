#include <stdio.h>
#include <stdlib.h>
#include <time.h>

__global__ void blur_kernel(float *image,float *filter,float *blurred,int r,int c,float filter_sum)
{
        int row=blockIdx.x*blockDim.x + threadIdx.x;
        int col=blockIdx.y*blockDim.y + threadIdx.y;
        int above=row-1;
        int below=row+1;
        int left=col-1;
        int right=col+1;
        int total_sum=0;

        // Checking conditions for each pixel value
        if(0<=above&&above<r){
                if(0<=left&&left<c)
                        total_sum+=(image[above*c+left]*filter[0*3+0]);
                if(0<=col&&col<c)
                        total_sum+=(image[above*c+col]*filter[0*3+1]);
                if(0<=right&&right<c)
                        total_sum+=(image[above*c+right]*filter[0*3+2]);
        }

        if(0<=row&&row<r){
                if(0<=left&&left<c)
                        total_sum+=(image[row*c+left]*filter[1*3+0]);
                if(0<=col&&col<c)
                        total_sum+=(image[row*c+col]*filter[1*3+1]);
                if(0<=right&&right<c)
                        total_sum+=(image[row*c+right]*filter[1*3+2]);
        }

        if(0<=below&&below<r){
                if(0<=left&&left<c)
                        total_sum+=(image[below*c+left]*filter[2*3+0]);
                if(0<=col&&col<c)
                        total_sum+=(image[below*c+col]*filter[2*3+1]);
                if(0<=right&&right<c)
                        total_sum+=(image[below*c+right]*filter[2*3+2]);
        }
        if((0<=row&&row<r)&&(0<=col&&col<c))
                blurred[row*c+col]=total_sum/filter_sum;
}

int main()
{
        srand(time(NULL));

        // Image of size 1000*768
        int dimx=1000;
        int dimy=768;

        // Device variables and memory allocation
        float *image,*filter,*blurred;
        image=(float*)malloc(sizeof(float)*dimx*dimy);
        filter=(float*)malloc(sizeof(float)*3*3);
        blurred=(float*)malloc(sizeof(float)*dimx*dimy);

        // Assigning fixed values to the filter matrix
        filter[0*3+0]=1; filter[0*3+1]=2; filter[0*3+2]=1;
        filter[1*3+0]=2; filter[1*3+1]=3; filter[1*3+2]=2;
        filter[2*3+0]=1; filter[2*3+1]=2; filter[2*3+2]=1;

        // Assigning random values between 0 and 255 to the image matrix
        for(int i=0;i<dimx;i++)
        {
                for(int j=0;j<dimy;j++)
                {
                        image[i*dimy+j]=rand()%256;
                }
        }

        // Device variables and memory allocation
        float *d_image,*d_filter,*d_blurred;
        cudaMalloc((void**)&d_image,sizeof(float)*dimx*dimy);
        cudaMalloc((void**)&d_filter,sizeof(float)*3*3);
        cudaMalloc((void**)&d_blurred,sizeof(float)*dimx*dimy);

        // Copying the image and filter matrix to device memory
        cudaMemcpy(d_image,image,sizeof(float)*dimx*dimy,cudaMemcpyHostToDevice);
        cudaMemcpy(d_filter,filter,sizeof(float)*3*3,cudaMemcpyHostToDevice);

        // Grid and block dimensions
        dim3 gridDim(63,48);
        dim3 blockDim(16,16,1);

        // Calling the kernel
        blur_kernel<<<gridDim,blockDim>>>(d_image,d_filter,d_blurred,dimx,dimy,15.0);

        // Copying the blurred image from device to host
        cudaMemcpy(blurred,d_blurred,sizeof(float)*dimx*dimy,cudaMemcpyDeviceToHost);

        // Printing original image
        printf("Original Image\n");
        for(int i=0;i<dimx;i++)
        {
                for(int j=0;j<dimy;j++)
                {
                        printf("%f ",image[i*dimy+j]);
                }
                printf("\n");
        }

        // Printing blurred image
        printf("\n\nBlurred Image\n");
        for(int i=0;i<dimx;i++)
        {
                for(int j=0;j<dimy;j++)
                {
                        printf("%f ",blurred[i*dimy+j]);
                }
                printf("\n");
        }

        // Freeing up memory
        free(image);
        free(filter);
        free(blurred);
        cudaFree(d_image);
        cudaFree(d_filter);
        cudaFree(d_blurred);

        return 0;
}                                                                                                                       