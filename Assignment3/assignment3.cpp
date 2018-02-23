/*

@Author : Ashutosh Upreti
ID  	: 2014B4A70784G

*/

#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

template<int N>
class Loop{
	public:
		static inline void copy(int a[], int b[], int i){
			b[i] = a[i];
			Loop<N-1>::copy(a,b,i+1);
		}
};

template<>
class Loop<1>{
	public:
		static inline void copy(int a[], int b[], int i){
			b[i] = a[i];
		}
};

template<int unrollingFactor>
class Unroll{
    public:
    	// unrollingFactor is passed as a template to this function
		static inline void copy(int a[], int b[], int arraySize){	

			int start_s=clock();
			int lastDivisibleElement;
			for( int i = 0; i < arraySize; i+=unrollingFactor ){
				Loop<unrollingFactor>::copy(a,b,i);	
				lastDivisibleElement = i;
			}
			// If arraySize is not perfectly divisible by unrollingFactor ---> Copy the remaining elements too.
			// if(unrollingFactor % arraySize != 0)
			// 	Loop<1>::copy(a,b,lastDivisibleElement+1);

			int stop_s=clock();
			cout << "Unrolling Factor : " << unrollingFactor << " Execution time =  " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
		}
};

template<int i>
class Loop_copy{
	public:
		static inline void loop_over_copy(int a[], int b[], int arraySize){
			Unroll<1>::copy(a,b,arraySize);
			Unroll<2>::copy(a,b,arraySize);
			Unroll<4>::copy(a,b,arraySize);
			Unroll<8>::copy(a,b,arraySize);
			Unroll<16>::copy(a,b,arraySize);
			Unroll<32>::copy(a,b,arraySize);
			Unroll<64>::copy(a,b,arraySize);
			Unroll<128>::copy(a,b,arraySize);
			Unroll<256>::copy(a,b,arraySize);
			Unroll<512>::copy(a,b,arraySize);
			Unroll<1024>::copy(a,b,arraySize);
			//Loop_copy<i+1>::loop_over_copy(a,b,arraySize);
		}
};


int main(){

	int arraySize;
	int a[100000], b[100000];

	cout << "Enter size of the source array : ";
	cin >> arraySize;
	cout << "\nEnter elements of the source array : ";
	for(int i = 0; i < arraySize; i++ ){
		cin >> a[i];
	}
	cout << endl;

	Loop_copy<0>::loop_over_copy(a,b,arraySize);



}
