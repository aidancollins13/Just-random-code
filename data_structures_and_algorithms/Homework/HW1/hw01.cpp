//Aidan Collins -- Feb 4  -- Professor Sellie
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <class Object>  // Template for a function that takes a vector and returns true if the vector has a duplicate
bool hasDublicate(vector<Object> v){
	for (size_t i = 0; i < v.size(); i++){
		for (size_t j = 0; j < v.size(); j++){
			if (v[i] == v[j]) return true;
		}
		return false;
	}
}

class Node

{

public: // These member variables are made public to simplify your coding.

Node( char ch, Node * ptr = NULL):data(ch),next(ptr){}

char data;

Node * next;

};

// timer class
class timer {
public:
    timer() : start(clock()) {}
    double elapsed() { return ( clock() - start ) / CLOCKS_PER_SEC; }
    void reset() { start = clock(); }
private:
    double start;
};


// Linear maximum contiguous subsequence sum algorithm.
// Comparable: must have constructor from int, must have
//     += and > defined, must have copy constructor
//     and operator=, and must have all properties
//     needed for vector.
// seqStart and seqEnd represent the actual best sequence.
template <class Comparable>
Comparable maxSubsequenceSum4( const vector<Comparable> & a, int  seqStart, int  seqEnd )
{
    int n = a.size( );
    Comparable thisSum = 0;
    Comparable maxSum = 0;
	
    for( int i = 0, j = 0; j < n; j++ )
    {
        thisSum += a[ j ];
		
        if( thisSum > maxSum )
        {
            maxSum = thisSum;
            seqStart = i;
            seqEnd = j;
        }
        else if( thisSum < 0 )
        {
            i = j + 1;
            thisSum = 0;
        }
    }
    return maxSum;
}



// Quadratic maximum contiguous subsequence sum algorithm.
// Comparable: must have constructor from int, must have
//     += and > defined, must have copy constructor
//     and operator=, and must have all properties
//     needed for vector.
// seqStart and seqEnd represent the actual best sequence.
template <class Comparable>
Comparable maxSubsequenceSum2( const vector<Comparable> & a,int  seqStart, int  seqEnd )
{
    int n = a.size( );
    Comparable maxSum = 0;
	
    for( int i = 0; i < n; i++ )
    {
        Comparable thisSum = 0;
        for( int j = i; j < n; j++ )
        {
            thisSum += a[ j ];
			
            if( thisSum > maxSum )
            {
                maxSum = thisSum;
                seqStart = i;
                seqEnd = j;
            }
        }
    }
	
    return maxSum;
}



// Cubic maximum contiguous subsequence sum algorithm.
// Comparable: must have constructor from int, must have
//     += and > defined, must have copy constructor
//     and operator=, and must have all properties
//     needed for vector.
// seqStart and seqEnd represent the actual best sequence.
template <class Comparable>
Comparable maxSubsequenceSum1( const vector<Comparable> & a, int  seqStart, int  seqEnd )
{
    int n = a.size( );
    Comparable maxSum = 0;
	
    for( int i = 0; i < n; i++ )
        for( int j = i; j < n; j++ )
        {
            Comparable thisSum = 0;
            for( int k = i; k <= j; k++ )
                thisSum += a[ k ];
			
            if( thisSum > maxSum )
            {
                maxSum = thisSum;
                seqStart = i;
                seqEnd = j;
            }
        }
	
    return maxSum;
}

int main(){
	Node * nodePtr;
	Node * cPtr = new Node('C');
	cPtr->next = new Node('B', new Node('D'));
	nodePtr = new Node('A',cPtr);
	
	Node * p = nodePtr;
	while(p){
		cout << p->data << " : " << p << endl;
		p = p->next;
	}
	cout << "nodePtr : " << nodePtr << endl;

	delete nodePtr;
	nodePtr = cPtr;

//-------------------------------------------------------------------
cout << endl << "===============\n\n";
int * intPtr = new int[5];

*intPtr = 2;
*(intPtr+1) = 3;
*(intPtr+2) = 4;
*(intPtr+3) = 5;

// for(int i = 0; i < 5; ++i){
// 	cout << intPtr[i] << endl;
// }
*(intPtr+4) = *(intPtr+3);
*(intPtr+3) = *(intPtr+2);
*(intPtr+2) = *(intPtr+1);
*(intPtr+1) = *(intPtr);
*intPtr = 1;

for(int i = 0; i < 5; ++i){
	cout << intPtr[i] << " : " << intPtr+i << endl;
}

delete intPtr;

cout << endl << "===============\n\n";

timer t;
double nuClicks;

vector<int> v (4096);
for(int i = 0 ; i< v.size(); ++i){
	v[i] = (rand() % 2001) -1000;
}
t.reset();
maxSubsequenceSum2(v,0,v.size());
nuClicks = t.elapsed();
cout << "MSS1 : " << nuClicks << endl;
}