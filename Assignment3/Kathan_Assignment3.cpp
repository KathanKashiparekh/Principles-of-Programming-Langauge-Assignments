#include <bits/stdc++.h>
#include <ctime>
#include <cmath>
using namespace std;

/* PoPl Assignment 3 : Kathan Kashiparekh : 2014B3A70792G */
/* Assumption: Array size is perfectly divisible by the unroll parameter */

// Template to get the powers
template<int base,int p>
struct powers{
	static const int value=base*powers<base,p-1>::value;
};

// Base case for powers template
template<int base>
struct powers<base,0>{
	static const int value=1;
};

// Looping
template<int N>
class Copy{
public:
	static inline void copy(int a[],int b[],int i){
		b[i]=a[i];
		Copy<N-1>::copy(a,b,i+1);
	}
};

// Base case for looping
template<>
class Copy<1>{
public:
	static inline void copy(int a[],int b[],int i){
		b[i]=a[i];
	}
};

// Main unroll function for a given unroll parameter
template<int  unrollParam>
class Unroll{
public:
	static inline void copyArray(int a[],int b[],int size){
		int lastElement;
		int start=clock();
		int i;
		for( i = 0; (i+unrollParam)<= size; i+=unrollParam ){
			Copy<unrollParam>::copy(a,b,i);	
			lastElement = i;
		}
		// If size is not perfectly divisible by unroll factor,copy the remaining elements as they are.
		if(i<size){
			for(int j=i;j<size;j++){
				Copy<1>::copy(a,b,j);
			}
		}
		// cout << "\nDestination array elements: ";
		// for( int i = 0; i < size; i++){
		// 	cout << b[i] << " ";
		// }
		int stop=clock();
		cout << "Unrolling Factor : " << unrollParam << " Execution time =  " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;
	}
};

template<int i>
class newLoop{
public:
	static inline void loop_over_copy(int a[],int b[],int size){
		// Unroll<1>::copyArray(a,b,size);
		// Unroll<2>::copyArray(a,b,size);
		// Unroll<4>::copyArray(a,b,size);
		// Unroll<8>::copyArray(a,b,size);
		// Unroll<16>::copyArray(a,b,size);
		// Unroll<32>::copyArray(a,b,size);
		// Unroll<64>::copyArray(a,b,size);
		// Unroll<128>::copyArray(a,b,size);
		// Unroll<256>::copyArray(a,b,size);
		// Unroll<512>::copyArray(a,b,size);
		// Unroll<1024>::copyArray(a,b,size);
		Unroll<powers<2,i>::value>::copyArray(a,b,size);
		newLoop<i+1>::loop_over_copy(a,b,size);
	}
};

template<>
class newLoop<10>{
public:
	static inline void loop_over_copy(int a[],int b[],int size){
		Unroll<1024>::copyArray(a,b,size);
	}
};

int main()
{
	int size;
	cout<<"Enter size of array: ";
	cin>>size;
	int a[size],b[size];
	for(int i=0;i<size;i++){
		a[i]=i;
	}
	newLoop<0>::loop_over_copy(a,b,size);
	// Unroll<2>::copyArray(a,b,size);
	return 0;
}