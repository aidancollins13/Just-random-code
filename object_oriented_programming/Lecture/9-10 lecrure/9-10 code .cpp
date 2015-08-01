#include <iostream>
#include <string>
#include <vector> 
#include <cstdlib>
#include <fstream>
using namespace std;

void myRecFunc(int n)
{
cout << n << ": ";
if (n < 1) return;
myRecFunc(n/2);
myRecFunc(n/2);
for (int i = 1; i < n; ++i)
cout << "*";
cout << endl;
}

int main(){
	myRecFunc(4);
	cout << endl;
}