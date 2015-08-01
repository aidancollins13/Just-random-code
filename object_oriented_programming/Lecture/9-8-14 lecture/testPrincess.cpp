#include <iostream>
#include <string>
#include <vector> 
#include <cstdlib>
using namespace std;

void addOne(int someInt)
{
	++someInt;
}

int addOneFunctional(int someInt)
{
	++someInt;
	return someInt;
}

void addOneRef(int& someInt)   //someInt is an alias on paramater instead of copy
{
	++someInt;
}

void printVector(const vector<int>& myVector) //cont makes it so the vector cnant
{
	for(size_t  i = 0; i< v.size() ; ++i)  // declare index as size_t instead of int
	{
		cout << myVector[i] << endl;
	}	
}

int main(){
	vector<int> v; //declares vector (array)
	cout << v.size() << endl;
	v.push_back(17); // stores 17 
	v.push_back(42);
	v.push_back(42);
	v.push_back(28); 
	cout << v[0] << endl;

	v[0] = 6;

	for(size_t  i = 0; i< v.size() ; ++i)  // declare index as size_t instead of int
	{
		cout << v[i] << endl;
	}

	for(int x : v) // use this to loop through a collection instead. more efficent 
	{
		cout << x << endl;
	}	

	v.pop_back(); // removes last item from vector
	v.clear();

	cout << "====================";
	int n = 0;
	addOne(n);
	cout << "n: " << n << endl;
	addOneFunctional(n);
	cout << "n: " << n << endl;
	addOneRef(n);
	cout << "n: " << n << endl;


}
