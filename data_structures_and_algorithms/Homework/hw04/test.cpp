//Aidan Collins
// 3/11/15
//Homework 4
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <stdlib.h>
#include <math.h>
#include <functional>
#include <limits>

using namespace std;
//Question 1
template<class Object>
void printVec(vector<Object> a){
	for(int i = 0; i < a.size(); ++i){
		cout<<a[i];
	}
	cout <<endl;
}
void quickSort( vector<int> & a, int low, int high )
{
if (low < high)
{
int mid = ( low + high )/2; // select pivot to be element in middle position
int pivot = a[ mid ];
swap( a[high], a[mid] ); // put pivot in a[high]
// Begin partitioning
int i, j;
for( i = low, j = high - 1; ; )
{
while ( a[i ] < pivot ) ++i;
while( j > i && pivot < a[j ] ) --j;
if( i < j )
swap( a[ i++ ], a[ j-- ] );
else
break;
}
swap( a[ i ], a[ high ] ); // Restore pivot
printVec(a); // prints the contents of the vector in order
quickSort( a, low, i - 1 ); // Sort small elements
quickSort( a, i + 1, high ); // Sort large elements
}
}


template <class Comparable>
void mergeSort( vector<Comparable> & a,
vector<Comparable> & tmpArray, int left, int right )
{
if( left < right )
{
int center = ( left + right ) / 2;
mergeSort( a, tmpArray, left, center );
mergeSort( a, tmpArray, center + 1, right );
merge( a, tmpArray, left, center + 1, right );
printVec(a); // prints the contents of the vector in order
}
}

int main(){
vector<int> a(6);
a[0] = 9;
a[1] = 8;
a[2] = -11;
a[3] = 2;
a[4] = 0;
a[5] = 3;
vector<int> temp(6);
quickSort(a,0,6);
}
