
/*

PoPL Assignment-3

Saurabh Shekher
2014B3A70621G

*/


#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

template <int A, int B>
struct get_power
{
    static const int value = A * get_power<A, B - 1>::value;
};

template <int A>
struct get_power<A, 0>
{
    static const int value = 1;
};

template<int N>
struct Loop{
	public:
		static inline void copy(int a[], int b[], int i){
			b[i] = a[i];
			Loop<N-1>::copy(a,b,i-1);
		}
};

template<>
struct Loop<1>{
	public:
		static inline void copy(int a[], int b[], int i){
			b[i] = a[i];
			//cout << "Copy " << a[i] << endl; 
		}
};

template<int unrollParameter>
struct Unroll{
    public:
    	// This loop does the time analysis and has to be called for processing.
		static inline void copy(int a[], int b[], int aSize){	

			clock_t begin=clock();
			int index_var=aSize;
			for( int i = aSize; i >= unrollParameter; i-=unrollParameter ){
				//cout << i << " ";
				Loop<unrollParameter>::copy(a,b,i-1);
				index_var = i;
			}
			
			if(aSize % unrollParameter != 0)
			{
			for (int i = index_var; i > 0; i--)
	    		Loop<1>::copy(a,b,i-1);
			}
			clock_t end=clock();
			double time_spent= (double) (end-begin)/CLOCKS_PER_SEC*1000;

			cout << "Unrolling Factor : " << unrollParameter << " Execution time =  " << time_spent << endl;
		}
};

template<int k>
struct Loop_copy{
	public:
		static inline void loop_over_copy(int a[], int b[], int aSize){
			Unroll< get_power<2, k>::value >::copy(a,b,aSize);
			Loop_copy<k+1>::loop_over_copy(a,b,aSize);
		}
};

template<>
struct Loop_copy<10>{
	public:
		static inline void loop_over_copy(int a[], int b[], int aSize){
			Unroll<1024>::copy(a,b,aSize);
			for (int i = 0; i < aSize; i++) {
				cout << b[i] << " ";
			}
	}
};

int main(){

	int aSize = 1000;
	int a[aSize], b[aSize];
	for(int i=0;i<aSize;i++)
	    a[i]=i;

	Unroll<256>::copy(a,b,aSize);

	Loop_copy<0>::loop_over_copy(a,b,aSize);

}
